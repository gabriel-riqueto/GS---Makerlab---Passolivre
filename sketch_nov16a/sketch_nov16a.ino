// =====================================================
// CARRINHO AUTONOMO - BUMPER + LED
//
// BFD-1000:
// CLP -> D3
// VCC -> 5V
// GND -> GND
//
// LED:
// D4 -> resistor 220~330 ohms -> perna longa do LED
// perna curta do LED -> GND
//
// L298N:
// IN1 -> D11
// IN2 -> D10
// IN3 -> D9
// IN4 -> D8
// =====================================================


// -------------------------
// PINOS
// -------------------------

#define CLP 3
#define LED_COLISAO 4

#define IN1 11
#define IN2 10
#define IN3 9
#define IN4 8


// =====================================================
// TEMPOS
// =====================================================

// Ré mais longa
const unsigned long TEMPO_RE = 1400;

// Curva para direita.
// Como agora está em potência máxima,
// começamos com um tempo menor.
const unsigned long TEMPO_CURVA_90 = 650;


// Estado normal do bumper ao ligar
int estadoNormalCLP;


// =====================================================
// PARAR
// =====================================================

void parar() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


// =====================================================
// FRENTE - POTÊNCIA TOTAL
// =====================================================

void frente() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


// =====================================================
// RÉ - POTÊNCIA TOTAL
// =====================================================

void re() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


// =====================================================
// VIRAR 90 GRAUS PARA DIREITA
// =====================================================

void virarDireita90() {

  parar();

  delay(400);


  // Motor A parado
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);


  // Motor B anda para frente
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);


  delay(TEMPO_CURVA_90);


  parar();

  delay(500);
}


// =====================================================
// VERIFICAR BUMPER
// =====================================================

bool bateu() {

  // O programa aprende qual é o estado normal
  // do CLP quando liga.
  if (digitalRead(CLP) != estadoNormalCLP) {

    // Pequeno debounce
    delay(20);

    if (digitalRead(CLP) != estadoNormalCLP) {

      return true;
    }
  }

  return false;
}


// =====================================================
// REAÇÃO À BATIDA
// =====================================================

void colisao() {

  // 1 - PARA
  parar();


  // 2 - ACENDE LED
  digitalWrite(LED_COLISAO, HIGH);

  delay(300);


  // 3 - DÁ RÉ
  re();

  delay(TEMPO_RE);


  // 4 - PARA
  parar();

  delay(500);


  // 5 - VIRA 90 GRAUS PARA DIREITA
  virarDireita90();


  // 6 - APAGA LED
  digitalWrite(LED_COLISAO, LOW);


  // 7 - Pequena pausa antes de sair novamente
  delay(700);
}


// =====================================================
// SETUP
// =====================================================

void setup() {

  pinMode(CLP, INPUT);

  pinMode(LED_COLISAO, OUTPUT);


  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);


  // Começa parado
  parar();


  // LED começa APAGADO
  digitalWrite(LED_COLISAO, LOW);


  // IMPORTANTE:
  // Ligue o carrinho sem o bumper pressionado.
  estadoNormalCLP = digitalRead(CLP);


  // 2 segundos antes de sair
  delay(2000);
}


// =====================================================
// LOOP
// =====================================================

void loop() {

  // Anda reto normalmente
  frente();


  // Bateu?
  if (bateu()) {

    colisao();


    // Espera o bumper voltar ao estado normal
    // antes de continuar.
    while (digitalRead(CLP) != estadoNormalCLP) {

      parar();

      delay(10);
    }


    delay(300);
  }
}
