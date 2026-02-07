# Smart IoT Lock System with Telegram & OLED
Created by: [agamsuteguh](https://github.com/agamsuteguh)

Lock Door With Iot Online **ESP32**, **Servo Motor**, dan **Telegram Bot** sebagai kontrol jarak jauh. Dilengkapi dengan layar **OLED** untuk monitoring status wifi dan koneksi bot.

## Fitur Utama
- **Remote Control:** Buka/Kunci pintu dari mana saja via Telegram.
- **Dual Monitoring:** Indikator status WiFi dan Bot di layar OLED.
- **Secure Access:** Hanya merespon perintah dari Chat ID Telegram pemilik.


## Komponen
- ESP32 WROOM Development Board
- Servo Motor (SG90/MG996R)
- OLED Display 128x64 (SSD1306)
- PSU Eksternal 5V 
- Diy 3d print linear servo actuator

## Wiring Design
https://github.com/agamSuteguh/Smart-IoT-Lock-ESP32/blob/main/Hardware/Wiring_Design.png

## Cara Penggunaan
1. Clone repository ini.
2. Install library: `ESP32Servo`, `UniversalTelegramBot`, `Adafruit_SSD1306`, dan `ArduinoJson`.
3. Buka telegram dan chat @idbot untuk mendapatkan `Chat ID` 
4. Chat @BotFather kirim /newbot lalu isi sesuai pertanyaaa hingga ada `Use this token to access the HTTP API:` gunakan itu sebagai `Bot Token`,
5. Masukkan `SSID Wifi`, `Password`, `Bot Token`, dan `Chat ID` di file `https://github.com/agamSuteguh/Smart-IoT-Lock-ESP32/blob/main/src/main.ino`.
6. Upload kode ke ESP32.
7. Gunakan perintah `/buka` dan `/kunci` pada bot Telegram Anda.

---
