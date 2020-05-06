//Asystent parkowania//Asystent parkowania////Asystent parkowania//Asystent parkowania//
//Asystent parkowania//Asystent parkowania////Asystent parkowania//Asystent parkowania//

#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <DHT.h>
#include <SPI.h>

#define DHT22_PIN 2

DHT dht;

//
/*

*/

#define MAX_DEVICES 4
#define CLK_PIN 13
#define DATA_PIN 11
#define CS_PIN 10

#define button 8

#define trigPin 6
#define echoPin 7

const uint16_t WAIT_TIME = 1000;
int buzzer = 5;
int fotoRezystor = 0;
int czas = 0;
int dystans = 0;

int zmierzOdleglosc();

MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);
// Arbitrary output pins
// MD_Parola P = MD_Parola(DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup(void)
{
  P.begin();
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(fotoRezystor, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  tone(buzzer, 4300);
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 4300);
  delay(125);
  noTone(buzzer);
  P.print("Mefiu");
  delay(2000);
  P.print("  LAB");
  delay(2000);
  dht.setup(DHT22_PIN);
}

void loop(void)
{
  fotoRezystor = analogRead(A0);
  if (fotoRezystor >= 400 && zmierzOdleglosc() >= 71)
  {
    P.print("Ride"); //Podjedź
  }
  else if (fotoRezystor >= 400 && zmierzOdleglosc() >= 27 && zmierzOdleglosc() <= 70)
  {
    P.print("Slowly"); //Powoli
  }
  else if (fotoRezystor >= 400 && zmierzOdleglosc() >= 22 && zmierzOdleglosc() <= 26)
  {
    P.print("STOP!"); //Stop
  }
  else if (fotoRezystor >= 400 && zmierzOdleglosc() <= 21)
  {
    P.print("STOP!"); //Stop
  }
  else
  {
    P.print(".");
  }
  delay(200);

  if (digitalRead(8) == LOW) //PO KLIKNIĘCIU W 5 SEKUND POKAZUJE WILGOTNOŚĆ I TEMPERATURE
  {
    tone(buzzer, 4300);
    delay(200);
    noTone(buzzer);
    int wilgotnosc = dht.getHumidity();
    P.print("Wet.");
    delay(1200);
    P.print(wilgotnosc);
    delay(1200);
    int temperatura = dht.getTemperature();
    P.print("Temp.");
    delay(1200);
    P.print(temperatura);
    delay(1200);
  }
}

int zmierzOdleglosc() //funkcja zwracająca wartość w cm
{
  long czas, dystans;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  czas = pulseIn(echoPin, HIGH);
  dystans = czas / 58;

  return dystans;
}
