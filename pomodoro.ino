#define LONG_BREAK_STATE 4
#define LEDS_ALL 6
#define LEDS_STATUS 4
#define MAX_POMODOROS_SCORE 15

long pomodorTime = 1500000; // 1000 * 60 * 25;
long shortBreak = 300000; // 1000 * 60 * 5;
long longBreak = 900000; // 1000 * 60 * 15;
int shortBreakLed = A2;
int led1 = A3;
int led2 = A4;
int led3 = 5;
int led4 = 6;
int longBreakLed = A5;
int button = 4;
int externalButton = 3;
int allLeds[LEDS_ALL] = { shortBreakLed, led1, led2, led3, led4, longBreakLed };
int statusLeds[LEDS_STATUS] = { led1, led2, led3, led4 };
int lowLedLevel = 128;
int highLedLevel = 1023;
int pomodorosScore = 0;

void setup() {
  for (int i = 0; i < LEDS_ALL; i++) {
    pinMode(allLeds[i], OUTPUT);
  }
  pinMode(button, INPUT_PULLUP);
  pinMode(externalButton, INPUT_PULLUP);
}
void loop() {
  initialize();
  while (1) {
    for (int i = 1; i <= LONG_BREAK_STATE; i++) {
      cleanAll();
      startPomodoros();
      showScore(0);
      if (i != LONG_BREAK_STATE) {
        startBreak(false);
        showScore(1);
      } else {
        startBreak(true);
        showScore(2);
      }
    }
  }
}
void cleanAll() {
  for (int i = 0; i < LEDS_ALL; i++) {
    analogWrite(allLeds[i], 0);
  }
}
void cleanStatus() {
  for (int i = 0; i < LEDS_STATUS; i++) {
    analogWrite(statusLeds[i], 0);
  }
}
void startPomodoros() {
  unsigned long startTime = millis();
  while (1) {
    if (digitalRead(button) == LOW || digitalRead(externalButton) == HIGH) {
      startTime = millis();
    }
    if (millis() - startTime >= pomodorTime) {
      analogWrite(statusLeds[3], lowLedLevel);
      pomodorosScore++;
      if (pomodorosScore > MAX_POMODOROS_SCORE) {
        pomodorosScore = 1;
      }
      delay(100);
      return;
    } else if (millis() - startTime >= pomodorTime * 0.75) {
      analogWrite(statusLeds[2], lowLedLevel);
    } else if (millis() - startTime >= pomodorTime * 0.50) {
      analogWrite(statusLeds[1], lowLedLevel);
    } else if (millis() - startTime >= pomodorTime * 0.25) {
      analogWrite(statusLeds[0], lowLedLevel);
    } else {
      cleanStatus();
    }
  }
}
void startBreak(boolean isLongBreak) {
  unsigned long startTime = millis();
  long breakTime;
  if (isLongBreak) {
    analogWrite(longBreakLed, highLedLevel);
    breakTime = longBreak;
  } else {
    analogWrite(shortBreakLed, highLedLevel);
    breakTime = shortBreak;
  }
  while (1) {
    if (millis() - startTime >= breakTime) {
      analogWrite(statusLeds[3], lowLedLevel);
      delay(100);
      return;
    } else if (millis() - startTime >= breakTime * 0.75) {
      analogWrite(statusLeds[2], lowLedLevel);
    } else if (millis() - startTime >= breakTime * 0.50) {
      analogWrite(statusLeds[1],
        lowLedLevel);
    } else if (millis() - startTime >= breakTime * 0.25) {
      analogWrite(statusLeds[0], lowLedLevel);
    } else {
      cleanStatus();
    }
  }
}
void showScore(int state) {
  unsigned long currentTime;  
  while (1) {
    if (state == 1) {
      analogWrite(shortBreakLed, highLedLevel);
    } else if (state == 2) {
      analogWrite(longBreakLed, highLedLevel);
    }
    
    switch (pomodorosScore) {
      case 0:
        analogWrite(statusLeds[0], 0);
        analogWrite(statusLeds[1], 0);
        analogWrite(statusLeds[2], 0);
        analogWrite(statusLeds[3], 0);
        break;
      case 1:
        analogWrite(statusLeds[0], 0);
        analogWrite(statusLeds[1], 0);
        analogWrite(statusLeds[2], 0);
        analogWrite(statusLeds[3], highLedLevel);
        break;
      case 2:
        analogWrite(statusLeds[0], 0);
        analogWrite(statusLeds[1], 0);
        analogWrite(statusLeds[2], highLedLevel);
        analogWrite(statusLeds[3], 0);
        break;
      case 3:
        analogWrite(statusLeds[0], 0);
        analogWrite(statusLeds[1], 0);
        analogWrite(statusLeds[2], highLedLevel);
        analogWrite(statusLeds[3], highLedLevel);
        break;
      case 4:
        analogWrite(statusLeds[0], 0);
        analogWrite(statusLeds[1], highLedLevel);
        analogWrite(statusLeds[2], 0);
        analogWrite(statusLeds[3], 0);
        break;
      case 5:
        analogWrite(statusLeds[0], 0);
        analogWrite(statusLeds[1], highLedLevel);
        analogWrite(statusLeds[2], 0);
        analogWrite(statusLeds[3], highLedLevel);
        break;
      case 6:
        analogWrite(statusLeds[0], 0);
        analogWrite(statusLeds[1], highLedLevel);
        analogWrite(statusLeds[2], highLedLevel);
        analogWrite(statusLeds[3], 0);
        break;
      case 7:
        analogWrite(statusLeds[0], 0);
        analogWrite(statusLeds[1], highLedLevel);
        analogWrite(statusLeds[2], highLedLevel);
        analogWrite(statusLeds[3], highLedLevel);
        break;
      case 8:
        analogWrite(statusLeds[0], highLedLevel);
        analogWrite(statusLeds[1], 0);
        analogWrite(statusLeds[2], 0);
        analogWrite(statusLeds[3], 0);
        break;
      case 9:
        analogWrite(statusLeds[0], highLedLevel);
        analogWrite(statusLeds[1], 0);
        analogWrite(statusLeds[2], 0);
        analogWrite(statusLeds[3], highLedLevel);
        break;
      case 10:
        analogWrite(statusLeds[0], highLedLevel);
        analogWrite(statusLeds[1], 0);
        analogWrite(statusLeds[2], highLedLevel);
        analogWrite(statusLeds[3], 0);
        break;
      case 11:
        analogWrite(statusLeds[0], highLedLevel);
        analogWrite(statusLeds[1], 0);
        analogWrite(statusLeds[2], highLedLevel);
        analogWrite(statusLeds[3], highLedLevel);
        break;
      case 12:
        analogWrite(statusLeds[0], highLedLevel);
        analogWrite(statusLeds[1], highLedLevel);
        analogWrite(statusLeds[2], 0);
        analogWrite(statusLeds[3], 0);
        break;
      case 13:
        analogWrite(statusLeds[0], highLedLevel);
        analogWrite(statusLeds[1], highLedLevel);
        analogWrite(statusLeds[2], 0);
        analogWrite(statusLeds[3], highLedLevel);
        break;
      case 14:
        analogWrite(statusLeds[0], highLedLevel);
        analogWrite(statusLeds[1], highLedLevel);
        analogWrite(statusLeds[2], highLedLevel);
        analogWrite(statusLeds[3], 0);
        break;
      case 15:
        analogWrite(statusLeds[0], highLedLevel);
        analogWrite(statusLeds[1], highLedLevel);
        analogWrite(statusLeds[2], highLedLevel);
        analogWrite(statusLeds[3], highLedLevel);
        break;
    }
    currentTime = millis();
    while (millis() - currentTime < 100) {
      if (digitalRead(button) == LOW || digitalRead(externalButton) == HIGH) {
        return;
      }
    }
    cleanAll();
    currentTime = millis();
    while (millis() - currentTime < 100) {
      if (digitalRead(button) == LOW || digitalRead(externalButton) == HIGH) {
        return;
      }
    }
  }
}
void initialize() {
  unsigned long currentTime;
  int randomDelay;
  int count = 4;
  while (1) {
    if (count % 4 == 0) {
      count = 0;
      randomDelay = random(1, 100);
    }
    for (int i = 0; i < LEDS_ALL - 1; i++) {
      if (i == 0) {
        analogWrite(allLeds[LEDS_ALL - 1], 0);
      } else {
        analogWrite(allLeds[i - 1], 0);
      }
      analogWrite(allLeds[i], highLedLevel);
      if (i == LEDS_ALL - 1) {
        analogWrite(allLeds[0], lowLedLevel);
      } else {
        analogWrite(allLeds[i + 1], lowLedLevel);
      }

      currentTime = millis();
      while (millis() - currentTime < randomDelay) {
        if (digitalRead(button) == LOW || digitalRead(externalButton) == HIGH) {
          return;
        }
      }
    }

    for (int j = LEDS_ALL - 1; j > 0; j--) {
      if (j == LEDS_ALL - 1) {
        analogWrite(allLeds[0], 0);
      } else {
        analogWrite(allLeds[j + 1], 0);
      }
      analogWrite(allLeds[j], highLedLevel);
      if (j == 0) {
        analogWrite(allLeds[LEDS_ALL - 1], lowLedLevel);
      } else {
        analogWrite(allLeds[j - 1], lowLedLevel);
      }

      currentTime = millis();
      while (millis() - currentTime < randomDelay) {
        if (digitalRead(button) == LOW || digitalRead(externalButton) == HIGH) {
          return;
        }
      }
    }
    count++; 
  }
}
