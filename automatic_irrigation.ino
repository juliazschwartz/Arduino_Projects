//This project was designed to automatic irrigation, based on the solo humidity.

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE); //ENDEREÇO DO I2C E DEMAIS INFORMAÇÕES

//variáveis do programa
const int pinoSensor = A0;
const int pinoValvula = 10;
const int limiarSeco = 36;
const int tempoRega = 10;
int umidadeSolo = 0;

void setup () {

  pinMode (pinoValvula, OUTPUT);
  digitalWrite(pinoValvula, HIGH);
  lcd.begin(16, 2);
  lcd.print("Plantas da Julia");

  Serial.begin(9600);
}


void loop() {
  // put your setup code here, to run once:
  //dá uma primeira lida, após 20s (para testar se tá bugado ou não, assim que põe na tomada)
  for(int i=0; i<20; i++) {
  umidadeSolo= analogRead(pinoSensor);
  umidadeSolo= map(umidadeSolo, 1023, 0, 0, 100);
  lcd.setCursor(6,1);
  lcd.print(umidadeSolo);
  lcd.print(" %        ");
  delay(1000);
}
//depois dos 20s ele decide se rega ou não
if(umidadeSolo < limiarSeco) {
  lcd.setCursor(0,1);
  lcd.print("    Regando     ");
  digitalWrite(pinoValvula, LOW);
  delay(tempoRega*1000);
  digitalWrite(pinoValvula, HIGH);
}
else {
  lcd.setCursor(0,1);
  lcd.print("Solo Encharcado");
  delay(3000);
}

// fim do teste    
//fica 10h aguardando para ler a umidade de novo
for(int i=0; i<36000; i++) {
  lcd.setCursor(0,1);
  lcd.print("  Aguardando  ");
  delay(1000);

}
//lê a umidade do solo por 10 segundos
for(int i=0; i<10; i++) {
 umidadeSolo= analogRead(pinoSensor);
 umidadeSolo= map(umidadeSolo, 1023, 0, 0, 100);
  lcd.print(umidadeSolo);
  lcd.print(" %        ");
  delay(1000);
}
//depois dos 10s ele decide se rega ou não
if(umidadeSolo < limiarSeco) {
  lcd.setCursor(0,1);
  lcd.print("    Regando     ");
  digitalWrite(pinoValvula, LOW);
  delay(tempoRega*1000);
  digitalWrite(pinoValvula, HIGH);
}
else {
  lcd.setCursor(0,1);
  lcd.print("Solo Encharcado");
  delay(3000);
}
}
