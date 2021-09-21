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

#define RXD2 16
#define TXD2 17

// Check using using adressdevice.ino
#define ADDRESS_SUB_ARDUINO 0x0A
#define ADDRESS_SUB_LCD     0x3F

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;

String msg="";
static byte x = 0;
int serialc;
char c;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(ADDRESS_SUB_LCD, lcdColumns, lcdRows); 

void setup() {
#ifdef MICON_ESP32
    Wire.begin( PIN_SDA, PIN_SCL ); // initialize esp32 as master
#else
    Wire.begin();
#endif

    Serial.begin( 115200 );         // start serial for output
    Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
    // initialize LCD
    lcd.init();
    // turn on LCD backlight                      
    lcd.backlight();
}

void loop(void) {
    writer();
    reader();
    printlcd();

    Serial.write("Random Number is ");
    Serial.print(serialc);
    Serial.write(" in ASCII is ");
    Serial.print(msg);  
    Serial.write("\n");

   if(Serial2.available()){
     Serial.write(Serial2.read());  
   }

    delay(500);
    msg="";
}

void writer(void) {
    //Serial.println("writer: ");
    
    Wire.beginTransmission(ADDRESS_SUB_ARDUINO);    // transmit to device 
    //Wire.write("x is ");            // sends five bytes
    Wire.write(x);                   // sends one byte
    Wire.endTransmission();         // stop transmitting
    x++;
}

void reader(void) {
    Serial.print("reader: ");

    Wire.requestFrom(ADDRESS_SUB_ARDUINO, 1);   // request 1 bytes from sub device

    while( Wire.available() ) {     // sub may send less than requested
        c = Wire.read();       // receive a byte as character
        Serial.print(c);            // print the character
        msg=msg+c;
    }
    serialc = c -' '+32; // random number
}

void printlcd(void){
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  lcd.print("SEND: ");
  lcd.print(x);
  lcd.setCursor(0, 1);
  lcd.print("RECEIVE: ");
  lcd.print(serialc);
  delay(500);
  lcd.clear();
}
