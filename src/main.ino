#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// --- KONFIGURASI ---
const char* ssid = "NAMA_WIFI";
const char* password = "PASSWORD_WIFI";
#define BOTtoken "XXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXX"
#define CHAT_ID "XXXXXXXXX"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
Servo myservo;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

const int servoPin = 13;
unsigned long lastBotCheck;
bool isBotConnected = false;

// Fungsi Tampilan OLED Keren
void drawUI(String lockStatus, String botMsg) {
  display.clearDisplay();
  
  // --- HEADER: Credit & WiFi ---
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Github:agamsuteguh"); // Credit Github
  
  // Ikon WiFi Sederhana
  display.setCursor(105, 0);
  if (WiFi.status() == WL_CONNECTED) {
    display.print("[W]"); // Simbol WiFi Connected
  } else {
    display.print("[X]"); // Simbol WiFi Disconnected
  }
  
  display.drawLine(0, 10, 128, 10, WHITE); // Garis Pembatas

  // --- CENTER: Status Kunci ---
  display.setTextSize(2);
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(lockStatus, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((128 - w) / 2, 25); // Auto center text
  display.println(lockStatus);

  // --- FOOTER: Bot Status ---
  display.drawLine(0, 50, 128, 50, WHITE);
  display.setTextSize(1);
  display.setCursor(0, 55);
  display.print("BOT: ");
  display.print(botMsg);
  
  display.display();
}

void setup() {
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  
  ESP32PWM::allocateTimer(0);
  myservo.attach(servoPin, 500, 2400);
  myservo.write(0);
  
  WiFi.begin(ssid, password);
  client.setInsecure();

  drawUI("STARTING", "Connecting...");
}

void loop() {
  // Cek Status Koneksi untuk OLED
  String botStatusMsg;
  
  if (WiFi.status() == WL_CONNECTED) {
    // Cek Bot setiap 2 detik agar tidak lag
    if (millis() - lastBotCheck > 2000) {
      int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
      if (numNewMessages >= 0) {
        isBotConnected = true;
        botStatusMsg = "Online";
        
        // Handle Pesan Telegram
        for (int i=0; i<numNewMessages; i++) {
          String text = bot.messages[i].text;
          if (text == "/buka") {
            myservo.write(90);
            drawUI("UNLOCKED", "Online");
            bot.sendMessage(CHAT_ID, "Akses diberikan. Pintu Terbuka.", "");
          } else if (text == "/kunci") {
            myservo.write(0);
            drawUI("LOCKED", "Online");
            bot.sendMessage(CHAT_ID, "Pintu dikunci kembali.", "");
          }
        }
      } else {
        isBotConnected = false;
        botStatusMsg = "Error/Offline";
      }
      
      // Update UI Standby
      static String lastLock = "LOCKED"; 
      // Ambil status posisi servo terakhir untuk display
      String currentStatus = (myservo.read() > 45) ? "UNLOCKED" : "LOCKED";
      drawUI(currentStatus, botStatusMsg);
      
      lastBotCheck = millis();
    }
  } else {
    drawUI("OFFLINE", "No WiFi");
  }
}