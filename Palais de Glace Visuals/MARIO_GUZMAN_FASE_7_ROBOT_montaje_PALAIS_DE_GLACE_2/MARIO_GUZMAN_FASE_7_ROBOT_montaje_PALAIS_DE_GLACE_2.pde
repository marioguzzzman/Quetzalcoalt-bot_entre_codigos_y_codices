/* 
 ***IMPORTANTE: CORRER PRIMERO EL SKETCH 
 Y DESPUES COMUNITY CORE VISION ***
 
 Mario Alberto Guzman Cerdio
 mariouzzzman@gmail.com
 
 
 El programa permite que una cámara PS3 Eye
 perciba la posición de un robot a partir de una selección del 
 rango de luminosidad emitido por una placa de leds infrarrojos, para
 posteriormente, envíar estos datos a través del protocolo de 
 comunicación TUIO de Community Core Vision a Processing, 
 desde el cual se proyecta el develamiento paulatino de 
 una página de un códice prehispánico.
 
 Menú I:
 Tecla 1: Muesrta objetos
 Tecla 2: Muestra imagen
 Tecla 3: Muestra imagen final
 
 Menú II:
 Letra 'c': Entrar/ Salir del modo warp
 Letra 'l': Cargar layout
 Letra 's': Salvar layout
 */

// -------------TAMAÑ0 PANTALLA-------

int alto = 900;
int ancho = 900;

//----------------KEYSTONE--------------

import deadpixel.keystone.*;

Keystone ks;
CornerPinSurface surface;

//----------------TUIO--------------

import TUIO.*;
TuioProcessing tuioClient;
import java.util.*; 

float cursor_size = 15;///tamano del cursor o dedo

//----------------IMAGENES Y OBJETOS--------------

int cantidad = 100;
Humo objeto[];//Objetos del tipo humo

PImage codice;//objeto tipo imagen
PGraphics pg_objetos;//grafico con  objetos

PGraphics imagen_salida;//imagen final

//Menú para mostrar en pantalla
int menu = 0; // estaba en 0
int menu_objetos=2; // estaba en 0
int menu_imagen=1;
int menu_imagen_final=0; // era 2

PVector surfaceMouse;


void setup() {

  size(alto, ancho, P3D);
  frameRate(30);

  //----------------KEYSTONE--------------

  ks = new Keystone(this);
  surface = ks.createCornerPinSurface(ancho-50, ancho-50, 10);


  //----------------TUIO--------------

  tuioClient  = new TuioProcessing(this);

  //----------------IMAGENES/ OBJETOS--------------

  codice = loadImage("codicecompleto.jpg");//leo la imagen
  codice.resize(alto, ancho);
  pg_objetos = createGraphics(alto, ancho);//inicio el Graphics
  ///constructor de objetos
  //cantidad de objetos
  objeto = new Humo [cantidad];
  for ( int i=0; i<cantidad; i++ ) {
    objeto[i] = new Humo();
  }  
  imagen_salida = createGraphics(alto, ancho, P3D);//inicio el Graphics
  // usar la misma resolución que CornerPinSurface.

  ks.load(); // PARA QUE CARGUE AUTOMATICAMENTE
}


void draw() {

  fill (0);
  rect (0, 0, alto, ancho);

  //----------------TUIO--------------

  Vector tuioCursorList = tuioClient.getTuioCursors(); 
  //cantidad de cursores = tuioCursorList.size()
  Vector tuioObjectList = tuioClient.getTuioObjects();
  //Recorro toda la lista de cursores
  for (int i=0; i<tuioCursorList.size (); i++) {
    TuioCursor curso = (TuioCursor)tuioCursorList.elementAt(i);
    Vector pointList = curso.getPath();//datos del cursor
    text(curso.getCursorID(), curso.getScreenX(width), curso.getScreenY(height));
    // text(curso.getCursorID(), curso.getScreenX(width)-5, curso.getScreenY(height)+5);
  }

  // -------PGRAPHICS + KEYSTONE --------

  surfaceMouse = surface.getTransformedMouse();

  pg_objetos.beginDraw();//incio el dibujo
  pg_objetos.fill(0, 0, 0, 10);
  pg_objetos.rect(0, 0, alto, ancho);
  for ( int i=0; i<cantidad; i++ ) {  
    objeto[i].update();
    objeto[i].dibuja(pg_objetos);
  }
  pg_objetos.endDraw();

  background(0); // ESTO LO AGREGUE DESPUES


  //--------------MENU -----------

  if (menu==menu_imagen) { // 1
    image(codice, 0, 0);//dibujo la imagen
  }
  //muestro la imagen formada por los objetos
  if (menu==menu_imagen_final) { //0 
    // image(pg_objetos, 0, 0);
  }
  //Muestro la sumatoria da las imagenes
  if (menu ==menu_imagen_final) { // 2
    imagen_salida.beginDraw (); 
    imagen_salida.image(codice, 0, 0); //primero la imagen de fondo
    imagen_salida.blend(pg_objetos, 03, 0, ancho, ancho, 0, 0, ancho, ancho, DARKEST);
    imagen_salida.endDraw ();
  }

  //----------------KEYSTONE RENDER--------------

  // render the scene, transformed using the corner pin surface
  surface.render(imagen_salida);

  //println (TuioCursor);
} ///------------------FIN DRAW --------


///------------------MENU FUNCION IMAGEN --------

