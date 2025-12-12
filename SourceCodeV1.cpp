/* ------------- PARÂMETROS DE CONFIGURAÇÃO ------------- */
constexpr int BUTTON_PIN = 4;
constexpr int LED_PIN    = 5;
constexpr int RELAY_PIN  = 6;
constexpr int MOIST_PIN  = A0;

/* ------------- BIBLIOTECAS E VARIÁVEIS ------------- */
#include "thingProperties.h"
#include <Bounce2.h>

Bounce b;
unsigned long startedWatering;
int raw_moisture = 0;
int moisture = 0;

/* ------------- CONFIGURAÇÃO INICIAL ------------- */
void setup() {
  Serial.begin(9600);
  b.attach(BUTTON_PIN, INPUT_PULLUP);
  b.interval(25);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  stopWatering();
}

/* ------------- LOOP PRINCIPAL ------------- */
void loop() {

  raw_moisture = analogRead(MOIST_PIN); 
  moisture = map(raw_moisture, 500, 100, 0, 100);
  moisture = constrain(moisture, 0, 100); 

  if (watering && (millis() - startedWatering) >= waterTime * 1000) {
    stopWatering();
  }

  b.update();
  if (b.changed() && b.read() == false) {
    if (watering) {
      stopWatering();
    } else {
      if (moisture < 30) {
        startWatering();
	  }
    }
  }
}

/* ------------- FUNÇÕES DE EVENTO DA NUVEM ------------- */
// Evento de mudança na variável watering
void onWateringChange() {
  if (watering) {
    if (moisture < 30) {
      startWatering();
    } else {
      watering = false;
    }
  } else {
    stopWatering();
  }
}

/* ------------- FUNÇÕES DE CONTROLE DE REGA ------------- */
void startWatering() {
  watering = true;                      		
  startedWatering = millis();          			
  digitalWrite(RELAY_PIN, HIGH);       			
}

void stopWatering() {
  watering = false;
  digitalWrite(RELAY_PIN, LOW);
}