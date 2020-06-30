
/* 
 -----QUETZATCOATL-BOT---
 
 Mario Alberto Guzman Cerdio
 mariouzzzman@gmail.com
 
 ROBOTICA
 Prof: Miguel Grassi
 Maetria en estetica de las artes electronicas
 2015
 
 Funciones:
 
 - Motores delanteros alternan encendido.
 - Velocidad controlada a partir de la luz, 
 si el mapeo de la informacion del LDR baja mas de 110 los
 motores se detienen, si sube mas de 230 = 255.
 - Limites: si hay contacto con un obstaculo el robot hace marcha 
 atras
 - 2 leds rojo y verde para indicar presencia o ausencia de obstaculos
 
 */


//-------------------------------------BOOLEAN

boolean ver_datos = false;

boolean miro_distancia ();
boolean frente_obstaculo;

boolean limite_izquierda();
boolean izquierda_obstaculo;

boolean limite_derecha();
boolean derecha_obstaculo;

//-------------------------------------LEDS

const int verde = 11; // Ultrasound signal pin
const int rojo = 10; // Ultrasound signal pin

int _tiempo_led;
int _espera_led;

const int IR = 8; // Ultrasound signal pin


//-------------------------------------VALORES SENSORES

int _tiempo = 1000;


//------------------------------------- SENSOR DISTANCIA

const int trigPin = 13; // Ultrasound signal pin
const int echoPin = 12;

int distance;
int distancia_contador_obstaculo;

//------------------------------------- SENSOR DE VELOCIDAD

const int LDR = A2;
int vel;
int velmap = 255; // cambiar para que funcione a una velocidad constante??
int ajuste_pote = 25;

//------------------------------------- SENSOR DE LIMITES

const int limite1 = A0;
const int limite2 = A1;

int estado_limite_1 = 0;         
int estado_limite_2 = 0;  

int cont_obstaculo = 0;

// ------------------------------------- MOTORES

int E1  = 5;  // Enable Pin para motor 1 // L239D 1 // Arduino pwm
int E2  = 3;  // Enable Pin para motor 2// L239D 9  // Arduino pwm

int motorizin1  = 7;  // Control pin 1 para motor 1 // L239D 7
int motorizin2  = 6;  // Control pin 2 para motor 1 // L239D 2 // Arduino pwm

int motordin3  = 4;  // Control pin 1 para motor 2 // L239D 15
int motordin4  = 2;  // Control pin 2 para motor 2 // L239D 10

/*int motor_left[] = { 7, 6};
 int motor_right[] = { 4, 2};*/

//---------------------------------------- VALORES MOTORES

int tiempo_del_paso = 1000; // tiempo prendido de cada ruedita
//int espera = 1000;

int arranque= 255; // velocidad de arranque
int no_arranque = 0; // velocidad de detencion

boolean que_rueda_muevo = false;//que rueda muevo
int tiempo_paso = 0 ;//contador
int limite_tiempo_paso = 12;//cunto tiempo cda rueda

int limite_tiempo_paso_atras = 10;//cunto tiempo cda rueda


void setup(){ //-------------------------------- SETUP
  Serial.begin(9600);

  //---PIN LUCES---
  pinMode(verde, OUTPUT);  
  pinMode(rojo, OUTPUT);  

  pinMode(IR, OUTPUT);  

  //---SENSOR VELOCIDAD---
  pinMode(LDR, INPUT);    

  //---SENSOR LIMITE---
  pinMode(limite1, INPUT);    
  pinMode(limite2, INPUT);  

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

void loop(){ //----------------------------------- LOOP

  //Serial.print(distance);
  //Serial.println(" cm");
     // int distancia_contador_obstaculo= int (random (6, 7));


  digitalWrite(IR, HIGH); // infrarojo


// Serial.print(velmap);
  //Serial.println(" luz");

  miro_todos_sensores ();  
  velocidad_luz ();

  if(frente_obstaculo == false && derecha_obstaculo == false &&izquierda_obstaculo == false){   //solo mueve si no hay obstaculo
    adelante (); 
  }

  leds ();



  delay(50);


} //------------------------------------------------- LOOP

//------------------------------------------------- //------------------------------------------------- 

//------------------------------------------------- MIRO TODOS LOS SENSORES

void miro_todos_sensores () {
  frente_obstaculo = miro_distancia();
  derecha_obstaculo = limite_derecha();
  izquierda_obstaculo = limite_izquierda();
  //velocidad_luz ();
}

// ------------------------------------------------- ADELANTE

void adelante () { 
  tiempo_paso ++;
  if(tiempo_paso >= limite_tiempo_paso){
    que_rueda_muevo = !que_rueda_muevo;  // ! significa que vale lo contrario
    tiempo_paso = 0;
  }
  if(ver_datos){
    Serial.print("Paso: " );
    Serial.println( que_rueda_muevo );
  }
  if(que_rueda_muevo){
    adelante_motor_2 (tiempo_del_paso); //prendo derecha
  }
  else{
    adelante_motor_1 (tiempo_del_paso); //prendo iaquierda
  }
}


// ------------------------------------------------- ATRAS

void atras () { 
  tiempo_paso ++;
  if(tiempo_paso >= limite_tiempo_paso_atras){
    que_rueda_muevo = !que_rueda_muevo;  // ! significa que vale lo contrario
    tiempo_paso = 0;
  }
  if(ver_datos){
    Serial.print("Paso: " );
    Serial.println( que_rueda_muevo );
    //delay (25);
  }
  if(que_rueda_muevo){
    atras_motor_1 (tiempo_del_paso); //prendo derecha
    //apago izquerda

  }
  else{
    atras_motor_2 (tiempo_del_paso); //prendo iaquierda
    //apago derecha
  }

  // velocidad_luz ();
}


//--------------------------LEDS

void leds () {

  if(frente_obstaculo || derecha_obstaculo || izquierda_obstaculo){   //solo mueve si no hay obstaculo
    digitalWrite(verde, LOW); // vel motor 1
    digitalWrite(rojo, HIGH); // vel motor 1

  } 
  else {
    digitalWrite(verde, HIGH); // vel motor 1
    digitalWrite(rojo, LOW); // vel motor 1
  }

}



/*void leds (int _tiempo_led, int _espera_led){
 digitalWrite(verde, HIGH);
 digitalWrite(rojo, LOW);
 
 for(int i = 0 ; i < _tiempo_led; i++){
 // sensores ();
 if(frente_obstaculo || derecha_obstaculo || izquierda_obstaculo){   //solo mueve si no hay obstaculo
 digitalWrite(verde, HIGH);
 digitalWrite(rojo, LOW);
 
 break;
 }
 delay(1);
 }
 
 digitalWrite(verde, HIGH);
 digitalWrite(rojo, LOW);
 
 espera(_espera_led);
 }
 
 void espera(int _tiempo_led){
 for(int i = 0 ; i < _tiempo_led; i++){
 //  sensores ();
 if(frente_obstaculo || derecha_obstaculo || izquierda_obstaculo){   //solo mueve si no hay obstaculo
 digitalWrite(verde, HIGH);
 digitalWrite(rojo, LOW);
 
 
 break;
 }
 delay(1);
 }
 }
 */









