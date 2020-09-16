            Integrantes 
      ｡*:☆☞°ヮ°)☞ ☜(°ヮ°☜)｡:゜☆｡
+---------------------+-------------+
| Nombre              | ROL         |
+---------------------+-------------+
| Héctor Larrañaga    | 201873623-6 |
+---------------------+-------------+
| Anastasiia Fedorova | 201873505-1 |
+---------------------+-------------+

+---------------------------------------------------------+
SOBRE MAKEFILE
(los comandos se anotan en comillas para diferenciarlas del texto simple)
	☆ Ingresar "make" en la consola para ejecutar el makefile.
	☆ Ingresar “./main.out” para ejecutar el código.
	☆ Ingresar "make clean" en la consola para borrar los archivos .o y .out
	☆ Para evitar los conflictos con <dirent.h> se utiliza gnu11 para la compilación.
+---------------------------------------------------------+
SOBRE LOS ARCHIVOS DE JUEGOS Y LAS CARPETAS
	☆ Se asume que los archivos de juegos tendrán nombres en formato "nombrejuego.txt"
	☆ Para el correcto funcionamiento, los .txt deben estar ubicados en carpeta "games", 
	en el mismo directorio donde se ubica el ejecutable.
	☆ En caso contrario, el programa desplegará el error de "./games no encontrada".
	☆ Para ordenar los juegos se creará la carpeta base "Steam"
	☆ Se entrega los .txt generados a partir de un .csv de manera aleatoria. 
	Las categorías de cada juego no necesariamente reflejan la realidad 
	(ej. Payday2 puede ser un Visual Novel porque así fue generado etc.)

+---------------------------------------------------------+
SOBRE LA APLICACIÓN DE LA CONSOLA
	☆ La aplicación de consola tiene 2 "fases". Se utiliza el input de usuario para mostrar los 
	contenidos correspondientes.
	☆ Fase 1: Lista de categorías. Se despliega la lista de categorías disponibles. El
	usuario debe escoger una de ellas, ingresado un entero de 1 a 5. En caso de ingresar
	un 0, se cierra la aplicación. En caso de ingresar un número inválido, se avisará de ello
	por la consola. En caso de ingresar un número entre 1 a 5 el usuario accede la lista de juegos
	según la categoría que eligió.
	☆ Fase 2: Lista de juegos. Se despliega la lista de juegos ordenada según el número de categorías.
	El usuario puede acceder a la información de juego al ingresar su número. Se puede volver a la lista
	de las categorías al ingresar 0.
+---------------------------------------------------------+
