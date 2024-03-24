/// \file Player.h
/// \brief Interface for the player object class CPlayer.

#ifndef __L4RC_GAME_HAWK_H__
#define __L4RC_GAME_HAWK_H__
#include "Component.h"
#include "Common.h"
#include "ObjectManager.h"
#include "Settings.h"
#include <Windows.h>
#include "shellapi.h"
#include "Object.h"
#include "EventTimer.h"

/// \brief The player object. 
///
/// The abstract representation of the player object. The player differs from
/// the other objects in the game in that it moves in respond to device inputs.

class CHawk : public CObject {
protected:
    LEventTimer* m_pFrameEvent = nullptr; ///< Frame event timer.
    void UpdateFramenumber(); ///< Update frame number.
private:
    bool isMoveDown = true;
    Vector2 FrogPos;
    float velocity_x;
    float velocity_y;
    bool isProcessing = false;
    Vector2 currentPos;
public:
    CHawk(eSprite t, const Vector2& p); ///< Constructor.
    virtual ~CHawk(); ///< Destructor;
    virtual void move(); ///< Move player object.
    void action();

}; //CPlayer

#endif //__L4RC_GAME_PLAYER_H__

