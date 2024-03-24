/// \file Player.h
/// \brief Interface for the player object class CPlayer.

#ifndef __L4RC_GAME_PLAYER_H__
#define __L4RC_GAME_PLAYER_H__

#include <Windows.h>
#include "shellapi.h"

#include "Object.h"
#include "EventTimer.h"

/// \brief The player object. 
///
/// The abstract representation of the player object. The player differs from
/// the other objects in the game in that it moves in respond to device inputs.

class CPlayer: public CObject{
  protected:  
    LEventTimer* m_pFrameEvent = nullptr; ///< Frame event timer.
    
    void UpdateFramenumber(); ///< Update frame number.
private:
    float velocity_x = 100.0f;
    float jump_up = 50.f;
    float velocity_y = 350.0f;
    float gravity = -500.f;
    bool jumpLeft = false;
    bool jumpRight = false;
    bool isInAir = false;
    bool isJump = false;
    bool walkLeft = false;
    bool walkRight = false;
    bool isUp = true;
    bool jumpUp = false;
    bool jumpDown = false;
    bool isMovingUpDown = false;
    bool isJumpUp = false;
    bool isJumpDown = false;
    float fixHeight = 50;
    bool evol = false;

  public:
    CPlayer(eSprite t, const Vector2& p); ///< Constructor.
    virtual ~CPlayer(); ///< Destructor.

    virtual void move(); ///< Move player object.
    
    void JumpLeft(); ///< Start walking left.
    void JumpRight(); ///< Start walking right.
    void WalkRight();
    void WalkLeft();
    void Stop(); ///< Stop walking.
    void Jump();
    void setFrogStatus();
    void JumpLeftAct(); ///< Start walking left.
    void JumpRightAct(); ///< Start walking right.
    void WalkRightAct();
    void WalkLeftAct();
    void JumpAct();
    void Up();
    void Down();
    void JumpUpAct();
    void JumpDownAct();
    void JumpUp();
    void JumpDown();
    void JumpUpAct2();
    void JumpDownAct2();

}; //CPlayer

#endif //__L4RC_GAME_PLAYER_H__

