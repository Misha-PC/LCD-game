#include <Arduino.h>
#include <Wire.h>
#include "LiquidCrystal_I2C.h"
#include "customChar.h"
#include "game.h"

const char HERT = 7;
const char PLAYER = 6;
const char BOX = 2;
// const char eat[] = {0, 1, 2, 3, 4, 5};

GameMain::GameMain(){}


void GameMain::init ()
{
  lcd.begin();
  lcd.home();

  lcd.setCursor(6, 1);
  lcd.print("Cadrider");
  lcd.setCursor(8, 2);
  lcd.print("game");

  delay(200);

  lcd.createChar(PLAYER, player);
  lcd.createChar(HERT, hert);

  lcd.createChar(0, pos0);
  lcd.createChar(1, pos1);

}
void GameMain::addScore(int inc)    {  score += inc;}
void GameMain::addScore()           {  score++;     }
void GameMain::setScore(int s)      {  score = s;   }

void GameMain::clearStr(int x)
{
  lcd.setCursor(0, x);
  for(int i = 0; i < 20; i++)
  {
    lcd.print(" ");
  }
}

void GameMain::clearGameZone()
{
  for(int i = 0; i < 3; i++)
  {
    GameMain::clearStr(i);
  }
}

void GameMain::draw()
{

  if(x_player != x_playerDrawed)
  {
    x_playerDrawed = x_player;
    GameMain::clearGameZone();
  }

  lcd.setCursor(x_player, 2);
  lcd.write(PLAYER);

  if(live != liveDrawed || score != scoreDrawed)
  {
    GameMain::clearStr(3);
    liveDrawed  = live;
    scoreDrawed = score;

    lcd.setCursor(0, 3);
    lcd.print("Score:");
    lcd.print(score);

    lcd.setCursor(14, 3);
    lcd.print("HP:");

    // lcd.createChar(HERT, hert);
    lcd.setCursor(17, 3);
    for(int i = 0; i < live; i++)
    {
      lcd.write(HERT);
    }
  }
}


void GameMain::drawEat()
{
  if(lastEatMove + moveSpeed - score < millis()){
    lastEatMove = millis();
    if(eat_pos > 1)
    {
      eat_pos = 0;
      GameMain::clearStr(y_eat);
      y_eat++;
      if(y_eat > 2){
        y_eat = 0;
        eat_pos = 0;
        if(x_eat == x_player)
          GameMain::addScore();
        else
          GameMain::liveDown();
        x_eat = random(20);
      }
    }
    // GameMain::clearGameZone();
    lcd.setCursor(x_eat, y_eat);
    if(eat_pos) lcd.write(1);
    else lcd.write(0);
    eat_pos++;
  }
}


void GameMain::printTo(int x, int y, String i)
{
  lcd.setCursor(x, y);
  lcd.print(i);
}

void GameMain::printTo(int x, int y, int i)
{
  lcd.setCursor(x, y);
  lcd.print(i);
}

void GameMain::printTo(int x, int y, float i)
{
  lcd.setCursor(x, y);
  lcd.print(i);
}

int  GameMain::getLive()  {return(live);}

void GameMain::liveDown(int i)
{
  live-=i;
  if(live > 3) live = 3;
  else if(live < 0) live = 0;
}

void GameMain::liveDown(){ if(--live < 0) live = 0; }

void GameMain::setLive (int i)
{
  live = i;
  if(live > 3) live = 3;
  else if(live < 0) live = 0;
}

void GameMain::playerMove(int i)
{
  x_player += i;
  if(x_player > 19) x_player = 19;
  else if(x_player<0) x_player = 0;
}
