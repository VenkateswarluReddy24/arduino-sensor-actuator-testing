/*
  🧮 Embedded Scientific Calculator (Fixed & Clean Version)

  Author: Venkateswarlu Reddy
*/

#include <LiquidCrystal_I2C.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- KEYPAD ----------------
byte rowPins[4] = {4,5,6,7};
byte colPins[4] = {8,9,10,11};

char keys[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'.','0','#','D'}
};

String expr = "";

// ---------------- CONFIG ----------------
#define DEBOUNCE_DELAY 200
#define HOLD_DELAY 800

// ---------------- SETUP ----------------
void setup(){
  lcd.init();
  lcd.backlight();
  resetCalc();
}

// ---------------- LOOP ----------------
void loop(){

  bool hold=false;
  char k = getKey(hold);
  if(!k) return;

  // ---------- SCIENTIFIC FUNCTIONS ----------
  if(hold && expr!=""){

    float val = expr.toFloat();

    lcd.clear();

    if(k=='C'){
      lcd.print("Square:");
      lcd.setCursor(0,1);
      lcd.print(val * val);
    }
    else if(k=='D'){
      lcd.print("Cube:");
      lcd.setCursor(0,1);
      lcd.print(val * val * val);
    }
    else if(k=='A'){
      if(val < 0){ showError(); return; }
      lcd.print("Sqrt:");
      lcd.setCursor(0,1);
      lcd.print(sqrt(val));
    }

    delay(3000);
    resetCalc();
    return;
  }

  // ---------- INPUT ----------
  if((k>='0' && k<='9') || k=='.'){
    expr += k;
  }
  else if(k=='A') expr += '+';
  else if(k=='B') expr += '-';
  else if(k=='C') expr += '*';
  else if(k=='D') expr += '/';

  // ---------- EVALUATE ----------
  else if(k=='#'){

    if(expr=="" || !isValidExpression(expr)){
      showError();
      return;
    }

    bool err=false;
    float res = evaluate(expr, err);

    lcd.clear();
    lcd.print("Result:");
    lcd.setCursor(0,1);

    if(err || isnan(res) || isinf(res)){
      showError();
      return;
    }

    lcd.print(res);
    delay(4000);
    resetCalc();
    return;
  }

  lcd.clear();
  lcd.print(expr);
}

// ---------------- KEYPAD ----------------
char getKey(bool &hold){

  for(int r=0;r<4;r++){
    pinMode(rowPins[r],OUTPUT);
    digitalWrite(rowPins[r],LOW);

    for(int c=0;c<4;c++){
      pinMode(colPins[c],INPUT_PULLUP);

      if(digitalRead(colPins[c])==LOW){

        unsigned long start = millis();
        hold = false;

        while(digitalRead(colPins[c])==LOW){
          if(millis()-start > HOLD_DELAY){
            hold = true;
          }
        }

        delay(DEBOUNCE_DELAY);
        return keys[r][c];
      }
    }
    digitalWrite(rowPins[r],HIGH);
  }

  return 0;
}

// ---------------- UTIL ----------------
void resetCalc(){
  expr="";
  lcd.clear();
  lcd.print("Scientific Calc");
  delay(500);
  lcd.clear();
}

void showError(){
  lcd.clear();
  lcd.print("Math Error");
  delay(2000);
  resetCalc();
}

bool isOp(char c){
  return (c=='+'||c=='-'||c=='*'||c=='/');
}

// ---------------- VALIDATION ----------------
bool isValidExpression(String s){

  if(s.length() == 0) return false;

  if(isOp(s[s.length()-1])) return false;

  for(int i=0; i<s.length(); i++){

    if(!( (s[i]>='0'&&s[i]<='9') || s[i]=='.' || isOp(s[i]) ))
      return false;

    if(i > 0 && isOp(s[i]) && isOp(s[i-1])){
      return false;
    }

    if(i==0 && isOp(s[i]) && s[i] != '-'){
      return false;
    }
  }

  return true;
}

// ---------------- EVALUATOR ----------------
int precedence(char op){
  if(op=='+'||op=='-') return 1;
  if(op=='*'||op=='/') return 2;
  return 0;
}

float apply(float a,float b,char op,bool &err){
  if(op=='+') return a+b;
  if(op=='-') return a-b;
  if(op=='*') return a*b;
  if(op=='/'){
    if(b==0){ err=true; return 0; }
    return a/b;
  }
  err=true;
  return 0;
}

float evaluate(String s,bool &err){

  float numStack[20];
  char opStack[20];
  int ns=0, os=0, i=0;

  while(i<s.length()){

    if((s[i]>='0'&&s[i]<='9') || s[i]=='.'){
      String val="";
      while(i<s.length() && ((s[i]>='0'&&s[i]<='9')||s[i]=='.')){
        val+=s[i]; i++;
      }
      numStack[ns++] = val.toFloat();
    }

    else if(isOp(s[i])){
      while(os>0 && precedence(opStack[os-1]) >= precedence(s[i])){
        float b=numStack[--ns];
        float a=numStack[--ns];
        char op=opStack[--os];
        numStack[ns++] = apply(a,b,op,err);
        if(err) return 0;
      }
      opStack[os++] = s[i];
      i++;
    }

    else{
      err=true;
      return 0;
    }
  }

  while(os>0){
    float b=numStack[--ns];
    float a=numStack[--ns];
    char op=opStack[--os];
    numStack[ns++] = apply(a,b,op,err);
    if(err) return 0;
  }

  return numStack[0];
}
