#include <Keypad.h>
#include <Wire.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile byte half_revolutions = 0;
unsigned int rpmku = 0;
unsigned long timeold = 0;

char customKey;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {8, 9, 10, 11};
byte colPins[COLS] = {4, 5, 6, 7};

int speedx = 3;

float kp = 0, nilaikp = 0;
float ki = 0, nilaiki = 0;
float kd = 0, nilaikd = 0;
float sp = 0, nilaisp = 0;
float error = 0, errorx = 0, sumerr = 0;
float p = 0, i = 0, d = 0, pid = 0, rpmfix = 0;
float selisih = 0;

int kalibrasi = 0;
int x = 0;

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  lcd.begin();             // Ganti dari lcd.begin() ke lcd.init()
  lcd.backlight();        // Menyalakan backlight LCD
  lcd.clear();
  lcd.noCursor();

  attachInterrupt(digitalPinToInterrupt(2), rpm_fun, RISING);

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(speedx, OUTPUT);
  pinMode(2, INPUT);

  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
}

void loop() {
  customKey = customKeypad.getKey();

  if (x == 0) lcd.setCursor(0, 0), lcd.print("1.SET PID       ");
  if (x == 1) lcd.setCursor(0, 0), lcd.print("2.MULAI         ");
  if (x == 2) lcd.setCursor(0, 0), lcd.print("3.CEK PID       ");

  switch (customKey) {
    case 'A': x++; delay(200); break;
    case 'B': x--; delay(200); break;
    case 'D':
      lcd.clear();
      if (x == 0) { setkp(); setki(); setkd(); setsp(); cekpid(); }
      if (x == 1) mulai();
      if (x == 2) cekpid();
      break;
  }

  if (x > 2) x = 0;
  if (x < 0) x = 2;
}

void setkp() {
  kp = 0;
  lcd.setCursor(0, 0); lcd.print("SET KP     ");
  lcd.setCursor(0, 1); lcd.print("0");

  while (true) {
    customKey = customKeypad.getKey();
    if (customKey >= '0' && customKey <= '9') {
      kp = kp * 10 + (customKey - '0');
      lcd.setCursor(0, 1); lcd.print(kp);
    }
    if (customKey == 'A') { kp /= 100; break; }
    if (customKey == 'B') { kp /= 1000; break; }
    if (customKey == '*') { break; }
    delay(100);
  }

  lcd.clear(); nilaikp = kp;
}

void setki() {
  ki = 0;
  lcd.setCursor(0, 0); lcd.print("SET KI     ");
  lcd.setCursor(0, 1); lcd.print("0");

  while (true) {
    customKey = customKeypad.getKey();
    if (customKey >= '0' && customKey <= '9') {
      ki = ki * 10 + (customKey - '0');
      lcd.setCursor(0, 1); lcd.print(ki);
    }
    if (customKey == 'A') { ki /= 100; break; }
    if (customKey == 'B') { ki /= 1000; break; }
    if (customKey == '*') { break; }
    delay(100);
  }

  lcd.clear(); nilaiki = ki;
}

void setkd() {
  kd = 0;
  lcd.setCursor(0, 0); lcd.print("SET KD     ");
  lcd.setCursor(0, 1); lcd.print("0");

  while (true) {
    customKey = customKeypad.getKey();
    if (customKey >= '0' && customKey <= '9') {
      kd = kd * 10 + (customKey - '0');
      lcd.setCursor(0, 1); lcd.print(kd);
    }
    if (customKey == 'A') { kd /= 100; break; }
    if (customKey == 'B') { kd /= 1000; break; }
    if (customKey == '*') { break; }
    delay(100);
  }

  lcd.clear(); nilaikd = kd;
}

void setsp() {
  sp = 0;
  lcd.setCursor(0, 0); lcd.print("SET SP     ");
  lcd.setCursor(0, 1); lcd.print("0");

  while (true) {
    customKey = customKeypad.getKey();
    if (customKey >= '0' && customKey <= '9') {
      sp = sp * 10 + (customKey - '0');
      lcd.setCursor(0, 1); lcd.print(sp);
    }
    if (customKey == '*') { break; }
    delay(100);
  }

  lcd.clear(); nilaisp = sp;
}

void cekpid() {
  lcd.setCursor(0, 0);
  lcd.print("KP"); lcd.print(nilaikp, 2);
  lcd.print("-KI"); lcd.print(nilaiki, 2);
  lcd.setCursor(0, 1);
  lcd.print("KD"); lcd.print(nilaikd, 2);
  lcd.print("-SP"); lcd.print(nilaisp, 2);

  while (true) {
    customKey = customKeypad.getKey();
    if (customKey == '*') {
      lcd.clear();
      delay(500);
      break;
    }
    delay(100);
  }
}

void mulai() {
  while (true) {
    analogWrite(speedx, pid);

    error = nilaisp - rpmfix;
    p = error * nilaikp;
    sumerr = error + errorx;
    i = nilaiki * sumerr;
    selisih = error - errorx;
    d = nilaikd * selisih;
    pid = p + i + d;

    if (pid < 0) pid = 0;

    rpmku = 30 * 1000 / (millis() - timeold) * half_revolutions;
    timeold = millis();
    half_revolutions = 0;

    kalibrasi = (rpmku - 150) / 109;
    rpmfix = kalibrasi * 10;
    if (rpmfix > 2000) rpmfix = 0;

    lcd.setCursor(0, 0); lcd.print("RPM= "); lcd.print(rpmfix); lcd.print("     ");
    lcd.setCursor(0, 1); lcd.print("PID= "); lcd.print(pid); lcd.print("     ");

    customKey = customKeypad.getKey();
    if (customKey == '*') {
      lcd.clear();
      kp = ki = kd = sp = 0;
      analogWrite(speedx, 0);
      delay(1000);
      break;
    }

    errorx = error;
    delay(200);
  }
}

void rpm_fun() {
  half_revolutions++;
}
