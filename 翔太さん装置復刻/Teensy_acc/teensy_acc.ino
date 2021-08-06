#include<SD.h>
const int chipSelect = BUILTIN_SDCARD;
File dataFile;

IntervalTimer myTimer;
int Z;//accel
volatile int sw = LOW, sw_E = LOW, sw_S = LOW;
volatile unsigned long time_prev = 0, time_prev_E = 0, time_prev_S = 0, time_now, time_now_E, time_now_S;

char syokisw = 0;
volatile char inputchar = 0;
unsigned long time_chat = 20;
const int num = 3000;
const int sw1=8;
const int sw2=7;
const int ledpin=3;


float data [3] [num];
volatile unsigned long blinkCount = 0; // use volatile for shared variables
int amari;
int t0, t1;
int starttime;
int finishtime;

int mode =0;
int finished=0;

void setup() {
//  attachInterrupt(23, keisoku, RISING);
//  attachInterrupt(2, EPM, RISING);
//  attachInterrupt(0, syoki, RISING);


  analogReadResolution(16);//kaizoudo

  pinMode(ledpin, OUTPUT);  //EPM
  pinMode(4, INPUT);  //EPM
  pinMode(9, OUTPUT);  //LED_log
  pinMode(10, INPUT_PULLUP); //sw

  pinMode(sw1, INPUT); //sw
  pinMode(sw2, INPUT_PULLDOWN); //sw

  Serial.begin(9600);Serial1.begin(115200);
   digitalWrite(9, LOW);


  Serial.println(F("Initializing SD card..."));
  pinMode(SS, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println(F("Card failed, or not present"));
    // 失敗、何もしない
    while (1){
      Serial.println(analogRead(A0));
      int i;
      i++;
      if(i%2==0){digitalWrite(ledpin, HIGH);}
            else{digitalWrite(ledpin, LOW);}delay(500);
    }
  }
delay(1000);
  Serial.println(F("ok."));
  for (int i=0;i<1000;i++){
    //a (1).csv
    String temp = "data";
    temp.concat(i);
    temp.concat(".csv");
    char filename[temp.length()+1];
    temp.toCharArray(filename, sizeof(filename));
//    Serial.print(filename);
  if(SD.exists(filename)){
      SD.remove(filename);
//      Serial.printf("find%s\n",filename);
    }else{
      Serial.printf("NOTFIND %d\n",i);
    }
  }
  digitalWrite(9, HIGH);
}


//void syoki() {/*#################################################################################*/
//  time_now_S = millis(); //現在の割り込み時刻を取得
//  if ( time_now_S - time_prev_S > time_chat) {
//    if ( sw_S == 0 ) {
//      if (syokisw == 0) {
//        t0 = millis();
//        Serial.print("syokiawase");
//        digitalWrite(10, HIGH); //LED表示
//        delay(1000);
//        digitalWrite(10, LOW);
//        syokisw = 1;
//      }
//    }
//    sw_S = !sw_S; //前回の割り込みから20[ms]以上経過ならば、スイッチの状態を切り替え
//  }
//  time_prev_S = time_now_S; //現在の割り込み時刻を前回の割り込み時刻へコピー
//}



//void keisoku() {
//  time_now = millis(); //現在の割り込み時刻を取得
//  myTimer.begin(ReadAnalog, 2000);  // 500 Hz
//}


int datanumber=1;

void ReadAnalog() {//2000msごとに起動される
  
  Z = analogRead(A0);
  t1 = millis();// - t0;
  
  data [0] [blinkCount] = Z;
  data [1] [blinkCount] = t1;
  data [2] [blinkCount] = time_now;
  blinkCount++;
  if(mode!=2 || finished!=1){
      if (blinkCount % 500 == 0 ) {digitalWriteFast(9, HIGH); }
      else                        {digitalWriteFast(9, LOW) ; }
      
      if (blinkCount == 1) {
        starttime=millis();
        finished=0;
        Serial.printf("data %d ",datanumber);
      }
      if (blinkCount %500 == 0) {
        logging((blinkCount / 500)-1,datanumber);
      }
      if (blinkCount >= num) {
        datanumber++;
        blinkCount=0;
        finished=1;
    //    finishtime=millis();    
//        myTimer.end();
        Serial.println("Finished\t");
      }  
  }else{//mode:     no logging     スタンプ合わせ
    if (blinkCount % 200 == 0 ) {digitalWriteFast(9, HIGH); }
      else                        {digitalWriteFast(9, LOW) ; }
    if (blinkCount >= num) {
      datanumber++;
      blinkCount=0;        
    }    
  }
}

