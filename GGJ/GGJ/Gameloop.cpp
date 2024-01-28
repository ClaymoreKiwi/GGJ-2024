#include "Gameloop.h"
#include "StateMachine.h"
#include "Player.h"
#include "enemy.h"
#include "GasCanister.h"

Gameloop::Gameloop(SDL_Renderer* r, const int windowWidth, const int windowHeight)
    :g_renderer(r), windowWidth(windowWidth), windowHeight(windowHeight)
{}

int Gameloop::init()
{
    //crt effect
    SDL_Surface* image = IMG_Load("content/background/CRT.png");
    g_textureCRT = SDL_CreateTextureFromSurface(g_renderer, image);
    SDL_FreeSurface(image);

    Time = new deltaTime();
    CameraC = new Camera(camera);
    //create a new player
    MakeCanisters();
    player = new Player(this->g_renderer, windowWidth, windowHeight, CameraC, Time, &this->gasCanisters);
    GiveCanistersPlayerRef(player);
    //create tiled map - (this will be moved in the future to cater for map changing)
    g_tiledMap = std::shared_ptr<TileMap>(new TileMap(g_renderer, LoadMap(MapOne), player, windowWidth, windowHeight));

    for (int i = 1; i <= 2; ++i)
    {
        //add enemies to the list that is pre allocated
        enemyList.push_back(new Enemy(this->g_renderer, windowWidth, windowHeight, CameraC, player, i, Time, g_tiledMap));
    }

    this->laughter = new LaughterAtExit(this->g_renderer, windowWidth, windowHeight, CameraC, Time, 300, 300, -1);
    this->laughter->setPlayerRef(player);

    return 0;
}
void Gameloop::MakeCanisters()
{
    int xLocations[] = {800, 100,600};
    int yLocations[] = {550, 300, 300};
    for (int i = 0; i < 3; ++i) {
    this->gasCanisters.push_back(new GasCanister(this->g_renderer, windowWidth, windowHeight, CameraC, Time, xLocations[i], yLocations[i], i));
    }
}
void Gameloop::GiveCanistersPlayerRef(Player* player)
{
    for(GasCanister* canister : this->gasCanisters)
    {
        canister->setPlayerRef(player);
    }
}
//function to map select at a later date
std::string Gameloop::LoadMap(const int mapNum)
{
    switch (mapNum)
    {
    case MapOne:
        return "./content/maps/map1.txt";
    case MapTwo:
        return "./content/maps/map2.txt";
    }
    return"";
}

bool Gameloop::processInput()
{
    //check for an event 
    SDL_Event e;
    SDL_GetMouseState(&mousePos.x, &mousePos.y);
    while (SDL_PollEvent(&e))
    {
        //check for the key presses specific to movement
        const Uint8* state = SDL_GetKeyboardState(NULL);

        //use this as the flag to check the movement of the player
        player->movingUp = state[SDL_SCANCODE_W] > 0;
        player->movingDown = state[SDL_SCANCODE_S] > 0;
        player->movingLeft = state[SDL_SCANCODE_A] > 0;
        player->movingRight = state[SDL_SCANCODE_D] > 0;
        //checking if the player has quit the game
        if (e.type == SDL_QUIT || e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
        {
            g_state = 5;
            return false;
        }
    }
        player->processInput(e);
        return true;
}

void Gameloop::update()
{
    Time->Update();
    draw();
    player->Update();
    for (GasCanister* canister : this->gasCanisters) {
        canister->Update();
    }
    for (auto& enemy : enemyList)
    {
        enemy->update();
    }
    this->laughter->Update();
    //(other class updates go here)
}

void Gameloop::draw()
{
    //clear the render before drawing the next frame
    SDL_RenderClear(g_renderer);
    //Draw routines go here
    SDL_Delay(80);
    g_tiledMap->draw(CameraC);
    for (GasCanister* canister : this->gasCanisters) {
        canister->Render();
    }
    player->draw();
    for (auto& enemy : enemyList)
    {
        enemy->draw();
    }
    SDL_RenderCopy(this->g_renderer, this->g_textureCRT, NULL, NULL);
    this->laughter->Render();
    //render the new frames that happened since the last call
    SDL_RenderPresent(g_renderer);
}

void Gameloop::clean()
{
    //clear player status
    player->clean();
    if (player)
    {
        //clear player from memory and set to NULL
        delete player;
        player = nullptr;
    }
    if (Time)
    {
        delete Time;
        Time = nullptr;
    }
    for (auto& enemy : enemyList)
    {
        enemy->clean();
        delete enemy;
        enemy = nullptr;
    }
    enemyList.clear();
}

bool Gameloop::gameRunning()
{
    return processInput();
}

int Gameloop::gameStateUpdate()
{
    return g_state;
}
