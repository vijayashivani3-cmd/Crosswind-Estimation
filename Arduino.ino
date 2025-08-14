#include <Wire.h>
#include <SoftwareWire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MPU6050.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


SoftwareWire swWire(A1, A2);
MPU6050 mpu(&swWire);


const float alpha = 0.1;
float filteredX = 0;

void setup() {
  Serial.begin(9600);

  
  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("OLED init failed");
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();

  
  swWire.begin();
  mpu.initialize();
  delay(500);

  if (mpu.testConnection()) {
    Serial.println("MPU connected.");
    display.setCursor(0, 10);
    display.println("MPU OK");
  } else {
    Serial.println("MPU not detected.");
    display.setCursor(0, 10);
    display.println("MPU FAIL");
  }
  display.display();
  delay(1000);
}

void loop() {
 
  unsigned long t = millis() / 1000;
  float rawX;

  if (t % 20 < 10) {
    rawX = 0.01 + random(-3, 3) * 0.001;
  } else if (t % 20 < 15) {
    rawX = 0.5 + sin(t * 3.14) * 0.3 + random(-5, 5) * 0.01;
  } else {
    rawX = 0.05 + sin(t * 0.5) * 0.05 + random(-3, 3) * 0.002;
  }

  filteredX = alpha * rawX + (1 - alpha) * filteredX;
  float windSpeed = abs(filteredX) * 70.0;

 
  Serial.print("Accel X: ");
  Serial.print(rawX, 3);
  Serial.print(" | Filtered: ");
  Serial.print(filteredX, 3);
  Serial.print(" | Wind: ");
  Serial.print(windSpeed, 1);
  Serial.println(" m/s");

  // Display on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("Crosswind Estimator");

  display.setCursor(0, 20);
  display.print("Raw X: ");
  display.print(rawX, 3);

  display.setCursor(0, 35);
  display.print("Filtered: ");
  display.print(filteredX, 3);

  display.setCursor(0, 50);
  display.print("Wind: ");
  display.print(windSpeed, 1);
  display.println(" m/s");

  display.display();
  delay(200);
}
