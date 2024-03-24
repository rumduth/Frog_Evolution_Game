/// \file Object.cpp
/// \brief Code for the game object class CObject.

#include "Object.h"
#include "ComponentIncludes.h"

/// Create an object, given its sprite type and initial position.
/// \param t Type of sprite.
/// \param p Initial position of object.

CObject::CObject(eSprite t, const Vector2& p):
  LBaseObject(t, p){ 
} //constructor


/// The only object in this game is the text wheel, which slowly rotates at 1/8
/// revolutions per second. This is achieved by adding a small amount to its
/// roll angle, proportional to frame time.

void CObject::move(){ 
	
  const float t = m_pTimer->GetFrameTime(); //frame interval in seconds
 
} //move

/// Ask the renderer to draw the sprite described in the sprite descriptor.
/// Note that `CObject` is derived from `LBaseObject` which is inherited from
/// `LSpriteDesc2D`. Therefore `LSpriteRenderer::Draw(const LSpriteDesc2D*)`
/// will accept `this` as a parameter, automatically down-casting it from
/// `CObject*` to `LSpriteDesc2D*`, effectively drawing the object from its
/// sprite descriptor.

void CObject::draw(){ 
  m_pRenderer->Draw(this);
} //draw
CObject::~CObject() {
} //destructor
const Vector2& CObject::GetPos() {
	return m_vPos;
}

bool CObject::isDead()
{
	return m_bDead;
}

void CObject::kill()
{
	m_bDead = true;
}

void CObject::CollisionResponse(const BoundingBox& b)
{
	float w, h;
	m_pRenderer->GetSize(m_nSpriteIndex, w, h);
	w /= 2; h /= 2;

	const float top = b.Center.y + b.Extents.y;
	const float bottom = b.Center.y - b.Extents.y;

	const float left = b.Center.x - b.Extents.x;
	const float right = b.Center.x + b.Extents.x;
	if (m_vPos.x >= left - w && m_vPos.x <= right + w && m_vPos.y <= top + h && m_vPos.y >= bottom - h)
		kill();
}


void CObject::CreateBoundingShapes()
{
	float w, h;
	m_pRenderer->GetSize(m_nSpriteIndex, w, h);
	const Vector2 tl = m_vPos + 0.25f * Vector2(-w, h); //top left corner
	const Vector2 br = m_vPos + 0.25f * Vector2(w, -h); //bottom right corner
	BoundingBox::CreateFromPoints(m_box, tl, br);
}
