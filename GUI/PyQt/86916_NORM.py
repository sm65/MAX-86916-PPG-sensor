import sys
import time
import serial
import struct
import numpy as np
import csv
import bisect
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QPushButton, QLabel, QTextEdit, QCheckBox, QComboBox, QFileDialog
from PyQt5.QtCore import QTimer
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
import serial.tools.list_ports
from scipy.signal import find_peaks

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("MAX86916 PPG Heart Monitor")
        self.setGeometry(100, 100, 800, 600)

        # Serial port variables
        self.serial_port = None
        self.is_reading = False
        self.data_buffer = {'RED': [], 'IR': [], 'GREEN': [], 'BLUE': [], 'Pulse': [], 'SpO2': [], 'Time': []}
        self.start_time = None

        # Biofeedback variables for 4-7-8 pattern
        self.biofeedback_active = False
        self.breathing_pattern = [("Inhale", 4), ("Hold", 7), ("Exhale", 8)]  # 4-7-8 pattern
        self.state_index = 0
        self.breathing_state = ""
        self.duration = 0
        self.countdown = 0
        self.biofeedback_timer = QTimer()
        self.biofeedback_timer.timeout.connect(self.biofeedback_timeout)

        # GUI components
        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)
        self.layout = QVBoxLayout(self.central_widget)

        # COM port selection
        self.port_combo = QComboBox()
        self.port_combo.setMinimumWidth(150)
        port_layout = QHBoxLayout()
        port_layout.addWidget(QLabel("COM Port:"))
        port_layout.addWidget(self.port_combo)
        refresh_button = QPushButton("Refresh Ports")
        refresh_button.clicked.connect(self.refresh_ports)
        port_layout.addWidget(refresh_button)
        port_layout.addStretch()
        self.layout.addLayout(port_layout)

        # Start/Stop/Save/Scan buttons
        self.start_button = QPushButton("Start Reading")
        self.start_button.clicked.connect(self.start_reading)
        self.stop_button = QPushButton("Stop Reading")
        self.stop_button.clicked.connect(self.stop_reading)
        self.stop_button.setEnabled(False)
        self.clear_button = QPushButton("Clear Data")
        self.clear_button.clicked.connect(self.clear_data)
        self.save_button = QPushButton("Save to CSV")
        self.save_button.clicked.connect(self.save_to_csv)
        self.biofeedback_button = QPushButton("Start Biofeedback")
        self.biofeedback_button.clicked.connect(self.toggle_biofeedback)
        self.scan_anomalies_button = QPushButton("Scan Anomalies")
        self.scan_anomalies_button.clicked.connect(self.scan_anomalies)
        self.scan_anomalies_button.setEnabled(False)  # Disabled until Stop Reading
        button_layout = QHBoxLayout()
        button_layout.addWidget(self.start_button)
        button_layout.addWidget(self.stop_button)
        button_layout.addWidget(self.clear_button)
        button_layout.addWidget(self.save_button)
        button_layout.addWidget(self.biofeedback_button)
        button_layout.addWidget(self.scan_anomalies_button)
        self.layout.addLayout(button_layout)

        # Checkboxes for selecting signals to plot
        self.checkbox_layout = QHBoxLayout()
        self.red_cb = QCheckBox("RED")
        self.red_cb.setStyleSheet("color: #FF0000")
        self.red_cb.setChecked(False)
        self.ir_cb = QCheckBox("IR")
        self.ir_cb.setStyleSheet("color: #8B0000")
        self.ir_cb.setChecked(True)
        self.green_cb = QCheckBox("GREEN")
        self.green_cb.setStyleSheet("color: #00FF00")
        self.green_cb.setChecked(False)
        self.blue_cb = QCheckBox("BLUE")
        self.blue_cb.setStyleSheet("color: #0000FF")
        self.blue_cb.setChecked(False)
        self.checkbox_layout.addWidget(self.red_cb)
        self.checkbox_layout.addWidget(self.ir_cb)
        self.checkbox_layout.addWidget(self.green_cb)
        self.checkbox_layout.addWidget(self.blue_cb)
        self.checkbox_layout.addStretch()
        self.layout.addLayout(self.checkbox_layout)

        # Status label
        self.status_label = QLabel("Status: Disconnected")
        self.layout.addWidget(self.status_label)

        # Heart Rate and SpO2 display
        self.hr_label = QLabel("Heart Rate: -- bpm")
        self.hr_label.setStyleSheet("font-size: 20px;")
        self.spo2_label = QLabel("SpO2: -- %")
        metrics_layout = QHBoxLayout()
        metrics_layout.addWidget(self.hr_label)
        metrics_layout.addWidget(self.spo2_label)
        self.layout.addLayout(metrics_layout)

        # Breathing guide label with countdown
        self.breathing_label = QLabel("")
        self.breathing_label.setStyleSheet("font-size: 18px;")
        self.layout.addWidget(self.breathing_label)

        # Data display
        self.data_display = QTextEdit()
        self.data_display.setReadOnly(True)
        self.layout.addWidget(self.data_display)

        # Matplotlib plot
        self.figure, self.ax = plt.subplots()
        self.canvas = FigureCanvas(self.figure)
        self.layout.addWidget(self.canvas)
        self.figure.patch.set_facecolor('white')
        self.ax.set_facecolor('white')
        self.ax.grid(True, which='major', linestyle='--', alpha=0.3)
        self.ax.tick_params(colors='black')
        self.ax.spines['top'].set_color('black')
        self.ax.spines['bottom'].set_color('black')
        self.ax.spines['left'].set_color('black')
        self.ax.spines['right'].set_color('black')
        self.ax.xaxis.set_major_locator(plt.MultipleLocator(1.0))

        # Timers
        self.read_timer = QTimer()
        self.read_timer.timeout.connect(self.read_serial_data)
        self.plot_timer = QTimer()
        self.plot_timer.timeout.connect(self.update_plot)

        # Initial port refresh
        self.refresh_ports()

    def refresh_ports(self):
        self.port_combo.clear()
        ports = [port.device for port in serial.tools.list_ports.comports()]
        if ports:
            self.port_combo.addItems(ports)
            self.start_button.setEnabled(True)
        else:
            self.port_combo.addItem("No ports found")
            self.start_button.setEnabled(False)

    def start_reading(self):
        selected_port = self.port_combo.currentText()
        if not selected_port or selected_port == "No ports found":
            self.status_label.setText("Error: No valid COM port selected")
            return
        try:
            self.serial_port = serial.Serial(selected_port, 115200, timeout=1)
            self.is_reading = True
            self.start_time = time.time()
            self.status_label.setText(f"Status: Connected to {selected_port}, reading data")
            self.start_button.setEnabled(False)
            self.stop_button.setEnabled(True)
            self.scan_anomalies_button.setEnabled(False)
            self.read_timer.start(50)
            self.plot_timer.start(100)
        except Exception as e:
            self.status_label.setText(f"Error: {str(e)}")
            self.data_display.append(f"Error opening port: {str(e)}")

    def stop_reading(self):
        if self.serial_port and self.serial_port.is_open:
            self.serial_port.close()
        self.is_reading = False
        self.start_time = None
        self.status_label.setText("Status: Disconnected")
        self.start_button.setEnabled(True)
        self.stop_button.setEnabled(False)
        self.scan_anomalies_button.setEnabled(True)
        self.read_timer.stop()
        self.plot_timer.stop()
        if self.biofeedback_active:
            self.toggle_biofeedback()

    def clear_data(self):
        self.data_buffer = {'RED': [], 'IR': [], 'GREEN': [], 'BLUE': [], 'Pulse': [], 'SpO2': [], 'Time': []}
        self.data_display.clear()
        self.hr_label.setText("Heart Rate: -- bpm")
        self.spo2_label.setText("SpO2: -- %")
        self.ax.clear()
        self.ax.set_facecolor('white')
        self.ax.grid(True, which='major', linestyle='--', alpha=0.3)
        self.ax.tick_params(colors='black')
        self.ax.spines['top'].set_color('black')
        self.ax.spines['bottom'].set_color('black')
        self.ax.spines['left'].set_color('black')
        self.ax.spines['right'].set_color('black')
        self.ax.xaxis.set_major_locator(plt.MultipleLocator(1.0))
        self.canvas.draw()
        if self.biofeedback_active:
            self.toggle_biofeedback()
        self.scan_anomalies_button.setEnabled(False)

    def save_to_csv(self):
        if not self.data_buffer['Time']:
            self.status_label.setText("Error: No data to save")
            return
        file_path, _ = QFileDialog.getSaveFileName(self, "Save CSV File", "", "CSV Files (*.csv)")
        if file_path:
            if not file_path.endswith('.csv'):
                file_path += '.csv'
            with open(file_path, 'w', newline='') as csvfile:
                writer = csv.writer(csvfile)
                writer.writerow(['Time (s)', 'RED', 'IR', 'GREEN', 'BLUE', 'Pulse (bpm)', 'SpO2 (%)'])
                for i in range(len(self.data_buffer['Time'])):
                    writer.writerow([
                        self.data_buffer['Time'][i],
                        self.data_buffer['RED'][i],
                        self.data_buffer['IR'][i],
                        self.data_buffer['GREEN'][i],
                        self.data_buffer['BLUE'][i],
                        self.data_buffer['Pulse'][i],
                        self.data_buffer['SpO2'][i]
                    ])
            self.status_label.setText(f"Data saved to {file_path}")

    def calculate_heart_rate(self):
        if len(self.data_buffer['IR']) < 20:
            return None
        ir_data = np.array(self.data_buffer['IR'][-200:])
        time_data = np.arange(len(ir_data)) * 0.05
        signal_range = np.max(ir_data) - np.min(ir_data)
        prominence = signal_range * 0.05
        min_distance = 6
        peaks, _ = find_peaks(ir_data, prominence=prominence, distance=min_distance)
        if len(peaks) < 2:
            return None
        time_span = (peaks[-1] - peaks[0]) * 0.05
        if time_span == 0:
            return None
        bpm = (len(peaks) - 1) / time_span * 60
        return round(bpm)

    def scan_anomalies(self):
        if not self.data_buffer['Time']:
            self.data_display.append("Error: No data available for anomaly scan")
            return

        self.data_display.append("Scanning for anomalous heart conditions...")
        anomalies_detected = False
        pulse_data = np.array(self.data_buffer['Pulse'])
        time_data = np.array(self.data_buffer['Time'])
        ir_data = np.array(self.data_buffer['IR'])

        # Parameters
        window_size = 100  # 5 seconds at 20 Hz (50ms samples)
        bradycardia_threshold = 60
        tachycardia_threshold = 100
        ibi_variability_threshold = 0.2
        pvc_ibi_threshold = 0.6  # IBIs <60% of mean IBI are potential PVCs

        # Bradycardia and Tachycardia Detection
        num_windows = len(pulse_data) // window_size
        for i in range(num_windows):
            start_idx = i * window_size
            end_idx = start_idx + window_size
            window_pulse = pulse_data[start_idx:end_idx]
            window_time = time_data[start_idx:end_idx]
            avg_pulse = np.mean(window_pulse)

            if avg_pulse < bradycardia_threshold:
                self.data_display.append(
                    f"Potential Bradycardia detected at time {window_time[0]:.2f}s to {window_time[-1]:.2f}s: "
                    f"Average HR = {avg_pulse:.1f} bpm"
                )
                anomalies_detected = True
            elif avg_pulse > tachycardia_threshold:
                self.data_display.append(
                    f"Potential Tachycardia detected at time {window_time[0]:.2f}s to {window_time[-1]:.2f}s: "
                    f"Average HR = {avg_pulse:.1f} bpm"
                )
                anomalies_detected = True

        # Irregularity, HRV, and PVC Analysis
        signal_range = np.max(ir_data) - np.min(ir_data)
        prominence = signal_range * 0.05
        min_distance = 6
        peaks, _ = find_peaks(ir_data, prominence=prominence, distance=min_distance)
        if len(peaks) >= 2:
            ibis = np.diff(peaks) * 0.05 * 1000  # Convert to milliseconds
            ibi_std = np.std(ibis)
            ibi_mean = np.mean(ibis)
            ibi_cv = ibi_std / ibi_mean if ibi_mean != 0 else 0

            # SDNN (Standard Deviation of NN intervals)
            sdnn = ibi_std

            # RMSSD (Root Mean Square of Successive Differences)
            successive_diffs = np.diff(ibis)
            rmssd = np.sqrt(np.mean(successive_diffs ** 2)) if len(successive_diffs) > 0 else 0

            # Report HRV
            hrv_status = "normal"
            if sdnn < 20 or rmssd < 15:
                hrv_status = "low (possible stress or fatigue)"
            elif sdnn > 100 or rmssd > 80:
                hrv_status = "high (may indicate irregularities)"
            self.data_display.append(
                f"HRV Analysis: SDNN = {sdnn:.1f} ms, RMSSD = {rmssd:.1f} ms ({hrv_status})"
            )

            # Irregularity Check
            if ibi_cv > ibi_variability_threshold:
                self.data_display.append(
                    f"Potential Irregularity detected: High IBI variability (CV = {ibi_cv:.2f})"
                )
                anomalies_detected = True

            # PVC Detection
            pvc_count = 0
            for i, ibi in enumerate(ibis):
                if ibi < ibi_mean * pvc_ibi_threshold:
                    peak_time = time_data[peaks[i + 1]]
                    self.data_display.append(
                        f"Potential PVC detected at time {peak_time:.2f}s: IBI = {ibi:.1f} ms (normal ~{ibi_mean:.1f} ms)"
                    )
                    pvc_count += 1
                    anomalies_detected = True
            if pvc_count > 0:
                total_time = time_data[-1] - time_data[0]
                pvc_rate = pvc_count / (total_time / 60) if total_time > 0 else 0
                self.data_display.append(
                    f"Total PVCs detected: {pvc_count} (rate: {pvc_rate:.1f} per minute)"
                )

        # Summary
        if not anomalies_detected:
            self.data_display.append("No anomalous heart conditions detected")
        else:
            self.data_display.append("Anomaly scan completed with potential issues detected")
        self.data_display.append("---")

    def read_serial_data(self):
        if not self.is_reading or not self.serial_port or not self.serial_port.is_open or self.start_time is None:
            return
        try:
            if self.serial_port.in_waiting >= 20:
                data = self.serial_port.read(20)
                if len(data) == 20:
                    red, ir, green, blue, pulse, spo2 = struct.unpack('<IIIIHH', data)
                    current_time = time.time() - self.start_time
                    self.data_buffer['RED'].append(red)
                    self.data_buffer['IR'].append(ir)
                    self.data_buffer['GREEN'].append(green)
                    self.data_buffer['BLUE'].append(blue)
                    self.data_buffer['Pulse'].append(pulse)
                    self.data_buffer['SpO2'].append(spo2)
                    self.data_buffer['Time'].append(current_time)

                    self.data_display.append(
                        f"RED: {red}, IR: {ir}, GREEN: {green}, BLUE: {blue}, "
                        f"Pulse: {pulse} bpm, SpO2: {spo2}%"
                    )
                    self.spo2_label.setText(f"SpO2: {spo2} %")
                    if len(self.data_buffer['Time']) > 1:
                        idx = bisect.bisect_left(self.data_buffer['Time'], current_time - 10)
                        for key in self.data_buffer:
                            self.data_buffer[key] = self.data_buffer[key][idx:]
                else:
                    self.data_display.append(f"Error: Incomplete packet received ({len(data)} bytes)")
        except Exception as e:
            self.data_display.append(f"Error reading data: {str(e)}")

    def update_plot(self):
        self.ax.clear()
        self.ax.set_facecolor('white')
        self.ax.grid(True, which='major', linestyle='--', alpha=0.3)
        self.ax.tick_params(colors='black')
        self.ax.spines['top'].set_color('black')
        self.ax.spines['bottom'].set_color('black')
        self.ax.spines['left'].set_color('black')
        self.ax.spines['right'].set_color('black')
        self.ax.xaxis.set_major_locator(plt.MultipleLocator(1.0))

        plotted = False
        time_data = self.data_buffer['Time']
        if time_data:
            current_time = time_data[-1]
            self.ax.set_xlim(max(0, current_time - 10), current_time)

            # Normalize IR and RED if both are checked
            if self.ir_cb.isChecked() and self.red_cb.isChecked():
                ir_data = np.array(self.data_buffer['IR'])
                red_data = np.array(self.data_buffer['RED'])
                # Subtract DC (mean) to center around zero
                ir_normalized = ir_data - np.mean(ir_data)
                red_normalized = red_data - np.mean(red_data)
                # Plot normalized signals
                self.ax.plot(time_data, ir_normalized, label="IR (normalized)", color="#8B0000", linewidth=1.0)
                self.ax.plot(time_data, red_normalized, label="RED (normalized)", color="#FF0000", linewidth=1.0)
                plotted = True
                # Set y-axis limits based on max AC amplitude
                max_amplitude = max(np.max(np.abs(ir_normalized)), np.max(np.abs(red_normalized)))
                self.ax.set_ylim(-max_amplitude * 1.2, max_amplitude * 1.2)
            else:
                # Plot raw signals if only one or neither is checked
                if self.ir_cb.isChecked():
                    self.ax.plot(time_data, self.data_buffer['IR'], label="IR", color="#8B0000", linewidth=1.0)
                    plotted = True
                if self.red_cb.isChecked():
                    self.ax.plot(time_data, self.data_buffer['RED'], label="RED", color="#FF0000", linewidth=1.0)
                    plotted = True

            # Plot GREEN and BLUE raw if checked
            if self.green_cb.isChecked():
                self.ax.plot(time_data, self.data_buffer['GREEN'], label="GREEN", color="#00FF00", linewidth=1.0)
                plotted = True
            if self.blue_cb.isChecked():
                self.ax.plot(time_data, self.data_buffer['BLUE'], label="BLUE", color="#0000FF", linewidth=1.0)
                plotted = True

            if plotted:
                self.ax.legend(loc='upper right')
                self.ax.set_title("PPG Heart Monitor")
                self.ax.set_xlabel("Time (seconds)")
                self.ax.set_ylabel("Amplitude (normalized)" if self.ir_cb.isChecked() and self.red_cb.isChecked() else "Amplitude")
        else:
            self.ax.set_xlim(0, 10)

        bpm = self.calculate_heart_rate()
        self.hr_label.setText(f"Heart Rate: {bpm if bpm is not None else '--'} bpm")
        self.canvas.draw()

    def toggle_biofeedback(self):
        if self.biofeedback_active:
            self.biofeedback_active = False
            self.biofeedback_timer.stop()
            self.breathing_label.setText("")
            self.biofeedback_button.setText("Start Biofeedback")
        else:
            self.biofeedback_active = True
            self.state_index = 0
            self.breathing_state, self.duration = self.breathing_pattern[self.state_index]
            self.countdown = self.duration
            self.breathing_label.setText(f"{self.breathing_state} ({self.countdown})")
            self.biofeedback_timer.start(1000)
            self.biofeedback_button.setText("Stop Biofeedback")

    def biofeedback_timeout(self):
        if self.countdown > 1:
            self.countdown -= 1
        else:
            self.state_index = (self.state_index + 1) % len(self.breathing_pattern)
            self.breathing_state, self.duration = self.breathing_pattern[self.state_index]
            self.countdown = self.duration
        self.breathing_label.setText(f"{self.breathing_state} ({self.countdown})")

    def closeEvent(self, event):
        self.stop_reading()
        event.accept()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())