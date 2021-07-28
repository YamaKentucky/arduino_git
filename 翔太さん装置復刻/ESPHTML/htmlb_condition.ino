String color(String condition){
  String color;
  if (condition=="0"){
    color="blue";
//    condition="CA";
  }else if(condition=="1"){
    color="yellow";
//    condition="NCA";
  }else if(condition=="2"){
    color="red";
//    condition="LEAVE";
  }else{
    color="red";
//    condition="NONE";
  }
  return color;
}
String condition(String condition){
  
  if (condition=="0"){
    condition="CA";
  }else if(condition=="1"){
    condition="NCA";
  }else if(condition=="2"){
    condition="LEAVE";
  }else{
    condition="NONE";
  }
  return condition;
}

void condition_EPM() { 
int Activation=0;int Force; String check;String input;String msg;  
check = Serial.readStringUntil(';');delay(500);     
     input = Serial.readStringUntil(';');
     Serial.print("check="); Serial.println(check);
     Serial.print("input="); Serial.println(input);
     Activation =  check.toInt();
     Force =  input.toInt();
//  String conditionA=Serial.readStringUntil(';');String ForceA = Serial.readStringUntil(';');
//  String conditionB=Serial.readStringUntil(';');String ForceB = Serial.readStringUntil(';');
//  String conditionC=Serial.readStringUntil(';');String ForceC = Serial.readStringUntil(';');
//  Serial.print(conditionA +";"+ ForceA +";"+ conditionB +";"+ ForceB +";"+ conditionC +";"+ ForceC+";");
   int conditionA=-1;  int ForceA1=-1; int ForceA2=-1;
     Wire.requestFrom(8, 3);
         if ( Wire.available() > 0 ){
            conditionA = Wire.read(); ForceA1 = Wire.read();ForceA2 = Wire.read();
            }  
   int conditionB=-1;  int ForceB1=-1; int ForceB2=-1; 
     Wire.requestFrom(7, 3);
         if ( Wire.available() > 0 ){
            conditionB = Wire.read(); ForceB1 = Wire.read();ForceB2 = Wire.read();
            }  
////  String conditionB;  String ForceB1;  String ForceB2;
//////   Wire.requestFrom(7, 2);
//////       if ( Wire.available() > 1 ){
//////         conditionB=Wire.readStringUntil(';'); ForceB1 = Wire.readStringUntil(';');
////////          conditionB = Wire.read();ForceB1 = Wire.read(); ForceB2 = Wire.read();
//////          }           
//  String conditionC;  String ForceC1;  String ForceC2;
////   Wire.requestFrom(6, 2);
////       if ( Wire.available() > 1 ){
////        conditionC=Wire.readStringUntil(';'); ForceC1 = Wire.readStringUntil(';');
//////          conditionC = Wire.read(); ForceC1= Wire.read();  ForceC2= Wire.read();
////          }    
  msg=html_M300(String(conditionA),String(ForceA1),String(conditionB),String(ForceB1));
  server.send(200, "text/html", msg);
  } 

