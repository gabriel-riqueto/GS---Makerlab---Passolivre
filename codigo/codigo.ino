#define CLP 3
#define LED_COLISAO 4

#define IN1 11
#define IN2 10
#define IN3 9
#define IN4 8

const unsigned long TEMPO_RE = 1400;

const unsigned long TEMPO_CURVA_90 = 650;

int estadoNormalCLP;

void parar() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void frente() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void re() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void virarDireita90() {

  parar();

  delay(400);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);


  delay(TEMPO_CURVA_90);

  parar();

  delay(500);
}

bool bateu() {

  if (digitalRead(CLP) != estadoNormalCLP) {

    delay(20);

    if (digitalRead(CLP) != estadoNormalCLP) {

      return true;
    }
  }

  return false;
}

void colisao() {

  parar();

  digitalWrite(LED_COLISAO, HIGH);

  delay(300);

  re();

  delay(TEMPO_RE);

  parar();

  delay(500);

  virarDireita90();

  digitalWrite(LED_COLISAO, LOW);

  delay(700);
}

void setup() {

  pinMode(CLP, INPUT);

  pinMode(LED_COLISAO, OUTPUT);


  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  parar();

  digitalWrite(LED_COLISAO, LOW);

  estadoNormalCLP = digitalRead(CLP);

  delay(2000);
}

void loop() {

  frente();

  if (bateu()) {

    colisao();

    while (digitalRead(CLP) != estadoNormalCLP) {

      parar();

      delay(10);
    }


    delay(300);
  }
}
