#include <EtherCard.h>

static byte mac[] = {0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};
static byte ip[] = {192,168,0,20};
byte Ethernet::buffer[700]; //MAC, IP, y tamaño de buffer para ENC28J60.

#include <Wire.h> //Libreria I2C
#include "SparkFunMPL3115A2.h" //Libreria MPL3115A2
#include <SparkFunCCS811.h> //Libreria CCS811
#include <DHT.h> //Libreria DHT11

#define DHTPIN 4
#define DHTTYPE DHT11
DHT TempHum(DHTPIN, DHTTYPE); //Definir pin y tipo de DHT, incializar servicio.

#define CCS811ADDR 0x5B
CCS811 CalidadAire(CCS811ADDR); //Define dirección e inicializa el sensor de calidad del aire.

MPL3115A2 Barometro; //Crear instancia de presion barometrica.

#define STATUSLED 3 //Definir pin para el LED de estado.

const int valoresInternosViento[] = {786, 406, 461, 84, 84, 92, 66, 184, 127, 287, 244, 631, 600, 946, 827, 979, 702};
const float cardinal[] = {0, 22.5, 45, 67.5, 90, 112.5, 135, 157.5, 180, 202.5, 225, 247.5, 270, 292.5, 315, 337.5}; //Traducción de valores de veleta.

bool primerGatilloViento = true;

unsigned long tInicial = 0;
unsigned long cuentaVolcados = 0;

float Temperatura;
float Humedad;
float Presion;
float EnergiaUV;
float DirViento;
int Precip;
float VelViento;
int CO2;
int TVOC; //Definir todas las variables a utilizar. Se hace en esta instancia porque de lo contrario la página web no sabe de que estamos hablando.

int pinAnemometro = 2;
int pinPluviometro = 3;

void setup() {

  pinMode(pinAnemometro, INPUT);
  pinMode(pinPluviometro, INPUT);
  attachInterrupt(digitalPinToInterrupt(pinAnemometro), viento, FALLING); //gatillo para medir velocidad de viento.
  attachInterrupt(digitalPinToInterrupt(pinPluviometro), lluvia, FALLING); //gatillo para medir precipitación.
  
  pinMode(STATUSLED, OUTPUT);
  
  Serial.begin(9600); //Inicializar comunicacion serial USB a 9600 bits por segundo.
  Serial.println("Comunicación serial inicializada exitosamente."); //Mensaje de control.

  Wire.begin(); //Inicializar bus I2C
  Serial.println("Bus I2C inicializado");
  
  TempHum.begin(); //Iniciar mediciones para DHT11
  Serial.println("DHT11 inicializado");

  CalidadAire.begin();
  Serial.println("CCS811 inicializado"); //Inicializar CCS811

  Barometro.begin();
  Barometro.setModeBarometer();
  Barometro.setOversampleRate(7);
  Barometro.enableEventFlags(); //Inicializar barómetro MPL3115A2
  Serial.println("MPL3115A2 inicializado");

  if (!ether.begin(sizeof Ethernet::buffer, mac, 10))
    Serial.println( "ERROR: ENC28J60 no inicializado");
 else
   Serial.println("ENC28J60 inicializado");
 
  if (!ether.staticSetup(ip))
    Serial.println("ERROR: IP no obtenida");
  else
    Serial.println("Acceso a la red completado");

  Serial.println("Proceso de inicialización completado exitosamente!");
  delay(100);
  for(int i=0; i==4; i++){ //Parpadear el LED de estado 5 veces para indicar que el proceso de inicialización ha sido compleatado.
    digitalWrite(STATUSLED, HIGH);
    delay(100);
    digitalWrite(STATUSLED, LOW);
    delay(100);
  }
}

static word homePage() {
  
 BufferFiller bfill = ether.tcpOffset();
 bfill.emit_p(PSTR("HTTP/1.0 200 OK\r\n"
      "Content-Type: text/htmlrnPragma: no-cachernRefresh: 60\r\n\r\n"
      "<html><head><title>Estación Meteorológica</title></head>"
      "<body>"
      "<p>$D, $D, $D, $D, $D, $D, $L, $L</p>"
      "</body></html>"      
      ),Temperatura, Humedad, Presion, EnergiaUV, VelViento, DirViento, Precip, CO2, TVOC); //Valores a transmitir.
     
  return bfill.position(); //Página web. La verdad no tengo idea como funciona esto, lo copié desde naylampmechatronics.com y lo dejo ser.
}
  
void loop() {

  Temperatura = TempHum.readTemperature(); //recoger temperatura y humedad de DHT11. Grados Celsius y % Relativo.
  Humedad = TempHum.readHumidity();

  int GroveUV = analogRead(A1); // Leer sensor UV.
  EnergiaUV = (GroveUV * 1.5043); // Conversión a mW/m2 usando el número mágico proporcionado por la documentación del sensor.

  CalidadAire.readAlgorithmResults(); //iniciar transmisión del sensor CCS811. Obtener CO2 en ppm y TVOC en ppb.
  CO2 = CalidadAire.getCO2();
  TVOC = CalidadAire.getTVOC();

  int DirVientoRAW = analogRead(A0); //Leer veleta.
  for(int j=0; j=15; j++) {
    if(DirVientoRAW == valoresInternosViento[j]){
      DirViento = cardinal[j]; //este for cicla por todos los valores de viento posibles. cuando encuentra el correcto lo toma y lo tira en la variable DirViento.
    }
  }

  Presion = Barometro.readPressure(); //leer presión
  
  
  digitalWrite(STATUSLED, HIGH); //Parpadear el LED una vez de estado una vez para indicar el fin del muestreo de sensores.
  delay(100);
  digitalWrite(STATUSLED, LOW);

  ether.httpServerReply(homePage()); // se envia página Web
}

void viento() {
  if(primerGatilloViento == true) { //gatillo para viento
    tInicial = millis(); //tomar tiempo inicial en la primera instancia del anemómetro
    primerGatilloViento = false; //declarar que ya no es el primer gatillo.
  }
  else {
    unsigned long deltaT = millis() - tInicial; //tomar la diferencia de tiempo entre ambos gatillos.
    VelViento = (deltaT / 1000) / 2.4; //toma el tiempo entre gatillos en segundos, y lo divide por el número mágico de la hoja de datos del anemómetro para obtener la velocidad en km/h.
    primerGatilloViento = true; //reinicia el sistema.
  }
}

void lluvia() {
 cuentaVolcados++; //cada vez que el gatillo lluvia es llamado suma uno al cuenta volcados. el overflow se gatilla aproximadamente a los 1200km de precipitaciones, lo cual debería tomar unos 10k años.
 Precip = cuentaVolcados * 0.2794;
}

