

// Kicco972  // 2022
// modello "AA1", Analizzatore Ambientale

#include <DHT.h>
#include <DHT_U.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

int SensoreMetano = A0;
float SensoreMetanoValore = 0;
int SensoreAlcool = A1;
float SensoreAlcoolValore = 0;
int SensoreMonossido = A2;
float SensoreMonossidoValore = 0;
int SensoreIdrogeno = A3;
float SensoreIdrogenoValore = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  float h = dht.readHumidity();
  float t = dht.readTemperature();


  SensoreMetanoValore = analogRead(SensoreMetano);
  SensoreAlcoolValore = analogRead(SensoreAlcool);
  SensoreMonossidoValore = analogRead(SensoreMonossido);
  SensoreIdrogenoValore = analogRead(SensoreIdrogeno);

  Serial.print("Prototipo AA1 Controllo ambiente");
  Serial.println("   ");
  Serial.println("   ");
  Serial.println("- - - - - - - - o - - - - - - - -");
  Serial.print("- Metano            (ppm):  ");
  Serial.println(SensoreMetanoValore, 1);
  Serial.print("- Alcool          (mmg/L): ");
  Serial.println(SensoreAlcoolValore, 1);
  Serial.print("- Monossido         (ppm): ");
  Serial.println(SensoreMonossidoValore, 1);
  Serial.print("- Idrogeno          (ppm): ");
  Serial.println(SensoreIdrogenoValore, 1);
  
  Serial.println("- - - - - - - - o - - - - - - - -");
  Serial.print("- Umidita'            (%): ");
  Serial.println(h, 1);
  Serial.print("- Temperatura         (C): ");
  Serial.println(t, 1);
  Serial.println("- - - - - - - - o - - - - - - - -");
  Serial.println("----------------o----------------");


  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" -Metano      ");lcd.print(  SensoreMetanoValore, 1);
  lcd.setCursor(0, 1);
  lcd.print(" -Alcool     ");lcd.print(  SensoreAlcoolValore, 1); 
  lcd.setCursor(0, 2);
  lcd.print(" -Monossido  ");lcd.print(  SensoreMonossidoValore, 1);
  lcd.setCursor(0, 3);
  lcd.print(" -Idrogeno   ");lcd.print(  SensoreIdrogenoValore, 1); 
  
   


  delay(5000);
}
