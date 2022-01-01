#ifndef ROCKET_H
#define ROCKET_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "constants.h"
#include "particle.h"
#include <vector>

using namespace std;

const int ROCKET_ANGLE_MIN = 160;
const int ROCKET_ANGLE_MAX = 200;
const int ROCKET_X_MIN = WIDTH * 0.1;
const int ROCKET_X_MAX = WIDTH * 0.9;
const int ROCKET_SIZE_MIN = 2;
const int ROCKET_SIZE_MAX = 8;
const int ROCKET_VELOCITY_MIN = 500;
const int ROCKET_VELOCITY_MAX = 1000;
const float ROCKET_LIFETIME_MIN = 2.0;
const float ROCKET_LIFETIME_MAX = 3.0;
const int ROCKET_PARTICLES_MIN = 100;
const int ROCKET_PARTICLES_MAX = 200;

class Rocket
{
    private:
        float x, y;
        int size;
        int w, h;
        float v;
        float vx, vy;
        float a;
        bool alive;
        SDL_Color color;
        float lifetime, age;
        vector<Particle> trail;

    public:
        Rocket(float x, int size, float v, float a);
        Rocket();
        bool update(float timedelta);
        void render(SDL_Renderer *renderer);
        vector<Particle> createParticles();
        void die();
};

#endif
