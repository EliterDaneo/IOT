# 💡 LED ESP32 Control via Blynk

Proyek ini menggunakan **ESP32** dan **Blynk IoT Platform** untuk mengontrol **relay** (misalnya lampu) melalui aplikasi **Blynk** di smartphone.
Ketika tombol di aplikasi ditekan, relay akan aktif/nonaktif sesuai dengan perintah, dan LED indikator pada board ESP32 akan menunjukkan statusnya.

---

## 📁 Isi Repo

* `led_esp32_blynk.ino` — sketch Arduino/PlatformIO untuk ESP32 (kode yang Anda berikan).
* `wiring.svg` — diagram wiring (SVG) yang dapat ditampilkan langsung di GitHub.
* `README.md` — file ini.

---

## 🚀 Fitur Utama

* Kontrol relay secara **real-time** melalui aplikasi Blynk.
* Indikator **LED on-board** untuk menampilkan status relay.
* **Koneksi WiFi otomatis** ke jaringan lokal.
* **Status log** ditampilkan di Serial Monitor untuk debugging.

---

## 🧠 Spesifikasi Teknis

| Komponen              | Deskripsi                          |
| --------------------- | ---------------------------------- |
| **Board**             | ESP32                              |
| **Relay Pin (IN)**    | GPIO 23                            |
| **LED Pin**           | GPIO 2 (on-board LED)              |
| **Blynk Virtual Pin** | V0                                 |
| **Blynk Template ID** | `TMPL61_4XFpE5`                    |
| **Blynk Auth Token**  | `wXWa2PNQCnfA9vhsLyTWEBDmIlmcHP0K` |
| **SSID WiFi**         | `RM PUTRI SEJATI`                  |
| **WiFi Password**     | `pasukanbrondong`                  |

> **Catatan keamanan:** Jangan sertakan kredensial sensitif (token, password) di repositori publik. Untuk publik repositori, simpan nilai-nilai tersebut di file konfigurasi lokal mis. `secrets.h` atau gunakan variabel lingkungan.

---

## ⚙️ Cara Instalasi & Upload

1. **Clone** repositori:

   ```bash
   git clone https://github.com/username/led-esp32-blynk.git
   cd led-esp32-blynk
   ```

2. Buka file `.ino` (`led_esp32_blynk.ino`) dengan **Arduino IDE** atau PlatformIO.

3. Pilih board:

   ```
   Tools → Board → ESP32 Dev Module
   ```

4. Pastikan library **Blynk** sudah terpasang lewat Library Manager.

5. Sesuaikan kredensial (WiFi & Blynk token) di file `.ino` atau pindahkan ke file `secrets.h` yang tidak di-commit.

6. Upload ke ESP32 dan buka **Serial Monitor** dengan baud rate `9600`.

---

## 📱 Pengaturan di Blynk App

1. Buat **New Template** dengan Template ID sesuai kode.
2. Tambahkan **Button Widget** dan hubungkan ke:

   * **Datastream:** `V0`
   * **Mode:** Switch (ON/OFF)
3. Jalankan project di app Blynk.

---

## 🔌 Diagram Wiring (SVG)

Simpan blok SVG di bawah sebagai file `wiring.svg` di root repositori agar GitHub menampilkannya otomatis.

