// -------------DEFINO CLASE-------

class Lineas
{
  // ---- ATRIBUTOS-----
  PVector posicion;
  PVector velocidad;
  PVector aceleracion;
  PVector direccion;
  float amplitud;
  float alfa;
  float gris;

  // -------------INICIO CLASE-------

  Lineas(float _x, float _y) {
    posicion = new PVector(random(-50, 50), random(50, 50));
    // posicion = new PVector(width, height); 

    velocidad = new PVector(0, 1);
    aceleracion = new PVector(0, 0);
    direccion = new PVector(0, 0);
    inicio_al_centro(direccion.x, direccion.y);
    amplitud = 0.20;
  }

  // -------------METODOS CLASE-------

  void update () {
    //direccion random
    PVector aux = new PVector(0.0, 0.0);
    PVector dir_al_centro = PVector.sub (aux, posicion);
    dir_al_centro.normalize ();
    float aux_x = (direccion.x*0.5)+(dir_al_centro.x*0.5);
    float aux_y = (direccion.y*0.5)+(dir_al_centro.y*0.5);
    direccion.set(aux_x, aux_y, 0);
    direccion.x+=random(-amplitud, amplitud);
    direccion.y+=random(-amplitud, amplitud);

    // Normalizo la dirrecion, para perder la magnitud
    direccion.normalize ();

    // Escalo la normal 
    direccion.mult (10);

    // Acelero el objeto
    aceleracion = direccion;
    //Limite de aceleración
    velocidad.add(aceleracion);
    velocidad.limit (1);
    //cambio de posicion  
    posicion.add(velocidad);

    //Control y variación del alfa  
    if (alfa < 100) {
      alfa+=0.1;
    } else {
      alfa=0;
    }
  }

  void dibuja_linea (Lineas _lineas, PGraphics _pg) {
    _pg.strokeWeight(1);
    _pg.stroke(gris, alfa);
    _pg.line(posicion.x, posicion.y, _lineas.posicion.x, _lineas.posicion.y);
  }

  void inicio_al_centro(float _x, float _y) {
    direccion.x= _x + random(-1, 1) ;
    direccion.y= _y + random(-1, 1);

    velocidad.x = 0;
    velocidad.y = 0;

    posicion.x = 0;
    posicion.y = 0;

    alfa=0;
    gris = int(random (0, 10))*128;
  }
}

