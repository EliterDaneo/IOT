#define BLYNK_PRINT Serial

/* Ganti dengan informasi dari Blynk Device Info Anda */
#define BLYNK_TEMPLATE_ID "TMPL61_4XFpE5"
#define BLYNK_TEMPLATE_NAME "LED ESP32 1"
#define BLYNK_AUTH_TOKEN "wXWa2PNQCnfA9vhsLyTWEBDmIlmcHP0K"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Ganti dengan kredensial WiFi Anda.
char ssid[] = "RM PUTRI SEJATI";
char pass[] = "pasukanbrondong";

// Definisikan pin GPIO ESP32 yang terhubung ke pin IN relai
const int RELAY_PIN = 23; // Contoh menggunakan GPIO 23
// Pin LED (opsional, misalnya LED internal di beberapa board ESP32 adalah GPIO 2)
const int LED_PIN = 2; 

// Gunakan Virtual Pin V0 di Blynk App/Web Dashboard
#define BLYNK_VIRTUAL_PIN V0 


// Fungsi yang dipanggil setiap kali nilai Virtual Pin V0 berubah di Blynk
BLYNK_WRITE(BLYNK_VIRTUAL_PIN) {
    // param.asInt() akan bernilai 1 (saat Button ON) atau 0 (saat Button OFF)
    int pinValue = param.asInt(); 

    // --- LOGIKA KONTROL RELAI AKTIF-RENDAH ---
    // HIGH (1) = Relai OFF (Lampu MATI)
    // LOW (0) = Relai ON (Lampu HIDUP)
    if (pinValue == 1) {
        // Tombol Blynk ON (1) -> Matikan Relai
        digitalWrite(RELAY_PIN, HIGH);
        // Atur LED (misalnya LED indikator) ke LOW agar ON (jika LED aktif-rendah), atau HIGH agar OFF
        digitalWrite(LED_PIN, HIGH); // LED ON (Sebagai indikator bahwa relai OFF)
        Serial.println("Relai ON (Tegangan Tinggi)");
    } else {
        // Tombol Blynk OFF (0) -> Hidupkan Relai
        digitalWrite(RELAY_PIN, LOW);
        // Atur LED ke HIGH agar OFF (jika LED aktif-rendah), atau LOW agar ON
        digitalWrite(LED_PIN, LOW); // LED OFF (Sebagai indikator bahwa relai ON)
        Serial.println("Relai OFF (Tegangan Tinggi)");
    }
}


void setup()
{
    // Debug console
    Serial.begin(9600);

    // Konfigurasi Pin
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    
    // Pastikan relai dalam kondisi default (MATI) saat startup
    digitalWrite(RELAY_PIN, HIGH); // Set default ke OFF (jika relai aktif-rendah)
    digitalWrite(LED_PIN, LOW);    // Set default LED ke kondisi yang mencerminkan Relai OFF

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
    Blynk.run();
}