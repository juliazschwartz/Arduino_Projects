//This code is from the project made for a new type of detection for Point of Care (POC) diagnosis systems,
//based in fluorescence results from molecular assays.
//This was first designed to read different levels of fluorescence from CRISPR -Sherlock systems (https://sherlock.bio/) 
// and DETECTR systems (https://mammoth.bio/diagnostics/), as a portable method to detect covid in communities, in the 2020 pandemics,
// but other uses can be made.
// Some adjustments are still required, as the sensitivity of the LDR light sensor.


//Ajuste para não agrupar valores com divisores de tensão.
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); //ENDEREÇO DO I2C E DEMAIS INFORMAÇÕES
float LDRValor = 0;
float LDRValor2 = 0;
float media = 0;
int ValorMin = 0;
int ValorMax = 1023;
int ledPin = 3;
int ledPin2 = 5;
int ledPin3 = 6;




void setup() {
  // put your setup code here, to run once: 
  pinMode(ledPin,OUTPUT); //define a porta 10 como saída
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(pino265, OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.setCursor(0,0);
  lcd.write("fluorescencia: ");
  
  digitalWrite(pino265,HIGH);
}

  
void loop() {
  
for (int readIndex = 0; readIndex<=5; readIndex++){

    LDRValor= (analogRead(A1));
    delay(200);
    if (LDRValor > ValorMax){
      ValorMax = LDRValor ;
    }
    if (LDRValor < ValorMin){
      ValorMin = LDRValor;
    }
     
    
    LDRValor2 = LDRValor - 0;
    LDRValor2 = map(LDRValor2, ValorMin, ValorMax, 0, 100);
    LDRValor2 = constrain(LDRValor2, 0, 100);
    
//Com um resistor de 10k. Assim, em luz ambiente dá 90. Mas ele fica sensível em toda os outros espectros (não agrupa).
    LDRValor2 = map(LDRValor2, 10, 99, 0, 100);
    LDRValor2 = constrain(LDRValor2, 0, 100);
    
    media = media + LDRValor2;
    delay(200);
    
 

  
    
}

media= media/7;
lcd.setCursor(2,1);
lcd.print(media);
Serial.println(media);
lcd.setCursor(8,1);
lcd.print(" %        ");

if (media > 0.00001 and  media < 50 ) { 
  digitalWrite(ledPin2,HIGH);
}

 // senão, apaga o led
else   digitalWrite(ledPin2, LOW);

if (media > 50) {
  digitalWrite(ledPin,HIGH );
 
}
else   digitalWrite(ledPin, LOW);


if (media <= 0.00001){
  digitalWrite(ledPin3, HIGH );
 
}
else   digitalWrite(ledPin3, LOW);

}
