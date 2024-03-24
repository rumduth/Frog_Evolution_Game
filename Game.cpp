/// \file Game.cpp
/// \brief Code for the game class CGame.

#include "Game.h"

#include "GameDefines.h"
#include "SpriteRenderer.h"
#include "ComponentIncludes.h"
#include "Player.h"
#include "shellapi.h"

/// Delete the object manager. The renderer needs to be deleted before this
/// destructor runs so it will be done elsewhere.

CGame::~CGame(){
  delete m_pObjectManager;
} //destructor

/// Create the renderer and the object manager, load images and sounds, and
/// begin the game.

void CGame::Initialize(){
  m_pRenderer = new LSpriteRenderer(eSpriteMode::Batched2D); 
  m_pRenderer->Initialize(eSprite::Size); 
  LoadImages(); //load images from xml file list

  m_pObjectManager = new CObjectManager; //set up the object manager 
  LoadSounds(); //load the sounds for this game
  
  BeginGame();
} //Initialize

/// Load the specific images needed for this game. This is where `eSprite`
/// values from `GameDefines.h` get tied to the names of sprite tags in
/// `gamesettings.xml`. Those sprite tags contain the name of the corresponding
/// image file. If the image tag or the image file are missing, then the game
/// should abort from deeper in the Engine code leaving you with an error
/// message in a dialog box.

void CGame::LoadImages(){  
  m_pRenderer->BeginResourceUpload();
  m_pRenderer->Load(eSprite::Background, "background");

  if (frog_winning == true)
  {
      m_pRenderer->Load(eSprite::PlayerStandLeftSpriteSheet, "standleftsheet1");
      m_pRenderer->Load(eSprite::PlayerStandLeft, "standleft1");

      m_pRenderer->Load(eSprite::PlayerStandRightSpriteSheet, "standrightsheet1");
      m_pRenderer->Load(eSprite::PlayerStandRight, "standright1");

      m_pRenderer->Load(eSprite::PlayerWalkRightSpriteSheet, "walkrightsheet1");
      m_pRenderer->Load(eSprite::PlayerWalkRight, "walkright1");
      m_pRenderer->Load(eSprite::PlayerWalkLeftSpriteSheet, "walkleftsheet1");
      m_pRenderer->Load(eSprite::PlayerWalkLeft, "walkleft1");

      m_pRenderer->Load(eSprite::PlayerWalkUpSpriteSheet, "walkupsheet1");
      m_pRenderer->Load(eSprite::PlayerWalkUp, "walkup1");

      m_pRenderer->Load(eSprite::PlayerWalkDownSpriteSheet, "walkdownsheet1");
      m_pRenderer->Load(eSprite::PlayerWalkDown, "walkdown1");
  }
  else
  {
      m_pRenderer->Load(eSprite::PlayerStandLeftSpriteSheet, "standleftsheet");
      m_pRenderer->Load(eSprite::PlayerStandLeft, "standleft");

      m_pRenderer->Load(eSprite::PlayerStandRightSpriteSheet, "standrightsheet");
      m_pRenderer->Load(eSprite::PlayerStandRight, "standright");

      m_pRenderer->Load(eSprite::PlayerWalkRightSpriteSheet, "walkrightsheet");
      m_pRenderer->Load(eSprite::PlayerWalkRight, "walkright");
      m_pRenderer->Load(eSprite::PlayerWalkLeftSpriteSheet, "walkleftsheet");
      m_pRenderer->Load(eSprite::PlayerWalkLeft, "walkleft");

      m_pRenderer->Load(eSprite::PlayerWalkUpSpriteSheet, "walkupsheet");
      m_pRenderer->Load(eSprite::PlayerWalkUp, "walkup");

      m_pRenderer->Load(eSprite::PlayerWalkDownSpriteSheet, "walkdownsheet");
      m_pRenderer->Load(eSprite::PlayerWalkDown, "walkdown");
  }


  //For Chicken chicken
  m_pRenderer->Load(eSprite::ChickenStandLeftSpriteSheet, "chickenstandleftsheet");
  m_pRenderer->Load(eSprite::ChickenStandLeft, "chickenstandleft");

  m_pRenderer->Load(eSprite::ChickenStandRightSpriteSheet, "chickenstandrightsheet");
  m_pRenderer->Load(eSprite::ChickenStandRight, "chickenstandright");

  m_pRenderer->Load(eSprite::ChickenWalkRightSpriteSheet, "chickenwalkrightsheet");
  m_pRenderer->Load(eSprite::ChickenWalkRight, "chickenwalkright");
  m_pRenderer->Load(eSprite::ChickenWalkLeftSpriteSheet, "chickenwalkleftsheet");
  m_pRenderer->Load(eSprite::ChickenWalkLeft, "chickenwalkleft");



  //For Spider and Snail
  m_pRenderer->Load(eSprite::SpiderSriteSheet, "spidersheet");
  m_pRenderer->Load(eSprite::SpiderMove, "spider");
  m_pRenderer->Load(eSprite::SnailSpriteSheet, "snailsheet");
  m_pRenderer->Load(eSprite::SnailMove, "snail");

  //For Water
  m_pRenderer->Load(eSprite::WaterSpriteSheet, "watersheet");
  m_pRenderer->Load(eSprite::WaterMove, "water");

  //For Fox
  m_pRenderer->Load(eSprite::FoxUpSpriteSheet, "foxmoveupspritesheet");
  m_pRenderer->Load(eSprite::FoxMoveDown, "foxmoveup");
  m_pRenderer->Load(eSprite::FoxDownSpriteSheet, "foxmovedownspritesheet");
  m_pRenderer->Load(eSprite::FoxMoveUp, "foxmovedown");
  
  //For Hawk
  m_pRenderer->Load(eSprite::HawkRightSpriteSheet, "hawkrightspritesheet");
  m_pRenderer->Load(eSprite::HawkMoveRight, "hawkmoveright");
  m_pRenderer->Load(eSprite::HawkLeftSpriteSheet, "hawkleftspritesheet");
  m_pRenderer->Load(eSprite::HawkMoveLeft, "hawkmoveleft");

  //For Grass
  m_pRenderer->Load(eSprite::GrassSpriteSheet, "grasssheet");
  m_pRenderer->Load(eSprite::Grass, "grass");

  //For Frog Evolution
  
  m_pRenderer->EndResourceUpload();
} //LoadImages

