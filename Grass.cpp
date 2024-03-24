#include "Grass.h"

#include "ComponentIncludes.h"

CGrass::CGrass(eSprite t, const Vector2& p) : CObject(t, p) {
	m_pFrameEvent = new LEventTimer(0.12f);
} //constructor

/// Destructor.

CGrass::~CGrass() {
	delete m_pFrameEvent;
} //destructor



void CGrass::move()
{
	m_nSpriteIndex = (UINT)eSprite::Grass;
	const float delta = m_pTimer->GetFrameTime(); //change in position
	UpdateFramenumber(); //choose current frame
}

void CGrass::UpdateFramenumber() {

	const UINT n = (UINT)m_pRenderer->GetNumFrames(m_nSpriteIndex); //number of framer
	if (n > 1 && m_pFrameEvent && m_pFrameEvent->Triggered())
		m_nCurrentFrame = (m_nCurrentFrame + 1) % n;
}
