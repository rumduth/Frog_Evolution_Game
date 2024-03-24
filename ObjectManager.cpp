/// \file ObjectManager.cpp
/// \brief Code for the the object manager class CObjectManager.

#include "ObjectManager.h"
#include "ComponentIncludes.h"
#include "Object.h"
#include "Player.h"
#include "Chicken.h"
#include "Spider.h"
#include "Snail.h"
#include "ParticleEngine.h"
#include "River.h"
#include "Fox.h"
#include "Hawk.h"
#include "Grass.h"
using namespace std;

/// Create an object and put a pointer to it at the back of the object list
/// `m_stdObjectList`, which it inherits from `LBaseObjectManager`.
/// \param t Sprite type.
/// \param pos Initial position.
/// \return Pointer to the object created.

CObject* CObjectManager::create(eSprite t, const Vector2& pos){
    CObject* pObj = nullptr;

    switch (t) {
    case eSprite::PlayerWalkLeft:
        pObj = new CPlayer(eSprite::PlayerWalkLeft, pos);
        break;

    case eSprite::PlayerWalkRight:
        pObj = new CPlayer(eSprite::PlayerWalkRight, pos);
        break;

    case eSprite::PlayerStandLeft:
        pObj = new CPlayer(eSprite::PlayerStandLeft, pos);
        break;

    case eSprite::PlayerStandRight:
        pObj = new CPlayer(eSprite::PlayerStandRight, pos);
        break;
    case eSprite::PlayerWalkDown:
        pObj = new CPlayer(eSprite::PlayerWalkDown, pos);
        break;
    case eSprite::PlayerWalkUp:
        pObj = new CPlayer(eSprite::PlayerWalkUp, pos);
        break;

    case eSprite::ChickenStandLeft:
        pObj = new CChicken(eSprite::ChickenStandLeft,pos);
        break;
    case eSprite::ChickenStandRight:
        pObj = new CChicken(eSprite::ChickenStandRight, pos);
        break;
    case eSprite::ChickenWalkRight:
        pObj = new CChicken(eSprite::ChickenWalkRight, pos);
        break;
    case eSprite::ChickenWalkLeft:
        pObj = new CChicken(eSprite::ChickenWalkLeft, pos);
        break;
     
    case eSprite::SpiderMove:
        pObj = new CSpider(eSprite::SpiderMove, pos);
        break;
    
    case eSprite::SnailMove:
        pObj = new CSnail(eSprite::SnailMove, pos);
        break;

    case eSprite::WaterMove:
        pObj = new CRiver(eSprite::WaterMove, pos);
        break;

    case eSprite::FoxMoveUp:
        pObj = new CFox(eSprite::FoxMoveUp, pos);
        break;
    case eSprite::FoxMoveDown:
        pObj = new CFox(eSprite::FoxMoveDown, pos);
        break;

    case eSprite::HawkMoveRight:
        pObj = new CHawk(eSprite::HawkMoveRight, pos);
        break;

    case eSprite::HawkMoveLeft:
        pObj = new CHawk(eSprite::HawkMoveLeft, pos);
        break;
    case eSprite::Grass:
        pObj = new CGrass(eSprite::Grass, pos);
        break;

    default: pObj = new CObject(t, pos);
    } //switch
	m_stdObjectList.push_back(pObj); //push pointer onto object list
	return pObj; //return pointer to created object
} //create


CObjectManager::CObjectManager() {
} //constructor

/// Destruct all of the objects in the object list.

