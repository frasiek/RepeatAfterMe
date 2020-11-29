#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988

int red[5]; 
int buzzer = 3;
int button[5];
int buzzTone[5];
int seq[500];
int currentSeqPlace;
  
void setup() {
  Serial.begin(9600);
  
  for(int i = 0; i < 5; i++){
    red[i] = 13 - i;  
    button[i] = 8 - i;  
    pinMode(red[i], OUTPUT); 
    pinMode(button[i], INPUT);
  }

  buzzTone[0] = NOTE_C5;
  buzzTone[1] = NOTE_D5;
  buzzTone[2] = NOTE_E5;
  buzzTone[3] = NOTE_F5;
  buzzTone[4] = NOTE_G5;
  
  pinMode(buzzer, OUTPUT);
}

void intro() {
  for(int i = 0; i < 5; i++){
    if(i > 0){
        digitalWrite(red[i-1], LOW);
    }
    digitalWrite(red[i], HIGH);
    tone(buzzer, buzzTone[i]);
    delay(100); 
  }
  digitalWrite(red[4], LOW);
  delay(100);
  noTone(buzzer);
}

void play(int i){
   digitalWrite(red[i], HIGH);
   tone(buzzer, buzzTone[i]);
   delay(150);
   digitalWrite(red[i], LOW);
   noTone(buzzer);
    delay(50);
}

void initSeq(){
  currentSeqPlace = -1;

  for(int i = 0; i < 500; i++){
    seq[i] = random(0,5);
  }
}

int getPlayerOption(){
  while(true){
     for(int i = 0; i < 5; i++){;
      if (digitalRead(button[i]) == HIGH) {
         play(i);
         return i;
      }
     }
  }
}
void loop() {
  intro();
  delay(1000);
  initSeq();
  int alive = 1;
  while(alive > 0){
    currentSeqPlace++;
    for(int i = 0; i <= currentSeqPlace; i++){
        play(seq[i]);
    }

    for(int i = 0; i <= currentSeqPlace; i++){
      int playerOption = getPlayerOption();
      if(playerOption !=  seq[i]){
        alive = 0;
        break;
      }
      delay(500);
    }
  }
}
