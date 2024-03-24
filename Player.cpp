/// \file Player.cpp
/// \brief Code for the player object class CPlayer.

#include "Player.h"
#include "ComponentIncludes.h"

/// Create and initialize an player object given its initial position.
/// \param t Sprite type.
/// \param p Initial position of player.

CPlayer::CPlayer(eSprite t, const Vector2& p): CObject(t, p){ 
  m_pFrameEvent = new LEventTimer(0.12f);
} //constructor

/// Destructor.

//

CPlayer::~CPlayer(){
  delete m_pFrameEvent;
} //destructor

/// Move in response to device input. The amount of motion is proportional to
/// the frame time.

void CPlayer::move() {
    
    
    if (doneflying == false)
    {
        doneflying = true;
        frog_pos = m_vPos;
    }
    if (isInAir)
    {
        if (jumpRight)
            JumpRightAct();
        else if (jumpLeft)
            JumpLeftAct();
        else if (isJump)
            JumpAct();
        m_nCurrentFrame = 0;
    }
    else
    {
        if (walkRight)
            WalkRightAct();
        else if (walkLeft)
            WalkLeftAct();
        else if (jumpUp)
            JumpUpAct();
        else if (jumpDown)
            JumpDownAct();
        else if (isJumpDown)
            JumpDownAct2();
        else if (isJumpUp)
            JumpUpAct2();
        else
            Stop();
    }
    if (m_vPos.y >= 350 + 25 * level_frog)
        m_vPos.y = 350 + 25 * level_frog;
   
    m_fXScale = level_frog * 0.75;
    m_fYScale = level_frog * 0.75;
    
    UpdateFramenumber(); //choose current frame
}
void CPlayer::Jump()
{
    isJump = true;
    isInAir = true;
    fixHeight = m_vPos.y;
}


void CPlayer::JumpAct()
{
    const float delta = m_pTimer->GetFrameTime(); //change in position
    const float h = m_pRenderer->GetHeight(eSprite::PlayerStandRight);
   
    velocity_y += delta * gravity;
    if (isUp)
    {
        m_vPos += velocity_y * delta * Vector2::UnitY;
        if (velocity_y <= 0)
        {
            isUp = false;
            velocity_y = 0;
            gravity = -gravity;
        }
    }
    else
    {
        m_vPos -= velocity_y * delta * Vector2::UnitY;
        if (m_vPos.y <= fixHeight - h)
        {
            m_vPos.y = fixHeight - h;
            setFrogStatus();

        }
    }
    
    
}

void CPlayer::WalkLeftAct()
{
    if (isInAir)
        return;
    const float delta = m_pTimer->GetFrameTime(); //change in position
    m_vPos.x -= velocity_x * delta;
    setFrogStatus();
}

void CPlayer::WalkRightAct()
{
    if (isInAir)
        return;
    const float delta = m_pTimer->GetFrameTime(); //change in position
    m_vPos.x += velocity_x * delta;
    setFrogStatus();

}
void CPlayer::JumpLeftAct()
{
    const float delta = m_pTimer->GetFrameTime(); //change in position
    const float h = m_pRenderer->GetHeight(eSprite::PlayerStandRight);

    float jump_velocity_x = velocity_x + 30;
    m_vPos.x -= jump_velocity_x * delta;
   
    velocity_y += gravity * delta;
    if (isUp)
    {
        m_vPos += velocity_y * delta * Vector2::UnitY;
        if (velocity_y <= 0)
        {
            isUp = false;
            velocity_y = 0;
            gravity = -gravity;
        }
    }
    else
    {
        m_vPos -= velocity_y * delta * Vector2::UnitY;
        if (m_vPos.y <= fixHeight - h)
        {
            m_vPos.y = fixHeight - h;
            setFrogStatus();
        }
    }
   
}

void CPlayer::JumpRightAct()
{
    const float delta = m_pTimer->GetFrameTime(); //change in position
    const float h = m_pRenderer->GetHeight(eSprite::PlayerStandRight);

    float jump_velocity_x = velocity_x + 30;
   
    m_vPos.x += jump_velocity_x * delta;
    velocity_y += gravity * delta;
    if (isUp)
    {
        m_vPos += velocity_y * delta * Vector2::UnitY;
        if (velocity_y <= 0)
        {
            isUp = false;
            velocity_y = 0;
            gravity = -gravity;
        }
    }
    else
    {
        m_vPos -= velocity_y * delta * Vector2::UnitY;
        if (m_vPos.y <= fixHeight - h)
        {
            m_vPos.y = fixHeight - h;
            setFrogStatus();
        }
    }
   
}
  /*
  * 
  * 
  if (isJump)
  {
      delta = m_pTimer->GetFrameTime();
      velocity += gravity * delta;
      if (upward)
      {
          m_vPos += velocity * delta * Vector2::UnitY;
          if (velocity <= 0)
          {
              upward = false;
              velocity = 0;
              gravity = -gravity;
          }
      }
      else
      {
          m_vPos -= velocity * delta * Vector2::UnitY;
          if (m_vPos.y <= 0)
          {
              m_vPos.y = 0;
              upward = true;
              gravity = -gravity;
              velocity = 350.0f;
              isJump = false;
          }
      }
  }
  */
   //move

/// Update the frame number in the animation sequence.

void CPlayer::UpdateFramenumber(){
  const UINT n = (UINT)m_pRenderer->GetNumFrames(m_nSpriteIndex); //number of frames
  if (isInAir)
      return;
  if(n > 1 && m_pFrameEvent && m_pFrameEvent->Triggered())
    m_nCurrentFrame = (m_nCurrentFrame + 1)%n; 
 
} //UpdateFramenumber

