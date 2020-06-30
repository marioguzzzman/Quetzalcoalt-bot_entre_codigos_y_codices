/* 
 ***IMPORTANTE: CORRER PRIMERO EL SKETCH 
 Y DESPUES COMUNITY CORE VISION ***
 
 Mario Alberto Guzman Cerdio
 mariouzzzman@gmail.com
 
 
 El programa permite que una cámara Infrarroja PS3 Eye 
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


// ------------- TIMER -------------

boolean salida = false;
int cuantos_cuadros = 200;


// -------------TAMAÑ0 PANTALLA-------

int alto = 1280;
int ancho = 720;

// -------------LOCACION ESCRITO--------------


int[] locX = {
  0, 250, 520, 0, 270, 520, 0, 270, 520
};
int[] locY = {
  0, 0, 0, 250, 260, 250, 520, 520, 520
};

//----------------IMAGENES Y OBJETOS ESCRITO --------------
PImage codiceBase;//objeto tipo imagen

PImage[] images = new PImage[9]; // todas las imagenes

Glifo[] glifos;


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

int cantidad = 200;
Humo objeto[];//Objetos del tipo humo

PImage codice;//objeto tipo imagen
PGraphics pg_objetos;//grafico con  objetos

PGraphics imagen_salida;//imagen final

//Menú para mostrar en pantalla 
int menu = 2;
int menu_objetos=2;
int menu_imagen=2;
int menu_imagen_final=2;

/*
int menu = 0;
 int menu_objetos=0;
 int menu_imagen=1;
 int menu_imagen_final=2;
 */
PVector surfaceMouse;


void setup() {

  size(ancho, ancho, P3D);
  frameRate(30);

  //----------------KEYSTONE--------------

  ks = new Keystone(this);
  surface = ks.createCornerPinSurface(ancho-50, ancho-50, 10);


  //----------------TUIO--------------

  tuioClient  = new TuioProcessing(this);

  //----------------IMAGENES/ OBJETOS--------------

  codice = loadImage("codicecompleto.jpg");//leo la imagen
  codice.resize(ancho, ancho);
  pg_objetos = createGraphics(ancho, ancho);//inicio el Graphics
  ///constructor de objetos
  //cantidad de objetos
  objeto = new Humo [cantidad];
  for ( int i=0; i<cantidad; i++ ) {
    objeto[i] = new Humo();
  }  
  imagen_salida = createGraphics(ancho, ancho, P3D);//inicio el Graphics
  // usar la misma resolución que CornerPinSurface.

  //----------------CARGAR CONFIGURACIÓN MAPEO--------------


  ks.load();// para que cargue automaticamente


  //----------------IMAGENES/ OBJETOS ESCRITO--------------

  codiceBase = loadImage("basecodice.jpg");//leo la imagen de base
  codiceBase.resize(ancho, ancho);


  // cargo imagenes individuales
  for ( int i = 0; i< images.length; i++ ) {
    images[i] = loadImage( "c" + i + ".png" );   // make sure images "0.jpg" to "11.jpg" exist
    images[i].resize(180, 180);
  }


  glifos = new Glifo[images.length];
  for ( int i = 0; i< glifos.length; i++ ) {
    glifos[i] = new Glifo(locX[i], locY[i], images);
  }
}

void draw() {

  //----------------TUIO--------------

  Vector tuioCursorList = tuioClient.getTuioCursors(); 
  //cantidad de cursores = tuioCursorList.size()
  Vector tuioObjectList = tuioClient.getTuioObjects();
  //Recorro toda la lista de cursores
  for (int i=0; i<tuioCursorList.size (); i++) {
    TuioCursor curso = (TuioCursor)tuioCursorList.elementAt(i);
    Vector pointList = curso.getPath();//datos del cursor
    // text(curso.getCursorID(), curso.getScreenX(width)-5, curso.getScreenY(height)+5);
  }

  // -------PGRAPHICS + KEYSTONE --------

  surfaceMouse = surface.getTransformedMouse();

  pg_objetos.beginDraw();//incio el dibujo
  pg_objetos.fill(0, 0, 0, 10);
  pg_objetos.rect(0, 0, ancho, ancho);
  for ( int i=0; i<cantidad; i++ ) {  
    objeto[i].update();
    objeto[i].dibuja(pg_objetos);
  }
  pg_objetos.endDraw();


  /// --------------  TIMER   --------------------------------


  if (frameCount % cuantos_cuadros == 0) { 

    salida = !salida;
  }

  if (salida == true) {
    escritura ();
  } else { 

    lectura ();       

    //----------------KEYSTONE RENDER--------------
    // render the scene, transformed using the corner pin surface
    surface.render(imagen_salida);
  }
} ///------------------FIN DRAW --------





// ------------- PRUEBA MOUSE ---------

void mouseMoved() {

  for ( int i=0; i<cantidad; i++ ) {
    if (objeto[i].vivo == false) { 
      objeto[i].vivo = true;
      objeto[i].vida = 50; //cantidad de cuadros que permanece en pantalla
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
  for ( int i=0; i<cantidad; i++ ) {
    if (objeto[i].vivo == false) { 
      objeto[i].vivo = true;
      objeto[i].vida =50; //cantidad de cuaros que permanece en pantalla
      objeto[i].posicion.x= tcur.getX()*width;
      objeto[i].posicion.y= tcur.getY()*height;
      i = cantidad + 1;
    }
  }
}
// Se mueve un cursor del escenario
void updateTuioCursor (TuioCursor tcur) {
  //println("Se mueve un cursor");
  for ( int i=0; i<cantidad; i++ ) {
    if (objeto[i].vivo == false) { 
      objeto[i].vivo = true;
      objeto[i].vida =50; //cantidad de cuaros que permanece en pantalla
      objeto[i].posicion.x= tcur.getX()* width;
      objeto[i].posicion.y= tcur.getY()* height;
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
