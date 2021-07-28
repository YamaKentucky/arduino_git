/*2020/11/05
 * Teensy用
 * UWBの値のみを送信したいときに使用
 * 
*/
String recv_data = String(0); // 受信データ
String str_out;

void setup() {
//  Serial1.begin(115200); //from arduino with UWB
//  Serial3.begin(115200); //to raspberry pi
  Serial.begin(9600);  //to debug PC
delay(1);

}

void loop() {
Serial.println("aaaaa");
//  if (Serial1.available() > 0) {
//    recv_data = Serial1.readStringUntil('\n');
////    delay(1);
////      Serial.println(recv_data);
////  Serial3.println(recv_data);
//  }
//
//  if(recv_data.length()<20){
//  str_out =',' + recv_data;
////  Serial.println("distance\tdeltaX\tdeltaY\tdeltaX_sum\tdeltaY_sum\trecv_data");
////  Serial.print(distance);Serial.print("\t\t");Serial.print(deltaX);Serial.print("\t");Serial.print(deltaY);Serial.print("\t");
////  Serial.print(deltaX_sum);Serial.print("\t\t");Serial.print(deltaY_sum);Serial.print("\t\t");
////  Serial.print(recv_data);Serial.print("\n");
//  Serial.println(str_out);
//  Serial3.println(str_out);
//  }
}