void keyPressed() {
  if (key == '2') {
    menu=menu_imagen;
  }
  if (key == '1') {
    menu=menu_objetos;
  }
  if (key == '3') {
    menu=menu_imagen_final;
  }

  ///------------------MENU FUNCION KEYSTONE --------

  switch(key) {
  case 'c':
    // enter/leave calibration mode, where surfaces can be warped 
    // and moved
    ks.toggleCalibration();
    break;

  case 'l':
    // loads the saved layout
    ks.load();
    break;

  case 's':
    // saves the layout
    ks.save();
    break;
  }
}

// ------------- PRUEBA MOUSE ---------

void mouseMoved() {

  for ( int i=0; i<cantidad; i++ ) {
    if (objeto[i].vivo == false) { 
      objeto[i].vivo = true;
      objeto[i].vida = 5; //50 cantidad de cuadros que permanece en pantalla
      objeto[i].posicion.x= surfaceMouse.x;
      objeto[i].posicion.y= surfaceMouse.y;
      i = cantidad + 1;
    }
  }
}

// ------------- TUIO FUNCIONES ---------

// Nuevo objeto en el escenario
void addTuioObject(TuioObject tobj) {
  //println("Nuevo objeto");
}
// Desaparece un objeto en el escenario
void removeTuioObject(TuioObject tobj) {
  //println("Se elimino un objeto");
}
// Se mueve un objeto del escenario
void updateTuioObject (TuioObject tobj) {
  //println("Se mueve un objeto");
}
// Nuevo cursor en el escenario
void addTuioCursor(TuioCursor tcur) {
  //////////////////////COSAS PARA CAMBIAR EN MONTAJE/////////////////////
  for ( int i=0; i<cantidad; i++ ) {
    if (objeto[i].vivo == false) { 
      objeto[i].vivo = true;
      objeto[i].vida =5; //cantidad de cuaros que permanece en pantalla

      int donde_inicia_x = 0;//donde inicia la posicion del robot
      int donde_inicia_y = 0;//donde inicia la posicion del robot
      int donde_termina_x = 0;//donde termina la posicion del robot
      int donde_termina_y = 0;//donde termina la posicion del robot

      int correxion_inicio_x = 0; // para correr hacia un costado
      int correxion_inicio_y = 0;

      float estiro_hacia_el_final_x = 0; //multiplicar por .0 para acortar y por 1.0 para aumentar
      float estiro_hacia_el_final_y = 0; //multiplicar por .0 para acortar y por 1.0 para aumentar
      //------MAPEO DE DISTORCION DE CAMARA ------

      float faseX = (map(tcur.getX(), 0, 1, 0, width)+correxion_inicio_x)*estiro_hacia_el_final_x; 
      float faseY = (map(tcur.getY(), 0, 1, 0, height)+correxion_inicio_y)*estiro_hacia_el_final_y;

      //------MAPEO DE DISTORCION DE CAMARA ------
      //  float faseX = map(tcur.getScreenX(width), 0, 1,30, width);
      //float faseY = map(tcur.getScreenY(height),0, 1, 150, height);

      //------MAPEO DE DISTORCION DE CAMARA ------
      //   float faseX= map(tcur.getX(), 0, 1, 1.1, width);
      // float faseY = map(tcur.getY(), 0, 1, 0, height);

      //  objeto[i].posicion.x= faseX;
      //  objeto[i].posicion.y= faseY;

      objeto[i].posicion.x= tcur.getX()*width;
      objeto[i].posicion.y= tcur.getY()*height;
      i = cantidad + 1;
    }
  }
}

//////////////////////COSAS PARA CAMBIAR EN MONTAJE/////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Se mueve un cursor del escenario
void updateTuioCursor (TuioCursor tcur) {
  //println("Se mueve un cursor");
  for ( int i=0; i<cantidad; i++ ) {
    if (objeto[i].vivo == false) { 
      objeto[i].vivo = true;
      objeto[i].vida =30; //cantidad de cuaros que permanece en pantalla
      // objeto[i].posicion.x= tcur.getX()* width;
      //objeto[i].posicion.y= tcur.getY()* height;

      int donde_inicia_x = 10;//donde inicia la posicion del robot
      int donde_inicia_y = 10;//donde inicia la posicion del robot
      int donde_termina_x = 600;//donde termina la posicion del robot
      int donde_termina_y = 600;//donde termina la posicion del robot

      int correxion_inicio_x = -70; // para correr hacia un costado
      int correxion_inicio_y = -50;

      float estiro_hacia_el_final_x = 1.8; //multiplicar por .0 para acortar y por 1.0 para aumentar
      float estiro_hacia_el_final_y = 1.3; //multiplicar por .0 para acortar y por 1.0 para aumentar

      float faseX = (map(tcur.getX(), 0, 1,donde_inicia_x , donde_termina_x)+correxion_inicio_x)*estiro_hacia_el_final_x; 
      float faseY = (map(tcur.getY(), 0, 1, donde_inicia_y, donde_termina_y)+correxion_inicio_y)*estiro_hacia_el_final_y;

      objeto[i].posicion.x= faseX;
      objeto[i].posicion.y= faseY;   
      i = cantidad + 1;
    }
  }
}
// Desaparece un cursor en el escenario
void removeTuioCursor(TuioCursor tcur) {
  //  println("Se elimino un cursor");
}

void refresh(TuioTime bundleTime) {
}


//----------------KEYSTONE DEMO--------------

/* 
 // Draw the scene, offscreen
 offscreen.beginDraw();
 offscreen.background(255);
 offscreen.fill(0, 255, 0);
 offscreen.ellipse(surfaceMouse.x, surfaceMouse.y, 75, 75);
 offscreen.endDraw();
 // most likely, you'll want a black background to minimize
 // bleeding around your projection area
 background(0);
 */
