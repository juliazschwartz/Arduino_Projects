#include <CapacitiveSensor.h>

CapacitiveSensor   cs_2_4 = CapacitiveSensor(2,4); // 1M resistor between pins 2 & 4, pin 4 is sensor pin, add a wire and 
int cnt=0;
int in = 2; 
int out = 4;  
int state = HIGH;  
int r;           
int p = LOW;    
long time = 0;       
long debounce = 200;
int fadeValue;
void setup()
{
  pinMode(4, INPUT);
  /*    LED Outputs   */
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
}
void loop()                    
{
 
  r = digitalRead(4);
  if (r == HIGH && p == LOW && millis() - time > debounce) {    //Da primeira vez que eu encosto, isso roda direto depois de passar 200ms. Aí incrementa ctn.
                                                                //Nas outras vezes, p=r. Então, se eu tiro a mão, ele entra como LOW, mas r também é LOW, então não entra no loop de incremento. 
                                                                //Assim, ele fica na cor que estava, sem se alterar.
                                                                //Se eu tiro a mão, p entra como LOW, mas se eu encosto novamente, r entra como HIGH, assim, 
                                                                //entramos no loop de incremento e outro led acende.
                                                                //Se eu fico com a  mão, sem tirar
                                                                //millis() - time > debounce assegura que se passou 200ms entre um ciclo e outro
    cnt++;
  if (state == HIGH)    //. Na primeira vez que encostro, após os 200ms, state entra como HIGH e o tempo não incrementa. Nas outras ele é LOW e só continua incrementando o tempo.
     state = LOW;
    else                //o tempo nao passa se eu tiro a mao
    
    time = millis();
  }
  
  if(cnt == 1){
  //  digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
     for(int fadeValue = 0; fadeValue<= 255; fadeValue +=5) {
  analogWrite(5, fadeValue);
  delay(30);
 }
 
  }
  if(cnt == 2){
    digitalWrite(5, LOW);
   // digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
       for(int fadeValue = 0; fadeValue<= 255; fadeValue +=5) {
  analogWrite(6, fadeValue);
  delay(30);
 }
  }
  if(cnt == 3){
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
       
  }
  if(cnt > 3){
      cnt = 1;
  }
  p = r;
}
