
#include <SPI.h>
#include <WiFiNINA.h>
#include <DHT.h>
#include <DHT_U.h>
#include <DFRobot_RGBLCD1602.h>
DFRobot_RGBLCD1602 lcd(/*lcdCols*/16,/*lcdRows*/2);
#include <Wire.h>
#include "arduino_secrets.h"
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


//inserisci i tuoi dati sensibili nella scheda Segreto/arduino_secrets.h
char ssid[] = SECRET_SSID;        // SSID di rete (nome)
char pass[] = SECRET_PASS;        // la password di rete (utilizzare per WPA o utilizzare come chiave per WEP)
int keyIndex = 0;                 // il numero di indice della chiave di rete (necessario solo per WEP)
int status = WL_IDLE_STATUS;

WiFiServer server(80);




void setup() {
  //Inizializza seriale e attendi l'apertura della porta:
  Serial.begin(9600);
  lcd.init();
  dht.begin();

  while (!Serial) {
    //; attendere che la porta seriale si connetta. Necessario solo per la porta USB nativa
  }

  // controlla il modulo WiFi:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Comunicazione con il modulo WiFi non riuscita!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Aggiornare il firmware");
  }

  //tentativo di connessione alla rete WiFi:
  while (status != WL_CONNECTED) {
    Serial.print("Tentativo di connessione a SSID:");
    Serial.println(ssid);
    //Connettersi alla rete WPA/WPA2. Modificare questa riga se si utilizza una rete aperta o WEP:
    status = WiFi.begin(ssid, pass);

    //attendere 10 secondi per la connessione:
    delay(10000);
  }
  server.begin();
  //ora sei connesso, quindi stampa lo stato:
  printWifiStatus();
}






void loop() {
  // ascolta i client in arrivo
  WiFiClient client = server.available();
  if (client) {
    Serial.println("nuovo cliente");


    //Una richiesta HTTP termina con una riga vuota
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);


        //se sei arrivato alla fine della riga (hai ricevuto una nuova riga)
        //carattere) e la riga è vuota, la richiesta HTTP è terminata,
        //in modo da poter inviare una risposta
        if (c == '\n' && currentLineIsBlank) {
          //  Inviare un'intestazione di risposta HTTP standard
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

          // uscita il valore di ogni pin di ingresso analogico
          for (int analogChannel = 0; analogChannel < 4; analogChannel++) {
            
            int sensorReading = analogRead(analogChannel);

            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {

          //    stai iniziando una nuova linea
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          //    hai ottenuto un carattere sulla riga corrente
          currentLineIsBlank = false;
        }
      }
    }
    //dare al browser web il tempo di ricevere i dati
    delay(1);

    //chiudere la connessione:
    client.stop();
    Serial.println("client disconnesso");
  }
}


void printWifiStatus() {
  //stampare l'SSID della rete a cui si è collegati:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  //stampa l'indirizzo IP della tua bacheca:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  //stampare la potenza del segnale ricevuto:
  long rssi = WiFi.RSSI();
  Serial.print("potenza del segnale (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");


  float h = dht.readHumidity();
  float t = dht.readTemperature();

  SensoreMetanoValore = analogRead(200 + (4800 * SensoreMetano) / 1023);
  SensoreAlcoolValore = analogRead(0.05 + (9.8 * SensoreMetano) / 1023);
  SensoreMonossidoValore = analogRead(20 + (188 * SensoreMetano) / 1023);
  SensoreIdrogenoValore = analogRead(1 + (99 * SensoreMetano) / 1023);

  Serial.print("Francesco Bevilacqua");
  Serial.println("   ");
  Serial.println("   ");
  Serial.println("- - - - - - - - o - - - - - - - -");
  Serial.print("- Metano            (ppm): ");
  Serial.println(SensoreMetanoValore, 1);
  Serial.print("- Monossido di C.   (ppm): ");
  Serial.println(SensoreMonossidoValore, 1);
  Serial.print("- Idrogeno          (ppm): ");
  Serial.println(SensoreIdrogenoValore, 1);
  Serial.print("- Alcool          (mmg/L): ");
  Serial.println(SensoreAlcoolValore, 1);
  Serial.println("- - - - - - - - o - - - - - - - -");
  Serial.print("- Umidita'            (%): ");
  Serial.println(h, 1);
  Serial.print("- Temperatura         (C): ");
  Serial.println(t, 1);
  Serial.println("- - - - - - - - o - - - - - - - -");
  Serial.println("----------------o----------------");

  if (Serial.available()) {
    lcd.clear();
    while (Serial.available() > 0) {
      lcd.write(Serial.read());
    }
  }
  delay(1000);

}
