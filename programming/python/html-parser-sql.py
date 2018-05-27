import urllib
from bs4 import BeautifulSoup
import html2text
import sqlite3
import time

print "Estación Meteorológica SS.CC Manquehue"
print "Copyright 2018 Benjamin Santelices"

servidorSQL = sqlite.connect(datos.db) #configuración de SQLite

url = "http://www.fantini.cl" #dirección de estación meteorológica.

while (time())%60 = 0):
    with urllib.request.urlopen('url') as webDump:
            statPage = webDump.read() #urllib busca la pagina y y la guarda como variable
        parsedText = BeautifulSoup(statPage) #Carga BS para iniciar el parseoself.
        varsHTML = soup.find("p") # busca el tag <p>
        VarsText = html2text.html2text(varsHTML) #convierte el HTML a string.

        varsList = VarsText.split(",") #separa los valores usando las comas como referencia.
        print varsList
        varsList = Temperatura, Humedad, Presion, EnergiaUV, VelViento, DirViento, PrecipRAW, CO2, TVOC
        #convierte una variable de multiples elementos en multiples variables de un elemento.

        #aqui tengo que hacer algo con las precipitaciones.

        cursorSQL = sqlite.cursor()

        cargarDB = """ INSERT INTO datos (Temperatura, Humedad, Presion, EnergiaUV, VelViento, DirViento, Precip, CO2, TVOC)
            VALUES (Temperatura, Humedad, Presion, EnergiaUV, VelViento, DirViento, Precip, CO2, TVOC)""" #cargar datos al servidor SQL.

        cursorSQL.execute(cargarDB) #Ejecutar comando SQL.
