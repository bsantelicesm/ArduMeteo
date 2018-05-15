#include <enc28j60.h>
#include <EtherCard.h>
#include <net.h>

static byte mac[] = {0xDD,0xDD,0xDD,0x00,0x01,0x05};
static byte ip[] = {192,168,103,10}; //Especificar MAC e IP para ENC28J60

#include <SparkFunCCS811.h> //Libreria CCS811
#include <DHT.h> //Libreria DHT11


#define DHTPIN = 2
#define DHTTYPE = DHT11
DHT.dht(DHTPIN, DHTTYPE); //Definir pin y tipo de DHT, incializar servicio.

#define CCS811ADDR 0x5B
CCS811.SensorCalidadAire(CCS811ADDR) //Define dirección e inicializa el sensor de calidad del aire.

#define STATUSLED = 3 //Definir pin para el LED de estado.
void setup() {

  pinMode(STATUSLED, OUTPUT);
  
  Serial.begin(9600); //Inicializar comunicacion serial USB a 9600 bits por segundo.
  Serial.println("Comunicación serial inicializada exitosamente."); //Mensaje de control.

  DHT.begin(); //Iniciar mediciones para DHT11
  Serial.println("DHT11 inicializado");

  SensorCalidadAire.begin();
  Serial.println("CCS811 inicializado");

  Serial.println("Proceso de inicialización completado exitosamente");
  delay(100)
  for(i=0, i=4, i++){ //Parpadear el LED de estado 5 veces para indicar que el proceso de inicialización ha sido compleatado.
    digitalWrite(STATUSLED, HIGH);
    delay(100);
    digitalWrite(STATUSLED, LOW);
    delay(100);
  }
  
}

static word homePage() {
  
 BufferFiller bfill = ether.tcpOffset();
 bfill.emit_p(PSTR("HTTP/1.0 200 OK\r\n"
      "Content-Type: text/htmlrnPragma: no-cachernRefresh: 5\r\n\r\n"
      "<html><head><title>Estación Meteorológica SSCC</title></head>"
      "<body>"
      "<p>$D,$D,$D,$D,$D</p>"
      "</body>"
      ),Temperatura,Humedad,EnergiaUV,CO2,TVOC,Presion,Precip,VelViento,DirViento); //transmision de los datos a través de HTML
     
  return bfill.position();
}

void loop() {
  float Temperatura == DHT.readTemperature(); //recoger temperatura y humedad de DHT11. Grados Celsius y % Relativo.
  float Humedad == DHT.readHumidity():

  int GroveUV == analogRead(A1) // Leer sensor UV.
  float EnergiaUV == GroveUV * 1.5043 // Conversión a mW/m2 usando el número mágico proporcionado por la documentación del sensor.

  SensorCalidadAire.readAlgorithmResults(); //iniciar transmisión del sensor CCS811. Obtener CO2 en ppm y TVOC en ppb.
  int CO2 == SensorCalidadAire.getCO2();
  int TVOC == SensorCalidadAire.getTVOC();

  digitalWrite(STATUSLED, HIGH); //Parpadear el LED una vez de estado una vez para indicar el fin del muestreo de sensores.
  delay(100);
  digitalWrite(STATUSLED, LOW);
  }
    
}
