#include "Gameloop.h"
#include "StateMachine.h"
#include"Player.h"

Gameloop::Gameloop(SDL_Renderer* r, const int windowWidth, const int windowHeight)
    :g_renderer(r), windowWidth(windowWidth), windowHeight(windowHeight)
{}

int Gameloop::init()
{
    Time = new deltaTime();
    //create a new player
    player = new Player(this->g_renderer, windowWidth, windowHeight, &camera, Time);
    //create tiled map - (this will be moved in the future to cater for map changing)
    g_tiledMap = std::shared_ptr<TileMap>(new TileMap(g_renderer, LoadMap(MapOne), player, windowWidth, windowHeight));

    return 0;
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

        //pass that key press to the players processing
        player->processInput(e);
        //default return to continue playing
        return true;
    }
}

void Gameloop::CameraUpdate()
{
    camera.x = player->p_positionDest.x - (windowWidth / 2);
    camera.y = player->p_positionDest.y - (windowHeight / 2);

    //stop camera from going too far left
    if (camera.x < 0)
        camera.x = 0;
    //stop camera from going too far up
    if (camera.y < 0)
        camera.y = 0;
    //stop camera from going too far right
    if (camera.x > ((windowWidth / 10) * mapWidth) - windowWidth)
        camera.x = ((windowWidth / 10) * mapWidth) - windowWidth;
    //stop camera from going too far down
    if (camera.y > ((windowHeight / 10) * mapHeight) - windowHeight)
        camera.y = ((windowHeight / 10) * mapHeight) - windowHeight;
}

void Gameloop::update()
{
    Time->Update();
    draw();
    CameraUpdate();
    //(other class updates go here)
}

void Gameloop::draw()
{
    //clear the render before drawing the next frame
    SDL_RenderClear(g_renderer);

    //Draw routines go here
    SDL_Delay(80);
    g_tiledMap->draw(camera);
    player->draw();
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
