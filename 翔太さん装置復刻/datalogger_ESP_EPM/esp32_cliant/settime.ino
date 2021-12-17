void settime(){
   digitalWrite(logTeensy,HIGH);/*for time set*/
   Serial.println("time");
   String S=comtime();
   Serial.println(S);
   int i=0;
   while(1){
    if (Serial2.available() > 0) {
       String A=Serial2.readStringUntil(';');
       if(A=="A"){
          Serial.println("set comp");
          Serial2.print(S);  
          delay(5000);
          ESP.restart();while(1);
       }
    }
    if(i%2==0){digitalWrite(led1,HIGH);digitalWrite(led2,LOW);}
    else       {digitalWrite(led1,LOW);digitalWrite(led2,HIGH);}
    i++;//delay(10);
    }
}
