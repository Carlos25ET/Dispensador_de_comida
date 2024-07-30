#include <DHT.h>
#include <ESP32Servo.h>

// Definir los pines
#define DHTPIN 4
#define SERVOPIN 5

// Definir el tipo de sensor DHT
#define DHTTYPE DHT11

// Inicializar el sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Crear una instancia del servo
Servo myServo;

// Ángulos para el servo
int minAngle = 0;
int maxAngle = 180;

void setup() {
  Serial.begin(115200);
  dht.begin();
  myServo.attach(SERVOPIN);

  // Colocar el servo en la posición inicial
  myServo.write(minAngle);
}

void loop() {
  // Leer la temperatura y la humedad
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Verificar si hay fallos en la lectura
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Imprimir las lecturas en el serial
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Controlar el servo basado en la temperatura
  int servoAngle = map(temperature, 0, 40, minAngle, maxAngle); // Ajusta los valores según tu rango de temperatura
  servoAngle = constrain(servoAngle, minAngle, maxAngle);

  myServo.write(servoAngle);

  // Esperar 2 segundos antes de la siguiente lectura
  delay(2000);
}