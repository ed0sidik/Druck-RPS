#include <FreqCount.h>
int i, j, k;
float K[5][4];
float X;
float Y;
float P;
float Fx;
float Ty;
float Freq = 30564;
float Temp = 529.5;
int test = 4321;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(5000);
//  Serial1.begin(9600);
//  Serial1.setTimeout(5000);
//  FreqCount.begin(1000);
  analogReference(INTERNAL);
  
  i = 0;
  j = 0;
  k = 0;
}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned long count;
  float voltage;

  if(FreqCount.available()){
    count = FreqCount.read()+4;
//    Serial.print("Freq : ");
//    Serial.println(count);
    float adc = analogRead(0);
    voltage = (adc*1.1)/1024 * 979.889 + 3.171;
//    Serial.print("Voltage : ");
//    Serial.println(voltage,4);
    Fx = float(count) - X;
    //Fx = Freq -X;
    Ty = voltage - Y;
    //Ty = Temp - Y;
    P = 0;

    for(i=0;i<=4;i++){
      for(j=0;j<=3;j++){
        P += K[i][j]*pow(Fx,i)*pow(Ty,j);
      }
    }
    Serial.println(P,2);
  }

}


void serialEvent() {
  if(Serial.available()>0){
    // Read serial until LF
    String input = Serial.readStringUntil(10);
    input.trim();
    //
    if(i<5){
      K[i][j] = input.toDouble();
      delay(50);
      Serial.println(K[i][j],30);
      //Serial.println(1234);
      if(j<3){
        j++;
      }
      else{
        j=0;
        i++;
      }
    }

    else{
      if(k==0){
        X = input.toDouble();
        k++;
        Serial.println(X,2);
      }
      else if(k==1){
        Y = input.toDouble();
        Serial.println(Y,4);
        FreqCount.begin(1000);
        k++;
      }
      else{

      }
    }
  }
}

/*void serialEvent1() {
  if(Serial1.available()>0){
    // Read serial until LF
    String input = Serial1.readStringUntil(10);
    input.trim();
    float K = input.toDouble();
    delay(50);
    Serial1.println(K);
  }
}*/
