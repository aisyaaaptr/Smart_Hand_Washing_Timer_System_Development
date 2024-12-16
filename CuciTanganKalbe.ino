#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definisi ukuran layar OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Deklarasi pin
const int proximityPin = 2;  // Pin sensor proximity
const int buzzerPin = 3;     // Pin buzzer

// Inisialisasi layar OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Waktu countdown dalam detik
int countdownTime = 30;
bool isCountingDown = false;

void setup() {
  // Set pin sebagai input atau output
  pinMode(proximityPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  // Inisialisasi komunikasi serial (opsional)
  Serial.begin(9600);

  // Inisialisasi layar OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Alamat I2C umum untuk OLED adalah 0x3C
    Serial.println(F("Failed to initialize OLED display!"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int proximityState = digitalRead(proximityPin);

  if (proximityState == HIGH && !isCountingDown) {
    // Nyalakan buzzer dan tampilkan pesan saat pertama kali deteksi objek
    tone(buzzerPin, 1000);    // Nyalakan buzzer selama 1 detik
    delay(1000);              // Tunggu 1 detik
    noTone(buzzerPin);        // Matikan buzzer

    // Mulai countdown
    isCountingDown = true;
    countdownTime = 30;
  }
  
  if (isCountingDown) {
    // Tampilkan countdown di layar OLED
    display.clearDisplay();
    display.setCursor(10, 25);
    display.setTextSize(2);
    display.print("Timer: ");
    display.print(countdownTime);
    display.display();
    delay(1000); // Menunggu 1 detik

    countdownTime--;

    // Jika countdown selesai
    if (countdownTime < 0) {
      // Bunyikan buzzer sesuai instruksi
      tone(buzzerPin, 1000); // Nyalakan buzzer selama 3 detik
      delay(2000);
      noTone(buzzerPin); // Matikan buzzer selama 2 detik
      delay(1000);
      tone(buzzerPin, 1000); // Nyalakan buzzer selama 3 detik
      delay(2000);
      noTone(buzzerPin); // Matikan buzzer selama 2 detik
      delay(1000);
      tone(buzzerPin, 1000); // Nyalakan buzzer selama 3 detik
      delay(2000);
      noTone(buzzerPin); // Matikan buzzer selama 2 detik
      delay(1000);
      noTone(buzzerPin); // Matikan buzzer

      // Reset countdown
      isCountingDown = false;
      display.clearDisplay();
      display.setCursor(10, 20);
      display.print("Thank you");
      display.display();
    }
  } else {
    // Jika tidak ada objek atau countdown selesai, pastikan buzzer mati
    noTone(buzzerPin);
    delay(100);
  }
}