/// Initialize the audio player and load game sounds.

void CGame::LoadSounds(){
  m_pAudio->Initialize(eSound::Size);
  //Background, Chicken, Insects, Frog, Hawk, Fox,

  m_pAudio->Load(eSound::Background, "background");
  m_pAudio->Load(eSound::Chicken, "chicken");
  m_pAudio->Load(eSound::Hawk, "hawk");
  m_pAudio->Load(eSound::Slurp, "slurp");
  m_pAudio->Load(eSound::Lose, "lose");
  m_pAudio->Load(eSound::Win, "win");
  m_pAudio->Load(eSound::Frog, "frog");
  m_pAudio->Load(eSound::Heal, "heal");
} //LoadSounds

/// Release all of the DirectX12 objects by deleting the renderer.

void CGame::Release(){
  delete m_pRenderer;
  m_pRenderer = nullptr; //for safety
} //Release

/// Ask the object manager to create the game objects. There's only one in this
/// game, the rotating wheel o' text centered at the center of the window.

void CGame::CreateObjects() {
   
    float h = m_pRenderer->GetHeight(eSprite::PlayerStandRight);
    m_pPlayer = (CPlayer*)m_pObjectManager->create(eSprite::PlayerStandRight,
        Vector2(m_nWinWidth / 2, h / 2.0f));
    //Creating 5 chicken
    for (int i = 0; i < number_chickens; i++)
    {
        float random_x = rand() % m_nWinWidth;
        float random_y = rand() % 350;
        if (i % 2 == 0)
            m_pChicken = (CChicken*)m_pObjectManager->create(eSprite::ChickenWalkLeft, { random_x, random_y + h / 2 });
        else
            m_pChicken = (CChicken*)m_pObjectManager->create(eSprite::ChickenWalkRight, { random_x, random_y + h / 2 });
    }
    //Creating 3,4 grass
    for (int i = 0; i < 7; i++)
    {
        float random_x = rand() % m_nWinWidth;
        float random_y = rand() % 350;
        m_pGrass = (CGrass*)m_pObjectManager->create(eSprite::Grass, { random_x,random_y});
    }
    //Creating 4 spiders
    for (int i = 0; i < number_spiders; i++)
    {
        float random_x = rand() % m_nWinWidth;
        float random_y = rand() % 350;
        m_pSpider = (CSpider*)m_pObjectManager->create(eSprite::SpiderMove, { random_x, random_y });
    }
    //Creating 5 snaisl
    for (int i = 0; i < number_snails; i++)
    {
        float random_x = rand() % m_nWinWidth;
        float random_y = rand() % 350;
        m_pSnail = (CSnail*)m_pObjectManager->create(eSprite::SnailMove, { random_x,random_y });
    }


    //Creating 3 foxes
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
   

    //Creating River
    float w;
    w = m_pRenderer->GetWidth(eSprite::WaterMove);
    h = m_pRenderer->GetHeight(eSprite::WaterMove);
    Vector2 v = { static_cast<float>(m_nWinWidth/2) + 7 * w, static_cast<float>(m_nWinHeight/2) - 4 * h };
    for (int i = 0; i < 3; i++)
    {
        v.y += h/2;
    }
    for (int i = 0; i < 4; i++)
    {
        float random_x = rand() % m_nWinWidth;
        while(random_x > 4/5 * m_nWinWidth)
            random_x = rand() % m_nWinWidth;
        m_pRiver = (CRiver*)m_pObjectManager->create(eSprite::WaterMove, { random_x,v.y });
    }
    m_pRiver = (CRiver*)m_pObjectManager->create(eSprite::WaterMove, v);
        
    /*
    
    for (int i = 0; i < 6; i++)
    {
        m_pRiver = (CRiver*)m_pObjectManager->create(eSprite::WaterMove, v);
        v.x += w / 2;
    }

    */
    //Creating hawks
    m_pHawk = (CHawk*)m_pObjectManager->create(eSprite::HawkMoveRight, { 0,700 });

}
  

