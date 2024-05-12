
void setup() {
Serial.begin(9600);
pinMode(13,OUTPUT);

}

void loop() {
char commando = Serial.read();
if (commando == 'a') {
    digitalWrite(13, HIGH);
}

if (commando == 's') {
    digitalWrite(13, LOW);
}
}