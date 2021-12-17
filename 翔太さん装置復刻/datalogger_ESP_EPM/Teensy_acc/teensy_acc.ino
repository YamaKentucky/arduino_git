#include<SD.h>
#include "M41T62.h"
RTC_Millis rtc;

const int chipSelect = BUILTIN_SDCARD;
File dataFile;

IntervalTimer myTimer;
int x=0;//accel
int y=0;//accel
int z=0;//accel
volatile int sw = LOW, sw_E = LOW, sw_S = LOW;
volatile unsigned long time_prev = 0, time_prev_E = 0, time_prev_S = 0, time_now, time_now_E, time_now_S;

char syokisw = 0;
volatile char inputchar = 0;
unsigned long time_chat = 20;
const int num = 3000;
const int sync=17;//同期
const int sw2=7;//log再開
const int ledsd=36;//36
const int ledlog=37;//37

int availabledata[12];//=(0,0,0,0,0,0,0,0,0,0,0);
float data [4] [num];
int fasttime=0;
volatile unsigned long blinkCount = 0; // use volatile for shared variables
bool logstatus=false;
int datanumber=1;
int amari;
int t0, t1;
int starttime;
int finishtime;

int mode =0;
int finished=0;



void setup() {  
  Serial.begin(9600);Serial1.begin(115200);
  analogReadResolution(16);//kaizoudo
 
  pinMode(ledsd, OUTPUT);  //LED_SD
  pinMode(ledlog, OUTPUT);  //LED_log
  pinMode(10, INPUT_PULLUP); //sw
  pinMode(sync, INPUT_PULLDOWN); //sw
  pinMode(sw2, INPUT_PULLDOWN); //sw
  digitalWrite(ledlog, LOW);

  Serial.println(F("Initializing SD card..."));
  pinMode(SS, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println(F("Card failed, or not present"));
    while (1){ // 失敗、何もしない
      int i;
      i++;
      if(i%2==0){digitalWrite(ledsd, HIGH);}
            else{digitalWrite(ledsd, LOW);}delay(500);
    }
  }delay(1);
  Serial.println(F("ok."));
  for (int i=0;i<1000;i++){
    if (i%10==0){digitalWrite(ledlog, HIGH);}else{digitalWrite(ledlog, LOW);}
    if (i%200==0){Serial.print(F("*"));}                 
    String temp = "data";
    temp.concat(i);
    temp.concat(".csv");
    char filename[temp.length()+1];
    temp.toCharArray(filename, sizeof(filename));
    if(SD.exists(filename)){SD.remove(filename);}
  }
  Serial.println(F("\n sd reset"));
  digitalWrite(ledlog, HIGH);
  if(analogRead(A9)>1000){
    timeset();
  }else{
    rtc.adjust(DateTime(2021, 8,20, 14, 0, 0));/*time*/
  }
  
  Serial.print("finish");   
  SdFile::dateTimeCallback( &dateTime );
}


int B=0;
int cut = 3000;

void ReadAnalog() {//4sごとに起動される
  Serial.print(millis());Serial.print("\tdata\t");Serial.println(datanumber);
  fasttime=millis()-time_now;
  while(1){
    x=analogRead(A2);
    y=analogRead(A1);
    z = analogRead(A0);
    t1 = millis();// - t0;
    data [0] [blinkCount] =t1-time_now-fasttime;
//    data [0] [blinkCount] = t1-time_now;//記録開始してからの時間
    data [1] [blinkCount] = x;
    data [2] [blinkCount] = y;
    data [3] [blinkCount] = z;
    blinkCount++; 
//    delay(1);
    if(mode!=2 || finished!=1){
      digitalWrite(ledsd, LOW);
        if (blinkCount % 500 == 0 ) {digitalWriteFast(ledlog, HIGH); }
        else                        {digitalWriteFast(ledlog, LOW) ; }
        
        if (blinkCount == 1) {
          starttime=millis();
          finished=0;
          for (int i=0;i<9;i++){
            availabledata[i]=availabledata[i+1];
          }
            availabledata[9]=datanumber;
            for (int i=0;i<10;i++){Serial.print(availabledata[i]);Serial.print(',');}
          }
        if (blinkCount %cut == 0) {
          logstatus=true;
          int A=millis();
          logging(datanumber);    

          Serial.println(millis()-A);
          if(blinkCount == num){
            datanumber++;
            blinkCount=0;
            finished=1;
            return;
          }
        }else{
          logstatus=false;
        }  
    }else{//mode:     no logging     スタンプ合わせ
      datanumber++;//
      blinkCount=0;  
      if(datanumber%2==0){digitalWrite(ledlog, HIGH);}
      else{digitalWrite(ledlog, LOW);}
      digitalWrite(ledsd, HIGH);
      return;   
    }
  while(millis()-t1<1){}   
  }
  }

