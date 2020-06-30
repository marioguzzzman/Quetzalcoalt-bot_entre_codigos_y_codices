
// ------------------------------------------------- ADELANTE


void adelante () {

  tiempo_paso ++;
  if (tiempo_paso >= limite_tiempo_paso) {
    que_rueda_muevo = !que_rueda_muevo;  // ! significa que vale lo contrario
    tiempo_paso = 0;
  }
  if (ver_datos) {
    Serial.print("Paso: " );
    Serial.println( que_rueda_muevo );
  }
  if (que_rueda_muevo) {
    adelante_motor_2 (tiempo_del_paso); //prendo derecha
  }
  else {
    adelante_motor_1 (tiempo_del_paso); //prendo iaquierda
  }
}


// ------------------------------------------------- ATRAS

void atras () {
  tiempo_paso ++;
  if (tiempo_paso >= limite_tiempo_paso_atras) {
    que_rueda_muevo = !que_rueda_muevo;  // ! significa que vale lo contrario
    tiempo_paso = 0;
  }
  if (ver_datos) {
    Serial.print("Paso: " );
    Serial.println( que_rueda_muevo );
    //delay (25);
  }
  if (que_rueda_muevo) {
    atras_motor_1 (tiempo_del_paso); //prendo derecha
    //apago izquerda

  }
  else {
    atras_motor_2 (tiempo_del_paso); //prendo iaquierda
    //apago derecha
  }
}

//----------------------------------- DETENER

void detener () {
  analogWrite(E1, no_arranque); // vel motor 1
  analogWrite(E2, no_arranque); // vel motor 2

  delay (50);// estaba en 50
}

//------------------------------------ PASOS-----------------------------------


//----------------------------------- ADELANTE 1

void adelante_motor_1(int tiempo_del_paso) {
  //void adelante_motor_1(int tiempo_del_paso) {

  analogWrite(E1, arranque); // vel motor 1 derecha
  analogWrite(E2, no_arranque);
  //direccio motor 1
  digitalWrite(motorizin1, HIGH);
  digitalWrite(motorizin2, LOW);


}

//----------------------------------- ADELANTE 2

void adelante_motor_2(int tiempo_del_paso) {

  analogWrite(E1, no_arranque ); // vel motor 1 izquierda
  analogWrite(E2, arranque ); // vel motor 2
  //direccio motor 2
  digitalWrite( motordin3, HIGH );
  digitalWrite( motordin4, LOW );


}

//----------------------------------- GIRO DERECHA

void giro_derecha (int limite_tiempo_paso_atras) {

  //analogWrite(E1, velmap-50); // vel motor 1
  analogWrite(E1, arranque); // vel motor 1

  digitalWrite(motorizin1, LOW);
  digitalWrite(motorizin2, HIGH);

  analogWrite(E2, arranque); // vel motor 2
  //direccio motor 2
  digitalWrite(motordin3, HIGH);
  digitalWrite(motordin4, LOW);
  //  delay (1000);


}

//----------------------------------- GIRO IZQUIERDA

void giro_izquierda (int limite_tiempo_paso_atras) {

  analogWrite(E1, arranque); // vel motor 1
  //direccio motor 1
  digitalWrite(motorizin1, HIGH);
  digitalWrite(motorizin2, LOW);

  //analogWrite(E2, arranque-50); // vel motor 2
  analogWrite(E2, arranque); // vel motor 2

  /*digitalWrite(motordin3, LOW);
    digitalWrite(motordin4, HIGH);
    //delay(2000);
     //   delay (1000);
  */
  digitalWrite(motordin3, LOW);
  digitalWrite(motordin4, LOW);


}

//----------------------------------- atras 1

void atras_motor_1(int tiempo_del_paso) {

  analogWrite(E2, no_arranque); // vel motor 2
  analogWrite(E1, arranque); // vel motor 1
  //direccio motor 1
  digitalWrite(motorizin1, LOW);
  digitalWrite(motorizin2, HIGH);

}


//----------------------------------- atras 2

void atras_motor_2(int tiempo_del_paso) {

  analogWrite(E1, no_arranque ); // vel motor 1
  analogWrite(E2, arranque ); // vel motor 2
  //direccio motor 2
  digitalWrite( motordin3, LOW );
  digitalWrite( motordin4, HIGH );

}


