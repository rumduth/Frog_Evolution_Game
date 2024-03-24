/// \file GameDefines.h
/// \brief Game specific defines.

#ifndef __L4RC_GAME_GAMEDEFINES_H__
#define __L4RC_GAME_GAMEDEFINES_H__

#include "Defines.h"
#include "Sound.h"

/// \brief Sprite enumerated type.
///
/// An enumerated type for the sprites, which will be cast to an unsigned
/// integer and used for the index of the corresponding texture in graphics
/// memory. `Size` must be last.

enum class eSprite : UINT {
	Background, TextWheel,
	PlayerWalkLeftSpriteSheet, PlayerWalkRightSpriteSheet,
	PlayerStandLeftSpriteSheet, PlayerStandRightSpriteSheet,
	PlayerWalkLeft, PlayerWalkRight, PlayerStandLeft, PlayerStandRight,
	PlayerWalkUpSpriteSheet, PlayerWalkUp,
	PlayerWalkDownSpriteSheet, PlayerWalkDown,
	ChickenWalkLeftSpriteSheet, ChickenWalkRightSpriteSheet,
	ChickenStandLeftSpriteSheet, ChickenStandRightSpriteSheet,
	ChickenWalkLeft, ChickenWalkRight, ChickenStandLeft, ChickenStandRight,
	SpiderSriteSheet, SpiderMove,
	SnailSpriteSheet, SnailMove,
	WaterSpriteSheet, WaterMove,
	FoxUpSpriteSheet, FoxMoveUp,
	FoxDownSpriteSheet, FoxMoveDown,
	HawkRightSpriteSheet, HawkMoveRight,
	HawkLeftSpriteSheet, HawkMoveLeft,


	PlayerWalkLeftSpriteSheet1, PlayerWalkRightSpriteSheet1,
	PlayerStandLeftSpriteSheet1, PlayerStandRightSpriteSheet1,
	PlayerWalkLeft1, PlayerWalkRight1, PlayerStandLeft1, PlayerStandRight1,
	PlayerWalkUpSpriteSheet1, PlayerWalkUp1,
	PlayerWalkDownSpriteSheet1, PlayerWalkDown1,

	GrassSpriteSheet, Grass,
  Size  //MUST BE LAST
}; //eSprite

/// \brief Sound enumerated type.
///
/// An enumerated type for the sounds, which will be cast to an unsigned
/// integer and used for the index of the corresponding sample. `Size` must 
/// be last.

enum class eSound: UINT{
  Background, Chicken, Hawk, Slurp, Lose, Win, Frog, Heal,
  Size  //MUST BE LAST
}; //eSound

#endif //__L4RC_GAME_GAMEDEFINES_H__

