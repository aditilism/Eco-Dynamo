#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2
int p1 = 13;
int p2 = 6;

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
OneWire oneWire(ONE_WIRE_BUS);	

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
void setup() {

  sensors.begin();	// Start up the library
  Serial.begin(9600);
  lcd.init();
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on
  
  // Print a message on both lines of the LCD.
  lcd.setCursor(0,0);   //Set cursor to character 2 on line 0
  lcd.print("Peltier Thermal power");
  
  lcd.setCursor(0,1);   //Move cursor to character 2 on line 1
  lcd.print("Extractor");
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  delay(1000);
}
char string = "";
void loop() {
  sensors.requestTemperatures(); // Send the command to get temperatures

  // Get the temperature in Celsius and store it in a variable
  float temperatureC = sensors.getTempCByIndex(0);
  int peltierOut = analogRead(A0);
  // Clear the previous temperature reading from the LCD
  lcd.clear();

  // Set the cursor to the beginning of the first line
  lcd.setCursor(0,0);

  // Print the temperature in Celsius to the LCD
  lcd.print("Temp: ");
  lcd.print(temperatureC);
  lcd.print((char)223); // Degree symbol
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Power: ");
  lcd.print(peltierOut);
  lcd.print(" Mv");
  if(peltierOut>50){
    lcd.clear();
    lcd.print("charging Smartphone");
    lcd.print(" -> -> ");
    digitalWrite(p1,HIGH);
    digitalWrite(p2,HIGH);

  }
    digitalWrite(p1,LOW);
    digitalWrite(p2,LOW);
  // delay(50);
}
