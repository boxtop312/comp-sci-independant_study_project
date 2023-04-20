#include <PS2KeyAdvanced.h>
#include <Wire.h>
#define DATAPIN 4
#define IRQPIN  3

uint16_t c;
int slaveAddress = 9;
PS2KeyAdvanced keyboard;
bool led = LOW;


void setup( )
{
  // Configure the keyboard library
  keyboard.begin( DATAPIN, IRQPIN );

  pinMode(LED_BUILTIN, OUTPUT);
  Wire.begin(8); 
  Wire.onRequest(requestEvent);
}

void requestEvent() {
//  Wire.write("hello ");
  if( keyboard.available( ) ){
//    if(c>0){
      c = keyboard.read( );
      d = keyboard.read();
      Wire.write(c); // sends x
//    }
  }else{
  Wire.write(c); // sends x
  }

  // as expected by master

}

void loop() {
  // put your main code here, to run repeatedly:
//  if( keyboard.available( ) ){
//    c = keyboard.read( );
//
//  }
}
