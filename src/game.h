#include <Wire.h>
#include "LiquidCrystal_I2C.h"

#ifndef GAME_H
#define GAME_H

class GameMain {
private:
  int moveSpeed = 500, eat_pos, x_player, x_playerDrawed, x_eat = 5, y_eat, y_eatDrawed, score, live, liveDrawed, scoreDrawed;
  unsigned long lastEatMove;
  LiquidCrystal_I2C lcd{0x27, 20, 4};

public:
  GameMain();
  // ~gameMain();

  void init();
  void draw();
  void drawEat();

  void addScore(int);
  void addScore();
  void setScore(int);

  void printTo(int, int, String);
  void printTo(int, int, int);
  void printTo(int, int, float);

  int  getLive();
  void setLive(int);
  void liveDown(int);
  void liveDown();

  void clearGameZone();
  void clearStr(int);

  void playerMove(int);


};


#endif
