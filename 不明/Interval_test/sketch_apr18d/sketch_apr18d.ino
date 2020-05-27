#include<SD.h>
const int chipSelect = BUILTIN_SDCARD;
File dataFile;

IntervalTimer myTimer;
int Z;//accel
volatile int sw = LOW;
volatile unsigned long time_prev = 0, time_now;
unsigned long time_chat = 20;
const int num = 5000;

float data [num];
volatile unsigned long blinkCount = 0; // use volatile for shared variables
int amari;

void setup() {
  attachInterrupt(0, keisoku, RISING);
  analogReadResolution(16);//kaizoudo
  pinMode(9, OUTPUT); //LED
  //attachInterrupt(0, keisoku, RISING);
  Serial.begin(9600);
  digitalWriteFast(9, HIGH);
  //myTimer.begin(ReadAnalog, 10000);  // 100 Hz

  Serial.print(F("Initializing SD card..."));
  pinMode(SS, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println(F("Card failed, or not present"));
    // 失敗、何もしない
    while (1);
  }

  Serial.println(F("ok."));
  if (SD.exists("datalog.csv")) {
    SD.remove("datalog.csv");
    Serial.println(F("File exist! Remove File."));
  }
  //dataFile = SD.open("datalog.csv", FILE_WRITE);
  digitalWriteFast(9, HIGH);
}

void keisoku() {
  time_now = millis(); //現在の割り込み時刻を取得
  if ( time_now - time_prev > time_chat) {
    if ( sw == LOW )
      
      delay(1000);
      //myTimer.begin(ReadAnalog, 10000);  // 100 Hz
      myTimer.begin(ReadAnalog, 2000);  // 500 Hz

    sw = !sw; //前回の割り込みから20[ms]以上経過ならば、スイッチの状態を切り替え
  }
  time_prev = time_now; //現在の割り込み時刻を前回の割り込み時刻へコピー
}

void logging() {
  //dataFile = SD.open("datalog.csv", FILE_WRITE);
  for (int m = 0; m < 10; m++) {
    dataFile = SD.open("datalog.csv", FILE_WRITE);
    for (int k = 0; k < 500; k++) {
      delay(5);
      //dataFile = SD.open("datalog.csv", FILE_WRITE);
      /* Serial.print("blinkCount = ");
        Serial.print(blinkCount);*/
      Serial.print("Number = ");
      Serial.print(k + 1 + 500 * m);
      Serial.print(",");
      Serial.println(data[k + 500 * m]);
      dataFile.print(k + 1 + 500 * m);
      dataFile.print(",");
      dataFile.println(data[k + 500 * m]);
      //i++;
    }
    dataFile.close();
  }
  digitalWrite(9,HIGH);
}

void ReadAnalog() {
  amari = blinkCount % 500;
  Z = analogRead(A0);
  data [blinkCount] = Z;
  blinkCount++;

  /*if(blinkCount==100){
    blinkCount = 1;
    }*/

  if (amari == 0 ) {
    digitalWriteFast(9, HIGH);
  }
  else {
    digitalWriteFast(9, LOW);
  }
  if (blinkCount >= 5000) {
    myTimer.end();
    Serial.println("Finished");
    logging();
  }
}

int i = 0;
void loop() {

  //dataFile.close();
  delay(1000000);
}
