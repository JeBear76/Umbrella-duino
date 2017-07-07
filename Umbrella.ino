int latchPin[] = { 8 };
int clockPin[] = { 9 };
int dataPin[] = { 7 };

int activeRegister = 0;

int sensorPin[] = { A0, A1, A2, A3, A4, A5 };
int sensorI[] = { 0, 0, 0, 0, 0, 0 };

byte leds[] = { 0, 0 };
 
void setup() 
{
  for(int i = 0; i < 6; i++){
    pinMode(sensorPin[i], INPUT);
  }
  pinMode(latchPin[activeRegister], OUTPUT);
  pinMode(dataPin[activeRegister], OUTPUT);  
  pinMode(clockPin[activeRegister], OUTPUT);
  updateShiftRegister();
}

void switchActiveRegister(){
  activeRegister = (int)!(activeRegister && 0);
}

void loop() 
{
  for(int i = 0; i < 6; i++){
    if(analogRead(sensorPin[i]) > 15){
      loopLights(sensorI[i]);
      sensorI[i]++;
      if(sensorI[i]>=7)
        sensorI[i]=0;
    }
  }
}

void loopLights(int sensorBit){
    if(sensorBit == 0)
      bitClear(leds[activeRegister], 6);
    else
      bitClear(leds[activeRegister], sensorBit-1);
    bitSet(leds[activeRegister], sensorBit);
    updateShiftRegister();
    delay(50);
  //}
}
 
void updateShiftRegister()
{
   digitalWrite(latchPin[activeRegister], LOW);
   shiftOut(dataPin[activeRegister], clockPin[activeRegister], LSBFIRST, leds[activeRegister]);
   digitalWrite(latchPin[activeRegister], HIGH);
}
