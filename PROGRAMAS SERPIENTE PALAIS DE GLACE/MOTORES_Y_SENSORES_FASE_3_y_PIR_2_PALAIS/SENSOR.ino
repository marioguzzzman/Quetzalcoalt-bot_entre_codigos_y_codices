
//-------------- INTERRUPCIONES --------------

//------------------ MIRO TODOS LOS SENSORES

void miro_todos_sensores () {
  frente_obstaculo = miro_distancia();
  // derecha_obstaculo = limite_derecha();
  //izquierda_obstaculo = limite_izquierda();
  //velocidad_luz ();
}

boolean miro_pir () {
  boolean hay_alguien = false;

  valor_pir = analogRead(pin_sensor);//leo sensor
  //Serial.print("PIR: ");
  //Serial.println (valor_pir);
  return (valor_pir > 500) ? true : false; // que era esto???

  // faltara un delay?

}


//----------------------------------FRENTE
boolean miro_distancia() {
  boolean frente_obstaculo = false;

  sensordistancia ();
if (distance < 47){ // limite de la distancia frontal en cm
    frente_obstaculo = true;
    //detener ();

    atras ();

      giro_izquierda (tiempo_del_paso);
      Serial.println("giro izquierda");

    if(ver_distancia){
      Serial.println("obstaculo adelante");
    }  
  } 
  else {
    if(ver_distancia){
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
  distance = duration / 58.2;
}

/*

  //------------------------------------- SENSOR DE LIMITES

  Sensores de limite:
  +5v  --> C SWITCH
  Ground -->  10k --> A0/A1 ---> NO SWITCH

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

*/


















