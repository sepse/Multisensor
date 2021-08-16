#include <LiquidCrystal.h>
#include <DHT.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define DHTPIN 8
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino
int led = 6;           // the PWM pin the LED is attached to, green
int brightness = 0;    // how bright the LED is
int fadeAmount = 10;    // how many points to fade the LED by
#define redLed 7
#define grnLed 9
#define ylLed 13
unsigned long previousMillis[3]; //[x] = number of leds

int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
const int OUTPUT_PIN = 10; //attach buzzer to pin 10

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Temp mrena ");
  lcd.setCursor(0, 1);
  lcd.print("Lageshtia ");
  pinMode(redLed, OUTPUT);   
  pinMode(grnLed, OUTPUT);
  pinMode(ylLed, OUTPUT);
  pinMode(OUTPUT_PIN, OUTPUT); //buzzerpin
}

void loop()
{
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    lcd.setCursor(11, 0);
    lcd.print(temp,0);
    lcd.print("'C");
    lcd.setCursor(10,1);
    lcd.print(hum,0);
    lcd.print("%");
    analogWrite(led, brightness);
    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;
    // reverse the direction of the fading at the ends of the fade:
    if (brightness <= 0 || brightness >= 255) 
    fadeAmount = -fadeAmount;
    delay(50); //WARNING: original was 2000
    BlinkLed(redLed, 1000, 0);   //BlinkLed( which led, interval, one of the stored prevMillis
    BlinkLed(grnLed, 30, 1);  //last parameters must be different for each led
    BlinkLed(ylLed, 500, 2);
}
   
void BlinkLed (int led, int interval, int array){   
  
  //(long) can be omitted if you dont plan to blink led for very long time I think
   if (((long)millis() - previousMillis[array]) >= interval){ 
   
    previousMillis[array]= millis(); //stores the millis value in the selected array
   
    digitalWrite(led, !digitalRead(led)); //changes led state
  }
 }
