#include <WiFi.h>
#include <FS.h>
#include "FastLED.h" 
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "Tree";
const char *password = "Buckeye1";

#define NUM_LEDS 144

int pattern = 8;
int wait = 65;
char html[2500];
int br = 255;
long randNumber;
int TwinkleRate = 5;
int color = 0;
long Lights[NUM_LEDS];

uint8_t gHue = 0; // rotating "base color" used by many of the patterns


#define BRIGHTNESS = br;

 int r = 255; 
 int g = 0;
 int b = 0;
 int a = 0;

unsigned long counter;
boolean breakFlag = false;
unsigned long breakTimer;

AsyncWebServer server(80);



CRGB leds[NUM_LEDS];
//int request->contentType


void createBreak() {
  breakFlag = true;
  breakTimer = millis();
  
  Serial.print( "breakFlag= ");
  Serial.println( breakFlag );
  while ((millis() - breakTimer) < 5000UL) {
    yield();
  }
  breakFlag = false;
}



void handleTest(){
  Serial.println("handleTest");
  
  pattern = 1;
}


void handleFade(){
  Serial.println("handleFade");
  pattern = 2;
}

void handleWhite(){
  Serial.println("handleFade");
  pattern = 3;
}
void handleBlue(){
  Serial.println("handleFade");
  pattern = 4;
if(color == 3){
    color = 1;
     
  }else{
    color += 1;
  }

  
}
void handleBright(){
  Serial.println("High Brightness");
  pattern = 5;
}

void handleMedium(){
  Serial.println("Low Brightness");
  pattern = 6;
}



void handleDim(){
  Serial.println("Low Brightness");
  pattern = 7;
}

void handleOFF(){
  Serial.println("handleOFF");
  Serial.print("Time: ");
  Serial.println(millis());

  pattern = 8;
}

void handleRainbow(){
  Serial.println("Low Brightness");
  pattern = 9;
}

void handleTest2(){
  Serial.println("test");
  pattern = 10;

}

void handleReg(){
  Serial.println("Regular");
  pattern = 11;

}

void handleRainbow15(){
  Serial.println("13");
  pattern = 13;

}

void handleRainbow5(){
  Serial.println("14");
  pattern = 14;

}


void handleFadeFast(){
  Serial.println("15");
  pattern = 15;
}

void handleRoot() {

 /* Dynamically generate the LED toggle link, based on its current state (on or off)*/
 int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  char ledText[80];
// Build an HTML page to display on the web-server root address
//    <meta http-equiv='refresh' content='10'/>\

  snprintf ( html, 2500,

"<html>\
  <head>\
    <title>Christmas Tree Lights</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; font-size: 5em; Color: #000000; }\
      h1 { Color: #AA0000; }\
      .button{font-size:48px; width:800px; color: red; text-align: center;'}\
    </style>\
  </head>\
  <body>\
    <h1>Christmas Tree Lights</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <form action=\"Test\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Test\" class='button'> </form>\
    <form action=\"Fade\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Fade Through Colors\" class='button'> </form>\
    <form action=\"White\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"White\" class='button'> </form>\
    <form action=\"Blue\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Color Select\" class='button'> </form>\
    <form action=\"Bright\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"High Brightness\" class='button'> </form>\
    <form action=\"Medium\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Medium Brightness\" class='button'> </form>\
    <form action=\"Dim\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Low Brightness\" class='button'> </form>\
    <form action=\"OFF\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"OFF/Clear\" class='button'> </form>\
    <form action=\"Rainbow\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Halloween Twinkle\" class='button'> </form>\
    <form action=\"Test2\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Rainbow 30 (aka Test2)\" class='button'> </form>\
    <form action=\"Reg\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Regular\" class='button'> </form>\
    <form action=\"13\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Rainbow 10\" class='button'> </form>\
    <form action=\"14\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Rainbow 1\" class='button'> </form>\
    <form action=\"15\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Fade Fast\" class='button'> </form>\
    <form action=\"16\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Red\" class='button'> </form>\
    <form action=\"17\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Green\" class='button'> </form>\
    <form action=\"18\" method=\"GET\" > <INPUT TYPE=\"submit\" VALUE=\"Clear\" class='button'> </form>\
  </body>\
</html>",

    hr, min % 60, sec % 60,
    ledText
  );

}

