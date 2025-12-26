// ПИНЫ МОТОРОВ (L298N)
const int ENA = 5; //левые моторы
const int IN1 = 22;
const int IN2 = 24;

const int ENB = 6; //правые моторы
const int IN3 = 26;
const int IN4 = 28;

// ПИН ЗУММЕРА
const int BUZZER_PIN = 32;

// Скорость (0..255)
const int SPEED_FWD  = 70;
const int SPEED_BACK = 70;

void setup() {
  Serial.begin(115200);      // открыть порт на ПК тем же baudrate[web:64]

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  stopMotors();
}

// --- ФУНКЦИИ ДВИЖЕНИЯ ---

void rightTurn() {
  // обе стороны вперёд
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, SPEED_FWD);
  analogWrite(ENB, SPEED_FWD);

  noTone(BUZZER_PIN);
 
}

void leftTurn() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, SPEED_BACK);
  analogWrite(ENB, SPEED_BACK);

  noTone(BUZZER_PIN);        // назад — без звука
}

void forward() {
  // левая пара назад, правая вперёд (разворот на месте)
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, SPEED_FWD);
  analogWrite(ENB, SPEED_FWD);
  noTone(BUZZER_PIN);
}

void backward() {
  // левая вперёд, правая назад
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, SPEED_FWD);
  analogWrite(ENB, SPEED_FWD);

  noTone(BUZZER_PIN);
}

void sound() {
  tone(BUZZER_PIN, 2300);
}

void silence() {
  noTone(BUZZER_PIN);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  noTone(BUZZER_PIN);
}

// --- ОСНОВНОЙ ЦИКЛ ---

void loop() {
  if (Serial.available() > 0) {        // есть символ от ПК[web:64][web:76]
    char c = Serial.read();

    switch (c) {
      case 'W':
      case 'w':
        forward();
        break;

      case 'S':
      case 's':
        backward();
        break;

      case 'A':
      case 'a':
        leftTurn();
        break;

      case 'D':
      case 'd':
        rightTurn();
        break;
      
      case 'O':
      case 'o':
        sound();
        break;

      case 'P':
      case 'p':
        silence();
        break;

      default:
        stopMotors();   // любая другая клавиша — стоп
        break;
    }
  }
}
