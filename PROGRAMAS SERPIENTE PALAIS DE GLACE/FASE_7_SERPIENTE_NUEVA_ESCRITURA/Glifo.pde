
class Glifo {

  int x, y;
  int ancho, alto; //tamaño imagen
  PImage[] imagenes;
  Timer timer; // velocidad de cambio

  int contador; // elige que imagen usar

  Glifo(int _x, int _y, PImage[] tempImagenes) {

    x = _x;
    y = _y;

    imagenes = tempImagenes;

    ancho = alto = imagenes[0].width; // porque son cuadradas, actualiza tamaño de imagen

    timer = new Timer(int(random(50, 200))); // velocidad de cambio
    timer.start();
    contador = int(random(8)); // que imagenes
  }

  void dibujar(float coordX, float coordY) { // que van a venir del blob

    image(imagenes[contador], x, y);

    if (estaEncima(coordX, coordY)) {

      if (timer.isFinished()) {
        contador++;
        if (contador > imagenes.length - 1) contador = 0;

        timer.start();
      }
    }
  }

  boolean estaEncima(float _x, float _y) {
    if (_x > x && (_x < x + ancho) && _y > y && (_y < y + alto)) {
      return true;
    } else {
      return false;
    }
  }
}

