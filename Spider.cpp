#include "Spider.h"
#include "ComponentIncludes.h"

CSpider::CSpider(eSprite t, const Vector2& p) : CObject(t, p) {
	m_pFrameEvent = new LEventTimer(0.12f);
} //constructor

/// Destructor.

CSpider::~CSpider() {
	delete m_pFrameEvent;
} //destructor



void CSpider::move()
{
	m_nSpriteIndex = (UINT)eSprite::SpiderMove;
	const float delta = m_pTimer->GetFrameTime(); //change in position
	UpdateFramenumber(); //choose current frame
}

void CSpider::UpdateFramenumber() {

	const UINT n = (UINT)m_pRenderer->GetNumFrames(m_nSpriteIndex); //number of framer
	if (n > 1 && m_pFrameEvent && m_pFrameEvent->Triggered())
		m_nCurrentFrame = (m_nCurrentFrame + 1) % n;
}
