// Definindo os pinos dos LEDs
const int ledVerdeCarro = 13;
const int ledAmareloCarro = 12;
const int ledVermelhoCarro = 14;
const int ledVerdePedestre = 27;
const int ledVermelhoPedestre = 26;

// Definindo o pino do botão
const int botao = 25;

// Variável para controlar o estado do semáforo
bool pedestreQuerAtravessar = false;

// Variáveis para controle de tempo
unsigned long previousMillis = 0;
const long intervalAmarelo = 1000; // 1 segundo
const long intervalVermelho = 2000; // 2 segundos

// Estados do semáforo
enum State {
  VERDE_CARRO,
  AMARELO_CARRO,
  VERMELHO_CARRO_VERDE_PEDESTRE,
  VERMELHO_PEDESTRE
};

State currentState = VERDE_CARRO;

void IRAM_ATTR handleButton() {
  pedestreQuerAtravessar = true;
}

void setup() {
  // Inicialização dos LEDs
  pinMode(ledVerdeCarro, OUTPUT);
  pinMode(ledAmareloCarro, OUTPUT);
  pinMode(ledVermelhoCarro, OUTPUT);
  pinMode(ledVerdePedestre, OUTPUT);
  pinMode(ledVermelhoPedestre, OUTPUT);

  // Inicialização do botão
  pinMode(botao, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(botao), handleButton, FALLING);

  // Inicializa os LEDs
  digitalWrite(ledVerdeCarro, HIGH);
  digitalWrite(ledAmareloCarro, LOW);
  digitalWrite(ledVermelhoCarro, LOW);
  digitalWrite(ledVerdePedestre, LOW);
  digitalWrite(ledVermelhoPedestre, HIGH);

  // Inicialização da comunicação serial
  Serial.begin(115200);
  Serial.println("Semáforo iniciado.");
}

void loop() {
  unsigned long currentMillis = millis();

  switch (currentState) {
    case VERDE_CARRO:
      if (pedestreQuerAtravessar) {
        Serial.println("Semáforo dos carros está em amarelo.");
        digitalWrite(ledVerdeCarro, LOW);
        digitalWrite(ledAmareloCarro, HIGH);
        previousMillis = currentMillis;
        currentState = AMARELO_CARRO;
      }
      break;

    case AMARELO_CARRO:
      if (currentMillis - previousMillis >= intervalAmarelo) {
        Serial.println("Semáforo dos carros está vermelho e dos pedestres em verde.");
        digitalWrite(ledAmareloCarro, LOW);
        digitalWrite(ledVermelhoCarro, HIGH);
        digitalWrite(ledVerdePedestre, HIGH);
        digitalWrite(ledVermelhoPedestre, LOW);
        previousMillis = currentMillis;
        currentState = VERMELHO_CARRO_VERDE_PEDESTRE;
      }
      break;

    case VERMELHO_CARRO_VERDE_PEDESTRE:
      if (currentMillis - previousMillis >= intervalVermelho) {
        Serial.println("Semáforo dos carros está verde e dos pedestres está vermelho.");
        digitalWrite(ledVerdePedestre, LOW);
        digitalWrite(ledVermelhoPedestre, HIGH);
        digitalWrite(ledVermelhoCarro, LOW);
        digitalWrite(ledVerdeCarro, HIGH);
        pedestreQuerAtravessar = false;
        currentState = VERDE_CARRO;
      }
      break;

    case VERMELHO_PEDESTRE:
      // Este estado não é usado, mas pode ser estendido para mais funcionalidades.
      break;
  }
}
