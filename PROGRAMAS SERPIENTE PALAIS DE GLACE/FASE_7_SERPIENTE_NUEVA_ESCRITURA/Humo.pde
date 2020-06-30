// -------------DEFINO CLASE-------

class Humo
{
  // ---- ATRIBUTOS-----
  PVector posicion;
  PVector velocidad;
  PVector aceleracion;
  PVector direccion;
  int cant_lineas;
  Float amplitud;
  Lineas [] lineas;

  int vida = 100; 
  boolean vivo = false;

  // -------------INICIO CLASE-------
  Humo() {
    posicion = new PVector (0, 0);
    velocidad = new PVector(0, 1);
    direccion = new PVector(0, 0);
    inicio_al_centro();

    cant_lineas = int(random(2, 40));
    lineas = new Lineas [cant_lineas];
    for ( int i=0; i<cant_lineas; i++ ) {
      lineas [i] = new Lineas (posicion.x, posicion.y);
    }      

    amplitud=1.0;
  }

  void update() {
    if (vivo) {
      vida--;
      if (vida<0) {
        vivo = false;
      }
      direccion.normalize ();
      direccion.mult (0.5);
      velocidad.add(direccion);
      velocidad.limit (0.5); 
      posicion.add(velocidad);
      limite();
      for ( int i=0; i<cant_lineas; i++ ) {
        lineas[i].update();
      }
    }
  }

  // -------------METODOS CLASE-------

  void dibuja (PGraphics _pg) {
    if (vivo) {
      _pg.stroke(255, 128, 0);
      _pg.strokeWeight(1);
      _pg.pushMatrix();
      _pg.translate(posicion.x, posicion.y);
      for ( int i=1; i<cant_lineas; i++ ) {
        lineas[i].dibuja_linea(lineas[i-1], _pg);
      }  
      _pg.popMatrix();
    }
  }

  void limite() {     //Limites de la pantalla

    if (posicion.x<0) {
      inicio_al_centro();
    }
    if (posicion.x>width) {
      inicio_al_centro();
    }

    if (posicion.y<0) {
      inicio_al_centro();
    }
    if (posicion.y>height) {
      inicio_al_centro();
    }
  }

  void inicio_al_centro() {
    direccion.x= random(-TWO_PI, TWO_PI);
    direccion.y= random(-TWO_PI, TWO_PI);

    velocidad.x = 0;
    velocidad.y = 0;

    posicion.x = width/2;
    posicion.y = height/2;

    for ( int i=0; i<cant_lineas; i++ ) {
      lineas[i].inicio_al_centro(direccion.x, direccion.y);
    }
  }
}

