int number = 130;
int flg = 1;
const int syuturyokupin[] = {12, 11, 5, 4, 3, 13, 10 };
const int kirikaepins[] = {2, 9, 8};

boolean NumArray[10][7] = {
  {0, 0, 0, 0, 0, 0, 1}, //0
  {1, 0, 0, 1, 1, 1, 1}, //1
  {0, 0, 1, 0, 0, 1, 0}, //2
  {0, 0, 0, 0, 1, 1, 0}, //3
  {1, 0, 0, 1, 1, 0, 0}, //4
  {0, 1, 0, 0, 1, 0, 0}, //5
  {0, 1, 0, 0, 0, 0, 0}, //6
  {0, 0, 0, 1, 1, 0, 1}, //7
  {0, 0, 0, 0, 0, 0, 0}, //8
  {0, 0, 0, 0, 1, 0, 0}, //9
};

void NumPrint(int Number) {
  for (int w = 0; w < 7; w++) {
    digitalWrite(syuturyokupin[w], NumArray[Number][w]);
  }
}

int NumParse(int Number, int s) {
  if (s == 1) {
    return Number % 10; //10で割ったあまり = 一桁目の値
  }
  else if (s == 2) {
    return Number / 10; //10で割った値を整数にする = 二桁目の値
  }
  else if (s == 3) {
    return Number / 100; //100
  }
  return 0;
}

void loop() {
  switch (flg) {
    case 1:
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(2, LOW);
      flg = 2;
      NumPrint(NumParse(number, 1));
      break;
    case 2:
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(2, LOW);
      NumPrint(NumParse(number, 2));
      flg = 3;
      break;
    case 3:
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(2, HIGH);
      NumPrint(NumParse(number, 3));
      flg = 1;
      break;
  }
}

//const int digits[] = {
//0b11000000, // 0
//0b11111001, // 1
//0b10100100, // 2
//0b10110000, // 3
//0b10011001, // 4
//0b10010010, // 5
//0b10000010, // 6
//0b11011000, // 7
//0b10000000, // 8
//0b10010000, // 9
//};

//void setup() {
// pinMode(2, OUTPUT);  //kirikae
// pinMode(3, OUTPUT);   //e
// pinMode(4, OUTPUT);   //d
// pinMode(5, OUTPUT);   //c
// pinMode(8, OUTPUT);   //kirikae
// pinMode(9, OUTPUT);   //kirikae
// pinMode(10, OUTPUT);   //g
// pinMode(11, OUTPUT);   //b
// pinMode(12, OUTPUT);   //a
// pinMode(13, OUTPUT);   //f


