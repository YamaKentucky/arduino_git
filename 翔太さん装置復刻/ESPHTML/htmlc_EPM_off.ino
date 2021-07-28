void action(){
  digitalWrite(Button,HIGH);
//  delay(1000);
//  digitalWrite(Button,LOW);
//  delay(1000);
  Serial.println("Flag");
}
void shut_down(){
  digitalWrite(reset,LOW);
  Serial.println("shut_down");
}

void start_up(){
  digitalWrite(reset,HIGH);
  Serial.println("start_up");
}


void Fake_react() {
String msg;  
    shut_down();
    delay(500);
    start_up();
    msg=html_test("5","/react","後に離脱します");
    server.send(200, "text/html", msg);
  } 
  
void reactivate(){
 String msg;
     delay(500);
    shut_down();
  Serial.println("EPM_OFF");
  Serial.println("wait for reactivate");
  msg=html_reactivate();    
  server.send(200, "text/html", msg);
}



void emergency(){
  shut_down();
  delay(500);
  start_up();
  delay(6000);
  shut_down();
 String msg;
 msg=html_emergency();
 server.send(200, "text/html", msg);
}


void Fake() {
int Activation=0;int Force; String check;String input;String msg;String Fake;
  start_up();
    if(Serial.available()){
     Fake = Serial.readStringUntil('%');
     Serial.println("Fake");
     Serial.print(Fake);
   }
   msg=html_test("9","/standby","後にスタンバイ");
   server.send(200, "text/html", msg);
  } 



String html_emergency(){
  String msg;
  msg +="  <html lang=\'ja\'>";
  msg +="<html><head><title>EPM</title>";
  msg +="<meta charset=\'utf-8\'>";
  msg +="<html>";
  msg +="<body><h1>強制離脱しました(約５s)</h1><br>";
  msg +="システムを再起動するまでEPMは磁化されません</body>";
  msg +="<br><br><br><br><br><br><br><br><br>";
  msg +="<body>";
  msg +="<div style='text-align: right'><button style='background:red;' ><font-size='40px'>";
  msg +="<a id = 'btn' onclick='MoveCheck();'>緊急離脱</a></font-size></button></div>";
  msg +="    <script>";
  msg +="        function MoveCheck() {";
  msg +="            if( confirm('強制離脱します(約7s)') ) {";
  msg +="            window.location.href = '/emergency';";
  msg +="            }else {";
  msg +="            alert('．．．');";
  msg +="            }";
  msg +="        }       ";
  msg +="    </script>";
  msg +="</body>";
  msg +="</html>";

return msg;
}

  
String html_reactivate(){
  String msg;
  msg +="<html lang=\'ja\'>";
  msg +="<html><head><title>EPM</title>";
  msg +="<meta charset=\'utf-8\'>";
  msg +="<html>";
  msg +="<body><h1>離脱しました[]</h1><br></body>";
  msg +="<style type='text/css'> ";
  msg +="button.button2 {";
  msg +="    font-size: 1.4em;"; /* 文字サイズを1.4emに指定 */
  msg +="    font-weight: bold;"; /* 文字の太さをboldに指定 */
  msg +="    text-align: center;";
  msg +="    padding: 10px 30px;"; /* 縦方向に10px、 * 横方向に30pxの余白を指定 */
  msg +="}";
  msg +="</style>";
  msg +="<center><button style='background-color: green;width:80%;padding:10px 50px;font-size:80px;'>";
  msg +="<a href='/fake'>ReActivate</a></button></center>";
  msg +="<br><br><br><br><br><br><br><br><br>";
  msg +="<body>";
  msg +="<div style='text-align: right'><button style='background:red;' ><font-size='40px'>";
  msg +="<a id = 'btn' onclick='MoveCheck();'>緊急離脱</a></font-size></button></div>";
  msg +="    <script>";
  msg +="        function MoveCheck() {";
  msg +="            if( confirm('強制離脱します(約7s)') ) {";
  msg +="            window.location.href = '/emergency';";
  msg +="            }else {";
  msg +="            alert('．．．');";
  msg +="            }";
  msg +="        }       ";
  msg +="    </script>";
  msg +="</body>";
  msg +="</html>";
return msg;
}

String html_fake(String i){
   String msg;
  msg +="<html lang=\"ja\">";
  msg +="<html><head><title>EPM</title>";
  msg +="<meta charset=\"utf-8\">";
  msg +="<head><pre><meta http-equiv='refresh' content='1,/fake'></pre></head>";
  msg +="<html><body><h1>"+i+"</h1><br></body>";
  msg +="<h1>秒後にスタンバイに移行します</h1><br>";

  msg +="</body>";
  return msg;
}

String html_fake_react(String i){
   String msg;
  msg +="<html lang=\"ja\">";
  msg +="<html><head><title>EPM</title>";
  msg +="<meta charset=\"utf-8\">";
  msg +="<head><pre><meta http-equiv='refresh' content='1,/fake_react'></pre></head>";
  msg +="<html><body><h1>"+i+"</h1><br></body>";
  msg +="<h1>秒後に離脱します</h1><br>";

  msg +="</body>";
  return msg;
}
