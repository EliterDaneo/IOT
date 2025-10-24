// Definisi Pin Relay
const int pinRelay1 = 18; // Hubungkan ke IN1 (atau saluran lain)
const int pinRelay2 = 19; // Hubungkan ke IN2
const int pinRelay3 = 23; // Hubungkan ke IN3
const int pinRelay4 = 5;  // Hubungkan ke IN4
// Pastikan pin ini terhubung ke input (IN1, IN2, IN3, IN4) pada modul relay 4 Channel Anda.

void setup() {
  Serial.begin(9600);
  Serial.println("======================================");
  Serial.println("Kontrol Semua 4 Channel Relay Siap Dijalankan!");

  // Konfigurasi keempat pin sebagai OUTPUT
  pinMode(pinRelay1, OUTPUT);
  pinMode(pinRelay2, OUTPUT);
  pinMode(pinRelay3, OUTPUT);
  pinMode(pinRelay4, OUTPUT);

  // Set kondisi awal: Semua Relay Mati (Asumsi Active HIGH)
  digitalWrite(pinRelay1, LOW);
  digitalWrite(pinRelay2, LOW);
  digitalWrite(pinRelay3, LOW);
  digitalWrite(pinRelay4, LOW);

  Serial.println("Status Awal: Semua Relay Mati (LOW)");
  Serial.println("======================================");
  delay(1000); 
}

void loop() {
  // Kondisi 1: Semua Relay Mati
  // (Jika relay Anda Active LOW, ganti semua LOW menjadi HIGH)
  digitalWrite(pinRelay1, LOW);
  digitalWrite(pinRelay2, LOW);
  digitalWrite(pinRelay3, LOW);
  digitalWrite(pinRelay4, LOW);
  
  Serial.println("Aksi: Semua 4 Relay MATI");
  delay(2000); // Jeda 2 detik

  // Kondisi 2: Semua Relay Menyala
  // (Jika relay Anda Active LOW, ganti semua HIGH menjadi LOW)
  digitalWrite(pinRelay1, HIGH);
  digitalWrite(pinRelay2, HIGH);
  digitalWrite(pinRelay3, HIGH);
  digitalWrite(pinRelay4, HIGH);
  
  Serial.println("Aksi: Semua 4 Relay HIDUP");
  delay(2000); // Jeda 2 detik
}