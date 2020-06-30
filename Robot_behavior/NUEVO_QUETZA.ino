
/*
  -----QUETZATCOATL-BOT---

  Mario Alberto Guzman Cerdio
  mariouzzzman@gmail.com  */


//-------------------------------------BOOLEAN

boolean ver_datos = true;

boolean miro_distancia (); // funcion
boolean frente_obstaculo;

boolean hay_alguien = true;

boolean ver_distancia = true;

boolean prender_IR = true;

//-------------------------------------LEDS

const int IR = 8; // Luces infrarojas
//int cantidad_luz;

//int prender_IR = 0;
//int limite_prender_IR = 3;

//-------------------------------------CONTADOR DE VUELTAS
//cantidad de vueltas que gira quetzi antes de detenerse a mirar el pir
//se detiene, pero no sensa el pir

int vueltas = 0;
//------------------------------------- SENSOR DISTANCIA

const int trigPin = 13; // Ultrasound signal pin
const int echoPin = 12;

int distance;
int distancia_contador_obstaculo;
//------------------------------------- SENSOR DE LIMITES

int cont_obstaculo = 0;

// ------------------------------------- MOTORES

int E1  = 5;  // Enable Pin para motor 1 // L239D 1 // Arduino pwm
int E2  = 3;  // Enable Pin para motor 2// L239D 9  // Arduino pwm

int motorizin1  = 7;  // Control pin 1 para motor 1 // L239D 7
int motorizin2  = 6;  // Control pin 2 para motor 1 // L239D 2 // Arduino pwm

int motordin3  = 4;  // Control pin 1 para motor 2 // L239D 15
int motordin4  = 2;  // Control pin 2 para motor 2 // L239D 10

//---------------------------------------- VALORES MOTORES

int tiempo_del_paso = 0; // 0 tiempo prendido de cada ruedita

int arranque = 190; // 190// 230 velocidad de arranque
int no_arranque = 0; // 0 velocidad de detencion

boolean que_rueda_muevo = false;//que rueda muevo
int tiempo_paso = 0 ;//contador

int limite_tiempo_paso = 36;//30 cunto tiempo cda rueda
int limite_tiempo_paso_atras = 20; //20 cunto tiempo cda rueda

void setup() { //-------------------------------- SETUP
  Serial.begin(9600);

  //---PIN LUCES---
  pinMode(IR, OUTPUT);
  //analogWrite(IR, cantidad_luz); // infrarojo
  digitalWrite(IR, HIGH); // infrarojo

  //---SENSOR DISTANCIA --
  pinMode ( trigPin, OUTPUT );
  pinMode ( echoPin, INPUT );

  //----MOTORES------
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);

  pinMode(motorizin1, OUTPUT);
  pinMode(motorizin2, OUTPUT);
  pinMode(motordin3, OUTPUT);
  pinMode(motordin4, OUTPUT);

} //---------------------------------------------- SETUP

void loop() { //----------------------------------- LOOP


      analogWrite(E1, 0 ); // vel motor 1
      analogWrite(E2, no_arranque ); // vel motor 2
      //direccio motor 2
      digitalWrite( motordin3, HIGH );
      digitalWrite( motordin4, LOW );



   // miro_todos_sensores ();
    //if (frente_obstaculo == false) { //solo mueve si no hay obstaculo
    //  adelante ();
   // } 


} //---------------- LOOP

//------------------------------------------------- //-------------------------------------------------

