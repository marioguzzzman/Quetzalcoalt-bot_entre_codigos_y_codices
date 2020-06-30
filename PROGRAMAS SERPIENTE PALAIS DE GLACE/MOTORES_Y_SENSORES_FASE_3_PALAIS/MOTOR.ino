

//----------------------------------- DETENER

void detener (){
  analogWrite(E1, no_arranque); // vel motor 1
  analogWrite(E2, no_arranque); // vel motor 2
 
  delay (50);
}

//------------------------------------ PASOS


/*void adelante_pasos(int _veces){ // veces que repite los pasos
  for( int i = 0 ; i < _veces ; i++ ){
    adelante_motor_1 ( tiempo_del_paso );
    adelante_motor_2 ( tiempo_del_paso );
    //break;
  }
}

//------------------------------------ PASOS ATRAS


void atras_pasos(int _veces){ // veces que repite los pasos
  for( int i = 0 ; i < _veces ; i++ ){
    atras_motor_1 ( tiempo_del_paso );
    atras_motor_2 ( tiempo_del_paso );
    //break;
  }
}
*/

//----------------------------------- ADELANTE 1 

void adelante_motor_1(int tiempo_del_paso){
  
  analogWrite(E1, 255); // vel motor 1
  analogWrite(E2, no_arranque); 
  //direccio motor 1
  digitalWrite(motorizin1, HIGH);
  digitalWrite(motorizin2, LOW);
}

//----------------------------------- ADELANTE 2 

void adelante_motor_2(int tiempo_del_paso){

  analogWrite(E1, no_arranque ); // vel motor 1
  analogWrite(E2, 255 ); // vel motor 2
  //direccio motor 2
  digitalWrite( motordin3, HIGH );
  digitalWrite( motordin4, LOW );
}

//----------------------------------- GIRO DERECHA

void giro_derecha (int tiempo_del_paso){

  //analogWrite(E1, velmap-50); // vel motor 1
  analogWrite(E1, 255); // vel motor 1
  
  digitalWrite(motorizin1, LOW);
  digitalWrite(motorizin2, HIGH);
  
  analogWrite(E2, 255); // vel motor 2
  //direccio motor 2
  digitalWrite(motordin3, HIGH);
  digitalWrite(motordin4, LOW);
}

//----------------------------------- GIRO IZQUIERDA

void giro_izquierda (int tiempo_del_paso){

  analogWrite(E1, 255); // vel motor 1
  //direccio motor 1
  digitalWrite(motorizin1, HIGH);
  digitalWrite(motorizin2, LOW);

  //analogWrite(E2, arranque-50); // vel motor 2
  analogWrite(E2, 255); // vel motor 2
  
   digitalWrite(motordin3, LOW);
  digitalWrite(motordin4, HIGH);
}

//----------------------------------- atras 1 

void atras_motor_1(int tiempo_del_paso){
  
  analogWrite(E2, no_arranque); // vel motor 2
  analogWrite(E1, 255); // vel motor 1
  //direccio motor 1
  digitalWrite(motorizin1, LOW);
  digitalWrite(motorizin2, HIGH);

}


//----------------------------------- atras 2 

void atras_motor_2(int tiempo_del_paso){

  analogWrite(E1, no_arranque ); // vel motor 1
  analogWrite(E2, velmap ); // vel motor 2
  //direccio motor 2
  digitalWrite( motordin3, LOW );
  digitalWrite( motordin4, HIGH );
 
}