void setup(){
  Serial.begin(115200);
 
  FastLED.addLeds<WS2813, 3, RGB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(12,25000);
  Serial.begin(115200);
  FastLED.setTemperature( UncorrectedTemperature );
  
  
  WiFi.softAP(ssid, password);
 
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
 
  server.on("/Test", HTTP_GET, [](AsyncWebServerRequest *request){
      handleTest();
      request->send( 200, "text/html", html );
  });

  server.on("/Fade", HTTP_GET, [](AsyncWebServerRequest *request){
    handleFade();
    request->send( 200, "text/html", html );
    
  });


  server.on("/Reg", HTTP_GET, [](AsyncWebServerRequest *request){
    handleReg();
    request->send( 200, "text/html", html );
    
  });
  
  server.on("/White", HTTP_GET, [](AsyncWebServerRequest *request){
    handleWhite();
    request->send( 200, "text/html", html );
    
  });
  server.on("/Blue", HTTP_GET, [](AsyncWebServerRequest *request){
    handleBlue();
    request->send( 200, "text/html", html );
    
  });
  server.on("/Bright", HTTP_GET, [](AsyncWebServerRequest *request){
    handleBright();
    request->send( 200, "text/html", html );
    
  });
  server.on("/Dim", HTTP_GET, [](AsyncWebServerRequest *request){
    handleDim();
    request->send( 200, "text/html", html );
    
  });

  server.on("/Rainbow", HTTP_GET, [](AsyncWebServerRequest *request){
    handleRainbow();
    request->send( 200, "text/html", html );
    
  });

  server.on("/Medium", HTTP_GET, [](AsyncWebServerRequest *request){
    handleMedium();
    request->send( 200, "text/html", html );
    
  });
  
  server.on("/OFF", HTTP_GET, [](AsyncWebServerRequest *request){
    handleOFF();
    request->send( 200, "text/html", html );
    
  });

  server.on("/13", HTTP_GET, [](AsyncWebServerRequest *request){
    handleRainbow15();
    request->send( 200, "text/html", html );
    
  });

  server.on("/14", HTTP_GET, [](AsyncWebServerRequest *request){
    handleRainbow5();
    request->send( 200, "text/html", html );
    
  });

    server.on("/Test2", HTTP_GET, [](AsyncWebServerRequest *request){
    handleTest2();
    request->send( 200, "text/html", html );
    
  });

    server.on("/15", HTTP_GET, [](AsyncWebServerRequest *request){
    handleFadeFast();
    request->send( 200, "text/html", html );
    
  });
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){

    handleRoot();

    request->send(200, "text/html",html);
  });

 
  server.begin();
}
int first = 1; 
int Count = 0;