CObjectManager::~CObjectManager() {
    for (auto const& p : m_stdObjectList) //for each object
        delete p; //delete object
} //destructor
void CObjectManager::clear() {
    for (auto const& p : m_stdObjectList) //for each object
        delete p; //delete object

    m_stdObjectList.clear(); //clear the object list
} //clear
void CObjectManager::move() {
    
    if (level_frog == 3 && updatedHawk == true)
    {
        m_pObjectManager->create(eSprite::HawkMoveLeft, { 0,600 });
        m_pObjectManager->create(eSprite::FoxMoveDown, { 50,300 });
        updatedHawk = false;
    }
    if (level_frog == 5 && updatedHawk == true)
    {
        m_pObjectManager->create(eSprite::HawkMoveRight, { 1400,650 });
        m_pObjectManager->create(eSprite::FoxMoveUp, { 140, 0 });

        updatedHawk = false;
    }
    if (score % 7 == 0 && updated == true)
    {
        for (int i = 0; i < number_snails/3; i++)
        {
            float random_x = rand() % m_nWinWidth;
            float random_y = rand() % 350;
            m_pObjectManager->create(eSprite::SnailMove, { random_x,random_y });
        }
        for (int i = 0; i < number_snails / 2; i++)
        {
            float random_x = rand() % m_nWinWidth;
            float random_y = rand() % 350;
            m_pObjectManager->create(eSprite::SpiderMove, { random_x,random_y });
        }
        for (int i = 0; i < number_foxes; i++)
        {
            if (i % 2 == 1)
            {
                float random_x = rand() % m_nWinWidth;
                m_pFox = (CFox*)m_pObjectManager->create(eSprite::FoxMoveUp, { random_x, 0 });
            }
            else
            {
                float random_x = rand() % m_nWinWidth;
                m_pFox = (CFox*)m_pObjectManager->create(eSprite::FoxMoveDown, { random_x, 300 });
            }
        }
        float random_x = rand() % m_nWinWidth;
        float random_y = rand() % 350;
        m_pObjectManager->create(eSprite::ChickenWalkLeft, { random_x,random_y });
        updated = false;
    }
    for (auto const& p : m_stdObjectList) //for each object
        p->move(); //move it

      //now do object-object collision detection and response and
      //remove any dead objects from the object list.
  
    BroadPhase(); //broad phase collision detection and response
    CullDeadObjects(); //remove dead objects from object list
} //move
void CObjectManager::CullDeadObjects() {
    for (auto i = m_stdObjectList.begin(); i != m_stdObjectList.end();) {
        if ((*i)->isDead()) { 
            delete* i; //delete object
            i = m_stdObjectList.erase(i); //remove from object list and advance to next object
        } //if

        else ++i; //advance to next object
    } //for
} //CullDeadObjects

void CObjectManager::BroadPhase() {
    for (auto i = m_stdObjectList.begin(); i != m_stdObjectList.end(); i++) {
        CObject* p = *i; //shorthand
        p->CreateBoundingShapes();
        for (auto j = next(i); j != m_stdObjectList.end(); j++)
            NarrowPhase(*i, *j);
        if (frog_winning)
        {
            clear();
            break;
        }
    } //BroadPhase
    if (frog_winning)
        lastBoss();
}
void CObjectManager::lastBoss()
{
    m_pPlayer = (CPlayer*)m_pObjectManager->create(eSprite::PlayerStandRight,
        Vector2(m_nWinWidth / 2, 80 / 2.0f));
}

