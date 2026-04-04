#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int leds[4] = {8, 9, 10, 11};
int buttons[4] = {2, 3, 4, 5};
int buzzer = 6;

#define MAX_LEVEL 100
int sequence[MAX_LEVEL];

int level = 1;   // start at 1 (score will be level-1)
int step = 0;

bool showNewSequence = true;

unsigned long lastInputTime;
int allowedTime;

// 🔧 SETUP
void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT_PULLUP);
  }
  pinMode(buzzer, OUTPUT);

  randomSeed(analogRead(0));

  lcd.init();
  lcd.backlight();

  showScore(); // shows 0
}

// 🔁 LOOP
void loop() {

  if (showNewSequence) {

    generateSequence();
    showSequence();

    step = 0;
    showNewSequence = false;

    lastInputTime = millis();

    // ⏱️ smoother timing
    allowedTime = 5000 - (level * 120);
    allowedTime = max(allowedTime, 1500);
  }

  // ⚠️ HURRY UP WARNING (last 1 sec)
  if (!showNewSequence && (millis() - lastInputTime > allowedTime - 1000)) {
    lcd.setCursor(0, 1);
    lcd.print("Hurry Up!   ");

    tone(buzzer, 1000, 50); // quick beep
  }

  // ❌ TOO SLOW
  if (!showNewSequence && (millis() - lastInputTime > allowedTime)) {
    tooSlow();
  }

  // 🔘 BUTTON INPUT
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttons[i]) == LOW) {
      checkInput(i);
      lastInputTime = millis();
      delay(200);
    }
  }
}

// 🔹 Generate random sequence
void generateSequence() {
  for (int i = 0; i < level; i++) {
    sequence[i] = random(0, 4);
  }
}

// 🔹 Show sequence
void showSequence() {

  showScore();

  int currentDelay = 600 - (level * 15);
  currentDelay = max(currentDelay, 180);

  delay(500);

  for (int i = 0; i < level; i++) {
    digitalWrite(leds[sequence[i]], HIGH);
    delay(currentDelay);
    digitalWrite(leds[sequence[i]], LOW);
    delay(currentDelay);
  }
}

// 🔹 Check input
void checkInput(int input) {
  if (input == sequence[step]) {
    step++;

    digitalWrite(leds[input], HIGH);
    tone(buzzer, 800 + input * 200, 100);
    delay(100);
    digitalWrite(leds[input], LOW);

    if (step == level) {
      levelUp();
    }

  } else {
    lose();
  }
}

// 🔹 Level up
void levelUp() {
  level++;
  showNewSequence = true;

  // 🎉 small success tone
  tone(buzzer, 1200, 150);
}

// 🔴 Wrong input
void lose() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wrong Input");

  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(level - 1);

  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], HIGH);
  }

  // 🎵 falling sound
  for (int freq = 800; freq >= 200; freq -= 50) {
    tone(buzzer, freq);
    delay(50);
  }
  noTone(buzzer);

  delay(2500);
  resetGame();
}

// ⏱️ TOO SLOW
void tooSlow() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Too Slow!");

  lcd.setCursor(0, 1);
  lcd.print("Score: ");
  lcd.print(level - 1);

  // 🔊 warning beeps
  for (int i = 0; i < 3; i++) {
    tone(buzzer, 400);
    delay(200);
    noTone(buzzer);
    delay(200);
  }

  delay(2000);
  resetGame();
}

// 🔄 Reset
void resetGame() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
  }

  level = 1;
  step = 0;
  showNewSequence = true;

  lcd.clear();
  showScore(); // back to 0
}

// 🖥️ Display score
void showScore() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Score: ");
  lcd.print(level - 1);
}