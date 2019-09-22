
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>

#define DHTPIN  5    
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

char auth[] = "i03k-OVQ4LxRhdd9yMFHsB-Oz3G8Lerg";
char ssid[] = "Hello_World";
char pass[] = "frame_mon_peem";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  timer.setInterval(5000L, sendUptime);
}

void loop()
{
  Blynk.run();
  timer.run();
}

void sendUptime()
{

  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  float fahranheit = Fahrenheit(temp);

  if(isnan(temp) || isnan(humid)){
    return;
  }
  Blynk.virtualWrite(V5, humid);
  Blynk.virtualWrite(V6, temp);
  Blynk.virtualWrite(V7, fahranheit);
}

double Fahrenheit(double celsius)

{

  return 1.8 * celsius + 32;

}
