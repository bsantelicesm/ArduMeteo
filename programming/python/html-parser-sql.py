#!/usr/bin/env python
# -*- coding: utf-8 -*-

import urllib2
from bs4 import BeautifulSoup
import time
import MySQLdb

print("Estación Meteorológica SS.CC Manquehue")
print("Copyright 2018 Benjamin Santelices")

url = "file:///sscctiempo/programming/html/arduino-sample-output.htm" #dirección de estación meteorológica.

PrecipInit = 0 #valor inicial para precipitaciones para cuando parta el sketch.

SQL = MySQLdb.connect(host="localhost", user="root", passwd="manquehue", db="meteorologia") #conección al servidor mysql local.

print("OK")
print(" ")

while True:

    while (time.time()) % 86400 == 0:
        Precip = 0 #Reiniciar valores de precipitación una vez al día.
        PrecipInit = PrecipRAW #tomar valor base
        print("Valores de precipitación reiniciados.")
        sleep(100)

    while (time.time()) % 60 == 0: #repetir una vez por minuto
        parsedText = BeautifulSoup(urllib2.urlopen(url).read(), "html.parser") #Carga BS para iniciar el parseo.
        varsHTML = parsedText.find("p").get_text().strip().split(",") # busca el tag <p> y convierte el HTML a string.
         #separa los valores usando las comas como referencia.
        varsFloat = [float(i) for i in varsHTML] #convierte el texto a punto flotante.
        Temperatura, Humedad, Presion, EnergiaUV, VelViento, DirViento, PrecipRAW, CO2, TVOC = varsFloat #separa variables.

        curTime = time.time()
        print (curTime)
        print (varsFloat) #toma la hora e imprime los valores y el timestamp.

        Precip = PrecipRAW - PrecipInit #sumar las precipitaciones

        SQL.cursor().execute("""INSERT INTO datos (timestamp, temperatura, humedad, presion, energiauv, velviento, dirviento, precip, co2, tvoc)
        VALUES ('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s');""",(float(curTime), float(Temperatura), float(Humedad), float(Presion), float(EnergiaUV), float(VelViento), float(DirViento), float(Precip), float(CO2), float(TVOC)))
        SQL.commit() #cargar los valores a la base de datos.
        print ("Valores cargados correctamente!")
        print (" ")

        sleep(100)