/// Change the sprite to the walking left sprite. This function will be called
/// in response to device inputs.

void CPlayer::WalkLeft(){
    if (isInAir)
        return;

  if(m_nSpriteIndex != (UINT)eSprite::PlayerWalkLeft)
    m_nSpriteIndex = (UINT)eSprite::PlayerWalkLeft;
  walkLeft = true;
} //WalkLeft

void CPlayer::Up()
{
    if (isInAir)
        return;
    m_nSpriteIndex = (UINT)eSprite::PlayerWalkUp;
    jumpUp = true;
}

void CPlayer::Down()
{
    if(isInAir)
        return;
    m_nSpriteIndex = (UINT)eSprite::PlayerWalkDown;
    jumpDown = true;

}
void CPlayer::JumpUpAct()
{
    const float delta = m_pTimer->GetFrameTime(); //change in position
    m_vPos += delta * jump_up * Vector2::UnitY;
    setFrogStatus();

}
void CPlayer::JumpUpAct2()
{
    const float delta = m_pTimer->GetFrameTime(); //change in position

    m_vPos += delta * jump_up* 1.5 * Vector2::UnitY;
    setFrogStatus();
}
void CPlayer::JumpDownAct()
{
    const float delta = m_pTimer->GetFrameTime(); //change in position

    m_vPos -= delta * jump_up * Vector2::UnitY;
    setFrogStatus();

}
void CPlayer::JumpDownAct2()
{
    const float delta = m_pTimer->GetFrameTime(); //change in position

    m_vPos -= delta * jump_up *1.25* Vector2::UnitY;
    setFrogStatus();

}
/// Change the sprite to the walking right sprite. This function will be called
/// in response to device inputs.

void CPlayer::WalkRight(){
    if (isInAir)
        return;
 
  if(m_nSpriteIndex != (UINT)eSprite::PlayerWalkRight)
    m_nSpriteIndex = (UINT)eSprite::PlayerWalkRight;
  walkRight = true;

} //WalkRight

void CPlayer::JumpLeft()
{
    if (m_nSpriteIndex != (UINT)eSprite::PlayerWalkLeft)
        m_nSpriteIndex = (UINT)eSprite::PlayerWalkLeft;
    jumpLeft = true;
    isInAir = true;
    fixHeight = m_vPos.y;
}

void CPlayer::JumpRight()
{
    if (m_nSpriteIndex != (UINT)eSprite::PlayerWalkRight)
        m_nSpriteIndex = (UINT)eSprite::PlayerWalkRight;
    jumpRight = true;
    isInAir = true;
    fixHeight = m_vPos.y;

}
/// Change the sprite to a standing sprite, depending on which direction the
/// player is walking.

void CPlayer::Stop(){
  if(m_nSpriteIndex == (UINT)eSprite::PlayerWalkRight)
    m_nSpriteIndex = (UINT)eSprite::PlayerStandRight;
  
  else if(m_nSpriteIndex == (UINT)eSprite::PlayerWalkLeft)
    m_nSpriteIndex = (UINT)eSprite::PlayerStandLeft;
  else if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkUp)
      m_nSpriteIndex = (UINT)eSprite::PlayerWalkUp;
  else if (m_nSpriteIndex == (UINT)eSprite::PlayerWalkDown)
      m_nSpriteIndex = (UINT)eSprite::PlayerWalkDown;

  m_nCurrentFrame = 0;
} //Stop




void CPlayer::setFrogStatus()
{
    jumpLeft = false;
    jumpRight = false;
    isInAir = false;
    isJump = false;
    walkLeft = false;
    walkRight = false;
    velocity_x = 100.f;
    velocity_y = 350.f + level_frog * 20;
    gravity = -500;
    isUp = true;
    jumpUp = false;
    jumpDown = false;
    isMovingUpDown = false;
    isJumpDown = false;
    isJumpUp = false;
}

/*
if (isInAir)
   {
       if (jumpLeft || jumpRight)
       {
           float jump_velocity = velocity_x + 50;
           if (jumpLeft)
               m_vPos.x -= jump_velocity * delta;
           if (jumpRight)
               m_vPos.x += jump_velocity * delta;
           velocity_y += gravity * delta;
           if (isUp)
           {
               m_vPos += velocity_y * delta * Vector2::UnitY;
               if (velocity_y <= 0)
               {
                   isUp = false;
                   velocity_y = 0;
                   gravity = -gravity;
               }
           }
           else
           {
               m_vPos -= velocity_y * delta * Vector2::UnitY;
               if (m_vPos.y <= h/2)
               {
                   m_vPos.y = h/2;
                   setFrogStatus();
               }
           }
       }
   }
   /*
   else if (walkLeft || walkRight)
   {
   if (walkLeft)
       m_vPos.x -= velocity_x * delta;
   if (walkRight)
       m_vPos.x += velocity_x * delta;
   setFrogStatus();
   }
   else if (isJump)
   {
   if (isUp)
   {
       m_vPos += velocity_y * delta * Vector2::UnitY;
       if (velocity_y <= 0)
       {
           isUp = false;
           velocity_y = 0;
           gravity = -gravity;
       }
   }
   else
   {
       m_vPos -= velocity_y * delta * Vector2::UnitY;
       if (m_vPos.y <= h / 2)
       {
           m_vPos.y = h / 2;
           setFrogStatus();
       }

*/

void CPlayer::JumpUp()
{
    isJumpUp = true;
}

void CPlayer::JumpDown()
{
    isJumpDown = true;
}

