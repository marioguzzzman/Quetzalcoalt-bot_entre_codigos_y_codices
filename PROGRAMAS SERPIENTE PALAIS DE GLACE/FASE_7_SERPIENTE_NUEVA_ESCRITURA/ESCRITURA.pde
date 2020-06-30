


//------------------LETRAS DIBUJOS ESCRITOS

void escritura () {
  
  image(codiceBase, 0, 0);//dibujo la imagen

    for ( int i = 0; i< glifos.length; i++ ) {
      glifos[i].dibujar(surfaceMouse.x, surfaceMouse.y);
    }

}
