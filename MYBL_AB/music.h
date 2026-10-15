#ifndef MUSIC_H
#define MUSIC_H

// Music and sound effects for Mystic Balloon (ATMlib).
//   mysticTitle   title screen and menus: 8 bars, 2 channels, loops forever
// Sound effects are one-track ATM_SFX_TRACKs for ATM.playSfx() (ATMlib has ONE effect slot, a new effect replaces the running one).

#include <ATMcmds.h>

#ifndef Song
#define Song const uint8_t PROGMEM
#endif

// ---------------------------------------------------------------------------
// Mystic Balloon - title. E phrygian, a sparse bell melody over a slow minor / major arpeggio pad. 8 bars of 64 ticks.
// ch0 lead (pulse), ch1 pad (square, arpeggio). 98 bytes
// ---------------------------------------------------------------------------
Song mysticTitle[] = {
  0x04,                         // Number of tracks
  0x00, 0x00,                   // Address of track 0   //0   lead
  0x38, 0x00,                   // Address of track 1   //56  pad (4 bars)
  0x4D, 0x00,                   // Address of track 2   //77  pad loop
  0x54, 0x00,                   // Address of track 3   //84  silent

  0x00,                         // Channel 0 entry track (lead)
  0x02,                         // Channel 1 entry track (pad loop)
  0x03,                         // Channel 2 entry track (silent)
  0x03,                         // Channel 3 entry track (silent)

  //"Track 0" lead [56 bytes]
  ATM_SET_TEMPO(30),
  ATM_VOL(40),
  ATM_SL_VOL((uint8_t)-1),
  ATM_NOTE_B4,  ATM_DELAY(24), ATM_NOTE_E5,  ATM_DELAY(8), ATM_NOTE_D5_, ATM_DELAY(32),   // Em
  ATM_NOTE_C5,  ATM_DELAY(24), ATM_NOTE_A4,  ATM_DELAY(8), ATM_NOTE_C5,  ATM_DELAY(32),   // F
  ATM_NOTE_B4,  ATM_DELAY(24), ATM_NOTE_G4,  ATM_DELAY(8), ATM_NOTE_B4,  ATM_DELAY(32),   // Em
  ATM_NOTE_D5_, ATM_DELAY(24), ATM_NOTE_F5_, ATM_DELAY(8), ATM_NOTE_D5_, ATM_DELAY(32),   // B
  ATM_NOTE_E5,  ATM_DELAY(24), ATM_NOTE_G5,  ATM_DELAY(8), ATM_NOTE_F5_, ATM_DELAY(32),   // Em
  ATM_NOTE_A4,  ATM_DELAY(24), ATM_NOTE_C5,  ATM_DELAY(8), ATM_NOTE_F5,  ATM_DELAY(32),   // F
  ATM_NOTE_E5,  ATM_DELAY(24), ATM_NOTE_D5,  ATM_DELAY(8), ATM_NOTE_B4,  ATM_DELAY(32),   // Em
  ATM_NOTE_F5_, ATM_DELAY(24), ATM_NOTE_D5_, ATM_DELAY(8), ATM_NOTE_B4,  ATM_DELAY(32),   // B
  ATM_GOTO(0),

  //"Track 1" pad, 4 bars [21 bytes]
  ATM_ARP(0x34, 0x23), ATM_NOTE_E3, ATM_DELAY(64),
  ATM_ARP(0x43, 0x23), ATM_NOTE_F3, ATM_DELAY(64),
  ATM_ARP(0x34, 0x23), ATM_NOTE_E3, ATM_DELAY(64),
  ATM_ARP(0x43, 0x23), ATM_NOTE_B2, ATM_DELAY(64),
  ATM_RETURN,

  //"Track 2" pad loop [7 bytes]
  ATM_VOL(20),
  ATM_REPEAT(2, 1),
  ATM_GOTO(2),

  //"Track 3" silent [1 byte]
  ATM_STOP_CHAN
};

