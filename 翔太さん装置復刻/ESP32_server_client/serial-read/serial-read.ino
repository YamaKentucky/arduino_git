const int datasize=3500l;
uint8_t buf[2];
String box[datasize];
//char* box[6001];
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
}
String A="";
String str="";
int i=0;
int ESPmode=0;

void loop() {
 
    if (Serial.available() > 0) { // 受信したデータが存在する
      while(ESPmode==0){
        Serial.print("1;");
        str = Serial.readStringUntil(';');
        if (str=="OK"){
          ESPmode=1;
          break;
        }
      }
          A = Serial.readStringUntil('\n'); // 受信データを読み込む
          box[i]=A;
          i++;
          }
          if(i==datasize){
            Serial.printf("%d,%d",box[0],box[1]);
            for (int i=0;i<=datasize;i++){
              Serial.println(box[i]);
            }while (1);
          }
}
