/*
  📟 Bluetooth LED Matrix Display System (MAX7219)

  Features:
  - Multi-matrix scrolling text
  - Bluetooth message input (HC-05)
  - Border animation effect
  - Smooth non-blocking scrolling

  Author: Venkateswarlu Reddy
*/

#include <LedControl.h>
#include <SoftwareSerial.h>

// ---------------- MATRIX CONFIG ----------------
#define DIN_PIN 11
#define CLK_PIN 13
#define CS_PIN 10
#define MATRICES 4

// ---------------- BLUETOOTH ----------------
#define BT_RX 9
#define BT_TX 8
SoftwareSerial BT(BT_RX, BT_TX);

// ---------------- OBJECTS ----------------
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, MATRICES);

// ---------------- PARAMETERS ----------------
const unsigned long SCROLL_INTERVAL = 20;
const unsigned long BORDER_INTERVAL = 500;

// ---------------- DATA ----------------
String words[MATRICES] = {"WELCOME","TO","THE","ROBOTICS"};

byte buffer[MATRICES][8];

int charIndex[MATRICES];
int colIndex[MATRICES];

unsigned long lastScroll = 0;
unsigned long borderTimer = 0;

bool borderState = false;

// ---------------- FONT ----------------
// (same font as your original — unchanged)
extern const byte font[][8];

// ---------------- BIT REVERSE ----------------
byte reverseByte(byte b){
  b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
  b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
  b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
  return b;
}

// ---------------- STARTUP ----------------
void startupAnimation(){
  for(int c=0;c<8;c++){
    for(int d=0; d<MATRICES; d++)
      lc.setColumn(d,c,B11111111);
    delay(40);
  }
  for(int d=0; d<MATRICES; d++)
    lc.clearDisplay(d);
}

// ---------------- BORDER ----------------
void borderEffect(){
  if(millis() - borderTimer > BORDER_INTERVAL){
    borderTimer = millis();
    borderState = !borderState;

    byte border = borderState ? B10000001 : 0;

    for(int d=0; d<MATRICES; d++){
      lc.setColumn(d,0,border);
      lc.setColumn(d,7,border);
    }
  }
}

// ---------------- SETUP ----------------
void setup(){

  Serial.begin(9600);
  BT.begin(9600);

  for(int d=0; d<MATRICES; d++){
    lc.shutdown(d,false);
    lc.setIntensity(d,6);
    lc.clearDisplay(d);

    charIndex[d]=0;
    colIndex[d]=0;
  }

  startupAnimation();
}

// ---------------- LOOP ----------------
void loop(){

  borderEffect();
  handleBluetooth();
  handleScrolling();
}

// ---------------- BLUETOOTH ----------------
void handleBluetooth(){

  if(BT.available()){

    String input = BT.readStringUntil('\n');
    input.trim();
    input.toUpperCase();

    Serial.print("[BT] ");
    Serial.println(input);

    for(int d=0; d<MATRICES; d++){
      words[d] = getWord(input,d);
      charIndex[d]=0;
      colIndex[d]=0;
      clearMatrix(d);
    }
  }
}

// ---------------- SCROLL ----------------
void handleScrolling(){

  if(millis() - lastScroll < SCROLL_INTERVAL) return;

  lastScroll = millis();

  for(int d=0; d<MATRICES; d++)
    scrollMatrix(d);
}

void scrollMatrix(int d){

  if(words[d].length()==0) return;

  char c = words[d][charIndex[d]];
  int idx = getFontIndex(c);

  byte col = reverseByte(font[idx][colIndex[d]]);
  shiftLeft(d,col);

  colIndex[d]++;

  if(colIndex[d]>=8){
    colIndex[d]=0;
    charIndex[d]++;

    if(charIndex[d]>=words[d].length())
      charIndex[d]=0;
  }
}

// ---------------- MATRIX HELPERS ----------------
void shiftLeft(int d, byte col){

  for(int i=0;i<7;i++)
    buffer[d][i]=buffer[d][i+1];

  buffer[d][7]=col;

  for(int i=0;i<8;i++)
    lc.setColumn(d,i,buffer[d][i]);
}

void clearMatrix(int d){

  for(int i=0;i<8;i++){
    buffer[d][i]=0;
    lc.setColumn(d,i,0);
  }
}

// ---------------- TEXT HELPERS ----------------
int getFontIndex(char c){

  if(c==' ') return 0;

  if(c>='A' && c<='Z')
    return c-'A'+1;

  if(c>='0' && c<='9')
    return c-'0'+27;

  return 0;
}

String getWord(String text,int index){

  int count=0;
  String word="";

  for(int i=0;i<text.length();i++){

    if(text[i]==' '){
      if(count==index) return word;
      word="";
      count++;
    }
    else if(count==index){
      word+=text[i];
    }
  }

  if(count==index) return word;
  return "";
}
