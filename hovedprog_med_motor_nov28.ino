#define LED_SMOR 2
#define LED_SYLTETOY 3
#define LED_OST 4
#define LED_AGURK 5

#define KNAPP_SMOR 8
#define KNAPP_SYLTETOY 9
#define KNAPP_OST 10
#define KNAPP_AGURK 11
#define KNAPP_RANDOM 12
#define KNAPP_START 13

#define KJOR_SMOR 14      //rele som styrer smørpumpe
#define KJOR_SYLTETOY 15  //rele som styrer syltetøypumpe
#define KJOR_LUFT 16      //rele som blåser ut luft
#define KJOR_OST 17       //rele som styrer ostehøvel
#define KJOR_AGURK 20     //rele som styrer agurkhøvel
#define KJOR_VIPP 32           //liten sylinder som vipper ut skiva

#define MOTOR_FRAM 23     //rele som kjører motor framover
#define MOTOR_TILBAKE 25  //rele som kjører motor tilbake 

#define MANUELL_FRAM 34   //knapp som kjører motor fram manuelt
#define MANUELL_TILBAKE 36 //knapp som kjører motor tilbake manuelt

#define POS_START 40      //bryter ved startposisjon
#define POS_SMOR 31       //bryter ved smørposisjon
#define POS_SYLTETOY 44   //...
#define POS_OST 47
#define POS_AGURK 48
#define POS_VIPP 51

//boolske verdier som lagrer om pålegget skal kjøres eller ikke:
bool SMOR = false;
bool SYLTETOY = false;
bool LUFT = false;
bool OST = false;
bool AGURK = false;
bool VIPP = true;

bool START = false;
bool FERDIG = false;

bool SMOR_NESTE = false;
bool SYLTETOY_NESTE = false;
bool LUFT_NESTE = false;
bool OST_NESTE = false;
bool AGURK_NESTE = false;
bool VIPP_NESTE = false;

long tall = 0;    //denne brukes til random-funksjonen, long fordi random gir ut long

//diverse lister for å kunne iterere gjennom diverse ting
char LEDS[] = {LED_SMOR, LED_SYLTETOY, LED_OST, LED_AGURK};
char KNAPPER[] = {KNAPP_SMOR, KNAPP_SYLTETOY, KNAPP_OST, KNAPP_AGURK, KNAPP_RANDOM, KNAPP_START};
char KJOR_PALEGG[] = {KJOR_SMOR, KJOR_SYLTETOY, KJOR_LUFT, KJOR_OST, KJOR_AGURK};
char PALEGG[] = {SMOR, SYLTETOY, LUFT, OST, AGURK, VIPP};
char POSISJONER[] = {POS_START, POS_SMOR, POS_SYLTETOY, POS_OST, POS_AGURK, POS_VIPP};
char NESTE_PALEGG[] = {SMOR_NESTE, SYLTETOY_NESTE, LUFT_NESTE, OST_NESTE, AGURK_NESTE, VIPP_NESTE};

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 6; i++) {         //setter alle knapper på ui til input_pullup
    pinMode(KNAPPER[i], INPUT_PULLUP);
  }

  for (int i = 0; i < 4; i++) {         //setter alle leds til output, og skrur dem av
    pinMode(LEDS[i], OUTPUT);
    digitalWrite(LEDS[i], LOW);
  }

  for (int i = 0; i < 5; i++) {         //setter aller pålegg til output, og skrur av
    pinMode(KJOR_PALEGG[i], OUTPUT);
    digitalWrite(KJOR_PALEGG[i], HIGH); //high fordi rele er motsatt
  }

  for (int i = 0; i < 6; i++) {         //setter alle mikrobrytere til input_pullup
    pinMode(POSISJONER[i], INPUT_PULLUP);
  }

  pinMode(MOTOR_FRAM, OUTPUT);        //setter motor til output
  digitalWrite(MOTOR_FRAM, HIGH);     //high fordi omvendt logikk
  pinMode(MOTOR_TILBAKE, OUTPUT);
  digitalWrite(MOTOR_TILBAKE, HIGH);

  pinMode(KJOR_VIPP, OUTPUT);
  digitalWrite(KJOR_VIPP, HIGH);

  pinMode(MANUELL_FRAM, INPUT_PULLUP);
  pinMode(MANUELL_TILBAKE, INPUT_PULLUP);

}

