//  IoT電子工作キット
//  4-2-1.SPIFFSによるファイル操作1
 
#include <SPIFFS.h>  // ①ライブラリを読み込み
 
void setup(void) {
  String A;String B;
  Serial.begin(115200); // ②Serial設定
  Serial.println ("");
  writeFile();
  readcsv(3000);
}
void readcsv(int max_data){
  String A;String B;
  SPIFFS.begin(true); // ③SPIFFS開始
  File f = SPIFFS.open("/accdata.csv", "r");
  int start=millis();
  if (!f) {
    Serial.println("file open failed");
  } else {
    Serial.println("====== Reading from SPIFFS file =======");
    // write 10 strings to file
    
    for (int i=0; i<=max_data; i++){
      String s=f.readStringUntil('\n');
      Serial.println(s);
//      if(i>3&&i<3000){
//        A+=s;
//      }else{
//        B+=s;
//      }
    } // end for
    f.close();
    
  } // end if
  Serial.print(millis()-start);
  Serial.println(A);
//  Serial.println(B);
}

void writeFile(){
    SPIFFS.begin(true); // ③SPIFFS開始
    File file = SPIFFS.open("/accdata.csv", "w");
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    for (int i=0;i<=3000;i++){
      file.println(i);
    }
    file.close();
}
void loop(void){
}