String html_M300(String conditionA,String ForceA,String conditionB,String ForceB){
  String msg;String EPMA_color;String EPMB_color;
  EPMA_color=color(conditionA);conditionA=condition(conditionA);
  EPMB_color=color(conditionB);conditionB=condition(conditionB);
//  EPMB_color,conditionB=color(conditionB);
  msg +="<html lang=\"ja\">";
  msg +="<html><head><title>EPM</title>";
  msg +="<meta charset=\"utf-8\">";  
  msg +="<?xml version='1.0' encoding='utf-8'?>";
  msg +="<svg version='1.1' id='レイヤー_1' xmlns='http://www.w3.org/2000/svg' xmlns:xlink='http://www.w3.org/1999/xlink' x='0px'";
  msg +="   y='0px' viewBox='0 0 400 400' style='enable-background:new 0 0 400 400;' xml:space='preserve'>";
  msg +="<style type='text/css'>";
  msg +="  .st0{opacity:0.48;fill:#4D4D4D;enable-background:new    ;}";
  msg +="  .st2{fill:#F7931E;stroke:#000000;stroke-width:0.5;stroke-miterlimit:10;}";
  msg +="  .st3{font-family:'ArialMT';}";
  msg +="  .st4{font-size:18.9125px;}";
  msg +="  .st5{font-size:12px;}";
  msg +="  .blue{opacity:0.5;fill:#0000FF;stroke:#000000;stroke-miterlimit:10;enable-background:new    ;}";
  msg +="  .yellow{opacity:0.5;fill:#FFFF33;stroke:#000000;stroke-miterlimit:10;enable-background:new    ;}";
  msg +="  .red{opacity:0.5;fill:#F22300;stroke:#000000;stroke-miterlimit:10;enable-background:new    ;}";
  msg +="  .s0{fill:#999999;}";
  msg +="  .s1{font-family:'ROGFonts-Regular';}";
  msg +="  .s2{font-size:90.3681px;}";
  msg +="  .btn:hover {opacity: .7;}";
  msg +="  .right {margin: 0 0 0 auto;}";
  msg +="  .header {border-top: 1px solid #eee; border-bottom: 1px solid #eee; display: table; text-align: center;width: 100%;}";
  msg +="  .header a {text-decoration: none;}";
  msg +="  .btn-L,";
  msg +="  .logo,";
  msg +="  .btn-R {display: table-cell; vertical-align: middle;}";
  msg +="  .btn-L a,";
  msg +="  .btn-R a {color: #999; font-size: 10px;}";
  msg +="  .btn-L {border-right: 1px solid #eee; width: 200px;}";
  msg +="  .logo a {}";
  msg +="  .btn-R { border-left: 1px solid #eee; width: 200px;}";
  msg +="</style>";
  msg +="<polygon class='st0' points='261,34.5 139,34.5 78,77.2 78,365.5 322,365.5 322,77.2 '/>";
  msg +="<g>";
  msg +="  <g>";
  msg +="    <rect x='96.6' y='72.4' class="+ String (EPMA_color) +" width='56.7' height='56.7'/>";
  msg +="    <path class='st2' d='M94.3,110.2V91.3h61.5v18.9H94.3z M94.3,100.7h61.5 M94.3,98.8h61.5 M94.3,104.5h61.5 M94.3,102.6h61.5";
  msg +="       M94.3,97h61.5 M94.3,95.1h61.5 M94.3,93.2h61.5H94.3z M94.3,108.3h61.5 M94.3,106.4h61.5'/>";
  msg +="    <g>";
  msg +="      <text transform='matrix(1 0 0 1 106.3666 89.6732)' class='st3 st4'>"+ String (conditionA) +"</text>";
  msg +="      <text transform='matrix(1 0 0 1 100.4965 126.4973)' class='st3 st4'>"+ String (ForceA) +"</text>";
  msg +="      <text transform='matrix(1 0 0 1 136.8852 127.4973)' class='st3 st5'>N</text>";
  msg +="    </g>";
  msg +="  </g>";
  msg +="  <g>";
  msg +="    <rect x='171.6' y='147.4' class="+ String (EPMA_color) +" width='56.7' height='56.7'/>";
  msg +="    <path class='st2' d='M169.3,185.2v-18.9h61.5v18.9H169.3z M169.3,175.7h61.5 M169.3,173.8h61.5 M169.3,179.5h61.5 M169.3,177.6";
  msg +="      h61.5 M169.3,172h61.5 M169.3,170.1h61.5 M169.3,168.2h61.5H169.3z M169.3,183.3h61.5 M169.3,181.4h61.5'/>";
  msg +="    <g>";
  msg +="      <text transform='matrix(1 0 0 1 181.3666 164.6733)' class='st3 st4'>"+ String (conditionA) +"</text>";
  msg +="      <text transform='matrix(1 0 0 1 175.4965 201.4974)' class='st3 st4'>"+ String (ForceA) +"</text>";
  msg +="      <text transform='matrix(1 0 0 1 211.8853 202.4974)' class='st3 st5'>N</text>";
  msg +="    </g>";
  msg +="  </g>";
  msg +="  <g>";
  msg +="    <rect x='246.6' y='72.4' class='st2' width='56.7' height='56.7'/>";
  msg +="    <path class='st2' d='M244.3,110.2V91.3h61.5v18.9H244.3z M244.3,100.7h61.5 M244.3,98.8h61.5 M244.3,104.5h61.5 M244.3,102.6h61.5";
  msg +="       M244.3,97h61.5 M244.3,95.1h61.5 M244.3,93.2h61.5H244.3z M244.3,108.3h61.5 M244.3,106.4h61.5'/>";
  msg +="    <g>";
  msg +="      <text transform='matrix(1 0 0 1 256.3666 89.6732)' class='st3 st4'></text>";
  msg +="      <text transform='matrix(1 0 0 1 250.4965 126.4973)' class='st3 st4'></text>";
  msg +="      <text transform='matrix(1 0 0 1 286.8853 127.4973)' class='st3 st5'>N</text>";
  msg +="    </g>";
  msg +="  </g>";
  msg +="  <g>";
  msg +="    <rect x='171.6' y='222.4' class="+ String (EPMB_color) +" width='56.7' height='56.7'/>";
  msg +="    <path class='st2' d='M169.3,260.2v-18.9h61.5v18.9H169.3z M169.3,250.7h61.5 M169.3,248.8h61.5 M169.3,254.5h61.5 M169.3,252.6";
  msg +="      h61.5 M169.3,247h61.5 M169.3,245.1h61.5 M169.3,243.2h61.5H169.3z M169.3,258.3h61.5 M169.3,256.4h61.5'/>";
  msg +="    <g>";
  msg +="      <text transform='matrix(1 0 0 1 181.3666 239.6733)' class='st3 st4'>"+ String (conditionB) +"</text>";
  msg +="      <text transform='matrix(1 0 0 1 175.4965 276.4975)' class='st3 st4'>"+ String (ForceB) +"</text>";
  msg +="      <text transform='matrix(1 0 0 1 211.8853 277.4975)' class='st3 st5'>N</text>";
  msg +="    </g>";
  msg +="  </g>";
  msg +="  <g>";
  msg +="    <rect x='246.6' y='297.4' class="+ String (EPMB_color) +" width='56.7' height='56.7'/>";
  msg +="    <path class='st2' d='M244.3,335.2l0-18.9l61.5,0l0,18.9L244.3,335.2z M244.3,325.7h61.5 M244.3,323.8h61.5 M244.3,329.5h61.5";
  msg +="       M244.3,327.6l61.5,0 M244.3,322l61.5,0 M244.3,320.1h61.5 M244.3,318.2l61.5,0L244.3,318.2z M244.3,333.3l61.5,0 M244.3,331.4";
  msg +="      l61.5,0'/>";
  msg +="    <g>";
  msg +="      <text transform='matrix(1 0 0 1 256.3691 314.6723)' class='st3 st4'>"+ String (conditionB) +"</text>";
  msg +="      <text transform='matrix(1 0 0 1 250.4991 351.4964)' class='st3 st4'>"+ String (ForceB) +"</text>";
  msg +="      <text transform='matrix(1 0 0 1 286.8878 352.4965)' class='st3 st5'>N</text>";
  msg +="    </g>";
  msg +="  </g>";
  msg +="</g>";
  msg +="  <g>";
  msg +="    <rect x='96.6' y='296.5' class='st2' width='56.7' height='56.7'/>";
  msg +="    <path class='st2' d='M94.3,334.3v-18.9l61.5,0v18.9L94.3,334.3z M94.3,324.9l61.5,0 M94.3,323h61.5 M94.3,328.7l61.5,0";
  msg +="       M94.3,326.8l61.5,0 M94.3,321.1l61.5,0 M94.3,319.2h61.5 M94.3,317.3l61.5,0L94.3,317.3z M94.3,332.5l61.5,0 M94.3,330.6l61.5,0'";
  msg +="      />";
  msg +="    <g>";
  msg +="      <text transform='matrix(1 0 0 1 106.3691 313.826)' class='st3 st4'></text>";
  msg +="      <text transform='matrix(1 0 0 1 100.4991 350.6501)' class='st3 st4'></text>";
  msg +="      <text transform='matrix(1 0 0 1 136.8878 351.6501)' class='st3 st5'>N</text>";
  msg +="    </g>";
  msg +="  </g>";
  msg +="<polyline points='322,83.2 399.9,46.9 415.5,80.5 322,124.1 '/>";
  msg +="<polyline points='78,335.8 0.1,372.1 -15.5,338.5 78,294.9 '/>";
  msg +="<polyline points='78,83.2 0.1,46.9 -15.5,80.5 78,124.1 '/>";
  msg +="<polyline points='322,335.3 400.9,372.1 416.5,338.5 322.2,294.6 '/>";
  msg +="</svg>";
  
  
  msg +="  <div class= 'header '>";
//  msg +="  <div class= 'btn-L '><a href= '/react'><br>";
  msg +="  <div class= 'btn-L '><a onclick='MoveCheck_EPM_OFF();'><br>";
  msg +="    <svg version='1.0' xmlns='http://www.w3.org/2000/svg'";
  msg +="    width='60pt' height='60pt' viewBox='0 0 1280.000000 1280.000000'";
  msg +="    preserveAspectRatio='xMidYMid meet'>";
  msg +="   <metadata>";
  msg +="   Created by potrace 1.15, written by Peter Selinger 2001-2017";
  msg +="   </metadata>";
  msg +="   <g transform='translate(0.000000,1280.000000) scale(0.100000,-0.100000)'";
  msg +="   fill='#000000' stroke='none'>";
  msg +="   <path d='M6605 11166 c-56 -25 -114 -102 -180 -239 -69 -148 -100 -213 -125";
  msg +="   -272 -10 -22 -47 -103 -83 -180 -63 -137 -91 -197 -147 -320 -28 -62 -34 -76";
  msg +="   -145 -315 -37 -80 -76 -163 -85 -185 -10 -22 -34 -75 -54 -118 -20 -42 -36";
  msg +="   -79 -36 -81 0 -2 -22 -50 -49 -107 -27 -57 -75 -160 -106 -229 -32 -69 -75";
  msg +="   -163 -97 -210 -22 -47 -57 -124 -79 -172 -21 -48 -43 -95 -48 -105 -6 -10 -47";
  msg +="   -99 -92 -198 -44 -99 -98 -217 -120 -262 -21 -45 -39 -84 -39 -86 0 -3 -22";
  msg +="   -51 -49 -108 -27 -57 -71 -153 -99 -214 -27 -60 -71 -155 -97 -210 -26 -55";
  msg +="   -75 -163 -110 -240 -34 -77 -88 -193 -119 -259 -31 -65 -56 -119 -56 -121 0";
  msg +="   -2 -21 -48 -46 -102 -55 -117 -62 -133 -155 -333 -63 -138 -72 -163 -76 -230";
  msg +="   -5 -65 -3 -78 15 -100 l20 -25 464 5 c254 3 614 5 798 5 l335 0 49 -25 c31";
  msg +="   -16 54 -36 64 -56 16 -35 21 -17 -87 -304 -21 -58 -53 -143 -70 -190 -17 -47";
  msg +="   -36 -94 -41 -105 -5 -11 -21 -54 -36 -95 -14 -41 -32 -88 -39 -105 -8 -16 -64";
  msg +="   -165 -126 -330 -61 -165 -121 -322 -131 -350 -11 -27 -30 -79 -43 -115 -13";
  msg +="   -36 -44 -119 -70 -185 -47 -123 -69 -181 -173 -460 -33 -88 -78 -209 -102";
  msg +="   -270 -23 -60 -52 -139 -65 -175 -13 -36 -44 -119 -70 -185 -25 -66 -62 -163";
  msg +="   -81 -215 -19 -52 -39 -104 -44 -115 -5 -11 -25 -65 -45 -120 -19 -55 -40 -109";
  msg +="   -45 -120 -6 -11 -28 -69 -50 -130 -21 -60 -60 -164 -85 -230 -25 -66 -57 -149";
  msg +="   -69 -185 -13 -36 -46 -126 -74 -200 -27 -74 -53 -150 -56 -168 -6 -36 17 -106";
  msg +="   33 -100 12 4 167 211 1506 2003 197 264 523 701 725 970 201 270 480 643 619";
  msg +="   830 140 187 273 365 296 395 55 72 175 232 625 835 205 275 395 529 422 565";
  msg +="   66 89 90 141 86 187 l-3 38 -200 6 c-110 4 -573 7 -1029 8 -751 1 -828 2 -822";
  msg +="   17 3 9 44 73 89 142 46 70 133 201 192 292 60 91 165 251 233 355 69 105 176";
  msg +="   267 237 360 62 94 177 269 257 390 79 121 198 301 263 400 65 99 182 277 260";
  msg +="   395 233 353 432 656 533 810 52 80 130 198 172 262 98 147 121 233 78 285 -16";
  msg +="   19 -2380 18 -2423 -1z'/>";
  msg +="   <path d='M5450 10521 c-562 -148 -1163 -468 -1635 -871 -718 -615 -1228 -1430";
  msg +="   -1430 -2285 -59 -249 -74 -345 -100 -645 -19 -219 -19 -367 0 -598 22 -267 32";
  msg +="   -346 75 -552 89 -427 195 -738 380 -1115 291 -591 727 -1127 1225 -1505 200";
  msg +="   -152 244 -173 307 -147 46 19 85 68 125 157 19 41 38 84 43 95 53 116 100 314";
  msg +="   100 422 0 72 -19 162 -48 222 -18 40 -59 82 -267 276 -190 178 -317 327 -471";
  msg +="   555 -363 535 -574 1221 -574 1863 0 405 93 854 260 1252 258 615 700 1148";
  msg +="   1255 1512 237 156 290 197 423 333 139 142 249 301 343 494 80 164 140 358";
  msg +="   164 529 8 58 15 58 -175 8z'/>";
  msg +="   <path d='M8876 9829 c-43 -38 -260 -338 -318 -439 -42 -74 -71 -175 -64 -223";
  msg +="   10 -63 29 -86 156 -188 396 -317 746 -786 957 -1284 50 -118 125 -326 142";
  msg +="   -395 5 -19 23 -87 39 -150 108 -409 130 -955 56 -1390 -31 -181 -127 -522";
  msg +="   -180 -637 -7 -17 -14 -33 -14 -36 0 -3 -23 -54 -51 -113 -269 -567 -670 -1024";
  msg +="   -1219 -1391 -204 -136 -455 -266 -675 -348 -246 -92 -469 -150 -712 -185 -189";
  msg +="   -27 -200 -28 -433 -36 -241 -8 -306 -23 -418 -98 -141 -94 -327 -327 -438";
  msg +="   -550 -41 -83 -46 -99 -38 -127 13 -47 48 -67 154 -88 331 -69 942 -76 1330";
  msg +="   -15 422 66 787 172 1152 333 1068 474 1880 1355 2278 2471 76 213 120 368 161";
  msg +="   557 5 27 12 57 14 68 20 94 56 354 65 464 13 172 13 549 0 706 -11 136 -44";
  msg +="   370 -65 460 -70 302 -114 456 -190 660 -276 740 -740 1384 -1355 1880 -135";
  msg +="   109 -181 135 -238 135 -43 0 -55 -5 -96 -41z'/>";
  msg +="   </g>";
  msg +="   </svg>";
     
  msg +="  </a></div>";
  msg +="  <div class= 'logo '> <width= '200 ' height= 'auto ' >";
  msg +="    <svg version= '1.1 ' id= 'レイヤー_1 ' xmlns= 'http://www.w3.org/2000/svg ' xmlns:xlink= 'http://www.w3.org/1999/xlink ' x= '0px '";
  msg +="   y= '0px ' viewBox= '-40 -10 321 81 ' style= 'enable-background:new 0 0 300 70; ' xml:space= 'preserve '>";
  
  msg +="<text transform= 'matrix(1 0 0 1 11.5039 80.5273) ' class= 's0 s1 s2 '>M300</text>";
  msg +="<text transform= 'matrix(1 0 0 1 2.5039 71.5273) ' class= 's1 s2 '>M300</text>";
  msg +="</svg>";
  msg +="</div>";
  msg +="  <div class= 'btn-R '><a href= '/fake_log'><br>";
  msg +="    <svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 24 24' width='80' height='80'><path class='heroicon-ui' d='M6 2h9a1 1 0 0 1 .7.3l4 4a1 1 0 0 1 .3.7v13a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V4c0-1.1.9-2 2-2zm9 2.41V7h2.59L15 4.41zM18 9h-3a2 2 0 0 1-2-2V4H6v16h12V9zm-2 7a1 1 0 0 1-1 1H9a1 1 0 0 1 0-2h6a1 1 0 0 1 1 1zm0-4a1 1 0 0 1-1 1H9a1 1 0 0 1 0-2h6a1 1 0 0 1 1 1zm-5-4a1 1 0 0 1-1 1H9a1 1 0 1 1 0-2h1a1 1 0 0 1 1 1z'/></svg>";
  msg +="  </a></div>";
  msg +="  </div>";
  msg +=" <br><br><br><br><br><br><br><br><br>";
  msg +="<body>";
  msg +="<div style='text-align: right'><button style='background:red;' ><font-size='40px'>";
  msg +="<a id = 'btn' onclick='MoveCheck_emergency();'>緊急離脱</a></font-size></button></div>";
  msg +="    <script>";
  msg +="        function MoveCheck_EPM_OFF() {";
  msg +="            if( confirm('EPMを無効化します') ) {";
  msg +="            window.location.href = '/fake_react';";
  msg +="            }else {";
  msg +="            alert('．．．');";
  msg +="            }";
  msg +="        }       ";
  msg +="        function MoveCheck_emergency() {";
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
  
