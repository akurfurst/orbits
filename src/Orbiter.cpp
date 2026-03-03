#include <bn_fixed_point.h>
#include <bn_sprite_ptr.h>
#include <bn_vector.h>
#include <bn_sprite_text_generator.h>
#include <bn_string.h>
#include <bn_log.h>

#include "bn_sprite_items_dot.h"
#include "common_fixed_8x16_font.h"

#include "Orbiter.h"
#include "Center.h"

static constexpr bn::fixed FORCE_SCALE = 10;

Orbiter::Orbiter(bn::fixed_point starting_location, bn::fixed_point starting_velocity, Center &center) : _sprite(bn::sprite_items::dot.create_sprite(starting_location)),
                                                                                                         _velocity(starting_velocity),
                                                                                                         _center(center) {}

void Orbiter::update()
{
    // A vector from the Orbiter to the Center
    bn::fixed_point delta = _center.position() - _sprite.position();

    // Scale the vector by the mass and apply a FORCE_SCALE
    // This is done in two steps instead of having a pre-scaled mass to prevent loss of
    // fixed point precision
    bn::fixed_point force = delta * _center.mass();
    force /= FORCE_SCALE;

    // Update the current velocity with the force
    _velocity += force;

    // Update the position by taking a step by the velocity vector
    _sprite.set_position(_sprite.position() + _velocity);

    
}

void Orbiter::set_velocity(int velocity){
    _velocity.set_y(velocity);
}
