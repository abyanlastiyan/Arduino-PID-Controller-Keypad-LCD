Motor PID Controller with Keypad and LCD Display
Deskripsi Proyek
Proyek ini merupakan sistem kontrol kecepatan motor berbasis algoritma PID (Proportional-Integral-Derivative) menggunakan Arduino Uno. Sistem ini memungkinkan pengaturan nilai PID secara real-time melalui input dari Keypad 4x4, serta menampilkan informasi parameter PID dan kecepatan motor (RPM) pada LCD 16x2 berbasis I2C.

Sistem dirancang untuk mempertahankan kecepatan motor secara stabil terhadap perubahan beban atau gangguan, sehingga meningkatkan performa dan efisiensi kontrol motor.

Apa itu PID Controller?
PID Controller adalah algoritma pengendalian berbasis umpan balik (feedback control) yang banyak digunakan untuk menjaga variabel proses (seperti kecepatan, suhu, tekanan) agar tetap pada nilai target (setpoint).
PID bekerja dengan kombinasi tiga komponen utama:

Proportional (P): Mengoreksi error berdasarkan nilai error saat ini.

Integral (I): Mengoreksi error berdasarkan akumulasi error masa lalu.

Derivative (D): Mengoreksi error berdasarkan prediksi tren perubahan error.

Dengan penyetelan yang tepat, PID mampu menghasilkan respon sistem yang cepat, stabil, dan minim osilasi.

Alat dan Bahan
Arduino Uno R3

Motor DC + Encoder atau Simulasi Motor

Driver Motor (contoh: L298N)

LCD 16x2 dengan modul I2C (alamat I2C: 0x27)

Keypad 4x4

Sensor kecepatan motor (optional, bisa menggunakan encoder atau sensor Hall Effect)

Breadboard dan Kabel Jumper

Power Supply sesuai spesifikasi motor

Library yang Digunakan
Pastikan library berikut sudah terinstall pada Arduino IDE:

PID_v1.h — Library untuk kontrol PID.

LiquidCrystal_I2C.h — Library untuk mengontrol LCD via I2C.

Keypad.h — Library untuk membaca input dari Keypad.

Tabel Input - Output Keypad

Tombol Keypad	Fungsi
1	Menambah nilai Kp (+)
2	Menambah nilai Ki (+)
3	Menambah nilai Kd (+)
4	Mengurangi nilai Kp (-)
5	Mengurangi nilai Ki (-)
6	Mengurangi nilai Kd (-)
7	Menambah target RPM (+)
8	Mengurangi target RPM (-)
9	Reset nilai PID dan target RPM ke default
0	Tidak digunakan
*	Simpan pengaturan ke EEPROM (opsional)
#	Beralih Mode Manual/Auto (opsional)
Cara Kerja Sistem
Nilai Kp, Ki, dan Kd dapat diubah secara dinamis melalui Keypad.

Target RPM juga dapat diatur menggunakan Keypad.

LCD akan menampilkan nilai parameter PID dan kecepatan motor aktual (RPM).

Arduino membaca error antara target RPM dan aktual RPM, lalu menghitung koreksi sinyal PWM menggunakan algoritma PID.

Output PWM digunakan untuk mengatur kecepatan motor melalui driver motor.

User dapat mereset nilai PID atau menyimpan pengaturan ke EEPROM sesuai kebutuhan.

Wiring Diagram
Wiring diagram lengkap tersedia di folder proyek dalam format Fritzing (.fzz) dan gambar (.png).

Keterangan utama koneksi:

SDA LCD → A4 Arduino

SCL LCD → A5 Arduino

Keypad dihubungkan ke pin digital 2-9 Arduino (atau sesuai skema)

Motor Driver → PWM control dari Arduino

Encoder/Sensor → Input interrupt Arduino (optional)

Fitur Tambahan (Opsional)
Penyimpanan nilai PID ke EEPROM untuk persistensi pengaturan saat reset/power off.

Mode Manual/Auto Switch.

Validasi input keypad untuk menghindari kesalahan setting.

Proteksi motor terhadap overcurrent/overspeed.

TODO / Rencana Pengembangan
Menambahkan auto-tuning PID.

Implementasi pengaturan batas maksimal dan minimal PWM output.

Menampilkan status sistem (Normal / Error) di LCD.

Optimasi penggunaan memori Arduino untuk proyek lebih besar.

Lisensi
Proyek ini bersifat open-source dan dapat digunakan untuk keperluan edukasi, penelitian, atau pengembangan lebih lanjut dengan mencantumkan sumber.