uint32_t chipId = 0;
void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  for(int i=0; i<17; i=i+8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }  
}

void loop() {
  String str1;
  // put your main code here, to run repeatedly:
  //com9 ==>14908468
  //com15==>14026897
  //com16==>14018061

  if(chipId==14908468){
      Serial.println("AAA");
    }else{
      Serial.println("NOO");
      }
 

}
