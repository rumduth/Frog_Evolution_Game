#include "Chicken.h"
#include "ComponentIncludes.h"

CChicken::CChicken(eSprite t, const Vector2& p) : CObject(t, p) {
	m_pFrameEvent = new LEventTimer(0.12f);
} //constructor

/// Destructor.

CChicken::~CChicken() {
	delete m_pFrameEvent;
} //destructor



void CChicken::move()
{
	action();
	if (level_frog < 3)
	{
		m_fYScale = level_frog + 0.5;
		m_fXScale = level_frog + 0.5;
	}
	else
	{
		m_fYScale = 2;
		m_fXScale = 2;
	}
	UpdateFramenumber(); //choose current frame

}
void CChicken::action()
{
	float vel = velocity + 10 * level_frog;
	const float delta = m_pTimer->GetFrameTime(); //change in position
	if (m_nSpriteIndex == (UINT)eSprite::ChickenWalkLeft)
	{
		m_vPos.x -= vel * delta;
		if (m_vPos.x <= 0)
			m_nSpriteIndex = (UINT)eSprite::ChickenWalkRight;
	}
	else if (m_nSpriteIndex == (UINT)eSprite::ChickenWalkRight)
	{
		m_vPos.x += vel * delta;
		if (m_vPos.x >= 1350)
			m_nSpriteIndex = (UINT)eSprite::ChickenWalkLeft;
	}

}
void CChicken::UpdateFramenumber() {
	const UINT n = (UINT)m_pRenderer->GetNumFrames(m_nSpriteIndex); //number of framer
	if (n > 1 && m_pFrameEvent && m_pFrameEvent->Triggered())
		m_nCurrentFrame = (m_nCurrentFrame + 1) % n;
}
