//07.12.2023 Kamil Kosmela
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
 
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define YPIN A0
#define XPIN A1
#define SWPIN 2
#define XG 3
#define XD 4
#define YG 5
#define YD 6
#define Middle 7
boolean gra = false;
int punkty = 0;
int ranNum;
int ranDel;
void setup() {
Serial.begin(115200);
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
  Serial.println(F("SSD1306 allocation failed"));
  for(;;);}
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0, 10);  
display.print("OS X: ");
display.println(analogRead(XPIN));
display.print("OS Y: ");
display.println(analogRead(YPIN));
display.print("Przycisk: ");
display.print(digitalRead(SWPIN));
display.display();

// Display static text

pinMode(SWPIN, INPUT);
digitalWrite(SWPIN, HIGH);
pinMode(XG, OUTPUT);
pinMode(XD, OUTPUT);
pinMode(YG, OUTPUT);
pinMode(YD, OUTPUT);
pinMode(Middle, OUTPUT);
}

void loop() {
Serial.print("\nPrzycisk: ");
Serial.println(digitalRead(SWPIN));
Serial.print("Oś X: ");
Serial.println(analogRead(XPIN));
Serial.print("Oś Y: ");
Serial.println(analogRead(YPIN));
Serial.print("\n\n ");
display.clearDisplay();
display.setCursor(0, 10);  
display.print("OS X: ");
display.println(analogRead(XPIN));
display.print("OS Y: ");
display.println(analogRead(YPIN));
display.print("Przycisk: ");
display.print(digitalRead(SWPIN));
display.display();
if (analogRead(XPIN) == 1023)
{
  digitalWrite(XG, HIGH);
}
else if (analogRead(YPIN) == 0)
{
  digitalWrite(XD, HIGH);
}
else if (analogRead(XPIN) == 0)
{
  digitalWrite(YD, HIGH);
}
else if (analogRead(YPIN) == 1023)
{
  digitalWrite(YG, HIGH);
}
else if (digitalRead(SWPIN) == 0)
{
  digitalWrite(Middle, HIGH);
}


delay(1000);
digitalWrite(XG, LOW);
digitalWrite(YG, LOW);
digitalWrite(XD, LOW);
digitalWrite(YD, LOW);
digitalWrite(Middle, LOW);
if (digitalRead(SWPIN) == 0){ //toggle between  manual and automatic
  gra = true;
}
if (gra == true){
  trybGry();
}
}
void trybGry(){
  gra = true;
  while (gra == true){
  display.clearDisplay();
  display.setCursor(0, 10);  
  display.print("SCORE: ");
  display.print(punkty);
  display.display();
  //Generate random number between 8 and 10
  ranNum=random(3,7);
  //Turn on the LED
  digitalWrite(ranNum, HIGH);
  if (analogRead(XPIN) == 1023  && digitalRead(XG) == HIGH)
  {
    punkty += 1;
  }
  else  if (analogRead(YPIN) == 0  && digitalRead(XD) == HIGH)
  {
    punkty += 1;
  }
  else  if (analogRead(XPIN) == 0  && digitalRead(YD) == HIGH)
  {
    punkty += 1;
  }
  else  if (analogRead(YPIN) == 1023  && digitalRead(YG) == HIGH)
  {
    punkty += 1;
  }
  delay(1000);
  digitalWrite(ranNum, LOW);
  if (digitalRead(SWPIN) == 0){ //toggle between  manual and automatic
    gra = false;
  }
  if (digitalRead(SWPIN) == 0)
  {
    loop();
  }
}}
