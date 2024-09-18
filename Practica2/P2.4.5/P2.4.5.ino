#include <WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Platillo en tierra";
const char* password = "TostadasDeChongos69$";

WiFiServer server(80);

//Usar el pin 15 GPIO
#define LED 2
#define LED2 15

String estado = "";
String estado2 = "";

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, LOW);
  
  // Conectando a WiFi
  WiFi.begin(ssid, password);
  // Checa si esta conectado
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.print("La dirección IP es: ");
  Serial.println(WiFi.localIP()); //Muestra IP
  
  // Inicio del Servidor web.
  server.begin();
  Serial.println("Servidor web iniciado.");
}

void loop() {
  // Consulta si se ha conectado algún cliente.
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.print("Nuevo cliente: ");
  Serial.println(client.remoteIP());
  // Espera hasta que el cliente envíe datos.
  while(!client.available()){ delay(1); }
  /////////////////////////////////////////////////////
  // Lee la información enviada por el cliente.
  String req = client.readStringUntil('\r');
  Serial.println(req);
  // Realiza la petición del cliente.
  if (req.indexOf("on2") != -1) {digitalWrite(LED, HIGH);
  estado = "Encendido";}
  if (req.indexOf("off2") != -1){digitalWrite(LED, LOW);
  estado = "Apagado";}

  if (req.indexOf("on3") != -1) {digitalWrite(LED2, HIGH);
  estado2 = "Encendido";}
  if (req.indexOf("off3") != -1){digitalWrite(LED2, LOW);
  estado2 = "Apagado";}
  //////////////////////////////////////////////

  // Página WEB. ////////////////////////////
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println(""); // Importante.
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<head><meta charset=utf-8></head>");
client.println("<body><center><font face='Arial'>");
client.println("<h1>Servidor web con ESP32.</h1>");
client.println("<h1>Napo el Guapisisisisisimo</h1>");
client.println("<h2><font color='#009900'>Webserver 1.0</font></h2>");
client.println("<h3>Práctica boton</h3>");
client.println("<br><br>");
client.println("<a href='on2'><button>Enciende LED</button></a>");
client.println("<a href='off2'><button>Apaga LED</button></a>");
client.println("<br><br>");
client.println(estado);
client.println("<br><br>");
client.println("<a href='on3'><button>Enciende LED2</button></a>");
client.println("<a href='off3'><button>Apaga LED2</button></a>");
client.println("<br><br>");
client.println(estado2);
client.println("</font></center></body></html>");
Serial.print("Cliente desconectado: ");
Serial.println(client.remoteIP());
client.flush();
client.stop();
}
