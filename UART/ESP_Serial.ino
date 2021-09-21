 #define RXD2 16
 #define TXD2 17
 void setup() {
   Serial.begin(115200);
   Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
   delay(1000);
   Serial.println("Loopback program started");
 }
 void loop() {
   if(Serial.available()){
     Serial.write("-");
     Serial2.write(Serial.read());  
   }
   if(Serial2.available()){
     Serial.write(".");
     Serial.write(Serial2.read());  
   }
 }
