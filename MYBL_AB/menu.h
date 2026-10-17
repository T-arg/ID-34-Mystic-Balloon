#ifndef MENU_BITMAPS_H
#define MENU_BITMAPS_H

#include <Arduino.h>
#include "globals.h"

#define FONT_TINY                 0
#define FONT_SMALL                1
#define FONT_BIG                  2

#define DATA_TIMER                0
#define DATA_SCORE                1
#define DATA_LEVEL                2

byte blinkingFrames = 0;
byte sparkleFrames = 0;
byte cont = 0;

extern void drawNumbers(byte numbersX, byte numbersY, byte fontType, byte data);

void drawTitleScreen()
{
  if (arduboy.everyXFrames(8))blinkingFrames = (++blinkingFrames) % 32;
  byte *p = arduboy.getBuffer();                                 // unpack the background straight into the screen buffer
  const byte *r = titleScreenRle;
  for (byte *e = p + 1024; p < e;)
  {
    byte c = pgm_read_byte(r++);
    if (c & 128)
    {
      byte v = pgm_read_byte(r++);
      c = (c & 127) + 3;
      while (c--) *p++ = v;
    }
    else
    {
      c++;
      while (c--) *p++ = pgm_read_byte(r++);
    }
  }
  sprites.drawSelfMasked(85, 45, badgeMysticBalloon, 0);
  sprites.drawSelfMasked(79, 43, stars, sparkleFrames);
  sprites.drawSelfMasked(9, 9, leftGuyLeftEye, pgm_read_byte(&blinkingEyesLeftGuy[blinkingFrames]));
  sprites.drawSelfMasked(15, 13, leftGuyRightEye, pgm_read_byte(&blinkingEyesLeftGuy[blinkingFrames]));
  sprites.drawSelfMasked(109, 34, rightGuyEyes, pgm_read_byte(&blinkingEyesRightGuy[blinkingFrames]));
}

void stateMenuIntro()
{
  if (introFrame < INTRO_FRAMES) arduboyIntro(introFrame);                  // the ARDUBOY letters land on the notes
  else if (introFrame < INTRO_FRAMES + 120) sprites.drawSelfMasked(49, 20, T_arg, 0);   // then the TEAM a.r.g. logo
  else
  {
    drawTitleScreen();
    if ((introFrame > INTRO_FRAMES + 210) || arduboy.justPressed(A_BUTTON | B_BUTTON))
    {
      gameState = STATE_MENU_MAIN;
      sfx(sfxSelect);
    }
  }
  introFrame++;
}

const byte menuStates[] PROGMEM = { STATE_MENU_SOUNDFX, STATE_MENU_PLAY, STATE_MENU_INFO, STATE_MENU_JBOX };   // CONF PLAY INFO JBOX

void stateMenuMain()
{
  drawTitleScreen();
  sprites.drawOverwrite(51, 9, mainMenu, 0);
  if (arduboy.justPressed(DOWN_BUTTON) && (menuSelection < 3))
  {
    menuSelection++;
    sfx(sfxMove);
  }
  if (arduboy.justPressed(UP_BUTTON) && (menuSelection > 0))
  {
    menuSelection--;
    sfx(sfxMove);
  }
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = pgm_read_byte(&menuStates[menuSelection]);
    sfx(sfxSelect);
  }
  sprites.drawPlusMask(46, 9 + 9 * menuSelection, selector_plus_mask, 0);
}

// jukebox: UP / DOWN picks SD (songs) or FX (sound effects), LEFT / RIGHT picks the number, A plays the effect again, B leaves
void jukeFxPlay() { if (jukeRow) sfx((const uint8_t *)pgm_read_word(&jukeFxList[jukeFx])); }

void stateMenuJbox()
{
  drawTitleScreen();
  sprites.drawOverwrite(53, 18, jboxMenu, 0);
  if (arduboy.justPressed(DOWN_BUTTON)) jukeRow = 1;
  if (arduboy.justPressed(UP_BUTTON)) jukeRow = 0;
  byte *v = jukeRow ? &jukeFx : &jukeTune;
  byte last = jukeRow ? JUKE_FX - 1 : TUNE_COUNT;
  if (arduboy.justPressed(RIGHT_BUTTON) && *v < last) { (*v)++; jukeFxPlay(); }
  if (arduboy.justPressed(LEFT_BUTTON) && *v > 0) { (*v)--; jukeFxPlay(); }
  if (arduboy.justPressed(A_BUTTON)) jukeFxPlay();
  for (byte r = 0; r < 2; r++)
  {
    byte y = 21 + 9 * r;                                                  // in the black space next to SD and FX
    sprites.drawSelfMasked(70, y, numbersSmall, (r ? jukeFx : jukeTune) + 1);
    if (arduboy.frameCount & 16)                                          // blinking arrows
    {
      sprites.drawSelfMasked(67, y, jukeArrowL, 0);
      sprites.drawSelfMasked(74, y, jukeArrowR, 0);
    }
  }
  sprites.drawPlusMask(48, 18 + 9 * jukeRow, selector_plus_mask, 0);
  if (arduboy.justPressed(B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
    sfx(sfxSelect);
  }
}


void stateMenuInfo()
{
  sprites.drawSelfMasked(43, 2, badgeMysticBalloon, 0);
  sprites.drawSelfMasked(37, 0, stars, sparkleFrames);
  sprites.drawSelfMasked(40, 48, madeBy, 0);
  EEPROM.get(OFFSET_HSCORE, scorePlayer);
  if (EEPROM.read(OFFSET_COINSHS) == TOTAL_COINS)
  {
    sprites.drawSelfMasked(21, 28, badgeSuper, 0);
  }
  else
  {
    sprites.drawSelfMasked(28, 28, badgeBorder, 0);
  }
  sprites.drawSelfMasked(30, 28, badgeHighScore, 0);
  drawNumbers(55, 30, FONT_BIG, DATA_SCORE);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
    sfx(sfxSelect);
  }
}

void stateMenuSoundfx()
{
  drawTitleScreen();
  sprites.drawOverwrite(51, 9, soundMenu, 0);
  if (arduboy.justPressed(DOWN_BUTTON))
  {
    arduboy.audio.on();
    sfx(sfxMove);
  }
  if (arduboy.justPressed(UP_BUTTON)) arduboy.audio.off();
  sprites.drawPlusMask(54, 18 + 9 * arduboy.audio.enabled(), selector_plus_mask, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    arduboy.audio.saveOnOff();
    gameState = STATE_MENU_MAIN;
    sfx(sfxSelect);
  }
}

void stateMenuPlaySelect()
{
  drawTitleScreen();
  sprites.drawOverwrite(53, 18, continueMenu, 0);
  if (arduboy.justPressed(DOWN_BUTTON))
  {
    cont = 1;
    sfx(sfxMove);
  }
  if (arduboy.justPressed(UP_BUTTON))
  {
    cont = 0;
    sfx(sfxMove);
  }
  sprites.drawPlusMask(48, 18 + 9 * cont, selector_plus_mask, 0);
  if (arduboy.justPressed(B_BUTTON))
  {
    gameState = STATE_GAME_PLAYCONTNEW + cont;
    cont = 0;
    sfx(sfxSelect);
  }
  if (arduboy.justPressed(A_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
    sfx(sfxSelect);
  }
}


#endif
