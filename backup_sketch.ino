#include<DHT.h>
#include<Servo.h>

#define DHTPIN 2          // Pin which is connected to the DHT sensor.
#define DHTTYPE DHT11     // DHT 11

DHT dht(2, DHT11);
Servo myservo;

#define soilSensorPin  A0 // Pin which is connected to the soil sensor.
#define soundSensorPin  A1// Pin which is connected to the sound sensor.

int BUZZER=9;

void setup() {
  Serial.begin(9600);
    pinMode(2,INPUT);
  pinMode(soilSensorPin,INPUT);
  pinMode(soundSensorPin,INPUT);
    pinMode(BUZZER,OUTPUT);
  myservo.attach(3);
}

void loop()
{
  dhtee();
  moisturee();
  soundo();
}
void dhtee()
{
  // Reading temperature or humidity from DHT sensor
  //int chk = DHT.read11(DHTPIN);
   float h;
  float t;
  h=dht.readHumidity();
  t=dht.readTemperature();
  Serial.print("Temperature = ");
  Serial.print(t);//DHT.temperature
  Serial.print(" Celsius\t");
  Serial.print("Humidity = ");
  Serial.print(h);//DHT.humidity
  Serial.println(" %");
  
  
  
 
  }
  void moisturee()
  {
    // Reading soil moisture sensor
  int soilSensorValue = analogRead(soilSensorPin);
  Serial.print("Soil Moisture: ");
  Serial.println(soilSensorValue);
  if(soilSensorValue <= 500)
   {
        digitalWrite(BUZZER,HIGH);
        delay(700);
        digitalWrite(BUZZER,LOW);
        delay(700); 
   }
  }
  void soundo()
  {
     // Reading sound sensor
  int soundSensorValue = analogRead(soundSensorPin);
  Serial.print("Sound Sensor: ");
  Serial.println(soundSensorValue);
  int angle = map(soundSensorValue, 0, 350, 0, 180);
  myservo.write(angle);
  
  // Delay for 1 second before taking the next sensor readings
  delay(1000);
  }
