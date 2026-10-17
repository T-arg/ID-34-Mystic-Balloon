/*
  Mystic Balloon: https://t-arg.github.io/ID-34-Mystic-Balloon/

  Arduboy version 1.7.2:  https://github.com/T-arg/ID-34-Mystic-Balloon

  MADE by TEAM a.r.g. : https://t-arg.github.io/

  2016-2018 - GAVENO - CastPixel - JO3RI - Martian220

  Game License: MIT : https://opensource.org/licenses/MIT

*/

//determine the game
#define GAME_ID 34

#include "globals.h"
#include "menu.h"
#include "game.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "levels.h"


typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM  mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuJbox,
  stateMenuPlaySelect,
  stateMenuInfo,
  stateMenuSoundfx,
  stateGameNextLevel,
  stateGamePlaying,
  stateGamePause,
  stateGameOver,
  stateMenuPlayContinue,
  stateMenuPlayNew,
};

void setup()
{
  arduboy.boot();                                           // begin with the boot logo en setting up the device to work
  arduboy.audio.begin();
  arduboy.setFrameRate(60);                                 // set the frame rate of the game at 60 fps
  loadSetEEPROM();
  if (arduboy.audio.enabled()) ATM.play(silentSong);        // an empty song keeps the playroutine running (music.h)
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  musicUpdate();
  if (gameState < STATE_GAME_NEXT_LEVEL && arduboy.everyXFrames(10))sparkleFrames = (++sparkleFrames) % 5;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}

