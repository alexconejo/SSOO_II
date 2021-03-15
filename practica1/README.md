# PRACTICA 1
Repositorio donde se usan los conocimientos aprendidos en el Tema 2

## Descripción
***
El objetivo principal de este proyecto es el uso de manejo de llamadas al sistema, tratamiento de señales y gestión de interrupciones.

Se usan algunas funciones para la gestión de procesos:

  - fork: para la creación de procesos hijos.
  - wait: para la espera de procesos
  - signal: para la gestión de señales.
  - pipe: para la comunicación de procesos (manager con PC).
  - execv: ejecución de PA, PB, PC, PD y daemon.
 

## Explicación de los procesos
***
La práctica consta de 6 procesos donde el proceso padre será el manager y los hijos ejecutarán el resto de procesos.

Los procesos son:
 - manager.c: se encarga de la gestión de procesos para la realización paralela de tareas y la creación del LOG.
 - PA.c: se encarga de la creacion del directorio /estudiantes y directorios de los alumnos.
 - PB.c: se encarga de la copia del modelo del examen en los directorios de los alumnos.
 - PC.c: se encarga de la creación del archivo nota.txt y de comunicar la media al manager.
 - PD.c: se encarga de la limpieza de archivos en caso de que salte el manejador.
 - daemon.c: se encarga de quedarse en segundo plano haciendo una copia de seguridad en la carpeta backup/.


## Ejecución
***
Para el correcto funcionamiento (aunque no es crítico) nos hará faltar asegurarnos de tener:
 - Carpeta src/ con archivos *.c*.
 - Carpeta utils/ con los archivos de los modelos de examen y archivo *estudiantes_p1.text* 
 - Archivo Makefile 

Una vez comprobamos tenemos varias opciones. La primera que veremos es la compilación completa
```
$ make all
```

Así se nos generarán las carpetas obj/ y exec/ con los archivos *.o* y los ejecutables.
Una vez lo tenemos todo si queremos lanzar los procesos debemos hacer:
```
$ make solution
```

Otra alternativa es la de la compilación archivo por archivo. Por ejemplo en el caso de querer
compilar solo el archivo *manager.c* podemos hacer:
```
$ make manager
```

En el caso de querer borrar la carpeta con archivos *.o*, la carpeta con los ejecutables y los archivos generados
podemos usar:
```
$ make clean
```
Si hemos ejecutado el programa tendremos un proceso daemon que debemos eliminar ya que se queda en segundo plano
haciendo la copia de seguridad. Para ello debermos buscar el numero del proceso y matarlo:
```
$ ps -e
$ kill -9 <Numero del proceso>
```
