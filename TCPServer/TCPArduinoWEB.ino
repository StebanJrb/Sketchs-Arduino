//Incluimos las librerias necesarias para el servidor web
#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h> //Introduzco la libreria necesaria para el sensor DHT22
#include <Wire.h>

//Declara constantes y pin de entrada
#define DHTPIN 2 //Indicamos el pin donde conectaremos la patilla data de nuestro sensor.

// Definimos el tipo de sensor que vas a emplear. En este caso usamos el DHT22
#define DHTTYPE DHT22   // DHT 22  (AM2302)

const int pirPin = 2;   // Pin donde está conectado el sensor PIR
DHT dht(DHTPIN, DHTTYPE);  //Indica el pin con el que trabajamos y el tipo de sensor

// Se introducen la ip y la mac.
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,10,1);

EthernetClient client;
// Inicializa la libreria ethernet, el puerto 80 esta por defecto para HTTP
EthernetServer server(125); //Abrir el puerto 125 en tu router si quieres poder verlo fuera de la red local.

void setup(){
  // Abrir comunicacion serial y esperar que el puerto responda
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
  dht.begin();
  while (!Serial) {
    ; // Esperar a que el puerto serial se conecte (solo cuando usamos Arduino Leonardo)
  }
  //Inicializar la conexion Ethernet y el servidor
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
} 
void loop(){
  //Escucha a clientes de entrada
  int state = digitalRead(pirPin);
  int valorADC = analogRead(A0);
  float v = (5.0 / 1023.0) * valorADC;

  EthernetClient webclient = server.available();
  if (client) {
    Serial.println("new client");
    //Una solicitud http cuya linea esta en blanco
    boolean currentLineIsBlank = true;
    while (webclient.connected()) {
      if (webclient.available()) {
        char c = webclient.read();
        Serial.write(c);
        // Si la linea en la solicitud http esta en blanco y el cliente esta disponible se puede enviar una respuesta
        if (c == '\n' && currentLineIsBlank) {
          webclient.println("HTTP/1.1 200 OK");
          webclient.println("Content-Type: text/html");
          webclient.println("Connnection: close");
          webclient.println();
          webclient.println("<!DOCTYPE HTML>");
          webclient.println("<html>");
          // Agregar una etiqueta meta que recargue la pagina cada segundo
          webclient.println("<meta http-equiv=\"refresh\" content=\"1\">");
          webclient.print("SENSORES POR FIBRAOPTICA!");   
          webclient.println("<br />");    

          //Obtener las lecturas del sensor e imprimir el resultado
          // La lectura de la temperatura o de la humedad tarda aproximadamente 250 milisegundos en el sensor 
          float h = dht.readHumidity();  //Guarda la lectura de la humedad en la variable float h
          float t = dht.readTemperature();  //Guarda la lectura de la temperatura en la variable float t

          //Escribimos en la página los valores de temperatura y humedad que hemos leído previamente
          webclient.print("Temperatura(C): ");
          webclient.println(t,1);  
          webclient.println("<br />");  
          webclient.print("Humedad(%): ");
          webclient.println(h, 0);  
          webclient.println("<br />");
          webclient.print("Precencia: ");
          webclient.println(state, 1);
          webclient.print("Voltaje: ");
          webclient.println(v, 1);      

          //Termina lectura del sensor
          webclient.println("</html>");
          sendToRaspberry(t,h,state,v);
          break;
        }
        if (c == '\n') {
          //Linea en blanco
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          //Si hay un caracter en la linea en blanco
          currentLineIsBlank = false;
        }
      }
    }
    //Darle al navegador web tiempo para recibir los datos 
    delay(1000); //Tiene un retardo de 1000 ms = 1s para repetir el ciclo void loop.
    //Se cierra la conexion
    client.stop();
    Serial.println("client disonnected");
  }
} //Termina loop

void sendToRaspberry(float temperature, float humidity, int state, int voltaje) {
  IPAddress serverIp(192,168,10,2); // IP de la Raspberry Pi
  int serverPort = 65432; // Puerto del servidor
  if (client.connect(serverIp, serverPort)) {
    Serial.println("Conexión con Raspberry Pi establecida");
    String data = String(temperature) + "," + String(humidity) + "," + String(state)+ "," + String(voltaje);
    client.print(data);
    delay(100); // Esperar un poco para asegurar que los datos se envíen
    client.stop();
    Serial.println("Datos enviados: " + data);
  } else {
    Serial.println("Conexión con Raspberry Pi fallida");
  }
}

