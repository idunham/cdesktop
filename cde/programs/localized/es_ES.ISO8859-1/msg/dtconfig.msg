$ $XConsortium: dtconfig.msg /main/6 1996/10/19 14:45:51 rws $
$ *****************************************************************************   
$ **   
$ **  File:        dtconfig.msg   
$ **   
$ **  Project:     CDE Session Management (dtconfig)   
$ **   
$ **  Description:   
$ **  -----------   
$ **  This file is the source for the message catalog for dtconfig   
$ **   
$ **  Message set 10: IBM   
$ **  Message set 20: Sun   
$ **   
$ *****************************************************************************   
$ *****************************************************************************   
$ **  Message set 10: For IBM platforms   
$ *****************************************************************************   
$quote "

$set 10

1 "s�lo el superusuario puede ejecutarla.\n"
$    

2 "El entorno CDE est� establecido en este momento como interfaz de \n\
usuario por omisi�n. Esta interfaz aparecer� al iniciar la sesi�n para\n\
todos los usuarios del sistema. Para ver que este cambio se produce\n\
realmente, deber� cerrar el sistema y rearrancarlo. \n"
$    

3 "La l�nea de Mandatos est� establecida en este momento como interfaz \n\
de usuario por omisi�n. Esta interfaz aparecer� al iniciar la sesi�n\n\
para todos los usuarios del sistema. Para ver que este cambio se\n\
produce realmente, deber� cerrar el sistema y rearrancarlo.\n"

4 "El entorno CDE ya est� establecido como Interfaz de Usuario por omisi�n.\n"
$    

5 "La l�nea de Mandatos ya est� establecida como Interfaz de Usuario por\n\
omisi�n.\n"
$    

6 "uso:   %s\n\
  -e (habilitar inicio autom�tico de dtlogin)\n\
  -d (inhabilitar inicio autom�tico de dtlogin)\n\
  -kill (eliminar dtlogin)\n\
  -reset (restaurar dtlogin - volver a leer los archivos de configuraci�n)\n"
$    

7 "Demasiados argumentos\n"
$    

8 "Necesita un argumento\n"
$    

9 "No se pudo inhabilitar xdm; por favor, consulte las p�ginas man de xdm \n\
para inhabilitar xdm e int�ntelo de nuevo."
$    

10 "Dtlogin no est� en ejecuci�n \n"
$ *****************************************************************************   
$ **  Message set 20: For Sun Platforms   
$ *****************************************************************************   

$set 20

$    

1 "Utilidad de configuraci�n de CDE"
$    

2 "%s -d     (inhabilitar inicio autom�tico)"

3 "%s -e     (habilitar inicio autom�tico)"

4 "%s -kill  (eliminar dtlogin)"

5 "%s -reset (restaurar dtlogin)"

6 "%s -p     (actualizar acci�n de impresora)"
$    
$ In above messages 2 through 6, only translate words between   
$ left "(" and right ").   
$    

7 "%s: este script debe ejecutarse como root"

8 "Uso:   Demasiados argumentos"

9 "Uso:   Se necesita un argumento"

10 "la opci�n ha fallado"

11 "no se ha podido ejecutar %s"

12 "la inhabilitaci�n ha fallado"

13 "no se ha podido eliminar %s"

14 "hecho"

15 "inhabilitado inicio autom�tico del escritorio."

16 "la habilitaci�n ha fallado"

17 "no se ha podido encontrar %s"

18 "no se ha podido crear %s"

19 "no se ha podido crear %s"

20 "inhabilitado inicio autom�tico del escritorio."

21 "eliminaci�n de dtlogin completada."

22 "se han vuelto a cargar los recursos de configuraci�n de dtlogin."

23 "la actualizaci�n de la acci�n de impresora se ha completado"

24 "Uso:  "
$ 
25 " %s -inetd    (daemons inetd.conf /usr/dt)"
26 " %s -inetd.ow (daemons inetd.conf /usr/openwin)"
$ 
$	In above messages 25 and 26, only translate words between
$	left "(" and right ").
$ 
27 "La pr�xima inicializaci�n del sistema se ejecutar� desde /usr/dt/bin"
$ 
28 "    rpc.ttdbserverd         (ToolTalk)"
29 "    rpc.cmsd                (Gestor del calendario)"
30 "    dtspcd                  (Control de subprocesos)"
$ 
$  Keep column allignment on messages 28 thru 30.  
$  Only translate what's beteen ( )'s
$ 
31 "La pr�xima inicializaci�n del sistema se ejecutar� desde /usr/openwin/bin"
$ 
32 "    rpc.ttdbserverd         (ToolTalk)"
33 "    rpc.cmsd                (Gestor del calendario)"
$ 
$  Keep column allignment on messages 32 thru 33.  
$  Only translate what's beteen ( )'s
$ 
