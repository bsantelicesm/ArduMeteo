# Estación Meteorológica Colegio Sagrados Corazones de Manquehue
Estación meteorológica de código abierto para educación

## About
Este proyecto tiene como objetivo detallar la construcción y el desarrollo de software para una estación meteorológica con fines educacionales, para ser utilizada tanto en educación primaria como secundaria. El sistema utiliza equipos e instrumentos de bajo costo, con el fin de desarrollar una estación que pueda ser implementada en cualquier establecimiento educacional a lo largo de todo Chile. En el caso de este repositorio en particular, la [documentación](/documentation/presentaciones_documentos) habla acerca de la implementación de este sistema en el colegio de los Sagrados Corazones de Manquehue, ubicado en Santiago.

## Objetivos

1. Crear una plataforma de **costo reducido** que permita a los estudiantes familiarizarse con las mediciones propias del estudio del clima.
2. Permitir a los estudiantes **acercarse a la construcción y mantención de sistemas electrónicos**, iniciándolos en materias como diseño de circuitos, programación, y tweaking/hacking.
3. Producir **datos a lo largo del tiempo** que permitan hacer un análisis del comportamiento climático de la zona, así como tener la posibilidad de compartir y comparar los datos con otras fuentes.

## Prestaciones

El sistema completo posee dos partes; la estación misma, la cual posee los sensores y la infraestructura requerida para sostenerla, y el servidor, que corresponde a un equipo que recibe los datos de la estación, guarda un registro de los valores, y produce una página web que permite la visualización amigable de los datos recopilados.

### Estación meteorológica

La estación meteorológica está basada alrededor la plataforma *Arduino*, con una serie de sensores que entregan nueve valores distintos:

* Temperatura (°C) 🡒 [DHT11](/documentation/hojas_datos/DHT11.pdf)
* Humedad Relativa (%RH) 🡒 [DHT11](/documentation/hojas_datos/DHT11.pdf)
* Presión Barométrica (hPa) 🡒 [MPL3115A2](/documentation/hojas_datos/MPL3115A2.pdf)
* Dirección del Viento (°) 🡒 [Argent Data Systems Weather Assembly](documentation/hojas_datos/Pluviómetro, Anemómetro, Veleta.pdf)
* Velocidad del Viento (km/h) 🡒 [Argent Data Systems Weather Assembly](documentation/hojas_datos/Pluviómetro, Anemómetro, Veleta.pdf)
* Precipitaciones (mm/hr) 🡒 [Argent Data Systems Weather Assembly](documentation/hojas_datos/Pluviómetro, Anemómetro, Veleta.pdf)
* Indice de Radiación UV 🡒 [GUVA-S12D](/documentation/hojas_datos/GUVA-S12D.pdf)
* Concentración de CO2 (ppm) 🡒 [CCS811](/documentation/hojas_datos/CCS811.pdf)
* Concentración de Compuestos Orgánicos Volátiles (ppb) 🡒 [CCS811](/documentation/hojas_datos/CCS811.pdf)

Para recopilar todos estos datos, la estación posee un *Arduino Nano*, que recibe los datos de todos los servidores y utiliza un controlador de Ethernet 802.3 [ENC28J60](/documentation/hojas_datos/ENC28J60) para generar un pequeño servidor web con los datos recopilados, para ser recibidos por el servidor.

### Servidor

El servidor utiliza  [Xubuntu 18.04 LTS](https://xubuntu.org/release/18-04/) como sistema operativo, utilizando LAMP (Linux Apache, MySQL, Python) Para recibir los datos y procesarlos con Python, generar una base de datos SQL con los datos, y generar una página web para mostrar todos los datos.

## ToDo

- [x] Diseño de la estación y sistemas
- [x] Programación
- [x] Diseño de infraestructura, circuitos, y tarjetas
- [ ] Prueba con equipos reales
- [ ] Bugfix y QA
- [ ] Instalación
- [ ] Release
