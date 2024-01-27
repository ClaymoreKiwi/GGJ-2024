#include "Gameloop.h"
#include "StateMachine.h"
#include "Player.h"

Gameloop::Gameloop(SDL_Renderer* r, const int windowWidth, const int windowHeight)
    :g_renderer(r), windowWidth(windowWidth), windowHeight(windowHeight)
{}

int Gameloop::init()
{
    //crt effect
    SDL_Surface* image = IMG_Load("content/background/CRT.png");
    g_textureCRT = SDL_CreateTextureFromSurface(g_renderer, image);
    SDL_FreeSurface(image);

    CameraC = new Camera(camera);
    Time = new deltaTime();
    //create a new player
    MakeCanisters();
    player = new Player(this->g_renderer, windowWidth, windowHeight, CameraC, Time, &this->gasCanisters);
    //create tiled map - (this will be moved in the future to cater for map changing)
    g_tiledMap = std::shared_ptr<TileMap>(new TileMap(g_renderer, LoadMap(MapOne), player, windowWidth, windowHeight));

    return 0;
}
void Gameloop::MakeCanisters()
{
    this->gasCanisters.push_back(new GasCanister(this->g_renderer, windowWidth, windowHeight, &camera, Time, 200, 40));
    this->gasCanisters.push_back(new GasCanister(this->g_renderer, windowWidth, windowHeight, &camera, Time, 500, 200));
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
    SDL_RenderCopy(this->g_renderer, this->g_textureCRT, NULL, NULL);
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
}

bool Gameloop::gameRunning()
{
    return processInput();
}

int Gameloop::gameStateUpdate()
{
    return g_state;
}
