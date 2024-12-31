#include "rocket.h"
#include "firework.h"
#include "particle.h"
#include "constants.h"
#include <stdio.h>
#include <iostream>

using namespace std;

vector<Rocket*> rockets;// = new vector<Rocket>();
vector<Particle> particles;
//Rocket *rocket = new Rocket(500, 20, 10, 80);
SDL_Renderer* renderer;

void launchRocket()
{
    Rocket *rocket = new Rocket();
    rockets.push_back(rocket);
}

void init()
{
    srand(time(NULL));
    
    SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

    SDL_Window* window = SDL_CreateWindow(__FILE__, 0, 0, WIDTH, HEIGHT, SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void update(float timedelta)
{
    for (vector<Rocket*>::iterator it = rockets.begin(); it != rockets.end(); )
    {
        Rocket *rocket = *it;
        bool alive = rocket->update(timedelta);
        if(!alive)
        {
            vector<Particle> newParticles = rocket->createParticles();
            particles.insert(particles.end(), newParticles.begin(), newParticles.end());
            //particles.push_back(rocket->createParticles());
            it = rockets.erase(it);
        }
        else 
            ++it;
     }

    for (vector<Particle>::iterator it = particles.begin(); it != particles.end(); )
    {
        bool alive = it->update(timedelta);
        if(!alive)
            it = particles.erase(it);
        else 
            ++it;
    }
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for(const auto rocket : rockets)
    {
        rocket->render(renderer);
    }

    for(const auto particle : particles)
    {
        particle.render(renderer);
    }

    SDL_RenderPresent(renderer);
}

int main()
{
    init();

    SDL_Event event;

    float lastTime = SDL_GetTicks();
    float time = SDL_GetTicks();

    float spawnTimer = 0;
    //float nextSpawnTime = SPAWN_TIME_MIN + rand() % (SPAWN_TIME_MAX - SPAWN_TIME_MIN);
    float nextSpawnTime = SPAWN_TIME_MIN + (float)(rand()) / (RAND_MAX / (SPAWN_TIME_MAX - SPAWN_TIME_MIN));


    while(1)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        launchRocket();
                    }
                break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_q)
                    {
                        SDL_Quit();
                        return 0;
                    }
                break;
            }
        }
        time = SDL_GetTicks();
        update((time - lastTime) / 1000);

        spawnTimer += (time - lastTime) / 1000;
        if(spawnTimer > nextSpawnTime)
        {
            launchRocket();
            nextSpawnTime = SPAWN_TIME_MIN + (float)(rand()) / (RAND_MAX / (SPAWN_TIME_MAX - SPAWN_TIME_MIN));
            spawnTimer = 0;
        }


        lastTime = time;

        render();
    }

    return 0;
}
