/*
 * Code Copiright by Francesco Zola (effezeta88)
 */
#include <Adafruit_NeoPixel.h>
#define SPIN1 7
#define btn_I 26
#define btn_R 28
#define btn_O 27
#define btn_S 24
#define btn_Sd 25
#define BUTTON_BLUE 22
#define BUTTON_RED 23
#define BUTTON_GREEN 24
#define BUTTON_YELLOW 25
#define NUM 4
#define Time_pressed 10
#define animation_time 2000
#define STRIP_NUM 4
#define startd 0 //numberPIN leds start
#define fin 12   //numberPIN leds stop
#define BLUE 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define LED_INTERVAL 12

Adafruit_NeoPixel strip=Adafruit_NeoPixel(50, SPIN1, NEO_GRB + NEO_KHZ800);

int val[NUM];
int status_Led[NUM];
int LED_[NUM*3];
int BTN_[NUM];
bool go = false;
int light = 0;

void setup() {
  Serial.begin(9600);
  load_led(LED_,startd,fin);
  load_btn(BTN_,NUM);
  init_ctrl_btn();
  Inizialize(status_Led,NUM,0);
  Inizialize(val,NUM,0);
  strip.begin();
  strip.show();
  while(!go){
  if(digitalRead(btn_I)==0){
      go=true;
      delay(100);
    }
  }
}
void loop(){  
  
  if(digitalRead(btn_R)==0){
    
    unsigned long time_s = 0;
    bool pressed = true;
    while(time_s<Time_pressed && pressed){
      if (digitalRead(btn_R)==1){
        pressed=false;
      }
      time_s++;
      delay(100);
    }
    if(pressed){
      go=true;
      setup();
    }
  }
  int int_dx = digitalRead(btn_Sd);
  if(int_dx == 1){
    int sum_ = 0;
    for(int i=0;i<NUM;i++){
      if(status_Led[i]==0)
      {
        val[i]= digitalRead(BTN_[i]);  // read input value
        if(val[i]==1){
            status_Led[i]=sum_+1;
            //colorSuspance(sum);  //posizione della strip, i colore della strip
            sum_ = somma(val,NUM);
        }
      }
    }
    int pos =STRIP_NUM;
    for(int i=0;i<NUM;i++){
      ordinaColore(pos);
      pos--;
    }
  }
  /*else{
    if(digitalRead(btn_O)==1){
      light=!light;
      delay(300);
    }
    if(light==0){
      gameLight(strip,STRIP_NUM);
    }
    else{
      Serial.print("scrivi qualcosa");
      //gameWrite();
    }
  }*/
}
void Inizialize(int v[], int size, int val){
  for(int i=0;i<size;i++){
    v[i]=val;
  }
}
void init_ctrl_btn(){
  pinMode(btn_I,INPUT);
  pinMode(btn_R,INPUT);
  pinMode(btn_O,INPUT);
  pinMode(btn_S,INPUT);
  pinMode(btn_Sd,INPUT);
  digitalWrite(btn_I,HIGH);
  digitalWrite(btn_R,HIGH);
  digitalWrite(btn_S,HIGH);
  digitalWrite(btn_O,HIGH);
  digitalWrite(btn_Sd,HIGH);
}
void load_led(int v[], int start, int x){
    for(int i=start;i<x;i++){   
      v[i-start]= i;
      pinMode(v[i],OUTPUT);
      digitalWrite(v[i],HIGH);
    }
}

int somma(int v[],int size){
  int somma=0;
    for(int i=0;i<size;i++){
        somma=somma+v[i];
    }
    return somma;
}

void load_btn(int v[],int size){
    v[0]= BUTTON_BLUE;
    v[1]= BUTTON_RED;
    v[2]= BUTTON_GREEN;
    v[3]= BUTTON_YELLOW;
    for(int i=0;i<size;i++){
      pinMode(v[i],INPUT);
    }
}

void ordinaColore(int pos){
  bool end_=false;
  int i=0;
  while(!end_ && i<STRIP_NUM){
    if(status_Led[i]==pos){
      colora(strip,i,pos);
      switch(i){
        case BLUE:
            digitalWrite(LED_[(pos*3)-1],HIGH);
            break;
        case RED:
            digitalWrite(LED_[(pos*3)-3],HIGH);
            break;
        case GREEN:
            digitalWrite(LED_[(pos*3)-2],HIGH);
            break;
        case YELLOW:
            digitalWrite(LED_[(pos*3)-1],HIGH);
            digitalWrite(LED_[(pos*3)-2],HIGH);
            break;
         default:
            digitalWrite(LED_[(pos*3)-1],LOW);
            digitalWrite(LED_[(pos*3)-2],LOW);
            digitalWrite(LED_[(pos*3)-3],LOW);
            break;
      }
      end_=true;
      i++;
    }
  }
}

void colora(Adafruit_NeoPixel strip, int col,int pos){
  switch(col){
    case BLUE:
        colorWipe(pos,strip,strip.Color(0, 0, 255), 50); // Blue
        break;
    case RED:
        colorWipe(pos,strip,strip.Color(255, 0, 0), 50); // Red
        break;
    case GREEN:
        colorWipe(pos,strip,strip.Color(0, 255, 0), 50); // Green
        break;
    case YELLOW:
        colorWipe(pos,strip,strip.Color(255, 255, 0), 50); // Yellow
        break;
  }
  
}

void colorSuspance(int pos){
    colorWipe(pos,strip,strip.Color(255, 255, 255), 1000);
}
void gameLight(Adafruit_NeoPixel strip, int size_){
  int i;
  colorWipeAll(strip,strip.Color(255, 0, 0), 50); // Red
  
  delay(animation_time);
  colorWipeAll(strip,strip.Color(0, 255, 0), 50); // Green  
 
  delay(animation_time);

  colorWipeAll(strip,strip.Color(0, 0, 255), 50); // Blue
  
  delay(animation_time);
  
  for(i=0;i<size_;i++){
    theaterChase(strip,strip.Color(127, 127, 127), 50); // White
    theaterChase(strip,strip.Color(127,   0,   0), 50); // Red
    theaterChase(strip,strip.Color(  0,   0, 127), 50); // Blue
  }

  for(i=0;i<size_;i++){
    rainbow(strip,20);
  }
  for(i=0;i<size_;i++){
      rainbowCycle(strip,20);
  }
   for(i=0;i<size_;i++){
      theaterChaseRainbow(strip,50);
   }
}

// Fill the dots one after the other with a color
void colorWipeAll(Adafruit_NeoPixel strip,uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      //delay(wait);
  }
}

void colorWipe(int pos,Adafruit_NeoPixel strip,uint32_t c, uint8_t wait) {
  for(uint16_t i=(pos-1)*LED_INTERVAL; i<pos*LED_INTERVAL; i++) {
      strip.setPixelColor(i, c);
      strip.show();
      //delay(wait);
  }
}

void rainbow(Adafruit_NeoPixel strip,uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(strip,(i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(Adafruit_NeoPixel strip,uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(strip,((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(Adafruit_NeoPixel strip,uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(Adafruit_NeoPixel strip,uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( strip,(i+j) % 255));    //turn every third pixel on
        }
        strip.show();

        delay(wait);

        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel strip,byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
 

