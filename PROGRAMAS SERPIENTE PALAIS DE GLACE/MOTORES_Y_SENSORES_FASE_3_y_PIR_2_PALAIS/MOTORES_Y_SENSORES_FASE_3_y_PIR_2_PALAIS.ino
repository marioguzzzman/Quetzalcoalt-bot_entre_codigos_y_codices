
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
//-------------------------------------PIR

boolean accion = false;
int tiempo_accion = 0;
int limite_accion = 1300; // 1700

boolean entrarEnSensadoEstatico = false;

int valor_pir = 0; // valor del pir
int pin_sensor = A2; // entrada de PIR

//---------
int calibrationTime = 7;
//the time when the sensor outputs a low impulse

//-------------------------------------LEDS


const int IR = 8; // Luces infrarojas


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

int arranque = 250; // 230 velocidad de arranque
//int arranqueiz = 245; // 230 motor a 165 rpm 1:48
//int arranqueder = 245; // 230 motor a 120 rpm 1:120

int no_arranque = 0; // 0 velocidad de detencion

boolean que_rueda_muevo = false;//que rueda muevo
int tiempo_paso = 0 ;//contador

int limite_tiempo_paso = 60; //30 con azules antes 12 con blancas //195 cunto tiempo cda rueda
int limite_tiempo_paso_atras =40;// 20 con azules 10 con blancas 170 cunto tiempo cda rueda


void setup() { //-------------------------------- SETUP
  Serial.begin(9600);

  //---PIN LUCES---

  pinMode(IR, OUTPUT);
  digitalWrite(IR, HIGH); // infrarojo

  //----------- PIR ------------
  pinMode(pin_sensor, INPUT);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(".");
    Serial.println(miro_pir());
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);

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

  //Serial.println(tiempo_accion);
  tiempo_accion--; // int tiempo_accion = 0;

  // PROCEDMIENTOS DE SENSADO CON EL PIR
  if (entrarEnSensadoEstatico) {
    sensadoEstatico();
  } else {
    if (vueltas == 2) {
      detener ();
      delay (7000); // tiempo para estabilizar sensor 6 seg aprox
      hay_alguien = miro_pir ();

      vueltas = 0;

      if (hay_alguien == true) {
        
        tiempo_accion = limite_accion;
      } else {
        //tiempo_accion = 10;
        entrarEnSensadoEstatico = true;
      }
    }

    if (tiempo_accion < 1) {
      detener ();
      tiempo_accion = limite_accion;
      vueltas++;
      delay (3600); // tiempo que espera y chillea entre vueltas
     Serial.println("pausa");
    }
  }


  if (hay_alguien == true) {

    //  BLOQUESITO DE ACCION

    miro_todos_sensores ();
    // velocidad_luz ();
    if (frente_obstaculo == false) { //solo mueve si no hay obstaculo
      adelante ();

    }
    // leds ();
    //delay(50);

    // BLOQUESITO DE ACCION /

  }

  // Serial.print(velmap);
  //Serial.println(" luz");

  /*****  BLOQUESITO DE ACCION

    miro_todos_sensores ();
    // velocidad_luz ();
    if(frente_obstaculo == false && derecha_obstaculo == false &&izquierda_obstaculo == false){   //solo mueve si no hay obstaculo
      adelante ();
    }
    leds ();
    delay(50);

    BLOQUESITO DE ACCION ******/

} //---------------- LOOP

//------------------------------------------------- //-------------------------------------------------

void sensadoEstatico() {
  delay(500);
  hay_alguien = miro_pir ();
  if (hay_alguien) {
    entrarEnSensadoEstatico = false;
  }
}




/*//--------------------------LEDS

  void leds () {

  if (frente_obstaculo || derecha_obstaculo || izquierda_obstaculo) { //solo mueve si no hay obstaculo
    digitalWrite(verde, LOW); // vel motor 1
    digitalWrite(rojo, HIGH); // vel motor 1

  }
  else {
    digitalWrite(verde, HIGH); // vel motor 1
    digitalWrite(rojo, LOW); // vel motor 1
  }

  }
*/









