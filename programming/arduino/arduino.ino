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
