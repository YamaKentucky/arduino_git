//  IoT電子工作キット
//  4-2-1.SPIFFSによるファイル操作1
 
#include <SPIFFS.h>  // ①ライブラリを読み込み
 
void setup(void) {
  String A;String B;
  Serial.begin(115200); // ②Serial設定
  Serial.println ("");
  readcsv(5000);
}
void readcsv(int max_data){
  String A;String B;
  SPIFFS.begin(); // ③SPIFFS開始
  File f = SPIFFS.open("/accdata.csv", "r");
  int start=millis();
  if (!f) {
    Serial.println("file open failed");
  } else {
    Serial.println("====== Reading from SPIFFS file =======");
    // write 10 strings to file
    
    for (int i=0; i<=max_data; i++){
      String s=f.readStringUntil('\n');
      if(i>3&&i<3000){
        A+=s;
      }else{
        B+=s;
      }
    } // end for
    f.close();
    
  } // end if
  Serial.print(millis()-start);
//  Serial.println(A);
//  Serial.println(B);
}

void loop(void){
}
