#define BLYNK_TEMPLATE_ID "TMPLc_e0uRfE"
#define BLYNK_DEVICE_NAME "test3"
#define BLYNK_AUTH_TOKEN "uIlk6_tEDbcnCXvybsryJG_lUfvIVp9w"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

int watersensor = 34;
int valuewatersensor = 0;

int relay = 35;
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
  valuewatersensor = digitalRead(watersensor);

  if(valuewatersensor == LOW && statewatersensor == false){
    digitalWrite(relay, LOW);
    statewatersensor = true;
    Blynk.logEvent("notification", "hujan.....");
  }

  else if(valuewatersensor == HIGH && statewatersensor == true){
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

  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
