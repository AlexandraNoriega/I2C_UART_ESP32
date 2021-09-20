// <https://www.arduino.cc/en/Tutorial/MasterWriter>
// <https://www.arduino.cc/en/Tutorial/MasterReader>
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI sub device

// This code send and receive data from slave device

#define MICON_ESP32                 // undefined if Arduino

#ifdef MICON_ESP32
#   define PIN_SDA  21               // GPIO21
#   define PIN_SCL  22               // GPIO22
#endif

// Check using using adressdevice.ino
#define ADDRESS_SUB 0x0A

#include <Wire.h>

void setup() {
#ifdef MICON_ESP32
    Wire.begin( PIN_SDA, PIN_SCL ); // initialize esp32 as master
#else
    Wire.begin();
#endif

    Serial.begin( 115200 );         // start serial for output
    while(!Serial);                 // Leonardo: wait for serial monitor
    Serial.println("\nI2C Main");
}

void loop(void) {
    writer();
    reader();
    delay(500);
}

void writer(void) {
    Serial.println("writer: ");
    
    static byte x = 0;
    Wire.beginTransmission(ADDRESS_SUB);    // transmit to device 
    //Wire.write("x is ");            // sends five bytes
    Wire.write(x);                   // sends one byte
    Wire.endTransmission();         // stop transmitting
    Serial.println(x);
    x++;
}

void reader(void) {
    Serial.print("reader: ");

    Wire.requestFrom(ADDRESS_SUB, 6);   // request 6 bytes from sub device

    while( Wire.available() ) {     // sub may send less than requested
        char c = Wire.read();       // receive a byte as character
        Serial.print(c);            // print the character
    }
}
