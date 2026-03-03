#ifndef ORBITER_H
#define ORBITER_H

//#include <bn_fixed_point.h>
//#include <bn_sprite_ptr.h>
#include <bn_string.h>

#include "Center.h"


/**
 * An object that orbits around a center. Orbits using Hooke's law, as if attached by a 2D spring.
 * The stiffness of the spring in each dimension is center.mass() / FORCE_SCALE. 
 */
class Orbiter {
    public:
        /**
         * Creates an orbiter.
         * 
         * @param starting_location the initial location of the Orbiter
         * @param starting_velocity the initial velocity of the Orbiter, {dx, dy}
         * @param center the center to orbit around
         */
        Orbiter(bn::fixed_point starting_location, bn::fixed_point starting_velocity, Center &center);

        /**
         * Take a step orbiting around the center.
         */
        void update();

        void set_velocity(int velocity);

    private:
        bn::sprite_ptr _sprite;
        bn::fixed_point _velocity;
        Center &_center;
};


#endif