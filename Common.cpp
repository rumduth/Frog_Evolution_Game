/// \file Common.cpp
/// \brief Code for the class CCommon.

#include "Common.h"

LSpriteRenderer* CCommon::m_pRenderer = nullptr;
CObjectManager* CCommon::m_pObjectManager = nullptr;
CPlayer* CCommon::m_pPlayer = nullptr;
CChicken* CCommon::m_pChicken = nullptr;
CGrass* CCommon::m_pGrass = nullptr;
bool CCommon::m_frog_dead = false;
CSpider* CCommon::m_pSpider = nullptr;
CSnail* CCommon::m_pSnail = nullptr;
int CCommon::max_frog_health = 20;
int CCommon::frog_health = 20;
int CCommon::score = 0;
int CCommon::level_frog = 1;
int CCommon::number_snails = 10;
int CCommon::number_spiders = 8;
int CCommon::number_chickens = 8;
bool CCommon::updated = false;
bool CCommon::frog_winning = false;
CRiver* CCommon::m_pRiver = nullptr;
CFox* CCommon::m_pFox = nullptr;
int CCommon::number_foxes = 3;
int CCommon::number_hawks = 2;
bool CCommon::update_frog = false;
CHawk* CCommon::m_pHawk = nullptr;
unordered_map<int, bool> CCommon::m_time = {};
unordered_map<int, bool> CCommon::m_time_fox = {};
float CCommon::m_frame_time = 0;

bool CCommon::doneflying = false;
Vector2 CCommon::frog_pos = { 0.0,0.0 };