void loop() {
  if (!digitalRead(MANUELL_FRAM)) {   //sjekker knapp for motor fram manuelt

    digitalWrite(MOTOR_FRAM, LOW);
    Serial.println("manuell fram");
    delay(250);
    digitalWrite(MOTOR_FRAM, HIGH);
  }

  if (!digitalRead(MANUELL_TILBAKE)) { //sjekker knapp for motor tilbake manuelt
    digitalWrite(MOTOR_TILBAKE, LOW);
    Serial.println("manuell tilbake");
    delay(250);
    digitalWrite(MOTOR_TILBAKE, HIGH);

  }

  if (!digitalRead(KNAPPER[0])) {
    if (PALEGG[0]) {         //endrer verdi til false hvis den er true, og skrur av lys:
      PALEGG[0] = false;
      digitalWrite(LEDS[0], LOW);
      delay(200);
    }
    else {       //endrer verdi til true hvis den er false, og skrur på lys
      PALEGG[0] = true;
      digitalWrite(LEDS[0], HIGH);
      delay(200);
    }
  }

  if (!digitalRead(KNAPPER[1])) {
    if (PALEGG[1]) {         //endrer verdi til false hvis den er true, og skrur av lys:
      PALEGG[1] = false;
      digitalWrite(LEDS[1], LOW);
      delay(200);
    }
    else {       //endrer verdi til true hvis den er false, og skrur på lys
      PALEGG[1] = true;
      digitalWrite(LEDS[1], HIGH);
      delay(200);
    }
  }

  if (!digitalRead(KNAPPER[2])) {
    if (PALEGG[3]) {         //endrer verdi til false hvis den er true, og skrur av lys:
      PALEGG[3] = false;
      digitalWrite(LEDS[2], LOW);
      delay(200);
    }
    else {       //endrer verdi til true hvis den er false, og skrur på lys
      PALEGG[3] = true;
      digitalWrite(LEDS[2], HIGH);
      delay(200);
    }
  }

  if (!digitalRead(KNAPPER[3])) {
    if (PALEGG[4]) {         //endrer verdi til false hvis den er true, og skrur av lys:
      PALEGG[4] = false;
      digitalWrite(LEDS[3], LOW);
      delay(200);
    }
    else {       //endrer verdi til true hvis den er false, og skrur på lys
      PALEGG[4] = true;
      digitalWrite(LEDS[3], HIGH);
      delay(200);
    }
  }

  if (!digitalRead(KNAPP_RANDOM)) {
    gi_random_verdier();
    blinklys();
    if (PALEGG[0] || PALEGG[1]) {     //Sjekker om det skal blåses luft, lagrer dette i en bool
      PALEGG[2] = true;
    }
    finn_neste_palegg();
    digitalWrite(MOTOR_FRAM, LOW);     //starter motor
    START = true;
  }

  if (!digitalRead(KNAPP_START)) {
    Serial.println("start");
    if (PALEGG[0] || PALEGG[1]) {   //Sjekker om det skal blåses luft, lagrer dette i en bool
      PALEGG[2] = true;
    }
    finn_neste_palegg();
    digitalWrite(MOTOR_FRAM, LOW); //starter motor
    START = true;

  }

  while (START) {
    if (NESTE_PALEGG[0]) { //Smør-stasjon! Kjøres hvis smør er true OG den er på rett sted
      Serial.println("smor next");
      if (!digitalRead(POS_SMOR)) {
        Serial.println("smor riktig plass");
        kjor(KJOR_SMOR, 2000, 1);
        PALEGG[0] = false;                     //Setter SMOR til false for å at den skal gå videre
        NESTE_PALEGG[0] = false;
        digitalWrite(LEDS[0], LOW);
        finn_neste_palegg();
      }
    }

    if (NESTE_PALEGG[1]) { //Syltetøy-stasjon!! Samme logikk som forrige
      Serial.println("syltetoy next");
      if (!digitalRead(POS_SYLTETOY)) {
        Serial.println("syltetoy riktig plass");
        kjor(KJOR_SYLTETOY, 2000, 1);
        PALEGG[1] = false;
        NESTE_PALEGG[1] = false;
        digitalWrite(LEDS[1], LOW);
        finn_neste_palegg();
      }
    }

    if (NESTE_PALEGG[2]) { //Luft
      Serial.println("luft er neste");
      if (!digitalRead(POS_SYLTETOY)) {
        Serial.println("luft riktig plass");
        kjor(KJOR_LUFT, 1000, 1);
        PALEGG[2] = false;
        NESTE_PALEGG[2] = false;
        finn_neste_palegg();
      }
    }

    if (NESTE_PALEGG[3]) {   //OST
      Serial.println("ost er neste");
      if (!digitalRead(POS_OST)) {
        Serial.println("ost riktig plass");
        kjor(KJOR_OST, 1500, 3);
        PALEGG[3] = false;
        NESTE_PALEGG[3] = false;
        digitalWrite(LEDS[2], LOW);
        finn_neste_palegg();
      }
    }

    if (NESTE_PALEGG[4]) {  //GURKA
      Serial.println("agurk next");
      if (!digitalRead(POS_AGURK)) {
        Serial.println("agurk riktig plass");
        kjor(KJOR_PALEGG[4], 1500, 3);
        PALEGG[4] = false;
        NESTE_PALEGG[4] = false;
        digitalWrite(LEDS[3], LOW);
        finn_neste_palegg();
      }
    }
    if (NESTE_PALEGG[5]) {                       //er vipp neste?
      Serial.println("vipp er neste");
      if (!digitalRead(POS_VIPP)) {              //siste stopp:)
        Serial.println("vipp posisjon");
        NESTE_PALEGG[5] = false;
        digitalWrite(MOTOR_FRAM, HIGH);         //motor av
        digitalWrite(KJOR_VIPP, LOW);           //sylinder opp
        delay(1500);
        digitalWrite(KJOR_VIPP, HIGH);               //sylinder ned
        FERDIG = true;
        delay(1000);
        digitalWrite(MOTOR_TILBAKE, LOW);       //motor kjøres bakover
        delay(1000);
      }
    }
    if (!digitalRead(POS_START)) {
      Serial.println("start posisjon");
      if (FERDIG) {
        Serial.println("ferdig er true");
        digitalWrite(MOTOR_TILBAKE, HIGH);      //skru av motor
        START = false;
        FERDIG = false;
      }
    }
  }

}

