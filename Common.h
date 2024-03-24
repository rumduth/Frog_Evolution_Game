/// \file Common.h
/// \brief Interface for the class CCommon.

#ifndef __L4RC_GAME_COMMON_H__
#define __L4RC_GAME_COMMON_H__
#include <unordered_map>
#include "GameDefines.h"
//forward declarations to make the compiler less stroppy
using namespace std;
class CObjectManager; 
class LSpriteRenderer;
class CPlayer;
class CChicken;
class CSpider;
class CSnail;
class CRiver;
class CHawk;
class CFox;
class CGrass;
/// \brief The common variables class.
///
/// CCommon is a singleton class that encapsulates things that are common to
/// different game components, including game state variables. Making it a
/// singleton class means that we can avoid passing its member variables
/// around as parameters, which makes the code minisculely faster, and more
/// importantly, makes the code more readable by reducing function clutter.

class CCommon{
  protected:  
    static LSpriteRenderer* m_pRenderer; ///< Pointer to renderer.
    static CObjectManager* m_pObjectManager; ///< Pointer to object manager.
    static CGrass* m_pGrass;
    static CPlayer* m_pPlayer;
    static CChicken* m_pChicken;
    static CSpider* m_pSpider;
    static CRiver* m_pRiver;
    static CFox* m_pFox;
    static bool m_frog_dead;
    static CSnail* m_pSnail;
    static CHawk* m_pHawk;
    static int score;
    static int max_frog_health;
    static int frog_health;
    static int level_frog;
    static int number_spiders;
    static int number_foxes;
    static int number_hawks;
    static int number_snails;
    static int number_chickens;
    static bool updated;
    static bool frog_winning;
    static float m_frame_time;
    static unordered_map<int, bool> m_time;
    static unordered_map<int, bool> m_time_fox;
    static bool update_frog;

    //For updating the hawk
    static bool doneflying;
    static Vector2 frog_pos;
}; //CCommon

#endif //__L4RC_GAME_COMMON_H__
