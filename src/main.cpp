#include <bn_core.h>
#include <bn_backdrop.h>
#include <bn_color.h>
#include <bn_keypad.h>
#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_vector.h>
#include <bn_sprite_text_generator.h>
#include <bn_log.h>

#include "bn_sprite_items_dot.h"
#include "common_fixed_8x16_font.h"

#include "movement.h"
#include "Center.h"
#include "Orbiter.h"

// A scaling factor by which to reduce the force applied when orbiting
// Important for numerical stability
static constexpr bn::fixed FORCE_SCALE = 10;

// Maximum number of orbiters allowed on the screen
static constexpr int MAX_ORBITERS = 90;

// Default starting posiiton and velocity for Orbiter
static constexpr bn::fixed_point ORBITER_START_POSIITON = {0, 0};
static constexpr bn::fixed_point ORBITER_START_VELOCITY = {0, 5};

// velocity text
// bn::vector<bn::sprite_ptr, 64> text_sprites = {};
// bn::vector<bn::sprite_ptr, 32> velocity_sprites = {};
// bn::sprite_text_generator text_generator(common::fixed_8x16_sprite_font);


int main()
{
    bn::core::init();

    // text_generator.generate(-120, -70, "LB to increase velocity", text_sprites);
    // text_generator.generate(-120, -60, "RB to decrease velocity", text_sprites);

    Center center = Center({30, 40}, .05, 2);
    bn::vector<Orbiter, MAX_ORBITERS> orbiters = {};

    int velocity = 5;

    while (true)
    {
        // Add an orbiter when A is pressed if there's room
        if (bn::keypad::a_pressed())
        {
            if (orbiters.size() < MAX_ORBITERS)
            {
                orbiters.push_back(Orbiter(ORBITER_START_POSIITON, ORBITER_START_VELOCITY, center));
            }
        }

        // Remove an orbiter when B is pressed if there's at least one
        if (bn::keypad::b_pressed())
        {
            if (orbiters.size() > 0)
            {
                orbiters.pop_back();
            }
        }

        center.update();
        for (Orbiter &orbiter : orbiters)
        {
            orbiter.update();
            //orbiter.set_velocity(velocity);
        }

        // velocity_sprites.clear();
        // bn::string<32> velocity_string = "Velocity: ";
        // velocity_string.append(bn::to_string<32>(velocity));
        // text_generator.generate(-120, -50, velocity_string, velocity_sprites);
        // BN_LOG("velocity_string");

        bn::core::update();
    }
}