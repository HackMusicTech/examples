#define potSize 2

int potPins[] = {0,1};
byte previousValue[] = {0,0};
byte newValue[] = {0,0};
byte ccMap[] = {0x10, 0x11};

void setup() {
  Serial.begin(31250); 
  while (!Serial) {
    ;
  }
}

void loop(){ 
  smooth();
  send_cc();
}

void smooth(){
  for (int i = 0; i < potSize; i++) {
    newValue[i] = analogRead(i) >> 3;
    delay(1);
  }   
}

void send_cc(){
  for (int i = 0; i < potSize; i++) {
    if (newValue[i] != previousValue[i]) {
      MIDImessage(0xB0, ccMap[i], newValue[i]);      
      previousValue[i] = newValue[i];
    }
  }
}

void MIDImessage(int command, int param1, int param2) {
  Serial.write(command);
  Serial.write(param1);
  Serial.write(param2);
}
