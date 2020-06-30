 
 void lectura () {
 
  //--------------MENU -----------
/*
  if (menu==menu_imagen) {
    image(codice, 0, 0);//dibujo la imagen
  }
  //muestro la imagen formada por los objetos
  if (menu==menu_objetos) {
    image(pg_objetos, 0, 0);
  }
  */
  //Muestro la sumatoria da las imagenes
  //if (menu ==menu_imagen_final) {
    imagen_salida.beginDraw (); 
    imagen_salida.image(codice, 0, 0); //primero la imagen de fondo
    imagen_salida.blend(pg_objetos, 03, 0, ancho, ancho, 0, 0, ancho, ancho, DARKEST);
    imagen_salida.endDraw ();
 // }



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



