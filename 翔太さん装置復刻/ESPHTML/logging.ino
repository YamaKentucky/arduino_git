void Fake_log(){
  String Fake;String msg;
//  action();//ボタン押した後再磁化待機画面
   msg=html_fake_log();  
   server.send(200, "text/html", msg);
}

String html_fake_log(){
  String msg;
  msg +="  <html lang=\'ja\'>";
  msg +="<html><head><title>EPM</title>";
  msg +="<meta charset=\'utf-8\'>";

  msg +="<head><pre><meta http-equiv='refresh' content='1,/log'></pre></head>";
  msg +="<html><body><h1>[FAKE log]</h1><br></body>";

return msg;
}

void logging(){
  
String str1[100];
String str2[100];
String str3[100];
String msg;
  action();
  Serial.println("log");
  if(Serial.available()){
   for(int i=0;i<100;i++){
      str1[i]=Serial.readStringUntil(';');
      str2[i]=Serial.readStringUntil(';');
      str3[i]=Serial.readStringUntil(';');
    }Serial.println("finish");
    msg=html_log(str1,str2,str3);
  }else{
    for(int i=0;i<100;i++){
      str1[i]=i;str2[i]=i;str3[i]=i;
    } msg=html_log(str1,str2,str3);
  }
  server.send(200, "text/html", msg);
  }


String html_log(String *str1,String *str2,String *str3){
  String msg;

msg +="<html lang=\'ja\'>";
msg +="<html><head><title>EPM</title>";
msg +="<meta charset=\'utf-8\'>";
msg +="<html>";
for(int i=0;i<100;i++){
  msg +="<html><body><font size='4'>"+str1[i]+"　　　　</font></body>";
  msg +="<html><body><font size='4'>"+str2[i]+"　　　　</font></body>";
  msg +="<html><body><font size='4'>"+str3[i]+"　　　　</font></body><br>";
  }
msg +="<center><button style='background-color: green;width:80%;padding:10px 50px;font-size:80px;'>";
msg +="    <a onclick='MoveCheck_EPM_OFF();'>離脱</a></button></center>";
msg +="<br><br><br><br><br><br><br><br><br>";
msg +="<body>";
msg +="<div style='text-align: right'><button style='background:red;' ><font-size='40px'>";
msg +="<a id = 'btn' onclick='MoveCheck();'>緊急離脱</a></font-size></button></div>";
msg +="    <script>";
  msg +="        function MoveCheck_EPM_OFF() {";
  msg +="            if( confirm('EPMを無効化します') ) {";
  msg +="            window.location.href = '/fake_react';";
  msg +="            }else {";
  msg +="            alert('．．．');";
  msg +="            }";
  msg +="        }       ";
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


void test(){
  String msg;
  msg=html_test("8","/standby","後に離脱します");
       
  server.send(200, "text/html", msg);
}

String html_test(String num,String page,String comment){
  String msg;
  msg +="<html lang=\"ja\">";
  msg +="<html><head><title>EPM_counter</title>";
  msg +="<meta charset=\"utf-8\">";
  msg +="</head>";
  msg +="<body onload='count_start();'>";
  msg +="           <pre><meta http-equiv='refresh' content='"+num+","+page+"'></pre>";
  msg +="    <form name='ktimer' onsubmit='return false;'>";
  msg +="        <font size='5'>約</font>";
//  msg +="        <center><font size='1000%'><B id='counter'>"+num+"</B></font></center>";
  msg +="  <center><p style='font-size:1000%'><B id='counter'>"+num+"</B></p></center>";
//
//  msg +="        <font size='7'><B id='counter'>"+num+"</B></font>";
  msg +="    <font size='5'><div align='right'>sec"+comment+"</div></font>";
  msg +="    </form>";
  msg +="    </body>";
  msg +="    <script type='text/javascript'>";
  msg +="        def_count = "+num+";";
  msg +="        var Status = -1;  ";
  msg +="        timer_reset();";
  msg +="        function timer_reset() {";
  msg +="            timerID = 0;";
  msg +="            commentID = 0;";
  msg +="            document.ktimer.counter.value = def_count;";
  msg +="            document.ktimer.b_start.disabled = false;";
  msg +="        }";
  msg +="        function set_timer(num) {";
  msg +="            if (timerID > 0) {";
  msg +="                count_stop();";
  msg +="            }";
  msg +="            document.ktimer.counter.value = num;";
  msg +="            count_start();";
  msg +="        }";
  msg +="        function count_start() {";
  msg +="            count = def_count;  ";
  msg +="            timerID = setInterval('countdown()', 1000);   ";
  msg +="        }";
  msg +="        function count_stop() {";
  msg +="            clearInterval(timerID);";
  msg +="            document.getElementById('b_stop').disabled = true;  ";
  msg +="        }";
  msg +="        function count_format(num) {";
  msg +="            var tm, ts;";
  msg +="            ts = num;";
  msg +="            return ts;";
  msg +="        }";
  msg +="        function countdown() {";
  msg +="            count--;";
  msg +="            document.getElementById('counter').innerHTML = count_format(count);   ";
  msg +="        }";
  msg +="    </script>";  
  return msg;
}
