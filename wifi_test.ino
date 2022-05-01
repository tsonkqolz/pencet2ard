#include <ESP8266WiFi.h>

const char* ssid = "Iyusapakis";//type your ssid
const char* password = "iyusapakis7894";//type your password

WiFiServer server(80);

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 19);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8); // optional
IPAddress secondaryDNS(8, 8, 4, 4); // optional

void setup() {
  Serial.begin(115200);
  delay(10);


  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  
  // Match the request

  if (request.indexOf("/on") != -1) {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(4, HIGH);
    Serial.println("off");
  }
  if (request.indexOf("/off") != -1) {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(4, LOW);
    Serial.println("on");
  }

  // Set ledPin according to the request
  //digitalWrite(ledPin, value);
  //digitalWrite(LED_BUILTIN, value);

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
//  client.println("<!DOCTYPE HTML>");
//  client.println("<html>");
  if (request.indexOf("/status") != -1) {
    client.println(digitalRead(4));
   }
//  client.println("</html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
