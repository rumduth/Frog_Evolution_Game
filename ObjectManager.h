/// \file ObjectManager.h
/// \brief Interface for the object manager CObjectManager.

#ifndef __L4RC_GAME_OBJECTMANAGER_H__
#define __L4RC_GAME_OBJECTMANAGER_H__

#include "BaseObjectManager.h"
#include "Object.h"
#include "Common.h"
#include "Settings.h"
#include <list>
/// \brief The object manager.
///
/// A collection of all of the game objects.

class CObjectManager: 
  public LComponent,
  public LBaseObjectManager<CObject>,

  public LSettings,
  public CCommon{

  private:
      std::list<CObject*> m_stdObjectList; ///< Object list.
      void BroadPhase(); ///< Broad phase collision detection and response.
      void NarrowPhase(CObject* p0, CObject* p1); ///< Narrow phase collision detection and response.
      void CullDeadObjects(); ///< Cull dead objects.
  public:
      bool updatedHawk = false;
    CObject* create(eSprite, const Vector2&); ///< Create new object.
    CObjectManager(); ///< Constructor.
    ~CObjectManager(); ///< Destructor.
    void clear(); ///< Reset to initial conditions.
    void move(); ///< Move all objects.
    void draw(); ///< Draw all objects.
    void lastBoss();
}; //CObjectManager

#endif //__L4RC_GAME_OBJECTMANAGER_H__
