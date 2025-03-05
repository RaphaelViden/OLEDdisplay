#include <Arduino.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


#include <RoboEyes.h>
roboEyes roboEyes;

void animateText(const char *text) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 25);

  String tempText = ""; // Variabel untuk menyimpan teks sementara
  for (int i = 0; text[i] != '\0'; i++) {
      tempText += text[i];  // Tambahkan huruf ke string
      display.clearDisplay(); // Bersihkan layar sebelum menggambar ulang
      display.setCursor(0, 0);
      display.print(tempText); // Cetak teks yang sudah terbentuk
      display.display();
      delay(150);  // Waktu jeda antar huruf
  }
  delay(1000); // Tunggu sebentar sebelum lanjut ke loading
}

void animateLoading(const char *text) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(33, 25);
  display.print(text);
  display.display();

    
    for (int i = 0; i < 20; i++) {
        display.fillCircle(60 + (i % 3) * 6, 45, 2, SSD1306_WHITE);
        display.display();
        delay(150);
        display.fillCircle(60 + (i % 3) * 6, 45, 2, SSD1306_BLACK);
        display.display();
    }
}


void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C or 0x3D
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  // display.setTextSize(1);
  // display.setTextColor(SSD1306_WHITE);
  // display.setCursor(0, 0);
  // display.println(F("Hello, OLED!"));

  // display.display();
  animateText("Hallo Rafael Videntio");
  animateLoading("initiating"); 

  roboEyes.begin(SCREEN_WIDTH, SCREEN_HEIGHT, 100);
  roboEyes.setAutoblinker(ON, 3, 2); // Start auto blinker animation cycle -> bool active, int interval, int variation -> turn on/off, set interval between each blink in full seconds, set range for random interval variation in full seconds
  roboEyes.setIdleMode(ON, 2, 2); // Start idle animation cycle (eyes looking in random directions) -> turn on/off, set interval between each eye repositioning in full seconds, set range for random time interval variation in full seconds
  
}


void loop() {
  roboEyes.update();
} 

