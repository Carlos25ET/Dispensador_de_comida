#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP32Servo.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

Servo myservo;  // crea el objeto servo

// GPIO de salida del servo
static const int servoPin = 13;

// Reemplazar con tus credenciales de Wifi
const char* ssid     = "CALERITY_ANIBAL_ARMIJO";
const char* password = ".2000.2002.2007.";

// Inicializa Bot Telegram
#define BOTtoken "7201824638:AAGLfxFxbTUqosI4ZuZxJU-j-Ny6EU0YTEg"  // Tu Bot Token (Obtener de Botfather)

#define CHAT_ID "TU-CHAT-ID"

WiFiClientSecure client;

UniversalTelegramBot bot(BOTtoken, client);

void handleNewMessages(int numNewMessages) {

  for (int i=0; i<numNewMessages; i++) {
    // Chat id del solicitante
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID){
      bot.sendMessage(chat_id, "Usuario no autorizado", "");
      continue;
    }

    String text = bot.messages[i].text;

    if (text == "/comida") {
      bot.sendMessage(chat_id, "Alimentando", "");
      myservo.write(90);             
      delay(500);                       
      myservo.write(0);              
    }
  }
}

void setup() {
  Serial.begin(115200);

  myservo.attach(servoPin);  // vincula el servo al servoPin

  // Conecta a la red WiFi con SSID y password
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Muestra IP local 
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "Bot iniciado", "");
}

void loop() {
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

  while(numNewMessages) {
    handleNewMessages(numNewMessages);
    numNewMessages = bot.getUpdates(bot.last_message_received + 1);
  }
}