void CObjectManager::NarrowPhase(CObject* p0, CObject* p1)
{
    if (p0->m_nSpriteIndex != (UINT)eSprite::PlayerWalkLeft && p0->m_nSpriteIndex != (UINT)eSprite::PlayerWalkRight
        && p0->m_nSpriteIndex != (UINT)eSprite::PlayerWalkUp &&  p0->m_nSpriteIndex != (UINT)eSprite::PlayerWalkDown)
        return;
    if (p1->m_nSpriteIndex == (UINT)eSprite::PlayerWalkLeft && p1->m_nSpriteIndex == (UINT)eSprite::PlayerWalkRight
        && p1->m_nSpriteIndex == (UINT)eSprite::PlayerWalkUp && p1->m_nSpriteIndex == (UINT)eSprite::PlayerWalkDown)
        return;

    

    

    if (!p0->m_bDead)
    {
        if (p1->m_nSpriteIndex == (UINT)eSprite::ChickenWalkLeft || p1->m_nSpriteIndex == (UINT)eSprite::ChickenWalkRight)
        {
            const BoundingBox& frog = p0->m_box;
            const BoundingBox& chicken = p1->m_box;
            if (frog.Intersects(chicken)) {
                if (level_frog < 3)
                {
                    m_pAudio->play(eSound::Frog);

                    frog_health -= 5;
                    p0->m_vPos.x += 50;
                    p0->m_vPos.y -= 50;
                    if (frog_health <= 0)
                    {
                        p0->kill();
                        m_frog_dead = true;
                        m_pAudio->play(eSound::Lose);

                    }
                }
                else
                {
                    score++;
                    m_pAudio->play(eSound::Slurp);

                    p1->kill();
                    m_time.clear();
                }
            }
        }
        else if (p1->m_nSpriteIndex == (UINT)eSprite::SnailMove || p1->m_nSpriteIndex == (UINT)eSprite::SpiderMove)
        {
            const BoundingBox& frog = p0->m_box;
            const BoundingBox& insects = p1->m_box;
            if (frog.Intersects(insects)) {
                p1->kill();
                score++;
                m_pAudio->play(eSound::Slurp);

                if (score == 10)
                {
                    max_frog_health = 25;
                    frog_health += 5;
                    number_chickens = 7;
                    updated = true;
                }
                else if (score == 20)
                {
                    max_frog_health = 30;
                    frog_health += 5;

                    level_frog = 3;
                    updatedHawk = true;
                    number_chickens = 8;
                    updated = true;
                }
                else if (score == 30)
                {
                    if(score >= 30)
                        level_frog = 4;

                    max_frog_health = 35;
                    frog_health += 5;
                    number_chickens = 9;
                    updated = true;
                }
                else if (score == 40)
                {
                    if(score >= 40)
                        level_frog = 5;

                    max_frog_health = 40;
                    frog_health += 5;
                    updatedHawk = true;
                    number_chickens = 11;
                    updated = true;
                }
                else if (score == 50)
                {
                    max_frog_health = 45;
                    frog_health += 5;
                    number_chickens = 12;
                    updated = true;
                }
                else if (score >= 60)
                {
                    frog_winning = true;
                    
                }
                else if (score % 10 == 0)
                {
                    updated = true;
                    m_pAudio->play(eSound::Win);

                }

                if (score < 10)
                    level_frog = 1;
                else if (score < 20)
                    level_frog = 2;
                else if (score < 30)
                    level_frog = 3;
                else if (score < 40)
                    level_frog = 4;
                else if (score < 50)
                    level_frog = 5;
                else
                    level_frog = 6;
            }
        }
         else if (p1->m_nSpriteIndex == (UINT)eSprite::WaterMove)
            {
                const BoundingBox& frog = p0->m_box;
                const BoundingBox& river = p1->m_box;
                if (frog.Intersects(river))
                {
                    int t = m_frame_time;
                    if (m_time.count(t))
                        return;
                    else
                    {
                        if (t % 3 == 0 && frog_health < max_frog_health)
                        {
                            m_pAudio->play(eSound::Heal);
                            frog_health++;
                            m_time[t] = true;
                        }
                    }
                }
            }
         else if (p1->m_nSpriteIndex == (UINT)eSprite::FoxMoveDown || p1->m_nSpriteIndex == (UINT)eSprite::FoxMoveUp)
        {
        const BoundingBox& frog = p0->m_box;
        const BoundingBox& fox = p1->m_box;
        if (frog.Intersects(fox))
        {
            if (level_frog >= 4)
            {
                p1->kill();
                score += 2;
                m_pAudio->play(eSound::Slurp);

            }
            else
            {
                m_pAudio->play(eSound::Frog);
                frog_health -= 8;
                p0->m_vPos.x += 50;
                p0->m_vPos.y += 50;
                if (frog_health <= 0)
                {
                    p0->kill();
                    m_frog_dead = true;
                    m_pAudio->play(eSound::Lose);

                }
            }
        }
        }
         else if (p1->m_nSpriteIndex == (UINT)eSprite::HawkMoveLeft || p1->m_nSpriteIndex == (UINT)eSprite::HawkMoveRight)
        {
        const BoundingBox& frog = p0->m_box;
        const BoundingBox& hawk = p1->m_box;
        if (frog.Intersects(hawk))
        {
            if (level_frog >= 5)
            {
                p1->kill();
                score += 3;
                m_pAudio->play(eSound::Slurp);

            }
            else
            {
                p0->kill();
                m_frog_dead = true;
                m_pAudio->play(eSound::Lose);

            }
        }
        }
           
    
    }
}



void CObjectManager::draw() {
    for (auto const& p : m_stdObjectList) { //for each object
        p->draw();
    } //for
} //draw

/*
void CObject::draw(){
  m_pRenderer->Draw(this);
} //draw*/