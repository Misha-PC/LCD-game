#include <Arduino.h>
#include "game.h"

   // w = 119   65
   // a = 97    68
   // s = 115   66
   // d = 100   67
   // esc     = 27
   // space   = 32

#define JOY_PIN A0

GameMain game;

void setup()
{
  game.init();
  while (digitalRead(A1)) {
    delay(10);
  }
  game.printTo(5, 3, "loading...");
  game.clearStr(3);
  game.setScore(0);
  game.setLive(3);
  delay(250);
  game.draw();
  Serial.begin(9600);
}

int moveDelay, joystickVal;
unsigned long lastLiveDown, lastMove;

void loop()
{
  game.draw();
  game.drawEat();
  if(!digitalRead(A1) && lastLiveDown + 1000 < millis())
  {
    lastLiveDown = millis();
    // game.playerMove(-1);
    game.draw();
  }

  joystickVal = analogRead(JOY_PIN);
  if (joystickVal > 550)
  {
    if(millis() > lastMove + moveDelay)
    {
      moveDelay = 0;
      lastMove = millis();
      game.playerMove(-1);
    }
    moveDelay = 1200 - joystickVal;
  }else if (joystickVal < 450)
  {
    if(millis() > lastMove + moveDelay)
    {
      moveDelay = 0;
      lastMove = millis();
      game.playerMove(1);
    }
    moveDelay = joystickVal + 185;
  }
}
//test