void logging(int m,int datanumber) {
    String temp = "data";
    temp.concat(datanumber);
    temp.concat(".csv");
    char filename[temp.length()+1];
    temp.toCharArray(filename, sizeof(filename));
    dataFile = SD.open(filename, FILE_WRITE);

    for (int k = 0; k < 500; k++) {
//      delay(1);
      dataFile.print(k + 500 * m);
      dataFile.print(",");
      dataFile.print(data [2][k + 500 * m]);
      dataFile.print(",");
      dataFile.print(data [1][k + 500 * m]);
      dataFile.print(",");
      dataFile.println(data[0][k + 500 * m]);
    }
    dataFile.close();
  Serial.print("*");
}

/*void EPM() {
  time_now_E = millis(); //現在の割り込み時刻を取得
  if ( time_now_E - time_prev_E > time_chat) {
    if ( sw_E == LOW ) //前回の割り込みから20[ms]以上経過かつスイッチの状態がLowならば、LED消点灯を切り替え
      switch (inputchar) {
        case 0:
          digitalWrite(10, HIGH); //LED表示
          Serial.print("EPM ON\n");//EPMをONにする
          digitalWrite(4, HIGH);
          delay(2000);
          digitalWrite(4, LOW);
          inputchar = 1;
          break;

        case 1:
          digitalWrite(10, LOW); //LED表示
          Serial.print("EPM OFF\n");//EPMをOFFにする
          digitalWrite(3, HIGH);
          delay(500);
          digitalWrite(4, HIGH);
          delay(2000);
          digitalWrite(4, LOW);
          delay(500);
          digitalWrite(3, LOW);
          inputchar = 0;
          break;
      }
    sw_E = !sw_E; //前回の割り込みから20[ms]以上経過ならば、スイッチの状態を切り替え
  }
  time_prev_E = time_now_E; //現在の割り込み時刻を前回の割り込み時刻へコピー
  }
*/

String SdFileRead(int number) {  //SDファイル読み込み
   String A="";String B="";String C="";String str;
   String temp = "ddata";
    temp.concat(number);
    temp.concat(".csv");
    char filename[temp.length()+1];
    temp.toCharArray(filename, sizeof(filename));
   File file = SD.open(filename);
   Serial.print(F("SD FileRead: ")); Serial.println(filename);
   if(file){
    for (int i=0; i<num; i++){
      String s=file.readStringUntil('\n');
      
      Serial1.println(s);Serial.println(s);
    } // end for
   } else{Serial.println(F(" error..."));}
   file.close();
   return str;
}


String A="";
String timenow="";
void loop() {
  if (mode ==0){////////////信号待ち
  while(digitalRead(sw1)==LOW){//HIGHになったら飛び出る//飛び出たときの時間//サーバーとの同期
    time_now = millis(); 
  }myTimer.begin(ReadAnalog, 2000);  // 500 Hz//whileに戻る
  Serial.print("1;");
  mode=1;
  }else if (mode==1){//////////ESP待ち
    while(digitalRead(sw2)==LOW){//HIGHになったら飛び出る//飛び出たときの時間 
  }
  mode=2;
  timenow=String(datanumber);
  
  }else if(mode==2 && finished==1){///////////////ESPmode
    while(digitalRead(sw2)==HIGH){//
      Serial1.print(timenow);Serial1.print(";");Serial.println(timenow);
      delay(500);
    }
//    while(digitalRead(10)==LOW){
      while(analogRead(A9)<1000){
      if (Serial1.available() > 0) { // 受信したデータが存在する
        A = Serial1.readStringUntil(';'); // 受信データを読み込む
        if(A.toInt()>0){
          Serial1.print("OK;");
          Serial.print("sending");
          SdFileRead(A.toInt());
          Serial.print("finish");
//          delay(1000);
        }else if(A.toInt()==0){
          Serial.println("stamp");
        }else{
          Serial.print("?wakaran?");
        }
//
//        Serial.print("I received: "); // 受信データを送りかえす
//        Serial.println(A);
      }
        


      
  }
  mode=1;finished=0;
//  Serial.println(".");
//  delay(100);
  }
//  delay(1000000);
}
