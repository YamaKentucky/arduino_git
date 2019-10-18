int pin = 3;
volatile int led = LOW, sw = LOW;
volatile unsigned long time_prev = 0, time_now;
unsigned long time_chat = 20;

void setup()
{
  pinMode(pin, OUTPUT);
  attachInterrupt(0, blink, CHANGE); //スイッチが変化したら、LED消点灯切り替えの割り込み処理を実行
}

void loop()
{
  digitalWrite(pin, led);
}

//LED消点灯切り替えの割り込み処理
void blink()
{
  time_now = millis(); //現在の割り込み時刻を取得
  if( time_now-time_prev > time_chat){
    if( sw == LOW ) //前回の割り込みから20[ms]以上経過かつスイッチの状態がLowならば、LED消点灯を切り替え
      led = !led;
    sw = !sw; //前回の割り込みから20[ms]以上経過ならば、スイッチの状態を切り替え
  }
  time_prev = time_now; //現在の割り込み時刻を前回の割り込み時刻へコピー

}
