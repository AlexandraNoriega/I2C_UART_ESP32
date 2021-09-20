// <https://www.arduino.cc/en/Tutorial/MasterWriter>
// <https://www.arduino.cc/en/Tutorial/MasterReader>
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI sub device

// This code receive and request data from master device (ESP32)

// #define MICON_ESP32              // undefined if Arduino

#ifdef MICON_ESP32
#   error "I2C Sub functionality is not implemented in ESP32 Arduino Core"
#   error "If you want to implement, see https://www.arduino.cc/reference/en/libraries/esp32-i2c-slave/"
#endif

#define ADDRESS 0x0A //Slave Address, we can check before using adressdevice.ino

#include <Wire.h>

void setup() {
    Wire.begin(ADDRESS);            // join i2c bus with address
    Wire.onReceive(receiveEvent);   // register event
    Wire.onRequest(requestEvent);   // register event

    Serial.begin( 115200 );         // start serial for output
    while(!Serial);                 // Leonardo: wait for serial monitor
    Serial.println("\nI2C Sub");
    for(int i=2;i<=9;i++){          // Initialize the output pins 
    pinMode(i, OUTPUT);
    }
}

void loop(void) {
    delay(100);
}

// function that executes whenever data is received from main
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
    if( howMany == 0 ) {
        return;
    }

    Serial.print("receiveEvent: ");

    while( 1 < Wire.available() ) { // loop through all but the last
        char c = Wire.read();       // receive byte as a character
        Serial.print(c);            // print the character
    }
    int x = Wire.read();            // receive byte as an integer
    //shows integer as binary with leds (D2(LSB)-D9(MSB))
    for(int i=2; i<=9; i++){        // Cycle to see what LEDs i turn on
    digitalWrite(i, x%2);           // Division by 2 module to see if led on or off
    x=x/2;                          // Divide the quotient by 2 for each cycle
    }
}

// function that executes whenever data is requested by main
// this function is registered as an event, see setup()
void requestEvent(void) {
    Serial.println("requestEvent: ");

    Wire.write("hello\n");          // respond with message of 6 bytes
    // as expected by main
}
