#include <enc28j60.h>
#include <EtherCard.h>
#include <net.h> //Librerias ENC28J60 y capacidades ethernet

static byte mac[] = {0xDD,0xDD,0xDD,0x00,0x01,0x05};
static byte ip[] = {192,168,103,10}; //Especificar MAC e IP para ENC28J60

#include <SparkFunCCS811.h> //Libreria CCS811
#include <DHT.h> //Libreria DHT11

#define DHTPIN 2
#define DHTTYPE DHT11
DHT TempHum(DHTPIN, DHTTYPE); //Definir pin y tipo de DHT, incializar servicio.

#define CCS811ADDR 0x5B
CCS811 CalidadAire(CCS811ADDR); //Define dirección e inicializa el sensor de calidad del aire.

#define STATUSLED 3 //Definir pin para el LED de estado.

const int valoresInternosViento[] = {786, 406, 461, 84, 84, 92, 66, 184, 127, 287, 244, 631, 600, 946, 827, 979, 702};
const String cardinal[] = {"N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"}; //Traducción de valores de veleta.

void setup() {

  pinMode(STATUSLED, OUTPUT);
  
  Serial.begin(9600); //Inicializar comunicacion serial USB a 9600 bits por segundo.
  Serial.println("Comunicación serial inicializada exitosamente."); //Mensaje de control.

  TempHum.begin(); //Iniciar mediciones para DHT11
  Serial.println("DHT11 inicializado");

  CalidadAire.begin();
  Serial.println("CCS811 inicializado");

  Serial.println("Proceso de inicialización completado exitosamente");
  delay(100);
  for(int i=0; i==4; i++){ //Parpadear el LED de estado 5 veces para indicar que el proceso de inicialización ha sido compleatado.
    digitalWrite(STATUSLED, HIGH);
    delay(100);
    digitalWrite(STATUSLED, LOW);
    delay(100);
  }
}

void loop() {
  float Temperatura = TempHum.readTemperature(); //recoger temperatura y humedad de DHT11. Grados Celsius y % Relativo.
  float Humedad = TempHum.readHumidity();

  int GroveUV = analogRead(A1); // Leer sensor UV.
  float EnergiaUV = (GroveUV * 1.5043); // Conversión a mW/m2 usando el número mágico proporcionado por la documentación del sensor.

  CalidadAire.readAlgorithmResults(); //iniciar transmisión del sensor CCS811. Obtener CO2 en ppm y TVOC en ppb.
  int CO2 = CalidadAire.getCO2();
  int TVOC = CalidadAire.getTVOC();

  int DirVientoRAW = analogRead(A0); //Leer veleta.
  for(int j=0; j=15; j++) {
    if(DirVientoRAW == valoresInternosViento[j]){
      String DirViento = cardinal[j]; //este for cicla por todos los valores de viento posibles. cuando encuentra el correcto lo toma y lo tira en la variable DirViento.
    }
  }

  digitalWrite(STATUSLED, HIGH); //Parpadear el LED una vez de estado una vez para indicar el fin del muestreo de sensores.
  delay(100);
  digitalWrite(STATUSLED, LOW);
  }
