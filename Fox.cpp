#include "Fox.h"
#include "ComponentIncludes.h"

CFox::CFox(eSprite t, const Vector2& p) : CObject(t, p) {
	m_pFrameEvent = new LEventTimer(0.12f);
} //constructor

/// Destructor.

CFox::~CFox() {
	delete m_pFrameEvent;
} //destructor



void CFox::move()
{
	int t = m_frame_time;
	if (m_vPos.y <= 0)
		m_nSpriteIndex = (UINT)eSprite::FoxMoveUp;
	if (m_vPos.y >= 300)
		m_nSpriteIndex = (UINT)eSprite::FoxMoveDown;
	if (t % 3 != 0)
		return;
		
	const float delta = m_pTimer->GetFrameTime(); //change in position
	if (m_nSpriteIndex == (UINT)eSprite::FoxMoveUp)
		m_vPos.y += velocity * delta;
	else
		m_vPos.y -= velocity * delta;

	m_fXScale = 2.0;
	m_fYScale = 2.0;
	UpdateFramenumber(); //choose current frame
	
}

void CFox::UpdateFramenumber() {

	const UINT n = (UINT)m_pRenderer->GetNumFrames(m_nSpriteIndex); //number of framer
	if (n > 1 && m_pFrameEvent && m_pFrameEvent->Triggered())
		m_nCurrentFrame = (m_nCurrentFrame + 1) % n;
}
