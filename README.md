# PIC18F
Plantilla para usar con el PIC18 en la materia Aplicaciones de Electronica Digitales(AEDIII)


# <strong> Ejercicio Maquina de Cafe☕ </strong> (ejemplo)
<p>
Se dispone de un sistema expendedor de variedades de cafe, que es controlado por una plaqueta
que utiliza el microcontrolador <strong>PIC18F4550</strong>. Cuenta con un teclado de 16 teclas para la
seleccion de sus 7 productos, construido internamente como un teclado matricial de 4 x 4.
Tambien cuenta con <strong>display LCD inteligente 16 caracteres, 2 lineas</strong> utilizado para indicar
el importe del producto seleccionado.
Al seleccionar alguno de los productos disponibles, se debe activar el monedero (LD2
LED1 que al principio esta desactivado); permitiendo de este modo que ingresen las monedas
de 25, 50 centavos, 1 y 2 pesos. El mecanismo utilizado para la detecci´on de la moneda NO ES
DE NUESTRA INCUMBENCIA. A los efectos del problema, seg´un el valor de la moneda
ingresada se activar´a (nivel bajo) una de las cuatro lineas RD4(moneda de $2) , RD5(moneda
de $1), RD6(moneda de $0,5), RD7(moneda de $0,25) (use dip-switch para remplazar los
botones).
</p>

<p>• El teclado esta conectado al puerto B. (Ya
lo tiene resuelto en el entrenador.)
</p>
<p>• Debe considerar el rebote de las teclas.</p>
<p>• El display est´an conectados en los mismos
pines que en el entrenador.
</p>
<p>• Al momento de seleccionar una bebida (al
presionar una tecla) se debe activar el timer por 5 segundos para que el usuario ingrese las monedas (en
nuestro caso, se ajustan los dip-switch que representan
las monedas).
</p>

<strong> Una vez finalizado el tiempo, debe: </strong>
<p>• Desactivar el monedero (LED1)</p>
<p>• Inhibir el teclado (deja de atender la opresi´on de una tecla)</p>
<p>• Activar la salidas correspondientes (LD3, LC6 y LC7) durante el tiempo indicado
en la tabla.</p>
<p>• Mostrar en el display la tarifa del producto seleccionado con coma.</p>

<p>Luego un dispositivo electromecanico que NO ES DE NUESTRA INCUMBENCIA procede a servir el vaso durante un tiempo de 20 segundos. A partir de all´ı, debe dejar
la maquina preparada para una proxima operacion.</p>

Tabla de transición de estados:

| N° de tecla | Producto seleccionado  | Importe  | LD3 | LC6  | LC7  | Tiempo |
| --- | --- | --- | --- | --- | --- | --- |
| 1  | Cafe solo amargo | $2,50  | 0 | 0 | 1 | 15s |
| 2 | Cafe solo dulce  | $3,00 | 0 | 1 | 0 | 15s |
| 3 | Cafe con leche amargo  | $2,75 | 0 | 1 | 1 | 25s |
| 4 | Cafe con leche dulce | $3,25  | 1 | 0 | 0 | 25s |
| 5 | Cafe con leche muy dulce | $3,50 | 1 | 0 | 1 | 25s |
| 6 | Capuchino amargo | $4,00 | 0 | 1 | 0 | 15s |
| 7 | Capuchino dulce | $4,25  | 1 | 0 | 0 | 25s |

## Explicación del Código en Lenguaje C (Máquina de Café)

### Cabeceras y definiciones iniciales:

El código comienza incluyendo librerías estándar y archivos de cabecera para la configuración del microcontrolador y los componentes del sistema. Además, se definen pines específicos para representar las señales de monedas.

### Variables globales:

Se declaran varias variables utilizadas en diferentes partes del código para el control de la máquina de café.

### Máquina de estados:

El programa utiliza una estructura de máquina de estados implementada con un bucle `while(1)` y un `switch(estado)`. Cada `case` dentro del `switch` representa un estado del programa:

- **MENU_PRINCIPAL:** Presenta las opciones de café y espera la selección del cliente.
- **MOSTRAR_CAFE_X:** Muestra información sobre el café seleccionado y pasa al estado `MONEDERO` para procesar el pago.
- **MONEDERO:** Gestiona el pago del cliente mediante monedas y controla el tiempo de espera para el pago.
- **PREPARANDO_CAFE:** Prepara el café seleccionado activando las salidas correspondientes.
- **RETIRE_CAFE:** Indica que el café está siendo servido.
- **ERROR:** Indica un error en el proceso.

### Interrupciones:

Se define una función de interrupción que se ejecuta en desbordamientos del temporizador o cuando se presiona un botón. En el caso del temporizador, se actualizan contadores y funciones relacionadas con el tiempo. En la interrupción del puerto B, se detecta la pulsación de botones.

### Funciones específicas:

Dentro de cada caso de la máquina de estados, se realizan acciones específicas como mostrar mensajes en la pantalla LCD, controlar las salidas para preparar el café, gestionar el pago, manejar errores, etc.

## Diagrama de la Máquina de Estados

El diagrama representa la estructura de la máquina de estados utilizada en el código de la máquina de café:

MENU_PRINCIPAL --> MOSTRAR_CAFE_... : (botón pulsado)
MOSTRAR_CAFE_... --> MONEDERO : (monedas ingresadas)
MONEDERO --> PREPARANDO_CAFE : (tiempo agotado o monedas suficientes)
PREPARANDO_CAFE --> RETIRE_CAFE : (tiempo de preparación agotado)
RETIRE_CAFE --> ERROR : (tiempo agotado)
ERROR --> MENU_PRINCIPAL : (tiempo de error agotado)



# <strong> Simualcion </strong>
La simulacion fue hecha en SimulIDE, configurando cada puerto del PIC con sus entradas y salidas correspondientes teniendo en cuenta el enunciado y la problematica.
<p>https://www.youtube.com/watch?v=cZwTsTdGOHY</p>
