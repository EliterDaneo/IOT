#define BLYNK_PRINT Serial

/* Ganti dengan informasi dari Blynk Device Info Anda */
#define BLYNK_TEMPLATE_ID "TMPL61_4XFpE5"
#define BLYNK_TEMPLATE_NAME "LED ESP32 1"
#define BLYNK_AUTH_TOKEN "wXWa2PNQCnfA9vhsLyTWEBDmIlmcHP0K"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h> // Library untuk LCD I2C

// Ganti dengan kredensial WiFi Anda.
char ssid[] = "LENOVO";
char pass[] = "nunutanbgt";

// --- DEFINISI PIN HARDWARE ---
const int RELAY_PIN = 23;       // GPIO 23 terhubung ke Relai IN
const int LED_PIN = 2;          // GPIO 2 untuk LED (indikator)

// --- PIN VIRTUAL BLYNK ---
#define BLYNK_VIRTUAL_PIN V0    // Pin untuk kontrol Relai (Saklar Lampu)

// --- INISIALISASI OBJEK ---
// Inisialisasi LCD 16x2 dengan alamat I2C 0x27. Ganti 0x27 jika alamat Anda berbeda.
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// --- VARIABEL STATUS ---
// Status Relai: HIGH = OFF (Active-Low), LOW = ON
int relayState = HIGH; 

// --- VARIABEL WAKTU (Non-Blocking Delay) ---
unsigned long previousMillis = 0;   // Waktu terakhir LCD diperbarui
const long interval = 2000;         // Interval pembaruan status lampu: 2 detik (2000 ms)
unsigned long startupTime = 0;      // Waktu saat setup dimulai
bool connectionInfoDisplayed = false; // Flag untuk status info koneksi


// --- FUNGSI TAMPILAN LCD ---

// Fungsi yang dijalankan secara berkala untuk menampilkan status lampu.
void displayStatusLampu() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Blynk: ");
    lcd.print(Blynk.connected() ? "ONLINE" : "OFFLINE");

    // Baris 2: Status Lampu
    lcd.setCursor(0, 1);
    lcd.print("Lampu: ");
    
    String status = (relayState == LOW) ? "MATI" : "NYALA";
    lcd.print(status);
}


// Fungsi untuk memperbarui status hardware (Relai dan LED)
void updateHardware() {
    digitalWrite(RELAY_PIN, relayState); 
    // Sesuaikan logika LED: LOW = ON (jika LED aktif-rendah), HIGH = OFF
    digitalWrite(LED_PIN, relayState == LOW ? LOW : HIGH); 
}


// --- FUNGSI BLYNK ---

BLYNK_WRITE(BLYNK_VIRTUAL_PIN) {
    int pinValue = param.asInt(); // 1 (ON) atau 0 (OFF) dari Blynk
    
    // 1. Tentukan status relai (Active-Low)
    // Blynk 1 (ON) = Relai OFF (HIGH); Blynk 0 (OFF) = Relai ON (LOW)
    relayState = (pinValue == 1) ? HIGH : LOW; 

    // 2. Perbarui Hardware
    updateHardware();
    
    Serial.print("Status diubah via Blynk. Relai: ");
    Serial.println(relayState == LOW ? "ON" : "OFF");

    // Opsional: Langsung update LCD saat ada perubahan dari Blynk
    displayStatusLampu();
}

// Dipanggil saat perangkat terhubung ke Blynk Server
BLYNK_CONNECTED() {
    // Minta server mengirimkan status terakhir V0 ke perangkat (untuk sinkronisasi awal)
    Blynk.syncVirtual(BLYNK_VIRTUAL_PIN); 
}

// --- SETUP & LOOP ---

void setup()
{
    Serial.begin(9600);
    startupTime = millis(); // Catat waktu saat setup dimulai

    // --- INISIALISASI PIN ---
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    
    // --- INISIALISASI LCD ---
    lcd.init();
    lcd.backlight();
    lcd.print("Connecting WiFi...");
    
    // Status awal (Relai OFF)
    relayState = HIGH;
    updateHardware();

    // --- INISIALISASI BLYNK ---
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
    Blynk.run();
    
    // Mekanisme Tampilan Awal: Tampilkan IP selama 5 detik
    if (WiFi.isConnected() && !connectionInfoDisplayed) {
        // Tampilkan Status Koneksi dan IP
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Connected!");
        lcd.setCursor(0, 1);
        lcd.print("IP: ");
        lcd.print(WiFi.localIP());
        
        // Atur flag dan waktu pembaruan agar tampilan lampu dimulai setelah 5 detik
        connectionInfoDisplayed = true;
        previousMillis = millis(); // Set waktu awal pembaruan status lampu
    }

    // Mekanisme Pembaruan Status Lampu (Non-Blocking)
    unsigned long currentMillis = millis();

    if (connectionInfoDisplayed && currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        displayStatusLampu();
    }
}