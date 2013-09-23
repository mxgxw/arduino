#include "name.h"
// Modificar aquí para agregar más motores
#define MOTORES 2

int lineasMotor[MOTORES][2] = {
  {3, 4}, // Driver motor 0
  {5, 6}  // Driver motor 1 
  // Si hay mas motores agregarlos aqui con sus
  // respectivas líneas luego de modificar "MOTORES"
  // en la parte inferior
};

void setup() {
  // Configura todas las líneas de motor
  // definidas en líneasMotor como Salidas
  for(int i = 0; i < MOTORES; i++) {
    pinMode(lineasMotor[i][0],OUTPUT);
    pinMode(lineasMotor[i][1],OUTPUT);
  }
}

// Esta función simplifica el código de controles de motores
// DC haciendo más fácil su lectura, toma como parámetro
// el número de motor y un "comando" que está definidio
// en el archivo encabezado llamado "name.h". Se utilizan
// comandos sencillos para facilitar la lectura del código
void controlarMotor(int numMotor, comandos accion) {
   switch(accion) {
     case DETENER:
       digitalWrite(lineasMotor[numMotor][0],0);
       digitalWrite(lineasMotor[numMotor][1],0);
       break;
     case ADELANTE:
       digitalWrite(lineasMotor[numMotor][0],1);
       digitalWrite(lineasMotor[numMotor][1],0);
       break;
     case REVERSA:
       digitalWrite(lineasMotor[numMotor][0],0);
       digitalWrite(lineasMotor[numMotor][1],1);
       break;
   }
}

void loop() {
  // EJEMPLOS DE CONTROL motor 0 en líneas 3 y 4
  controlarMotor(0,ADELANTE);
  delay(1000);
  controlarMotor(0,REVERSA);
  delay(1000);
  controlarMotor(0,DETENER);
  delay(1000);
  
  // EJEMPLOS DE CONTROL motor 1 en líneas 5 y 6
  controlarMotor(1,ADELANTE);
  delay(1000);
  controlarMotor(1,REVERSA);
  delay(1000);
  controlarMotor(1,DETENER);
  delay(1000);
}
