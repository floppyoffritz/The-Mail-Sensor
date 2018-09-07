#define echoPin D7 // Echo Pin
#define trigPin D6 // Trigger Pin
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

long duration;
int distance;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "d907d4e972544b41a107de9c9bd2bd35";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "iPhone";
char pass[] = "diarra10";

BlynkTimer timer;

void setup()  
{
  // Debug console
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Blynk.begin(auth, ssid, pass);

  // Notify immediately on startup
  Blynk.notify("Checking For Mail...");
  // Setup a function to be called every minute
}

void loop()
{
  Blynk.run();
  timer.run();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58.2;
  //Delay 50ms before next reading.
  delay(50);
  Serial.print("Distance = ");
  Serial.println(distance);
  Blynk.virtualWrite(V1, distance);

  /*NOTE: Change the (distance is less than) value, as this will go off as soon as you start the sensor. 
  You'll need to do some testing to see how deep the mail box is, so that you can determine your boundary parameters. 
  eg. If the distance is equal to 7cm, then you might want the notifcation to go off when the distance is equal to 6cm*/
  if (distance < 10){ Blynk.notify(String("You've Got Mail!"));
  }
  delay(10);
  }

