# Taller de Interacción Persona Computadora

Repositorio del grupo 5 del curso del taller de HCI.

El taller propone poner en práctica las nociones básicas sobre diseño de interacción, diseño centrado en el usuario, usabilidad y metodologías de evaluación de interfaces.

Programa del curso: [Link](http://www.fing.edu.uy/sites/default/files/cursos/2013/anexos/8289/Taller%20de%20Interaccion%20Persona%20Computadora.pdf)

## Integrantes

* "Milagros Garicoits" <mili.garicoits@gmail.com>
* "Agustín Prado" <aguprado@gmail.com>
* "Juan Pereira" <juanmanuel.pereira1@gmail.com>

## Laboratorio 1 - Memoria

Nuestra representación de la memoria fue sobre el movimiento de las personas en Montevideo. Decidimos desarrollar una aplicación que localice la ubicación de la persona y que envie como se esta moviendo, para luego se muestre en una aplicación web a través de mapas de calor.

Enlace al código: [Link](https://github.com/jotaemepereira/TDI-2014-5/tree/master/Lab1)

El proyecto consta de tres partes:

1. Aplicación web (HTML5 + CSS3 + JavaScript + GoogleMaps)
2. Servidor web (NodeJs + MongoDb)
3. Aplicación mobile (Android nativo)

Algunas imagenes de la app:

<pre>
<a href="#"><img src="http://i61.tinypic.com/2med2is.png" align="left"></a>
</pre>

## Laboratorio 2 - Reconocimiento Facial

Para el segundo laboratorio dentro del reconocimiento facial nos enfocamos en el tracking del movimiento ocular. 
Decidimos hacer un juego que reconozca a donde esta mirando el jugador y le vaya mostrando una imagen escondida, la cual es de una persona famosa que debe adivinar.


* Para el tracking del movimiento del ojo utilizamos EyeTribe: [Link](https://theeyetribe.com)
* El desarrollo del juego fue todo sobre openFrameworks: [Link](http://www.openframeworks.cc)

Imagen del juego:
<pre>
<a href="#"><img src="http://i62.tinypic.com/2501lrm.png" align="center" height="350" width="500"></a>
</pre>


## Laboratorio 3 - Datos Abiertos

En este labortario decidimos tomar los datos de la deforestación mundial para mostrarlos de una manera particular usando Processing. 
Hicimos el cruce de datos entre la deforestación de los países sumado a la emisión de CO2, la emisión de CO2 es representada por la cantidad de lluvia que cae sobre los árboles, cuanto más lluvia también más fuerte es el ruido de la misma.

Datos de la deforestación: [Link](http://data.un.org/Data.aspx?q=FOREST&d=MDG&f=seriesRowID%3a567)

Imagen de la aplicación:
<pre>
<a href="#"><img src="http://i60.tinypic.com/et8f83.png" align="center" height="350" width="500"></a>
</pre>

## Laborotario 4 - Instrumento Musical

El laboratorio cuatro se trató sobre crear un instrumento musical. Nostros tuvimos la idea de hacer un instrumento musical que reproduzca música según el RGB de una imagen. Por lo que el usuario podría cargar una imagen y reproducir música con tan solo moverse por la imagen.

El proyecto lo realizamos sobre OpenFrameworks (usamos el addon ofxMidi), y utilizamos Live Ableton para reproducir la música que pasaba por el contorlador MIDI.

El usuario luego de cargada la imagen tiene la posiblidad de cambiar los tonos de RGB apretando las teclas 'r', 'g' y 'b' para dismunir los tonos o 'R', 'G' y 'B' para aumentar los tonos. También se puede cambiar la altura de los tonos y los puertos por los cuales pueden salir las notas (usamos tres puertos, numerados del 1 al 3).



