#include <Wire.h>

int SLAVE_ADDRESS = 0x04;   //I2Cのアドレス『0x04』
int a = 1673;
int b = 12329;
int c = 8909;
int d = 31900;
String a_ = String(a);
String b_ = String(b);
String c_ = String(c);
String d_ = String(d);
char cmd;
int i = 0;
byte mes[2] = {0, 0};
byte num[8] = {0, 0, 0, 0, 0, 0, 0, 0};

//int str_out[3];
String str_out;

void setup() {
  //str_out[0] = a;
  //str_out[1] = b;
  //str_out[2] = c;
  Serial.begin(9600);
  str_out = String(a) + "," + String(b) + "," + String(c) + "," + String(d);
  //str_out = String(a) , String(b) , String(c) , String(d);

  //I2C接続を開始する
  Wire.begin(SLAVE_ADDRESS);

  //I2Cで受信したときに呼び出す関数を登録する
  Wire.onReceive(ReceiveMassage);

  //I2Cでリクエスト受信したときに呼び出す関数を登録する
  Wire.onRequest(RequestMassage);
}


void loop() {
  //  //Serial.print(Wire.write(str_out.c_str()));
  //  Serial.print(a_.c_str());
  //  Serial.print(b_.c_str());
  //  Serial.print(c_.c_str());
  //  Serial.print(Wire.write(d_.c_str()));
  //  Serial.println(d_.c_str());
  //  //Serial.println(str_out);
  //  byte mes[] = {a & 0xff, (a >> 8) & 0xff};

  num[0] = a & 0xff;
  num[1] =  (a >> 8) & 0xff;
  num[2] = b & 0xff;
  num[3] =  (b >> 8) & 0xff;
  num[4] = c & 0xff;
  num[5] =  (c >> 8) & 0xff;
  num[6] = d & 0xff;
  num[7] =  (d >> 8) & 0xff;

  a++; b++; c++; d++;
  delay(1000);
}


void ReceiveMassage(int byteCount) {
  while (Wire.available()) {
    cmd = Wire.read();     //文字を読む
    //Serial.println(cmd);       //シリアルポートにcmdを出力し表示する
  }

  if (cmd == '1') {
    // Serial.println('a');
    mes[0] = a & 0xff;
    mes[1] = (a >> 8) & 0xff;
    //    Serial.println(mes[0], BIN);
    //    Serial.println(mes[1], BIN);
  }

  if (cmd == '2') {
    //Serial.println('b');
    mes[0] = b & 0xff;
    mes[1] = (b >> 8) & 0xff;
    //    Serial.println(mes[0], BIN);
    //    Serial.println(mes[1], BIN);
  }

  if (cmd == '3') {
    //Serial.println('c');
    mes[0] = c & 0xff;
    mes[1] = (c >> 8) & 0xff;
    //    Serial.println(mes[0], BIN);
    //    Serial.println(mes[1], BIN);
  }

  if (cmd == '4') {
    //Serial.println('d');
    mes[0] = d & 0xff;
    mes[1] = (d >> 8) & 0xff;
    //    Serial.println(mes[0], BIN);
    //    Serial.println(mes[1], BIN);
  }
}


void RequestMassage() {
  //  byte str_out_byte[3];
  //  str_out_byte[0]=(byte)str_out[0];
  //  str_out_byte[1]=(byte)str_out[1];
  //  str_out_byte[2]=(byte)str_out[2];
  //  Wire.write(str_out_byte, 3);

  //Wire.write(str_out.c_str());
  Wire.write(num, 8);
  delay(20);

  //    byte mes[] = {d & 0xff, (d >> 8) & 0xff};
  //Wire.write(mes, sizeof(int));
  //  Serial.println(mes[0], BIN);
  //  Serial.println(mes[1], BIN);
  //delay(20);
  //mes[0] = 0;
  //mes[1] = 0;

  //  Serial.println(Wire.write(mes, sizeof(int)));

  //  if (cmd == '1') {
  //    Serial.println('a');
  //    byte mes[] = {a & 0xff, (a >> 8) & 0xff};
  //    Wire.write(mes, sizeof(int));
  //  }
  //
  //  if (cmd == '2') {
  //    Serial.println('b');
  //    byte mes[] = {b & 0xff, (b >> 8) & 0xff};
  //    Wire.write(mes, sizeof(int));
  //  }
  //
  //  if (cmd == '3') {
  //    Serial.println('c');
  //    byte mes[] = {c & 0xff, (c >> 8) & 0xff};
  //    Wire.write(mes, sizeof(int));
  //  }
  //
  //  if (cmd == '4') {
  //    Serial.println('d');
  //    byte mes[] = {d & 0xff, (d >> 8) & 0xff};
  //    Wire.write(mes, sizeof(int));
  //  }
  //  Wire.write(b_.c_str());
  //  Wire.write(c_.c_str());
  //  Wire.write(d_.c_str());
}
