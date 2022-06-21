#define BLYNK_TEMPLATE_ID           "TMPLxxxxxx"
#define BLYNK_DEVICE_NAME           "Device"
#define BLYNK_AUTH_TOKEN            "YourAuthToken"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

int watersensor = A0;
int valuewatersensor = 0;

int relay = D2;
bool statewatersensor = false;

BlynkTimer timer;

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt(); 

  if (pinValue == 1){ // true HIGH 1
    digitalWrite(relay, LOW); // relay aktif
    }
  else{
    digitalWrite(relay, HIGH); // relay x aktif
    }

}

void myTimerEvent()
{
  valuewatersensor = analogRead(watersensor);

  if(valuewatersensor <= 500 && statewatersensor == false){
    digitalWrite(relay, LOW);
    statewatersensor = true;
    Blynk.logEvent("notification", "hujan.....");
  }

  else if(valuewatersensor >= 500 && statewatersensor == true){
    digitalWrite(relay, HIGH);
    statewatersensor = false;
    }
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  pinMode(watersensor, INPUT);
  pinMode(relay, OUTPUT);

  digitalWrite(relay, HIGH);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
