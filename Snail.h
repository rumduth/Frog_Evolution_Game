/// \file Player.h
/// \brief Interface for the player object class CPlayer.

#ifndef __L4RC_GAME_SNAIL_H__
#define __L4RC_GAME_SNAIL_H__

#include <Windows.h>
#include "shellapi.h"

#include "Object.h"
#include "EventTimer.h"

/// \brief The player object. 
///
/// The abstract representation of the player object. The player differs from
/// the other objects in the game in that it moves in respond to device inputs.

class CSnail : public CObject {
protected:
    LEventTimer* m_pFrameEvent = nullptr; ///< Frame event timer.
    void UpdateFramenumber(); ///< Update frame number.
private:


public:
    CSnail(eSprite t, const Vector2& p); ///< Constructor.
    virtual ~CSnail(); ///< Destructor;
    virtual void move(); ///< Move player object.


}; //CPlayer

#endif //__L4RC_GAME_PLAYER_H__

