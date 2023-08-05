/*Con digitalRead(HIGH)*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);

int luzRoja = 2;
int luzAmarilla = 3;
int luzVerde = 4;
int luzAzul = 5;
int luzBlanca = 6;
int botonRojo = 12;
int botonAmarillo = 11;
int botonVerde = 10;
int botonAzul = 9;
int botonBlanco = 8;
int contador = 0;
int miArray[250];
int intentos = 0;
boolean fin = false;
int buzzer = 7;
int contadorRondas = 0;
int record = 0;

void setup()
{

  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 1);
  lcd.print("Simon Dice");
 
  pinMode(luzRoja, OUTPUT);
  pinMode(luzAmarilla, OUTPUT);
  pinMode(luzVerde, OUTPUT);
  pinMode(luzAzul, OUTPUT);
  pinMode(luzBlanca, OUTPUT);
  pinMode(botonRojo, INPUT);
  pinMode(botonAmarillo, INPUT);
  pinMode(botonVerde, INPUT);
  pinMode(botonAzul, INPUT);
  pinMode(botonBlanco, INPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  contador = 0;
  intentos = 0;
  fin = false;
  contadorRondas = 0;
 
  mostrarTitulo();
 
  while(digitalRead(botonBlanco) == HIGH && !fin){
    iniciarJuego();
    generarSecuencia();
    mostrarInstrucciones();
    for (int i = 0; i < intentos; i++){
       delay(700);
       for (int j = 0; j <= contador; j++){
         digitalWrite(miArray[j],HIGH);
         sonar(miArray[j]);
         delay(300);
         digitalWrite(miArray[j],LOW);
         delay(300);
       }
       for (int k = 0; k <= contador; k++){
         if (encenderLuz() == miArray[k]){
          digitalWrite(miArray[k],HIGH);
          delay(200);
          digitalWrite(miArray[k],LOW);
          delay(200);
          } else {
            pantallaFinal();
            finalizarJuego();
            fin = true;
            delay(5000);
            break;
              }
        }
      if (fin){
        break;
      } else {
        contador++;
        mostrarRondas();
      }
    }
    if (!fin){
      mostrarGanar();
      ganarJuego();
    }
  }
}

void mostrarInstrucciones(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" === Simon Dice ===");
  lcd.setCursor(0, 1);
  lcd.print("Repite la secuencia ");
  lcd.setCursor(0, 2);
  lcd.print("     de colores");
  delay(2000);
}

void mostrarGanar(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" === Simon Dice ===");
  lcd.setCursor(0, 1);
  lcd.print("     HAS GANADO");
  lcd.setCursor(0, 2);
  lcd.print("Rondas totales: ");
  lcd.setCursor(16, 2);
  if (contadorRondas == 0){
    lcd.print(contadorRondas);
  } else {
    lcd.print(contadorRondas - 1);
  }
  if (record < contadorRondas){
    record = contadorRondas - 1;
  }
  lcd.setCursor(0, 3);
  lcd.print("Record rondas: ");
  lcd.setCursor(15, 3);
  lcd.print(record);
  
}

void mostrarRondas(){
  contadorRondas = contador + 1;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("===Numero de ronda==");
  lcd.setCursor(9, 1);
  lcd.print(contadorRondas);
}

void mostrarTitulo(){
  lcd.setCursor(0, 0);
  lcd.print(" === Simon Dice ===");
  lcd.setCursor(0, 1);
  lcd.print(" Pulsa boton blanco");
  lcd.setCursor(0, 2);
  lcd.print("    para empezar    ");
}

void elegirNivel(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("===Elige un nivel===");
  lcd.setCursor(0, 1);
  lcd.print("1=Rojo    2=Amarillo");
  lcd.setCursor(0, 2);
  lcd.print("3=Verde   4=Azul");
}

void pantallaFinal(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" === Simon Dice ===");
  lcd.setCursor(0, 1);
  lcd.print("     HAS PERDIDO");
  lcd.setCursor(0, 2);
  lcd.print("Rondas totales: ");
  lcd.setCursor(16, 2);
  if (contadorRondas == 0){
    lcd.print(contadorRondas);
  } else {
    lcd.print(contadorRondas - 1);
  }
  if (record < contadorRondas){
    record = contadorRondas - 1;
  }
  lcd.setCursor(0, 3);
  lcd.print("Record rondas: ");
  lcd.setCursor(15, 3);
  lcd.print(record);
  
}



void sonar(int color){
  if (color == luzRoja){
    tone(buzzer,523.25,300);
  }
  if (color == luzAmarilla){
    tone(buzzer,659.26,300);
  }
  if (color == luzVerde){
    tone(buzzer,783.99,300);
  }
  if (color == luzAzul){
    tone(buzzer,987.77,300);
  }
 
}

int encenderLuz(){
  int opcion = 0;
  while (opcion == 0){
    if (digitalRead(botonRojo) == HIGH) {
      sonar(luzRoja);
      opcion = mantenerLuz(botonRojo, luzRoja);
    }
    if (digitalRead(botonAmarillo) == HIGH) {
      sonar(luzAmarilla);
      opcion = mantenerLuz(botonAmarillo, luzAmarilla);
    }
    if (digitalRead(botonVerde) == HIGH) {
      sonar(luzVerde);
      opcion = mantenerLuz(botonVerde, luzVerde);
    }
    if (digitalRead(botonAzul) == HIGH) {
      sonar(luzAzul);
      opcion = mantenerLuz(botonAzul, luzAzul);
    }
  }
  return opcion;
}

int mantenerLuz(int boton, int luz){
  while(digitalRead(boton) == HIGH){
    digitalWrite(luz,HIGH);
  }
  while(digitalRead(boton) == HIGH){
    digitalWrite(luz,LOW);
  }
  return luz;
}
 
 void iniciarJuego() {
   for (int i = 2; i <= 6; i++){
     digitalWrite(i,HIGH);
   }
   musicaIntro();
   elegirNivel();
   for (int i = 2; i <= 6; i++){
     digitalWrite(i,LOW);
   }  
   delay(1000);
}
void generarSecuencia(){
  while (intentos == 0){
    if(digitalRead(botonRojo) == LOW && digitalRead(botonAmarillo) == LOW && digitalRead(botonVerde) == LOW && digitalRead(botonAzul) == LOW){
      for (int i = 2; i <= 5; i++){
       digitalWrite(i,HIGH);
      }
      for (int i = 2; i <= 5; i++){
       digitalWrite(i,LOW);
      }
    }
   
    if (digitalRead(botonRojo) == HIGH) {
      intentos = 4;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("===Elige un nivel===");
      lcd.setCursor(0, 1);
      lcd.print("     Has elegido");
      lcd.setCursor(0, 2);
      lcd.print("     NIVEL FACIL");
      superMario();
      for (int i = 2; i <= 5; i++){
       digitalWrite(i,LOW);
      }
    }
    if (digitalRead(botonAmarillo) == HIGH) {
      intentos = 8;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("===Elige un nivel===");
      lcd.setCursor(0, 1);
      lcd.print("     Has elegido");
      lcd.setCursor(0, 2);
      lcd.print("  NIVEL INTERMEDIO");
      superMario();
      for (int i = 2; i <= 5; i++){
       digitalWrite(i,LOW);
      }
    }
    if (digitalRead(botonVerde) == HIGH) {
      intentos = 12;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("===Elige un nivel===");
      lcd.setCursor(0, 1);
      lcd.print("     Has elegido");
      lcd.setCursor(0, 2);
      lcd.print("    NIVEL DIFICIL");
      superMario();
      for (int i = 2; i <= 5; i++){
       digitalWrite(i,LOW);
      }
    }
    if (digitalRead(botonAzul) == HIGH) {
      intentos = 250;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("===Elige un nivel===");
      lcd.setCursor(0, 1);
      lcd.print("     Has elegido");
      lcd.setCursor(0, 2);
      lcd.print("   NIVEL EXPERTO");
      superMario();
      for (int i = 2; i <= 5; i++){
       digitalWrite(i,LOW);
      }
    }
  }
  for(int i = 0; i < intentos; i++){
    miArray[i] = random(2,6);
  }
}
void finalizarJuego() {
  delay(500);
  for (int i = 2; i <= 6; i++){
     digitalWrite(i,HIGH);
   }
   tone(buzzer,261.63);
   delay(3000);
   noTone(buzzer);
   for (int i = 2; i <= 6; i++){
     digitalWrite(i,LOW);
   }  
   delay(500);
}

void ganarJuego() {
  int vueltas = 0;
  sevenNationArmy();
  while(vueltas < 6){
   for (int i = 2; i <= 6; i++){
     digitalWrite(i,HIGH);
   }
   delay(100);
   for (int i = 2; i <= 6; i++){
     digitalWrite(i,LOW);
   }
   delay(100);
    vueltas+= 1;
  }
}

void sevenNationArmy(){
  float Mi = 659.26;
  float Sol = 783.99;
  float Re = 587.33;
  float Do = 523.25;
  float Si = 493.88;
 
  for(int i = 2; i <= 6; i++){
    digitalWrite(i,HIGH);
  }
  tone(buzzer,Mi);
  delay(500);
  noTone(buzzer);
  delay(250);
  tone(buzzer,Mi);
  delay(250);
  tone(buzzer,Sol);
  delay(333);
  tone(buzzer,Mi);
  delay(333);
  tone(buzzer,Re);
  delay(333);
  tone(buzzer,Do);
  delay(1000);
  tone(buzzer,Si);
  delay(500);
  noTone(buzzer);
  delay(500);

  tone(buzzer,Mi);
  delay(500);
  noTone(buzzer);
  delay(250);
  tone(buzzer,Mi);
  delay(250);
  tone(buzzer,Sol);
  delay(333);
  tone(buzzer,Mi);
  delay(333);
  tone(buzzer,Re);
  delay(333);
  tone(buzzer,Do);
  delay(333);
  tone(buzzer,Re);
  delay(333);
  tone(buzzer,Do);
  delay(333);
  tone(buzzer,Si);
  delay(500);
  noTone(buzzer);
  delay(500);
  for(int i = 2; i <= 6; i++){
    digitalWrite(i,LOW);
  }
}

void superMario(){
  float Mi = 659.26;
  float Sol = 783.99;
  float Do = 523.25;
  float SolGrave = 392.00;
  for(int i = 2; i <= 6; i++){
    digitalWrite(i,LOW);
  }
  delay(250);
  for(int i = 2; i <= 6; i++){
    digitalWrite(i,HIGH);
  }
  noTone(buzzer);
  delay(250);
  tone(buzzer,Mi);
  delay(125);
  noTone(buzzer);
  delay(125);
  tone(buzzer,Mi);
  delay(125);
  noTone(buzzer);
  delay(125);
  tone(buzzer,Mi);
  delay(125);
  noTone(buzzer);
  delay(125);
  tone(buzzer,Do);
  delay(125);
  tone(buzzer,Mi);
  delay(250);
  tone(buzzer,Sol);
  delay(250);
  noTone(buzzer);
  delay(250);
  tone(buzzer,SolGrave);
  delay(250);
  noTone(buzzer);
  delay(250);
  for(int i = 2; i <= 6; i++){
    digitalWrite(i,LOW);
  }
}

void musicaIntro() {
  float Do = 523.25;
  float Mi = 659.26;
  float Sol = 783.99;
  float Si = 987.77;
  float DoAgudo = 1046.50;
 
  tone(buzzer,Do);
  delay(125);
  tone(buzzer,Mi);
  delay(125);
  tone(buzzer,Sol);
  delay(125);
  tone(buzzer,DoAgudo);
  delay(250);
  tone(buzzer,Si);
  delay(125);
  tone(buzzer,DoAgudo);
  delay(250);
  noTone(buzzer);
  delay(250);
}
