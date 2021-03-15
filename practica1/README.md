# PRACTICA 1
Repositorio donde se usan los conocimientos aprendidos en el Tema 2

## Descripción
El objetivo principal de este proyecto es el uso de manejo de llamadas al sistema, tratamiento de señales y gestión de interrupciones.

Se usan algunas funciones para la gestión de procesos:

  - fork: para la creación de procesos hijos.
  - wait: para la espera de procesos
  - signal: para la gestión de señales.
  - pipe: para la comunicación de procesos (manager con PC).
  - execv: ejecución de PA, PB, PC, PD y daemon.
  
## Ejecución
***
Para el correcto funcionamiento (aunque no es crítico) nos hará faltar asegurarnos de tener:
 - Carpeta src/ con archivos ".c".
 - Carpeta utils/ con los archivos de los modelos de examen y archivo estudiantes_p1.text 
 - Archivo Makefile 

Una vez comprobamos tenemos varias opciones. La primera que veremos es la compilación completa
```
$ make all
```
Así se nos generarán las carpetas obj/ y exec/ con los archivos .o y los ejecutables.
Una vez lo tenemos todo si queremos lanzar los procesos debemos hacer:
```
$ make solution
```

