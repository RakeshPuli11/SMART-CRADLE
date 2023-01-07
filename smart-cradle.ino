#include<DHT.h>
#include<Servo.h>
#define msensor A0
#define DHTTYPE DHT11
#define DHTPIN 2 
#define SensorPin A1
float sensorValue = 0;
Servo Myservo;
int BUZZER=9;
DHT dht(2, DHT11);
float h;
float t;
int i;
void setup()
{ 
  Serial.begin(9600);
  pinMode(msensor,INPUT);
  pinMode(2,INPUT);
  pinMode(SensorPin,INPUT);
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
     readservo();
  }
}
void readmoisture()
{ int msvalue;
  msvalue=analogRead(msensor);
  Serial.println(msvalue);
  if(msvalue<=500)
  {
   for(i=0;i<=21;i++ )
      {      
        digitalWrite(BUZZER,HIGH);
        delay(700);
        digitalWrite(BUZZER,LOW);
        delay(700);        
      }
  }
}
void readdht()
{
  h=dht.readHumidity();
t=dht.readTemperature();
 if (isnan(h)|| isnan(t))
  {
    Serial.print("there is a problem from retrieving the data:");
  }
 if(t>30) 
  {
    for(i=0;i<=10;i++ )
      {      
        Serial.print("::::::::::::::high temperature detected:::::::::::::::");
        Serial.print("<<<<<<DANGER>>>>>");   
      }
  }  
  Serial.print("Humidity:");
  Serial.print(h);
  Serial.print("%, Temperature:");
  Serial.print(t);
  Serial.println("Celsius");
   delay(2000);

}
void readsound()
{
   for ( i = 0; i <= 4; i++) 
 { 
   sensorValue = sensorValue + analogRead(SensorPin); 
   delay(100); 
 } 
  sensorValue = sensorValue/10.0;
  Serial.println(sensorValue); 
  delay(100); 
}
void readservo()
{
    int k=2157;
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
