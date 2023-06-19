#include <dht.h>
#include<Servo.h>
#define moisturesensor A0
#define DHTTYPE DHT11
#define DHTPIN 2 
#define SoundSensorPin A1
Servo Myservo;
int BUZZER=9;
dht DHT;
float sensorValue = 0;
int msvalue=0;
void setup()
{ 
        Serial.begin(9600);
        pinMode(moisturesensor,INPUT);
        pinMode(2,INPUT);
        pinMode(SoundSensorPin,INPUT);
        Myservo.attach(3);//digital pin of arduino
        pinMode(BUZZER,OUTPUT);
}
void loop()
{
 
  readmoisture();
  readdht();
  readsound();
  if(sensorValue<=325)
            {  
              Serial.println("<:::::::::BABY IS CRYING:::::::::>");
              readservo();
            }
            else if(DHT.temperature > 33 && sensorValue<=325 && msvalue<=500)
            {
              Serial.println("BABY IS IN DANGER");
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
