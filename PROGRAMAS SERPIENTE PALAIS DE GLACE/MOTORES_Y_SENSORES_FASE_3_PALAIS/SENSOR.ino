
//-------------- INTERRUPCIONES --------------

//----------------------------------FRENTE
boolean miro_distancia(){
  boolean frente_obstaculo = false;

  sensordistancia ();

  if (distance < 47){ // limite de la distancia frontal en cm
    frente_obstaculo = true;
    //detener ();

    atras ();
    
    cont_obstaculo++; // esto estaba arriba de atras (); en algun momento

    if (cont_obstaculo = 6){
      
      giro_derecha (tiempo_del_paso);
            Serial.println("giro derecha");
      

    } 
    else if (cont_obstaculo = 6) {
      giro_izquierda (tiempo_del_paso);
            Serial.println("giro izquierda");

    }

    if(ver_datos){
      Serial.println("obstaculo adelante");
    }  
  } 
  else {
    if(ver_datos){
      //seguir adelante
      Serial.print(distance);
      Serial.println(" cm");
    }
  }
  return frente_obstaculo;
  cont_obstaculo = 0;

} 


//--------------- SENSORES ----------------

//----------------------- SENSOR DISTANCIA
void sensordistancia () {
  // boolean vuelve = false;
  long duration;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  // distance = (duration/2) / 29.1;
  distance = duration/58.2;
}

//----------------------------------- SENSOR VELOCIDAD

// LDR + 10k

void velocidad_luz (){

  vel = analogRead (LDR);

  /*
  velmap = map(vel, 0, 1023, 80, 300 );
   velmap = constrain(velmap,100,300 ); 
   
   if (velmap < 110) {
   velmap = no_arranque;
   } 
   else if (velmap > 230) {
   velmap = 255;
   } 
   
   */
  if(ver_datos){
    Serial.print(velmap);
    Serial.println(" luz");
  }
}

//------------------------------------- SENSOR DE LIMITES

/* Sensores de limite:
 +5v  --> C SWITCH
 Ground -->  10k --> A0/A1 ---> NO SWITCH */

//------------------------------------ CHOCO IZQUIERDA

boolean limite_izquierda(){

  boolean izquierda_obstaculo = false;
  estado_limite_1 = digitalRead(limite1);

  if (estado_limite_1 == HIGH) {     
    // turn LED on:    
    // digitalWrite(E1, HIGH);  
    izquierda_obstaculo = true;


    if(ver_datos){
      Serial.println("choco izquierda");
      // giro_izquierda (tiempo_del_paso);
      atras ();
    }
  } 
  else {
    //seguir adelante
  }
  return izquierda_obstaculo;
} 


//-------------- CHOCO DERECHA

boolean limite_derecha(){

  boolean derecha_obstaculo = false;
  estado_limite_2 = digitalRead(limite2);

  if (estado_limite_2 == HIGH) {     
    // digitalWrite(E1, HIGH);  
    derecha_obstaculo = true;
    if(ver_datos){
      Serial.println("choco derecha");
      atras ();
      //giro_derecha (tiempo_del_paso);
    }
  } 
  else {
    //seguir adelante
  }
  return derecha_obstaculo;
} 

//----------------------------------ESPERA SENSORES
/*
void espera_con_sensores (int _tiempo){
 int t_aux = int(_tiempo /50);
 for( int i = 0 ; i<t_aux ;i++){
 if(frente_obstaculo){
 i = t_aux +1;
 }
 if(derecha_obstaculo){
 i = t_aux +1;
 }
 if(izquierda_obstaculo){
 i = t_aux +1;
 }
 delay (50);
 }
 
 }
 */


















