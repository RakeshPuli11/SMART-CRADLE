#include <dht.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ThingSpeak.h>  // Include the ThingSpeak library
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL39aD1Jcf_"
#define BLYNK_TEMPLATE_NAME "babycadlee"
#define BLYNK_AUTH_TOKEN "L9hy5X98c4mZbfyLx__IbpgHviTCjetr"

#define moisturesensor A0
#define DHTTYPE DHT11
#define DHTPIN 2 
#define SoundSensorPin A1
Servo Myservo;
int BUZZER = 5;  // Use D5 pin for the buzzer
int msvalue = 0;
float sensorValue = 0;
DHT dht(DHTPIN, DHTTYPE);


char auth[] = "EQGS6JP8UD4YP7BV";


char ssid[] = "onepeice_is";
char pass[] = "nicorobin";
unsigned long previousMillis = 0;
const long interval = 60000;  // Interval for sending data to ThingSpeak (milliseconds)

void setup()
{ 
    Serial.begin(115200);
    pinMode(moisturesensor, INPUT);
    pinMode(DHTPIN, INPUT);
    pinMode(SoundSensorPin, INPUT);
    Myservo.attach(6);  // Use D6 pin for the servo
    pinMode(BUZZER, OUTPUT);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    dht.begin();
    ThingSpeak.begin(auth);  // Initialize ThingSpeak with your Wi-Fi client
}

void loop()
{
    Blynk.run();
    readmoisture();
    readdht();
    readsound();

    if (sensorValue <= 325)
    {
        // Your existing code
    }
    else if (dht.readTemperature() > 33 && sensorValue <= 325 && msvalue <= 500)
    {
        Serial.println("BABY IS IN DANGER");
        Blynk.notify("Baby is in danger!");

        // Send data to ThingSpeak
        ThingSpeak.setField(1, dht.readTemperature());  // Field 1: Temperature
        ThingSpeak.setField(2, dht.readHumidity());     // Field 2: Humidity
        ThingSpeak.setField(3, msvalue);                // Field 3: Moisture Value
        ThingSpeak.setField(4, sensorValue);            // Field 4: Sound Sensor Value

        // Write the data to ThingSpeak
        int response = ThingSpeak.writeFields();

        if (response == 200)
        {
            Serial.println("Data sent to ThingSpeak successfully.");
        }
        else
        {
            Serial.println("Failed to send data to ThingSpeak.");
        }
    }
    
    // Send data to ThingSpeak at regular intervals
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
        previousMillis = currentMillis;
        sendToThingSpeak();
    }
}

void sendToThingSpeak()
{
    // Send data to ThingSpeak
    ThingSpeak.setField(1, dht.readTemperature());  // Field 1: Temperature
    ThingSpeak.setField(2, dht.readHumidity());     // Field 2: Humidity
    ThingSpeak.setField(3, msvalue);                // Field 3: Moisture Value
    ThingSpeak.setField(4, sensorValue);            // Field 4: Sound Sensor Value

    // Write the data to ThingSpeak
    int response = ThingSpeak.writeFields();

    if (response == 200)
    {
        Serial.println("Data sent to ThingSpeak successfully.");
    }
    else
    {
        Serial.println("Failed to send data to ThingSpeak.");
    }
}

void readmoisture()
{ 
  msvalue=analogRead(moisturesensor);
  Serial.println(msvalue);
  if(msvalue<=500)
    {   
     Serial.println("<:::::::::::PEE DETECTED:::::::::>");
          for(int i=0;i<=21;i++ )
            {      
                digitalWrite(BUZZER,HIGH);
                delay(2000);
                digitalWrite(BUZZER,LOW);
                delay(2000);        
            }
    }
  
}
void readdht()
{ 
  
    // Reading temperature or humidity from DHT sensor
  int chk = DHT.read11(DHTPIN);
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.print(" Celsius\t");
  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);
  Serial.println(" %");
  if(DHT.temperature > 33) {
        Serial.print(" <:::::::::::HIGH TEMPERATURE DETECTED:::::::::::>\t");
        digitalWrite(BUZZER, HIGH);
            delay(2000);        
      } 
  else {
          digitalWrite(BUZZER, LOW);
            delay(2000);        
      }
}
void readsound()
{ 
       for (int i = 0; i <= 4; i++) 
           { 
               sensorValue = sensorValue + analogRead(SoundSensorPin); 
               delay(100); 
           } 
  sensorValue = sensorValue/10.0;
  Serial.println(sensorValue); 
  delay(100); 
}
void readservo()
{
    int k=21;
          while(k>=0)
             {
                Myservo.write(0);
                delay(1000);
                Myservo.write(90);
                delay(1000);
                Myservo.write(180);
                delay(1000);
                k--;
             }
}
