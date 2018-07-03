# Acerca de los sensores

## Temperatura

Medición | Temperatura
---------|------------
Representa | El movimiento de las partículas que conforman el aire.
Unidad de Medida | Grados Celsius (°C)
Instrumento | Termómetro

La medición de temperatura es quizás una de las actividades mas icónicas de la meteorología, y también la mas fácil de reconocer. Todos tenemos un termómetro en nuestras casas y constantemente estamos al tanto de la temperatura ambiental, dado que nos permite saber qué ponernos o si tenemos que prender la estufa.
Para medir la temperatura en la estación, utilizamos el sensor [DHT11](https://github.com/bsantelicesm/sscctiempo/documentation/hojas_datos/DHT11.pdf), el cual combina un sensor de temperatura con uno de humedad en un mismo paquete. Para realizar la medición, existe dentro del sensor un conductor especial conocido como Termistor, el cual cambia su conductividad eléctrica según la temperatura de manera conocida, lo que le permite al microprocesador deducir su temperatura.

## Humedad

Medición | Humedad
---------|------------
Representa | La cantidad de vapor de agua presente en el aire.
Unidad de Medida | Humedad Relativa Porcentual **(%RH)**
Instrumento | Higrómetro

La humedad es una medición que muchas veces pasamos por alto, e ignoramos su verdadera utilidad tanto para nuestros procesos productivos como nuestro propio bienestar. Bajas humedades generan incomodidad al respirar y piel seca, mientras que altas humedades genera malestar térmico (ya que el sudor deja de ser efectivo en retirar el calor excedente del cuerpo), una sensación pegajosa en la piel, y puede ser catastrófico para equipos electrónicos, ya que la acumulación de condensación puede terminar en daños para los dispositivos.
Para medir la humedad relativa en nuestra estación, utilizamos el sensor [DHT11](https://github.com/bsantelicesm/sscctiempo/documentation/hojas_datos/DHT11.pdf), el cual combina la medición de temperatura y humedad en un solo paquete. Para realizar esta medición el sensor posee dos placas de cobre separadas por un material higroscópico (que absorbe agua). Al aumentar la humedad, la conductividad en las placas de cobre aumenta, lo que es interpretado por el microprocesador.

## Presión

Medición | Presión
---------|------------
Representa | La fuerza con la que el aire nos empuja.
Unidad de Medida | Hectopascal **(hPa)**
Instrumento | Barómetro

La presión barométrica es uno de los indicadores más importantes a la hora de predecir fenómenos a corto plazo. Una reducción de presión por ejemplo, indica la llegada de nubes. También es importante para calcular el punto de congelación del agua (lo que a su vez nos permite saber, por ejemplo, si va a nevar).
Para medir la presión barométrica en nuestra estación utilizamos el sensor [MPL3115A2](https://github.com/bsantelicesm/sscctiempo/documentation/hojas_datos/MPL3115A2.pdf), el cual posee en su interior un elemento que cambia su conductividad de acuerdo a la presión que se le aplica. Para generar la diferencia de presión el sensor posee un vacío en su interior, con el elemento resistivo separando el vacío de la presión ambiente. La diferencia en conductividad de este elemento (conocido como elemento piezoresistivo) es interpretada por el microprocesador como una diferencia en presión.

## Radiación Ultravioleta

Medición | Luz UV
---------|------------
Representa | La cantidad de luz UV que llega a la superficie terrestre.
Unidad de Medida | **Índice UV**
Instrumento | Fotómetro

La luz ultravioleta (UV) corresponde al segmento del espectro electromagnético entre 295nm y 325nm, y tiene como particularidad que, a diferencia de la luz de menor frecuencia, posee suficiente energía para alterar la composición química de nuestra piel, lo que puede producir daño tanto a corto como largo plazo. Tradicionalmente se utiliza una medida de energía para este tipo de aplicaciones, aunque en el caso de la luz UV, el daño que hacen no sólo depende de la energía, si no que también de la frecuencia de la luz. Para esto, la escala de índice UV entrega una medida que no sólo toma en cuenta la energía de la luz, si no que también su frecuencia, para permitir comprender de manera mas intuitiva los efectos de exponerse a la luz ultravioleta.
En nuestra estación utilizamos el sensor [GUVA-S12D](https://github.com/bsantelices/sscctiempo/documentation/hojas_datos/GUVA-S12D.pdf), el cual está montado en la parte superior de la estación, apuntado directamente hacia el cielo. Este sensor es un fototransistor, es decir, un componente electrónico que cambia su conductividad eléctrica de acuerdo a la cantidad de luz que recibe. En el caso de este sensor en particular, posee una serie de lentes y filtros que les permite recibir únicamente UV-A y UV-B, los tipos mas abundantes de luz UV en la superficie.

## Viento

Medición | Velocidad del Viento
---------|------------
Representa | la rapidez con la que el viento se mueve con respecto a la superficie.
Unidad de Medida | Kilómetros por hora **(km/h)**
Instrumento | Anemómetro

Medición | Dirección del Viento
---------|------------
Representa | La dirección cardinal del viento.
Unidad de Medida | Grados **(°)**
Instrumento | Veleta

El comportamiento del viento es crucial para comprender y predecir el movimiento de las nubes, y cualquier otro fenómeno atmosférico. Estos sensores suelen ser mas especializados, y por ende, menos conocidos.
En nuestra estación usamos el [Argent Data Systems Weather Assembly]("documentation/hojas_datos/Pluviómetro, Anemómetro, Veleta.pdf"), que combina pluviómetro, anemómetro y veleta en un mismo paquete, montado en un poste libre de obstrucciones. En el caso de la velocidad, tenemos un anemómetro de copa que posee un interruptor. Cada vez que la hélice del anemómetro de una vuelta, será registrada por el microprocesador, y al medir el tiempo que toma en dar una vuelta podemos calcular la velocidad.
En el caso de la veleta, funciona de manera similar a una perilla. Al girar en la dirección del viento, voltaje cambia, lo cual puede ser convertido por el microprocesador en grados, o incluso en una dirección cardinal.

## Precipitaciones

Medición | Precipitaciones Diarias
---------|------------
Representa | La cantidad de lluvia que cae.
Unidad de Medida | milímetros por día **(mm/dia)**
Instrumento | Pluviómetro

Las precipitaciones son tradicionalmente medidas por un pluviómetro manual, el cual es nada más que un vaso graduado de vidrio puesto en el suelo. Este modo de medir la lluvia es problemático para un sistema automatizado como este, dado que no hay forma de reiniciar el instrumento automáticamente (debe ser vaciado de vez en cuando por el meteorólogo), y que no hay forma fácil de medir la cantidad de agua presente en el vaso.
Para superar este problema, nuestra estación utiliza un pluviómetro de copa abatible, estándar en las estaciones automatizadas. El método de funcionamiento es simple; en vez de tener un vaso graduado tenemos un pequeño balde o copa con un volumen conocido, que está montado en un eje. Cada vez que las precipitaciones llenan el balde, este se vacía automáticamente pivotando en el eje. Cada vez que esto sucede, el balde activa un interruptor, el cual notifica al microprocesador que las precipitaciones han aumentado por la cantidad almacenada por el balde.

## Concentración de Dióxido de Carbono

Medición | Concentración de Dióxido de Carbono
---------|------------
Representa | La cantidad de CO2 presente en la atmósfera
Unidad de Medida | Partículas por millón **(ppm)**
Instrumento | Sensor de Gases

El dióxido de carbono es el más abundante de los gases contaminantes en nuestra atmósfera. Es producto de la combustión de hidrocarburos y una vez en la atmósfera impide que la energía entregada por el sol escape, lo que genera un calentamiento en la superficie. Si bien es una parte natural de nuestra atmósfera, y forma parte crucial de los procesos biológicos de los humanos y las plantas, es altamente tóxico si se encuentra en muchas cantidades. Desde la revolución industrial, la cantidad de material quemado con el fin de producir energía (carbón, petróleo, leña, gas natural, etc.) se ha traducido en un aumento considerable en las concentraciones atmosféricas de este gas, con impactos devastadores para el medio ambiente.
Para medir este gas en la estación utilizamos el sensor [CCS811](/documentation/hojas_datos/CCS811.pdf), el cual utiliza una pequeña bandeja de óxido de Titanio (IV) calentada a unos 150 °C, la que ligeramente varía su resistencia dependiendo de la cantidad de CO2 presente en el aire.

## Concentración de Compuestos Orgánicos Volátiles (VOC)

Medición | concentración de compuestos orgánicos volátiles
---------|------------
Representa | la cantidad total de todos los VOCs presentes en la atmósfera
Unidad de Medida | Partículas por mil millones **(ppb)**
Instrumento | Sensor de Gases

En la atmósfera existen tambien otros contaminantes con variados efectos ambientales. Una familia importante de compuestos potencialmente dañinos son los compuestos orgánicos volátiles (VOC), moléculas muy variadas en propiedades, aunque la mayoría presenta algunas características comunes, tales como un olor característico y distintivo, un bajo punto de ebullición y baja presión de vapor (lo que significa que se convierten rápidamente en gases), y que son potentes gases invernadero, entre muchos otros. La gran mayoría de los VOC presentes en la atmósfera son producto de los procesos industriales humanos.
En nuestra estación utilizamos el sensor [CCS811](/documentation/hojas_datos/CCS811.pdf), el cual utiliza una pequeña bandeja de óxido de Titanio (IV) calentada a unos 150 °C, la que ligeramente varía su resistencia dependiendo de la cantidad de VOCs presente en el aire.
