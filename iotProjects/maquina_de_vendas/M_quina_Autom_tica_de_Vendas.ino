#include <Keypad.h>

// Definição dos pinos do teclado matricial
const byte numRows = 4; 
const byte numCols = 4;
byte rows[numRows] = { 23, 22, 21, 19 };
byte columns[numCols] = { 18, 5, 4, 2 };

char keys[numRows][numCols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

Keypad myKeypad = Keypad(makeKeymap(keys), rows, columns, numRows, numCols);

// Definição dos pinos dos LEDs
const int greenLedPin = 32;
const int redLedPin = 33;

// Definição dos estados
enum State {START, CHECK, VEND, INSUFFICIENT};
State state = START;

// Variável para acumular o valor inserido
float currentAmount = 0.0;

void setup() {
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(redLedPin, LOW);
  
  Serial.begin(9600);
  Serial.println("Sistema de Vendas Automático Iniciado");
}

void loop() {
  char key = myKeypad.getKey();
  
  switch (state) {
    case START:
      if (key != NO_KEY) {
        switch (key) {
          case '1':
            currentAmount += 0.10;
            Serial.println("R$ 0,10 inserido");
            break;
          case '2':
            currentAmount += 0.20;
            Serial.println("R$ 0,20 inserido");
            break;
          case '3':
            currentAmount += 0.25;
            Serial.println("R$ 0,25 inserido");
            break;
          case '4':
            currentAmount += 0.50;
            Serial.println("R$ 0,50 inserido");
            break;
          case '*':
            Serial.print("Valor total inserido: R$ ");
            Serial.println(currentAmount);
            state = CHECK;
            break;
          default:
            Serial.println("Tecla inválida");
            break;
        }
      }
      break;

    case CHECK:
      if (currentAmount >= 1.00) {
        state = VEND;
      } else {
        state = INSUFFICIENT;
      }
      break;

    case VEND:
      Serial.println("Produto Vendido");
      digitalWrite(greenLedPin, HIGH);
      delay(2000);
      digitalWrite(greenLedPin, LOW);
      currentAmount = 0.0;
      state = START;
      break;

    case INSUFFICIENT:
      Serial.println("Saldo Insuficiente");
      digitalWrite(redLedPin, HIGH);
      delay(3000);
      digitalWrite(redLedPin, LOW);
      currentAmount = 0.0;
      state = START;
      break;
  }
}
