void connection() {
int Activation=0;int Force; String check;String input;String msg;   
msg=html_connection();
server.send(200, "text/html", msg);
  } 


    
void standby() {
int Activation=0;int Force; String check;String input;String msg;  
if(Serial.available()){
  Serial.println("available");
  msg +="<head><pre><meta http-equiv='refresh' content='1,/condition'></pre></head>";
//  接続後に自動遷移
}else{
  msg= html_standby();
  }
server.send(200, "text/html", msg);
  } 



String html_connection(){
  String msg;
  msg +="<html lang=\"ja\">";
  msg +="<html><head><title>EPM</title>";
  msg +="<meta charset=\"utf-8\">";
  msg +="<head><pre><meta http-equiv='refresh' content='2,/standby'></pre></head>";
  msg +="<html><body><h1>[接続中です．．．]</h1><br></body>";  
  msg +="<style>";
  msg +="html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #444444;}";
  msg +="body{margin: 0px;} ";
  msg +="h1 {margin: 50px auto 30px;} ";
  msg +=".side-by-side{display: table-cell;vertical-align: middle;position: relative;}";
  msg +=".text{font-weight: 600;font-size: 19px;width: 200px;}";
  msg +=".reading{font-weight: 300;font-size: 50px;padding-right: 25px;}";
  msg +=".temperature .reading{color: #F29C1F;}";
  msg +=".humidity .reading{color: #3B97D3;}";
  msg +=".pressure .reading{color: #26B99A;}";
  msg +=".altitude .reading{color: #955BA5;}";
  msg +=".superscript{font-size: 17px;font-weight: 600;position: absolute;top: 10px;}";
  msg +=".data{padding: 10px;}";
  msg +=".container{display: table;margin: 0 auto;}";
  msg +=".icon{width:65px}";
  msg +="</style>";     
  msg +="<svg enable-background='new 0 0 19.438 54.003'height=54.003px id=Layer_1 version=1.1 viewBox='0 0 19.438 54.003'width=19.438px x=0px xml:space=preserve xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink y=0px><g><path d='M11.976,8.82v-2h4.084V6.063C16.06,2.715,13.345,0,9.996,0H9.313C5.965,0,3.252,2.715,3.252,6.063v30.982";
  msg +="C1.261,38.825,0,41.403,0,44.286c0,5.367,4.351,9.718,9.719,9.718c5.368,0,9.719-4.351,9.719-9.718";
  msg +="c0-2.943-1.312-5.574-3.378-7.355V18.436h-3.914v-2h3.914v-2.808h-4.084v-2h4.084V8.82H11.976z M15.302,44.833";
  msg +="c0,3.083-2.5,5.583-5.583,5.583s-5.583-2.5-5.583-5.583c0-2.279,1.368-4.236,3.326-5.104V24.257C7.462,23.01,8.472,22,9.719,22";
  msg +="s2.257,1.01,2.257,2.257V39.73C13.934,40.597,15.302,42.554,15.302,44.833z'fill=#F29C21 /></g></svg>";               
return msg;
}

String html_standby(){
  String msg;
  msg +="<html lang=\"ja\">";
  msg +="<html><head><title>EPM</title>";
  msg +="<meta charset=\"utf-8\">";
  msg +="<head><pre><meta http-equiv='refresh' content='2,/standby'></pre></head>";
  msg +="<html><body><h1>[スタンバイモードA]</h1><br></body>";
  msg +="<h1>EPMを自動吸着判定のため励磁しました</h1><br>";
  msg +="<h1>吸着対象物が近づくと自動で再励磁し，最大吸着力を発揮します</h1><br>";
  msg +="  <p>シリアルなしです。</p>";
  msg +="<br><br><br><br><br><br><br><br><br>";
  msg +="<body>";
  msg +="<div style='text-align: right'><button style='background:red;' ><font size='40px'>";
  msg +="<a id = 'btn' onclick='MoveCheck();'>緊急離脱</a></font></button></div>";
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
  return msg;
}
