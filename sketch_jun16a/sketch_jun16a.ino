void setup() {
  

}

void loop() { float samplerate=500;
float freq=50;
float q=1/pow(2,1/2);    
float omega = 2.0f*3.14159265f*freq/samplerate;
float alpha = sin(omega) / (2.0f * q);
 
float a0;
float a1;
float a2 ;
float b0 ;
float b1 ;
float b2 ;
float x,y,n ;

 y[n]=(b0/a0)*x[n]+(b1/a0)*x[n-1]+(b2/a0)*x[n-2]-(a1/a0)*y[n-1]-(a2/a0)*y[n-2];

}