void loop(){
  
  switch (pattern) {
  
  case 1:    // your hand is close to the sensor
    
   
    for(int z = 0; z <11; z++){
    int p = z * 50;
    leds[p] = CRGB::Red; 
    }
   
   
   FastLED.show();
   break;
  
  case 2:
     EVERY_N_MILLISECONDS( wait ){


if (a==0){
    if( b<255){            //check if green = 255
        b += 1;
    }else {                       //after blue is 255 
        if( r>0){
            r-=1;
        }else {                    //after red is 0
            if( g<255){
                g+=1;
            }else {  
                a=1;
            }
        }
    }
}else{    //else a not = 0
    if( b>0){            //check if green = 255
        b -= 1;
    }else {                       //after blue is 255 
        if( r<255){
            r+=1;
        }else {                    //after red is 0
            if( g>0){
                g-=1;
            }else {  
                a=0;
            }
        }
    }
}

      fill_solid( leds, NUM_LEDS,CRGB(r,g,b));
      FastLED.show();
}
  
   break;
   
   case 3:
   
   fill_solid( leds, NUM_LEDS, CRGB::White);
   FastLED.show();
   break;
   case 4:

   if(color == 1){
   fill_solid( leds, NUM_LEDS, CRGB(255,0,0));
}else if (color == 2){
   fill_solid( leds, NUM_LEDS, CRGB(0,255,0));
 }else if(color == 3){
  
   fill_solid( leds, NUM_LEDS, CRGB(0,0,255));
 }

FastLED.show();
   break;
  
   case 5:
   
   
   LEDS.setBrightness(255);
   FastLED.show();
    
   break;
   
   case 6:
   //Serial.println("Im here at case 6");
   
   LEDS.setBrightness(155); 
   FastLED.show();
   break;
   
   
   case 7:

   LEDS.setBrightness(55); 
   FastLED.show();
   break;
   
   case 8:
   
   fill_solid( leds, NUM_LEDS, CRGB::Black);
   FastLED.show();
   break;

   case 9:
//delay(5);
   if(first == 1) {
     
     fill_solid( leds, NUM_LEDS, CRGB(255,55,0));
     FastLED.show();
     LEDS.setBrightness(200);
     FastLED.setTemperature( Tungsten40W );
     for(int m = 0; m <NUM_LEDS; m++){
       Lights[m] = 170;
       Serial.print("Fill lights array: ");
       Serial.println(m);
     }
     
     first = 0;
   
   }  
   
EVERY_N_MILLISECONDS( 10 ){

     randNumber = random(0,NUM_LEDS-1);
     Serial.print("Random Number: ");
     Serial.println(randNumber);
     
     Lights[randNumber] -=TwinkleRate;

      for(int m = 0; m <NUM_LEDS; m++){
       if(Lights[m] != 170){
     Serial.print("Value Of Lights: ");
     Serial.print(m);
     Serial.print(": ");
     Serial.println(Lights[m]);
          if (Lights[m]<TwinkleRate+2){
             Lights[m] = 170;
             leds[m].maximizeBrightness(Lights[m]);
             Serial.print("This Should be 255: ");
             Serial.println(m);
             Serial.print("Lights[M] 255: ");
             Serial.println(Lights[m]);


          }else{
              Lights[m] -=TwinkleRate;
            }
           leds[m].maximizeBrightness(Lights[m]); 
          }
          
       }
       FastLED.show();
     }

break;

   case 10:
   EVERY_N_MILLISECONDS( 30 ){
   fill_rainbow( leds, NUM_LEDS, gHue, 7);
   gHue++;
   FastLED.show();
   }
break;
 
 case 11:
   for(int c = 0; c <100; c++){
       int d = c * 5;
       leds[d] = CRGB(255,20,147);
       leds[d+1] = CRGB(255,55,0);
       leds[d+2] = CRGB::Green;
       leds[d+3] = CRGB::Blue;
       leds[d+4] = CRGB::Red;
   }
   FastLED.show();
break;  

   case 13:
   EVERY_N_MILLISECONDS( 10 ){
   fill_rainbow( leds, NUM_LEDS, gHue, 7);
   gHue++;
   FastLED.show();
   }
break;

   case 14:
   EVERY_N_MILLISECONDS( 5 ){
   fill_rainbow( leds, NUM_LEDS, gHue, 7);
   gHue++;
   FastLED.show();
   }
break;

  case 15:
     EVERY_N_MILLISECONDS( 5 ){


if (a==0){
    if( b<255){            //check if green = 255
        b += 1;
    }else {                       //after blue is 255 
        if( r>0){
            r-=1;
        }else {                    //after red is 0
            if( g<255){
                g+=1;
            }else {  
                a=1;
            }
        }
    }
}else{    //else a not = 0
    if( b>0){            //check if green = 255
        b -= 1;
    }else {                       //after blue is 255 
        if( r<255){
            r+=1;
        }else {                    //after red is 0
            if( g>0){
                g-=1;
            }else {  
                a=0;
            }
        }
    }
}

      fill_solid( leds, NUM_LEDS,CRGB(r,g,b));
      FastLED.show();
}
  
   break;
   
}

}
  
