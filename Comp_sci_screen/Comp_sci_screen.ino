#include <Wire.h>
#include <bb_uc1701.h>

#define DC_PIN 4
#define RESET_PIN 6
#define LED_PIN 5
#define CS_PIN 10

// 16x16 (2 bytes x 16 lines) Arrow pointing up


const uint8_t ucSquare[] PROGMEM = {
  0xff,0xff,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,
  0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0xff,0xff
};
int led = 0;

void setup() {
  uc1701Init(DC_PIN,RESET_PIN,LED_PIN, CS_PIN, false, false, 4000000L);
  uc1701Fill(0);
//  pinMode(3, INPUT);
//  pinMode(2, INPUT);
//  Wire.begin(9); 
//  Wire.onReceive(receiveEvent);
//  Serial.begin(9600);

  Serial.begin(9600);  // start serial for output
  
}
char ty="";
char tty="";
char c = "";
int x = -6;
int y = 0;
int count = 0;
bool show = false;
void loop() {
  Wire.begin();        // join i2c bus (address optional for master)
  Wire.requestFrom(8, 8);    // request 6 bytes from peripheral device #8


  while (Wire.available()) { // peripheral may send less than requested
    c = Wire.read(); // receive a byte as character
    if(c != '?'&&c!=ty){
      Serial.println(c, HEX);
//      Serial.println(c);
      tty=ty;
      ty=c;
      if(c==(char)0x40){
        c='`';
      }else if(c==(char)0x3C){
        c='-';
      }else if(c==(char)0x5F){
        c='=';
      }else if(c==(char)0x5D){
        c='[';
      }else if(c==(char)0x5E){
        c=']';
      }else if(c==(char)0x5B){
        c=';';
      }else if(c==(char)0x3A){
        c='"';
      } else if(c==(char)0x3B){
        c=',';
      } else if(c==(char)0x3D){
        c='.';
      }else if(c==(char)0x3E){
        c='/';
      }else if(c==(char)0x15){
        x-=6;
        show = false;
        break;
      }else if(c==(char)0x16){
        x+=6;
        show = false;
        break;
      } else if(c==(char)0x17){
        y--;
        show = false;
        break;
      } else if(c==(char)0x18){
        y++;
        show = false;
        break;
      }else if(c==(char)0x1E){
        y++;
        x=0;
        count=0;
        show = false;
        break;
      } else if(c==(char)0x3){
        show=false;
        break;
      }
      
      if(count > 0){
        x+=6;
      }
      show = true;
    } else{
      show = false;
    }
    break;
  }
  Wire.end();
  if(c == (char)0x1C){
     uc1701Fill(0);
//     Serial.println("Cleared");
     show = false;
     x=-6;
     y=0;
  }
  if(show){
    char thing[1] = {c};
    thing[2]=' ';
    thing[1]=' ';
    thing[3]=' ';
    thing[4]=' ';
    uc1701WriteString(x,y,thing, FONT_SMALL,0);
//    Serial.println(thing);
    count = 1;
  }
  if(x>124&&y==0){
    x=0;
    y++;
    count=0;
  }else if(x>118){
    x=0;
    y++;
    count = 0;
  }
  if(y==8){
    y=0;
    x=0;
    count=0;
    uc1701Fill(0);
  }
  
//  Serial.println("hello");
//  delay(500);
}
