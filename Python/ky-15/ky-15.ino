#include <DHT.h>
#include <DHT_U.h>

#define DHTpin 2
#define DHTType DHT11
DHT dht = DHT(DHTpin, DHTType);


void setup() {
  
  Serial.begin(9600);

  dht.begin();
}

void loop() {

  float h = dht.readHumidity();

  float t = dht.readTemperature();


  Serial.print(t, 1);
  Serial.print(",");
  Serial.println(h, 1);
  delay(5000);
}