void logging(int datanumber) {
    String temp = "data";
    temp.concat(datanumber);
    temp.concat(".csv");
    char filename[temp.length()+1];
    temp.toCharArray(filename, sizeof(filename));
    dataFile = SD.open(filename, FILE_WRITE);
    String row="time "+String(fasttime)+"[ms],x_low,y_low,z_low";
    dataFile.println(row);
    for (int k = 0; k < cut; k++) {
//      delay(1);
    String getdata=String(int(data [0][k]))+',';
    getdata+=String(int(data [1][k]))+',';
    getdata+=String(int(data [2][k]))+',';
    getdata+=String(int(data [3][k]))+'\n';

      dataFile.print(getdata);
    }
    dataFile.close();
}

String SdFileRead(int number) {  //SDファイル読み込み
   String A="";String B="";String C="";String str;
   String temp = "data";
    temp.concat(String(number));
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
   } else{
    Serial.println(F(" error..."));
    for (int i=0; i<num; i++){   
      Serial1.print(i);Serial1.println("::error");
      Serial.println(i);Serial.println(F("::error"));
    } // end for    
   }
   file.close();
   return str;
}



String A="";
String datanow="";
void loop() {
  if (mode ==0){////////////信号待ち
    while(digitalRead(sync)==LOW);//HIGHになったら飛び出る
      time_now = millis(); //飛び出たときの時間//サーバーとの同期
      myTimer.begin(ReadAnalog, 4000000);//microsecounds //4000000μs==4s==4000ms 
      mode=1;
      digitalWriteFast(ledlog, LOW) ;
  }else if (mode==1){//////////ESP待ち
    while(digitalRead(sw2)==LOW);//HIGHになったら飛び出る
      mode=2;
      datanow=String(datanumber-1);    
  }else if(mode==2 && finished==1){///////////////ESPmode
    while(digitalRead(sw2)==HIGH){//
      for (int i=0;i<10;i++){Serial1.print(availabledata[i]);Serial1.print(',');}
//      Serial1.print(datanow);
      Serial1.print(";");Serial.println(F("logging"));
      delay(500);
    }Serial.println(datanow);
//    while(digitalRead(10)==LOW){
    while(analogRead(A9)<1000){
      if (Serial1.available() > 0) { // 受信したデータが存在する
        A = Serial1.readStringUntil(';'); // 受信データを読み込む
        if(A.toInt()>0){
          Serial1.print("OK;");
          Serial.print(F("sending"));
          SdFileRead(A.toInt());
          Serial.print(F("finish"));
        }else if(A.toInt()==0){
          Serial.println(F("stamp"));
        }else{
          Serial.print(F("?wakaran?"));
        }
      }  
  }
  mode=1;finished=0;
  }
}

void dateTime(uint16_t* date, uint16_t* time)
{
    DateTime now = rtc.now();
  uint16_t year = now.year();
  uint8_t month = now.month(), day = now.day(), hour = now.hour(), minute = now.minute(), second = now.second();
  *date = FAT_DATE(year, month, day);// FAT_DATEマクロでフィールドを埋めて日付を返す
  *time = FAT_TIME(hour, minute, second);// FAT_TIMEマクロでフィールドを埋めて時間を返す
}

void timeset(){
  Serial.print("timeset");
  
  while(1){
    Serial1.print("A;");
    if (Serial1.available() > 0) {
       String y= Serial1.readStringUntil(','); 
       String M=Serial1.readStringUntil(','); 
       String D=Serial1.readStringUntil(','); 
       String H=Serial1.readStringUntil(','); 
       String m=Serial1.readStringUntil(',');
       
       rtc.adjust(DateTime(y.toInt(), M.toInt(), D.toInt(), H.toInt(), m.toInt(), 0));/*time*/
       return;
    }
     
     
  }
}
