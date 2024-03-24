#include "Hawk.h"
#include "ComponentIncludes.h"
#include "Component.h"
#include "Common.h"
#include "ObjectManager.h"
#include "Settings.h"
#include <Windows.h>
#include "shellapi.h"
#include "Object.h"
#include "EventTimer.h"
CHawk::CHawk(eSprite t, const Vector2& p) : CObject(t, p) {
	m_pFrameEvent = new LEventTimer(0.12f);
} //constructor

/// Destructor.

CHawk::~CHawk() {
	delete m_pFrameEvent;
} //destructor



void CHawk::move()
{
	action();
	UpdateFramenumber(); //choose current frame
}

void CHawk::action()
{
	const float delta = m_pTimer->GetFrameTime(); //change in position
	if (m_vPos.x <= 0)
		m_nSpriteIndex = (UINT)eSprite::HawkMoveRight;
	if (m_vPos.x >= 1400)
		m_nSpriteIndex = (UINT)eSprite::HawkMoveLeft;
	
	if (doneflying && isMoveDown)
	{
		if (!isProcessing)
		{
			isProcessing = true;
			FrogPos = frog_pos;
			currentPos = m_vPos;
			velocity_x = abs(FrogPos.x - currentPos.x) / 4;
			velocity_y = abs(FrogPos.y - currentPos.y) / 4;
			if(m_nSpriteIndex == (UINT)eSprite::HawkMoveRight)
				m_vPos.x += velocity_x * delta;
			else
				m_vPos.x -= velocity_x * delta;
			m_vPos.y -= velocity_y * delta;
			if (m_vPos.y <= FrogPos.y)
				isMoveDown = false;
		}
		else
		{
			if (m_nSpriteIndex == (UINT)eSprite::HawkMoveRight)
				m_vPos.x += velocity_x * delta;
			else
				m_vPos.x -= velocity_x * delta;
			m_vPos.y -= velocity_y * delta;
			if (m_vPos.y <= frog_pos.y)
			{
				isMoveDown = false;
				isProcessing = false;
			}
		}
	}
	else if (doneflying && !isMoveDown)
	{
		if (!isProcessing)
		{
			isProcessing = true;
			currentPos = m_vPos;
			if (m_nSpriteIndex == (UINT)eSprite::HawkMoveRight)
			{
				velocity_x = (1400 - currentPos.x) / 4;
				velocity_y = (700 - currentPos.y) / 4;
				m_vPos.x += velocity_x * delta;
				m_vPos.y += velocity_y * delta;
				if (m_vPos.y >= 700)
					isProcessing = false;
			}
			else
			{
				velocity_x = (currentPos.x - 0.0) / 4;
				velocity_y = (700 - currentPos.y) / 4;
				m_vPos.x -= velocity_x * delta;
				m_vPos.y += velocity_y * delta;
				if (m_vPos.y >= 700)
					isProcessing = false;
			}
		}
		else
		{

			if (m_nSpriteIndex == (UINT)eSprite::HawkMoveRight)
			{
				m_vPos.x += velocity_x * delta;
				m_vPos.y += velocity_y * delta;
				if (m_vPos.y >= 700)
				{
					isMoveDown = true;
					isProcessing = false;
					doneflying = false;
				}
			}
			else
			{
				m_vPos.x -= velocity_x * delta;
				m_vPos.y += velocity_y * delta;
				if (m_vPos.y >= 700)
				{
					isMoveDown = true;
					isProcessing = false;
					doneflying = false;
				}
			}
			
		}

	}
}

void CHawk::UpdateFramenumber() {

	const UINT n = (UINT)m_pRenderer->GetNumFrames(m_nSpriteIndex); //number of framer
	if (n > 1 && m_pFrameEvent && m_pFrameEvent->Triggered())
		m_nCurrentFrame = (m_nCurrentFrame + 1) % n;
}
