/* This project is licensed under MIT. See `LICENSE` for details. 
*/
#ifndef SIMPLEGDEX_SIMPLE_NODE_H
#define SIMPLEGDEX_SIMPLE_NODE_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace godot {

class MovementSensor2D : public Node2D {
    GDCLASS(MovementSensor2D, Node2D)

private:
    Vector2 m_cached_translation;
    Vector2 m_velocity;
    Vector2 m_acceleration;

    float m_seconds_to_sleep = 3.0; // Three is a nice value
    float m_internal_idle_timer = 0.0;

protected:
    static void _bind_methods();
    Vector2 get_velocity();
    Vector2 get_acceleration();
    void set_seconds_to_sleep(float p_sleep_time);
    float get_seconds_to_sleep();

public:
    void _notification(int32_t p_what);
    MovementSensor2D();
    ~MovementSensor2D();
};

}


#endif //SIMPLEGDEX_SIMPLE_NODE_H