```svg
<!-- Simpan sebagai file: wiring.svg -->
<svg xmlns="http://www.w3.org/2000/svg" width="900" height="500" viewBox="0 0 900 500" role="img" aria-label="Wiring diagram ESP32 to Relay">
  <style>
    .board { fill:#2b2b2b; stroke:#000; stroke-width:2 }
    .pin { fill:#ffffff; stroke:#000; stroke-width:1 }
    .text { font-family:Arial, Helvetica, sans-serif; font-size:14px; fill:#111 }
    .line { stroke:#111; stroke-width:3; stroke-linecap:round }
    .label { font-size:12px; fill:#000 }
    .gnd { stroke:#000; stroke-width:2 }
    .vcc { stroke:#b30000; stroke-width:2 }
  </style>

  <!-- ESP32 module rectangle -->
  <rect x="20" y="40" width="300" height="220" rx="12" class="board"/>
  <text x="170" y="65" text-anchor="middle" class="text" fill="#fff">ESP32 Dev Module</text>

  <!-- Pins on ESP32 (simplified) -->
  <rect x="30" y="100" width="20" height="20" class="pin"/><text x="60" y="115" class="label">GPIO 2 (LED)</text>
  <rect x="30" y="140" width="20" height="20" class="pin"/><text x="60" y="155" class="label">GND</text>
  <rect x="30" y="180" width="20" height="20" class="pin"/><text x="60" y="195" class="label">5V (Vin)</text>
  <rect x="30" y="220" width="20" height="20" class="pin"/><text x="60" y="235" class="label">GPIO 23 (Relay IN)</text>

  <!-- Relay module -->
  <rect x="520" y="60" width="300" height="220" rx="8" fill="#eee" stroke="#444" stroke-width="2"/>
  <text x="670" y="85" text-anchor="middle" class="text">Relay Module (Active-Low)</text>

  <!-- Relay terminals -->
  <rect x="540" y="120" width="50" height="30" fill="#fff" stroke="#444"/><text x="565" y="140" text-anchor="middle" class="label">VCC</text>
  <rect x="620" y="120" width="50" height="30" fill="#fff" stroke="#444"/><text x="645" y="140" text-anchor="middle" class="label">GND</text>
  <rect x="700" y="120" width="50" height="30" fill="#fff" stroke="#444"/><text x="725" y="140" text-anchor="middle" class="label">IN</text>

  <!-- Lamp / load -->
  <g>
    <circle cx="675" cy="360" r="36" fill="#fffbcc" stroke="#b38f00"/>
    <rect x="340" y="330" width="220" height="60" rx="8" fill="#fff" stroke="#666"/>
    <text x="450" y="365" text-anchor="middle" class="text">Lamp / Load</text>
  </g>

  <!-- Wires -->
  <!-- GPIO 23 -> Relay IN -->
  <path d="M50 230 C200 240 520 150 700 135" class="line" stroke="#0066cc"/>
  <text x="370" y="210" text-anchor="middle" class="label">GPIO 23 → IN (Relay)</text>

  <!-- 5V -> VCC -->
  <path d="M50 200 C200 200 520 150 565 135" class="line" stroke="#b30000"/>
  <text x="360" y="170" text-anchor="middle" class="label">5V → VCC (Relay)</text>

  <!-- GND -> GND -->
  <path d="M50 160 C200 180 520 170 645 135" class="line" stroke="#000"/>
  <text x="360" y="150" text-anchor="middle" class="label">GND → GND (Relay & Lamp)</text>

  <!-- Relay common -> Lamp -->
  <path d="M720 150 C760 180 760 300 560 330" class="line" stroke="#6b6b6b"/>
  <text x="680" y="250" text-anchor="middle" class="label">COM → Lamp (Salah satu terminal)</text>

  <!-- Lamp other terminal -> Supply (contoh mains/other) -->
  <path d="M560 360 C440 360 330 360 320 360" class="line" stroke="#6b6b6b"/>
  <text x="430" y="385" text-anchor="middle" class="label">Lainnya → Sumber Daya (sesuaikan)</text>

  <!-- Notes -->
  <text x="170" y="290" class="label">Catatan: Pastikan relay kompatibel (5V/3.3V) dan gunakan sumber daya terpisah jika diperlukan.</text>
</svg>
```

Setelah Anda menyimpan `wiring.svg` di root repo, tampilkan di README dengan sintaks berikut (GitHub akan merendernya):

```md
![Wiring Diagram](wiring.svg)
```

---

## 🧾 Log Serial

Saat Anda menekan tombol di aplikasi Blynk:

| Aksi di Blynk | Output Serial            | Status Relay |
| ------------- | ------------------------ | ------------ |
| Tombol ON     | `Relai OFF (Lampu MATI)` | OFF          |
| Tombol OFF    | `Relai ON (Lampu HIDUP)` | ON           |

*(Keterangan: sketsa Anda menggunakan log seperti di atas; periksa kembali logic HIGH/LOW sesuai tipe relay Active-Low / Active-High.)*

---

## 🔐 Tips Keamanan & Praktis

* Jika relay mem-switching beban AC mains, pastikan **isolasi listrik** yang benar. Gunakan enclosure dan jaga jarak antar jalur bertegangan tinggi.
* Untuk beban besar, gunakan relay/SSR yang sesuai rating dan fuse/MCB.
* Sebaiknya beri catu daya terpisah untuk ESP32 dan modul relay jika relay drawing current besar atau jika ada noise.

---

## 🧑‍💻 Kontributor

* **Ari Setiawan**

---

## 📜 Lisensi

Lisensi **MIT** — lihat file `LICENSE` untuk detail.

---

Jika Anda mau, saya bisa:

* Menghasilkan file `wiring.svg` terpisah dan memberi instruksi commit (mis. `wiring.svg` sudah siap disimpan).
* Atau mengubah diagram supaya menampilkan koneksi sumber daya 3.3V vs 5V secara eksplisit.

Tinggal bilang mau yang mana — saya buatkan langsung.