// ---------------------------------------------------------------------------
// sound effects
// ---------------------------------------------------------------------------
ATM_SFX_TRACK(sfxMove,   ATM_VOL(34), ATM_SL_VOL((uint8_t)-8), ATM_NOTE_D4, ATM_DELAY(2));
ATM_SFX_TRACK(sfxSelect, ATM_VOL(40), ATM_SL_VOL((uint8_t)-3), ATM_NOTE_E4, ATM_DELAY(2), ATM_NOTE_A4, ATM_DELAY(8));
ATM_SFX_TRACK(sfxJump,   ATM_VOL(44), ATM_SL_VOL((uint8_t)-3), ATM_NOTE_G3, ATM_DELAY(2), ATM_NOTE_C4, ATM_DELAY(5));
ATM_SFX_TRACK(sfxStep,   ATM_VOL(26), ATM_SL_VOL((uint8_t)-6), ATM_NOTE_D3, ATM_DELAY(2));
ATM_SFX_TRACK(sfxLand,   ATM_VOL(44), ATM_SL_VOL((uint8_t)-6), ATM_NOTE_E2, ATM_DELAY(3));
ATM_SFX_TRACK(sfxWind,   ATM_VOL(22), ATM_SL_VOL((uint8_t)-4), ATM_NOTE_E4, ATM_DELAY(2));
ATM_SFX_TRACK(sfxHurt,   ATM_VOL(46), ATM_SL_VOL((uint8_t)-2), ATM_NOTE_A4, ATM_DELAY(2), ATM_NOTE_E4, ATM_DELAY(2), ATM_NOTE_A3, ATM_DELAY(6));
ATM_SFX_TRACK(sfxKey,    ATM_VOL(44), ATM_SL_VOL((uint8_t)-2), ATM_NOTE_B4, ATM_DELAY(2), ATM_NOTE_E5, ATM_DELAY(2), ATM_NOTE_A5, ATM_DELAY(8));
ATM_SFX_TRACK(sfxCoin,   ATM_VOL(44), ATM_SL_VOL((uint8_t)-3), ATM_NOTE_B4, ATM_DELAY(1), ATM_NOTE_E5, ATM_DELAY(6));
ATM_SFX_TRACK(sfxPop,    ATM_VOL(44), ATM_SL_VOL((uint8_t)-2), ATM_NOTE_A4, ATM_DELAY(2), ATM_NOTE_E5, ATM_DELAY(6));
// the score count at the end of a level: four rising notes
ATM_SFX_TRACK(sfxCount0, ATM_VOL(40), ATM_SL_VOL((uint8_t)-3), ATM_NOTE_C4, ATM_DELAY(3));
ATM_SFX_TRACK(sfxCount1, ATM_VOL(40), ATM_SL_VOL((uint8_t)-3), ATM_NOTE_E4, ATM_DELAY(3));
ATM_SFX_TRACK(sfxCount2, ATM_VOL(40), ATM_SL_VOL((uint8_t)-3), ATM_NOTE_G4, ATM_DELAY(3));
ATM_SFX_TRACK(sfxCount3, ATM_VOL(40), ATM_SL_VOL((uint8_t)-3), ATM_NOTE_C5, ATM_DELAY(3));
const uint8_t *const sfxCountList[] PROGMEM = { sfxCount0, sfxCount1, sfxCount2, sfxCount3 };

// ATMlib does not look at the Arduboy sound setting, so we do it here
void sfx(const uint8_t *track)
{
  if (arduboy.audio.enabled()) ATM.playSfx(track, 1);
}

// one step of the score count (game.h)
byte toneindex = 0;
void sfxCount()
{
  sfx((const uint8_t *)pgm_read_word(&sfxCountList[toneindex > 5 ? 3 : toneindex >> 1]));
  toneindex++;
}

// called once per frame: the title tune plays in the menus (not on the TEAM a.r.g. logo), nothing while playing
bool musicOn = false;
void musicUpdate()
{
  bool want = arduboy.audio.enabled() && gameState > STATE_MENU_INTRO && gameState < STATE_GAME_NEXT_LEVEL;
  if (want == musicOn) return;
  musicOn = want;
  if (want) ATM.play(mysticTitle);
  else ATM.stop();
}

#endif
