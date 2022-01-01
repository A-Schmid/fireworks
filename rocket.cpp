#include "firework.h"
#include "rocket.h"
#include <math.h>
#include <stdlib.h>

Rocket::Rocket(float x, int size, float v, float a)
{
    this->x = x;
    this->y = HEIGHT;
    this->size = size;
    this->w = size;
    this->h = size;
    this->v = v;
    this->a = (a * M_PI / 180);

    this->color = {255, 255, 255};

    this->vx = sin(a) * v;
    this->vy = cos(a) * v;
}

Rocket::Rocket()
{
    x = ROCKET_X_MIN + rand() % (ROCKET_X_MAX - ROCKET_X_MIN);
    y = HEIGHT;
    size = ROCKET_SIZE_MIN + rand() % (ROCKET_SIZE_MAX - ROCKET_SIZE_MIN);
    v = ROCKET_VELOCITY_MIN + rand() % (ROCKET_VELOCITY_MAX - ROCKET_VELOCITY_MIN);
    a = ROCKET_ANGLE_MIN + rand() % (ROCKET_ANGLE_MAX - ROCKET_ANGLE_MIN);
    a = (a * M_PI / 180);

    w = size;
    h = size;

    color = {255, 255, 255};

    vx = sin(a) * v;
    vy = cos(a) * v;

    lifetime = ROCKET_LIFETIME_MIN + (float)(rand()) / (RAND_MAX / (ROCKET_LIFETIME_MAX - ROCKET_LIFETIME_MIN));
    age = 0;
}

void Rocket::die()
{
    for (vector<Particle>::iterator it = trail.begin(); it != trail.end(); )
    {
        it = trail.erase(it);
    }
}

bool Rocket::update(float timedelta)
{
    x += vx * timedelta;
    y += vy * timedelta;

    vy += GRAVITY * timedelta;

    age += timedelta;

    for(vector<Particle>::iterator it = trail.begin(); it != trail.end(); )
    {
        if(!it->update(timedelta))
            it = trail.erase(it);
        else 
            ++it;
    }

    Particle trailParticle = Particle(x, y, 0xFF0088FF);
    trailParticle.setAngle(a - M_PI + ((5 - rand() % 10) / 180 * M_PI));
    trailParticle.setLifetime((rand() % 5) / 10.0f);
    trailParticle.setVelocity(50 + rand() % 100);
    trail.push_back(trailParticle);

    // still alive?
    if(y > HEIGHT || age > lifetime)
    {
        die();
        return false;
    }
    else
    {
        return true;
    }
}

void Rocket::render(SDL_Renderer *renderer)
{
    for(const auto particle : trail)
    {
        particle.render(renderer);
    }

    //filledCircleColor(renderer, x, y, size, 0xFFFFFFFF);
}

vector<Particle> Rocket::createParticles()
{
    vector<Particle> particles;
    Uint32 particleColor;
    int counter = 0;
    while(counter == 0)
    {
        particleColor = COLORS[rand() % (sizeof(COLORS) / sizeof(COLORS[0]))];
        int particleCount = ROCKET_PARTICLES_MIN + rand() % (ROCKET_PARTICLES_MAX - ROCKET_PARTICLES_MIN);
        for(int i = 0; i < particleCount; i++)
        {
            particles.push_back(Particle(x, y, particleColor));
        }
        counter += rand() % 3;
    }
    return particles;
}
