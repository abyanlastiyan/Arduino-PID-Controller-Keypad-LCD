# Motor PID Controller with Keypad and LCD Display
> Sistem Kontrol Kecepatan Motor Menggunakan Algoritma PID

---

## Deskripsi Proyek

Proyek ini merupakan sistem kontrol kecepatan motor berbasis algoritma PID (Proportional-Integral-Derivative) menggunakan Arduino Uno.  
Sistem ini memungkinkan pengaturan nilai PID secara real-time melalui input dari Keypad 4x4, serta menampilkan informasi parameter PID dan kecepatan motor (RPM) pada LCD 16x2 berbasis I2C.

Sistem dirancang untuk mempertahankan kecepatan motor secara stabil terhadap perubahan beban atau gangguan, sehingga meningkatkan performa dan efisiensi kontrol motor.

---

## Apa itu PID Controller?

PID Controller adalah algoritma pengendalian berbasis umpan balik (feedback control) yang banyak digunakan untuk menjaga variabel proses seperti kecepatan, suhu, atau tekanan agar tetap pada nilai target (setpoint).

PID bekerja dengan kombinasi tiga komponen utama:
- **Proportional (P)**: Mengoreksi error berdasarkan nilai error saat ini.
- **Integral (I)**: Mengoreksi error berdasarkan akumulasi error masa lalu.
- **Derivative (D)**: Mengoreksi error berdasarkan prediksi tren perubahan error.

Dengan penyetelan yang tepat, PID mampu menghasilkan respon sistem yang cepat, stabil, dan minim osilasi.

---

## Tabel Input dan Output

| Komponen          | Pin Arduino | Keterangan                                  |
|-------------------|-------------|---------------------------------------------|
| Motor Driver (ENA) | Pin 9       | PWM untuk kecepatan motor                   |
| Motor Driver (IN1) | Pin 7       | Arah motor 1                                |
| Motor Driver (IN2) | Pin 8       | Arah motor 2                                |
| Encoder Motor     | Pin 2        | Interrupt untuk pembacaan RPM motor         |
| LCD I2C           | SDA: A4, SCL: A5 | Menampilkan PID dan RPM                   |
| Keypad 4x4        | Pin 3, 4, 5, 6, 10, 11, 12, 13 | Input nilai PID dan kontrol |

---

## Alat dan Bahan

- Arduino Uno R3
- Motor DC + Encoder atau simulasi motor
- Driver Motor (contoh: L298N)
- LCD 16x2 dengan modul I2C (alamat I2C: 0x27)
- Keypad 4x4
- Sensor kecepatan motor (opsional, bisa menggunakan encoder atau sensor Hall Effect)
- Kabel jumper
- Breadboard
- Power supply motor (contoh: 12V adaptor)

---

## Library yang Digunakan

- **Keypad**  
  Library untuk membaca input dari keypad matrix.
- **LiquidCrystal_I2C**  
  Library untuk mengontrol LCD melalui I2C.
- **EEPROM**  
  Library untuk membaca dan menulis data ke memori EEPROM internal Arduino.
- **Wire**  
  Library untuk komunikasi I2C (Inter-Integrated Circuit) antar perangkat.


**Instalasi Library:**  
Bisa dilakukan melalui Arduino IDE → Library Manager (`Sketch > Include Library > Manage Libraries`).

---

## Skema Rangkaian

Skema rangkaian proyek ini dapat dilihat pada file berikut:

- [Wiring Diagram (PDF)]([diagram/Wiring_Diagram.pdf](https://github.com/abyanlastiyan/Arduino-PID-Controller-Keypad-LCD))

---

## File Program

Source code lengkap Arduino tersedia di:

- [Motor_PID_Controller.ino](code/Motor_PID_Controller.ino)

---

## Cara Kerja Singkat

1. Sistem membaca input nilai P, I, dan D dari keypad 4x4.
2. Nilai PID diupdate secara real-time tanpa perlu upload ulang program.
3. Sistem membaca kecepatan motor dari sensor encoder.
4. Output PID digunakan untuk mengatur PWM motor melalui driver motor.
5. Semua nilai PID dan kecepatan motor (RPM) ditampilkan pada LCD 16x2 I2C.

---

## Lisensi

Proyek ini dilisensikan di bawah [MIT License](LICENSE).

---
