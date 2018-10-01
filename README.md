NXTIoT_DEVKIT
=============

-	[Introducción](#introducción)

-	[Pinout](#pinout)

-	[Programación](#programación)

	-	[Devkit 1.0](#devkit-1.0)
	
	-	[Devkit 2.0](#devkit-2.0)
	
-	[Resolución de problemas](#resolución-de-problemas)

-	[Comandos importantes Modulo Wisol](#comandos-importantes-modulo-wisol)

-	[Librería](#librería)

	-	[Instalación](#instalación)
	
	-	[Funciones de la librería](#funciones-de-la-librería)

-	[Ejemplos](#ejemplos)

	-	[Leer ID/PAC](#leer-idpac)

	-	[Boton y led](#boton-y-led)
	
	-	[Sensor ultrasónico](#sensor-ultrasónico)

	-	[Sensor de Temperatura](#sensor-de-temperatura)
	
	-	[Downlink](#downlink)
	
	-	[Envio de Multiples Variables](#envio-de-multiples-variables)
	
- 	[Callbacks](#callbacks)
	
-	[Devkit Dual Zona 2 y 4](#devkit-dual-zona-2-y-4)

	-	[Cambio de Zona](#cambio-de-zona)
	
	-	[Ejemplo](#ejemplo)

Introducción
------------

Proyecto para aprender a utilizar el Devkit de desarrollo de NXTIoT, el cual trae un módulo Wisol de conectividad Sigfox y un microprocesador ATmega 328P, por lo que puede programarse mediante el IDE de Arduino (https://www.arduino.cc/en/Main/Software).
El Devkit cuenta con 6 GPIOs y 6 entradas analógicas, que también pueden configurarse como entradas digitales, un botón y un led que pueden programarse. 
A lo largo de este proyecto, se presentarán algunos ejemplos para demostrar lo fácil que es incluir la conectividad Sigfox a cualquier proyecto. Además, los ejemplos permitirán asociar las terminales de la tarjeta con las utilizadas en Arduino de manera que cualquier sketch utilizado en Arduino Uno puede ser cargado en el Devkit, únicamente cambiando los puertos utilizados a los disponibles en la tarjeta.

La tarjeta ya trae un programa precargado, con el que se obtiene el ID y el PAC del  modulo Wisol al presionar el boton, ademas, de mandar un mensaje por Sigfox.

Pinout
------

En la siguiente imagen se muestra el pinout del Devkit, de manera que se puedan asociar las terminales de la tarjeta con las utilizadas en Arduino Uno. 

![devkit_pinout](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/pinout_devkitV2.png?raw=true)


Programación
------------

### Devkit 1.0

Para cargar un programa a la tarjeta, primero se deben quitar los jumpers (o jumper, sea el caso) tal como se muestra en la imagen. TENER CUIDADO AL QUITAR LOS JUMPERS.

![dev1](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/dev1.png?raw=true)

### Devkit 2.0

El Devkit 2.0 es una mejora de la versión 1.0. Los cambios significativos son los siguientes:

-	Sustituye los pines y jumpers de programación por un switch. 
-	Se cambiaron los botones de Reset (rojo) y el botón programable (azul) para su facil identificación.
-	Se movió el módulo de comunicación Sigfox, de manera que las I/O quedan del lado izquierdo.

*Los cambios anteriores no afectan nada en cuanto a programación, por lo que los programas para el Devkit 1.0 funcionan en la versión 2.0.* 

Para cargar un programa en el Devkit 2.0, poner el switch a la *izquierda* para programar el microcontrolador y hacia la *derecha*, para restablecer la comunicación entre el microcontrolador y el módulo de comunicación Sigfox.

![devkit2mod](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/devkit2mod.png?raw=true)

Una vez conectada la tarjeta, deberemos selecccionar la "Placa" y el "Puerto" en la pestaña de HERRAMIENTAS. Seleccionamos "Arduino/Genuino uno" como nuestra placa y deberemos seleccionar el puerto.

En Windows seleccionamos el puerto *COM* que nos habilitó nuestra tarjeta. *En ocaciones, puede tardar un momento en habilitar el puerto la primera vez*

![con1](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/con1.png?raw=true)

en Mac, hacemos lo mismo

![config](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/config.png?raw=true)

En caso de tener varios puertos habilitados, probar hasta que nos permita cargar el programa. Una vez que se cargó el codigo, se vuelven a colocar los jumpers. Este procedimiento debe realizarse cada vez que se desee cargar un programa al Devkit.

Resolución de problemas
-----------------------

En sistemas operativos Windows 8 y Windows 10, puede que no reconozca el Devkit. Para la resolución de este problema, seguir los pasos descritos en el siguiente repositorio

https://github.com/NXTIoT/Drivers-para-DEVkit

Comandos importantes Modulo Wisol
---------------------------------

El modulo Wisol de conectividad Sigfox es un "pequeño" modem mediante el cual enviaremos nuestra información, por lo que para comunicarnos con el modulo utilizaremos comandos AT. Los principales comandos del modulo son:

-	AT	:	Comando de "Attention". El modulo regresa un "OK" como respuesta.
-	AT$I=10	:	Obtener el ID
-	AT$I=11	:	Obtener el PAC
-	AT$RC	:	Reset del módulo. Este comando debe utilizarse antes de mandar cualquier informacion por Sigfox.
-	AT$SF=	:	Comando para enviar datos (hasta 12 bytes en hexadecimal)

Librería
--------

Para simplificar el codigo, se creó la libreria "NXTIoT_dev.h". A continuación se mostrará el proceso de intalacion y un codigo base ([code](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/Ejemplos/programa_base.ino)) que puede ser usado para cualquier 
proyecto que se quiera realizar con el Devkit

### Instalación

Abrir en otra ventana el siguiente link

https://github.com/NXTIoT/Libreria_Devkit_NXTIoT

Dar click en Clone or download -> Download ZIP

![lib11](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/lib11.png?raw=true)

Una vez descargada, descomprimimos el archivo .ZIP y copiamos la carpeta "NXTIoT_dev"

![lib12](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/lib12.png?raw=true)

nos dirigimos a la carpeta donde se encuentran las librerías de Arduino y pegamos la carpeta. Comúnmente es Documentos -> Arduino -> libraries.

![lib13](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/lib13.png?raw=true)

Abrimos el IDE de Arduino. Si damos click en la pestaña "Programa -> Incluir Libreria", veremos que ya aparece en la lista de librerías.

![lib14](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/lib14.png?raw=true)

### Funciones de la librería

-	initpayload(): inicializa nuestro Payload con el comando "AT$SF=". (No recibe ningún argumento.)

-	addint(int var): función para agregar un entero representado a un byte (recibe un entero de 0 a 255 ó -127 a 127 como argumento.)

-	addfloat(float var): función para agregar un flotante representado a 4 bytes en formato little-endian. (Recibe un flotante como argumento.)

-	sendmessage(): Envia la información a traves de Sigfox. Maximo 12 bytes. (No recibe argumento.) 

Introducción al Backend
-----------------------

Antes de comenzar con la tarjeta de desarrollo y los ejemplos, es necesario conocer un poco sobre el backend de Sigfox. 
Una vez que se tiene una cuenta en el backend, ir al siguiente link:

https://backend.sigfox.com/auth/login

![dev2](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/bck1.png?raw=true)

Ingresamos con nuestras credenciales. Nos aparecerá la pagina principal del backend, en donde se muestran las actualizaciones que se van liberando.
Para ver los dispositivos en nuestra cuenta, damos click en la pestaña "DEVICE"

![dev2](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/bck2.png?raw=true)

entonces nos aparecerán los dispositivos asociados a nuestra cuenta. Un circulo Negro en la columna de "Communication Status" significa que a nuestro dispositivo se le terminó el año de conectividad, de lo contrario unicamente aparecera un circulo gris.
Para buscar un dispositivo, unicamente tenemos que ingresar el ID en el recuadro 

![dev2](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/bck3.png?raw=true)

![dev2](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/bck4.png?raw=true)

![dev2](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/bck5.png?raw=true)

Ejemplos
--------

A continuación, se presentan varios ejemplos donde se utilizan las entradas analógicas y digitales, además de los dispositivos integrados en el Devkit. Se presentan programas de ejemplo utilizando la libreria "NXTIoT_dev" y sin la libreria.

### Leer ID/PAC

En este ejemplo se utilizará el sketch devkit_info.ino ([Code](Ejemplos/devkit_info/devkit_info.ino)) para leer el ID y el PAC de nuestro Devkit, los cuales son necesarios para registrar el dispositivo en la plataforma de Sigfox y poder ver los mensajes enviados en el backend. Una vez descargado el sketch, procedemos a cargarlo en nuestra tarjeta siguiendo el procedimiento descrito anteriormente.
Abrimos el Monitor Serie 

![dev2](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/dev2.png?raw=true)

Presionamos el botón más cercano al Led que se encuentra encendido y en el monitor serial nos aparecerá la información sobre el ID y el PAC de nuestro Devkit.

![dev3](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/dev3.png?raw=true)

Una vez registrado, podemos enviar nuestro primer mensaje, lo cual podemos hacer con el mismo programa. Presionamos nuevamente el botón y nos desplegara la misma información que antes. Notar que los leds de status del módulo Wisol parpadearan 3 veces, lo que indica que se están enviando los mensajes. Si nos vamos al backend, veremos el mensaje que acabamos de enviar.

![dev4](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/dev4.png?raw=true)

### Boton y led

Este ejemplo nos permitirá conocer cuáles son los puertos a los que están conectados el botón y el led para poder utilizarlos en otros programas. Se utilizará el sketch boton_led.ino ([Code](Ejemplos/boton_led/boton_led.ino)). Una vez cargado el programa, al presionar el botón, el Led 6 se encenderá por 2 segundos para después apagarse.

![dev5](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/dev5.png?raw=true)

### Sensor ultrasónico

En este ejemplo se mostrará como conectar un sensor de distancia al Devkit y mandar por medio de Sigfox, la distancia medida entre el sensor y un objeto, de manera que pueda visualizarse en el backend. El sensor que se utilizará es el HC-SRQ4. Conectamos el sensor de acuerdo al siguiente diagrama

![sensor_distancia](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/sensor_distancia.jpg?raw=true)

Descargamos el sketch (sin usar librerías [Code](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/Ejemplos/sensor_distancia1/distancia_float.ino)) - (con librerías [Code](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/Ejemplos/Ejemplos_libreria/ultra_int.ino))) y lo cargamos en la tarjeta siguiendo el procedimiento descrito anteriormente. El programa manda la información de la distancia hacia el backend cada vez que se presione el boton mas cercano al led que se encuentra encendido.

Ponemos un objeto frente al sensor

![dev6](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/dev6.png?raw=true)

y abrimos el monitor serial de Arduino. Presionamos el boton e inmediatamente nos mostrara la distancia medida entre el sensor y el objeto

![dev7](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/dev7.png?raw=true)

Si revisamos el backend, veremos que cada mensaje nos mostrara la misma información de la distancia que la mostrada en el monitor serie

![back1](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/back1.png?raw=true)

### Sensor de Temperatura

En este ejemplo se mostrará como leer un sensor analógico además de realizar la codificación del dato antes de ser enviado y ya en el backend, se realizará la decodificación para poder visualizar la información en forma decimal. 

Descargar el sketch (sin usar librerías [Code](Ejemplos/sensor_temperatura/sensor_temperatura.ino)) - (con librerías [Code](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/Ejemplos/Ejemplos_libreria/temp_float.ino)). El sensor utilizado en este ejemplo es el LM35

![tmp36](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/tmp36.jpg?raw=true)

el cual debe ser conectado siguiendo el siguiente diagrama

![temp2](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/temp2.png?raw=true)

Una vez cargado el programa, abrimos el monitor serial, presionamos el botón mas cercano al Led encendido y nos desplegara la información de la temperatura

![dev8](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/dev8.png?raw=true)

Ahora para decodificar el dato enviado, se debe realizar el parsing del payload. Ir al “Device type” donde se encuentra el dispositivo y dar click en el botón “Edit” en la esquina superior derecha y en la sección “Payload display” seleccionamos “Custom grammar” y en “Custom configuration” escribimos temp::float:32:little-endian 

![dev10](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/dev10.png?raw=true)

Revisando los mensajes del dispositivo, veremos que ahora debajo del dato enviado aparecerá la información de la temperatura tal como nos aparece en el monitor serie de Arduino

![dev9](https://github.com/Iotnet/IoTnet_DEVKIT/blob/master/images/dev9.png?raw=true)

### Downlink

En el siguiente ejemplo, se mostrará como realizar un downlink, en el que se configurará la información que recibirá el Devkit directamente en el backend y, a través de esta información, realizará cierta acción, En este ejemplo, al recibir la información del backend, prenderá y apagará el led programable un número determinado de veces.

El comando utilizado para realizar un downlink, es el mismo que para enviar un mensaje (AT$SF=XXXXXX) pero se le agrega ",1" al final del comando, quedando de la siguiente manera (AT$SF=XXXXXX,1). 

En este caso, el dispositivo es el que comienza con el proceso del downlink. El proceso se puede resumir en los siguientes pasos:
<br />1.- El dispositivo debe mandar un mensaje con la petición para la nube de un downlink (AT$SF=XXXXXX,1). 
<br />2.- La nube al recibir la petición, procesa la información que tiene que mandar y busca la antena mas cerca al dispositivo que pueda atender a la peticion.
<br />3.- El dispositivo entrará en modo escucha por alrededor de 20 segundos, para captar la información que se le envie.
<br />4.- En dado caso que exista una antena que pueda realizar la petición de downlink, el estatus de downlink en el backend cambiará a verde.
<br />5.- Finalmente, en dado caso que la petición haya sido exitosa, el dispositivo recibirá la informacion y pasará a modo reposo nuevamente.

Descargar y subir al Devkit el siguiente programa ([code](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/Ejemplos/downlink.ino)).

Ahora, debemos configurar la información que recibirá nuestro Devkit. Buscamos nuestro dispositivo en el backend

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/down1.png?raw=true)

y damos click en el "Device Type". En la esquina superior izquierda seleccionamos "Edit"

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/down2.png?raw=true)

nos dirigimos hacia la parte de "Dwnlink data". Por default tendrá la configuración DIRECT en "Downlink mode" y {time}0000{rssi} como la información que será enviada en caso de que el dispositivo realice una petición de downlink. Esta informacion es la que deberemos modificar.

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/down3.png?raw=true)

modificamos la informacion de {time}0000{rssi} a {time}0400{rssi}, de esta manera, con el 4 que hemos agregado le indicaremos al Devkit el número de veces que queremos que encienda el led (El valor debe de ser del 1 al 9). Hacemos click en "OK"

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/down5.png?raw=true)

Ahora que ya tenemos configurada la información que recibirá el Devkit, nos vamos a los mensajes del dispositivo. Abrimos el "Monitor Serie" de Arduino y presionamos el boton programable (Azul). Enseguida nos apareceran los comandos de RESET y el de enviar mensaje con petición de downlink

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/down4.png?raw=true)

si observamos el backend, veremos que el mensaje presenta dos indicadores. 

-	"Flecha hacia arriba": estatus del callback en caso de tener alguno configurado.

-	"Flecha hacia abajo": estats del Downlink, es decir, disponibilidad de la red para atender la petición del dispositivo.

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/down6.png?raw=true)

una vez que el dispositivo hace una petición de downlink, abrirá una ventana de tiempo (alrededor de 20 segundos), durante la cual esperará la respuesta de la red. Despues de un tiempo, el estatus del Downlink aparecerá en verde, indicando que la red puede atender satisfactoriamente la petición del dispositivo.

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/down7.png?raw=true)

Y en el serial de arduino, se desplegará la informacion que recibió el dispositivo, en caso de que se realizara de forma exitosa. Aparecerà un "OK" de que se envió el mensje con la petición de downlink y en la siguiente linea, la información recibida y por ultimo, el numero de veces que se encenderá el led.. 

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/down8.png?raw=true)

### Envio de Multiples Variables

En el siguiente link se muestra un ejemplo de como enviar multiples variables dentro de un mensaje con el devkit

https://github.com/NXTIoT/Multiples_variables

Callbacks
---------

Ir a la siguiente liga para ver la informacion sobre la creación de callbacks hacia diferentes plataformas.

https://github.com/NXTIoT/Callbacks-hacia-plataformas

Devkit Dual Zona 2 y 4
----------------------

En esta parte del repositorio se presenta el uso del Devkit con el modulo Dual de Wisol para zona 2 y 4. Se presenta un codigo de ejemplo que realiza el cambio de zona de RCZ2 a RCZ4 y viceversa utilizando el botón programable (Azul) que trae incluido el Devkit.

### Cambio de Zona

Para establecer la zona de transmisión de RC2->RC4, es necesario la siguiente secuencia de comandos:

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/com4.png?raw=true)

y de RC4->RC2

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/com2.png?raw=true)

### Ejemplo

El siguiente codigo de ejemplo ([code](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/Ejemplos/demo_rcz24.ino)), permite realizar el cambio de zona (de zona 2 a 4 y viceversa) por medio del boton programable. Las acciones son:

-	1 click: obtener ID, PAC y enviar un mensaje por Sigfox.

-	click largo por 3 segundos: cambio de zona.

Ademas cuando el Devkit este configurado en zona 4, el led programable (led verde) estara encendido y al abrir la terminal de arduino, nos desplegara la informacion de la configuracion de la zona

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/rcz4.png?raw=true)

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/term4.png?raw=true)

y apagado cuando se encuentre en zona 2

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/rcz2.png?raw=true)

![dev9](https://github.com/NXTIoT/NXTIoT_DEVKIT/blob/master/images/term2.png?raw=true)
