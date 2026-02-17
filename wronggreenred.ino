#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// countdown var
int k = 20;
// var for each trap wire
int kred = 0;
int kgreen = 0;
// set screen width and height
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // set our 2 trap wires pins as input pins
  pinMode(2, INPUT);
  pinMode(4, INPUT);

  // set our buzzer to silent
  analogWrite(19,255);
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.println("Activating");
  display.display(); 
}

void loop() {
  // silence the buzzer
  analogWrite(19,255);
  //read the state of the wires
  kred = digitalRead(2);
  kgreen = digitalRead(4);
  // this section defines what happens when both wires are connected
  if ((kgreen == 1) and (kred == 1) and (k > 0)){
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("");
    display.print("0:00:");
    display.println(k);
    display.display(); 
    analogWrite(19,0);
    analogWrite(15,120);
    delay(200);
    analogWrite(19,255);
    analogWrite(15,0);
    k = k - 1;
    delay(800);
  }
  //this sections defines what happens if 1 of the wires is cut
  if (((kgreen == 1 and kred == 0) or (kgreen == 0 and kred == 1)) and k > 0) {
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("");
    display.print("0:00:");
    display.println(k);
    display.display(); 
    analogWrite(19,0);
    analogWrite(15,120);
    delay(100);
    analogWrite(19,255);
    analogWrite(15,0);
    delay(400);
    //digitalWrite(19,LOW);
    k = k - 1;
    

  }
  //  this section defines what happens if both wires are cut
  if (kgreen == 0 and kred == 0 and k > 0){
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("");
    display.print("0:00:");
    display.println(k);
    display.display(); 
    analogWrite(19,0);
    analogWrite(15,120);
    delay(50);
    analogWrite(19,255);
    analogWrite(15,0);
    delay(200);
    
    //digitalWrite(19,LOW);
    k = k - 1;
    

  }
  //this section defines what happens if the timer reaches zero
  if (k == 0){
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("");
    display.print("0:00:");
    display.println(k);
    display.display(); 
    analogWrite(19,0);
    analogWrite(15,120);
    delay(5000);
    analogWrite(19,255);
    analogWrite(15,0);
    k = 20;
    delay(800);
  }
  Serial.print("red");
  Serial.println(kred);
  Serial.print("green");
  Serial.println(kgreen);
}