/// Call this function to start a new game. This should be re-entrant so that
/// you can restart a new game without having to shut down and restart the
/// program. All we need to do is delete any old objects out of the object
/// manager and create some new ones.

void CGame::BeginGame(){  
  m_pObjectManager->clear(); //clear old objects

  CreateObjects(); //create new objects 
} //BeginGame

/// Poll the keyboard state and respond to the key presses that happened since
/// the last frame.

void CGame::KeyboardHandler() {
    m_pKeyboard->GetState(); //get current keyboard state 

    if (m_pKeyboard->TriggerDown(VK_F1)) //help
        ShellExecute(0, 0, "https://larc.unt.edu/code/blank/", 0, 0, SW_SHOW);

    
    /*
    if(m_pKeyboard->TriggerDown(VK_SPACE)) //play sound
      m_pAudio->play(eSound::Clang);

    if(m_pKeyboard->TriggerUp(VK_SPACE)) //play sound
      m_pAudio->play(eSound::Grunt);
    */
    if (m_pKeyboard->TriggerDown('R')) //restart game
    {
        level_frog = 1;
        score = 0;
        frog_health = 20;
        max_frog_health = 20;
        m_frog_dead = false;
        updated = false;
        number_chickens = 8;
        number_foxes = 3;
        number_hawks = 1;
        doneflying = false;
        frog_pos = { 0.0,0.0 };
        if (frog_winning == true)
        {
            LoadImages();
        }
        frog_winning = false;
        BeginGame(); //restart game

    }
   
    else if (m_pKeyboard->Down('D') && m_pKeyboard->Down(VK_SPACE))
        m_pPlayer->JumpRight();
    else if (m_pKeyboard->Down('A') && m_pKeyboard->Down(VK_SPACE))
        m_pPlayer->JumpLeft();
    else if (m_pKeyboard->Down('A'))
        m_pPlayer->WalkLeft();
    else if (m_pKeyboard->Down('D'))
        m_pPlayer->WalkRight();
    else if (m_pKeyboard->Down('S'))
        m_pPlayer->Jump();
    else if (m_pKeyboard->Down('W') && m_pKeyboard->Down(VK_SPACE))
        m_pPlayer->JumpUp();
    else if (m_pKeyboard->Down('W'))
        m_pPlayer->Up();
    else if (m_pKeyboard->Down('X') && m_pKeyboard->Down(VK_SPACE))
        m_pPlayer->JumpDown();
    else if (m_pKeyboard->Down('X'))
        m_pPlayer->Down();
}
  /*
  else if (m_pKeyboard->Down(VK_SPACE))
      m_pPlayer->Jump();
} //KeyboardHandler
*/

/// Draw the current frame rate to a hard-coded position in the window.
/// The frame rate will be drawn in a hard-coded position using the font
/// specified in gamesettings.xml.

void CGame::DrawFrameRateText(){
  const std::string s = "Score: " + std::to_string(score) +"\n" + "Health: "+std::to_string(frog_health) +
      "\nFrog Level: "+std::to_string(level_frog);
  const Vector2 pos(m_nWinWidth - 256.0f, 30.0f); //hard-coded position
  m_pRenderer->DrawScreenText(s.c_str(), pos, Colors::PeachPuff); //draw to screen
} //DrawFrameRateText

/// Ask the object manager to draw the game objects. The renderer is notified
/// of the start and end of the frame so that it can let Direct3D do its
/// pipelining jiggery-pokery.

void CGame::RenderFrame(){
  m_pRenderer->BeginFrame(); //required before rendering

  m_pRenderer->Draw(eSprite::Background, m_vWinCenter); //draw background
  
  m_pObjectManager->draw(); //draw objects

  if(m_bDrawFrameRate)DrawFrameRateText(); //draw frame rate, if required
  if (m_frog_dead) DrawCenteredText("You lost. Try again");
  if (frog_winning) DrawCenteredText("You are the winner");
  m_pRenderer->EndFrame(); //required after rendering
} //RenderFrame

/// This function will be called regularly to process and render a frame
/// of animation, which involves the following. Handle keyboard input.
/// Notify the  audio player at the start of each frame so that it can prevent
/// multiple copies of a sound from starting on the same frame.  
/// Move the game objects. Render a frame of animation.

void CGame::DrawCenteredText(std::string s)
{
    m_pRenderer->DrawCenteredText(s.c_str(),Colors::Red);
}
void CGame::ProcessFrame(){
  KeyboardHandler(); //handle keyboard input
  m_pAudio->BeginFrame(); //notify audio player that frame has begun
  m_pAudio->play(eSound::Background);
 
  m_pTimer->Tick([&](){ //all time-dependent function calls should go here
      m_pObjectManager->move(); //move all objects
      m_frame_time += m_pTimer->GetFrameTime();
  });
  RenderFrame(); //render a frame of animation
} //ProcessFrame

/*

*/