//funksjon som kjører blinking, til random-knapp:
void blinklys() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(LEDS[i], LOW);
  }
  for (int i = 0; i < 3; i++) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(LEDS[i], HIGH);
      delay(200);
      digitalWrite(LEDS[i], LOW);
    }
  }
}

//funksjon som assigner true eller false til påleggene:
void gi_random_verdier() {
  for (int i = 0; i < 4; i++) {
    tall = random(2);     //henter enten 0 eller 1 randomly
    if (tall == 0) {
      PALEGG[i] = false;  //0 blir false
    }
    else {
      PALEGG[i] = true;   //1 blir true
    }
  }
}

//funksjon for å kjøre pålegg:
void kjor(int HVILKEN, int pause1, int antallrep) {
  digitalWrite(MOTOR_FRAM, HIGH);    //motorstopp
  for (int i = 0; i < antallrep; i++) {
  digitalWrite(HVILKEN, LOW);      //stempel opp
  delay(pause1);
  digitalWrite(HVILKEN, HIGH);
  delay(2000);
  }
  digitalWrite(MOTOR_FRAM, LOW);
}

//funksjon for å finne neste pålegg
void finn_neste_palegg() {
  for (int i = 0; i < 6; i++) {
    if (PALEGG[i]) {
      NESTE_PALEGG[i] = true;
      break;
    }
  }
}
