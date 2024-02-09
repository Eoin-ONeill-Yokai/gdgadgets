/* This project is licensed under MIT. See `LICENSE` for details. 
*/

#include "movement_sensor_2d.h"

void godot::MovementSensor2D::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_velocity"), &MovementSensor2D::get_velocity);
    ClassDB::bind_method(D_METHOD("get_acceleration"), &MovementSensor2D::get_acceleration);
    ClassDB::bind_method(D_METHOD("_notification", "p_what"), &MovementSensor2D::_notification);
}

godot::Vector2 godot::MovementSensor2D::get_velocity() {
    return m_velocity;
}

godot::Vector2 godot::MovementSensor2D::get_acceleration()
{
    return m_acceleration;
}

void godot::MovementSensor2D::_notification(int p_what)
{
    if (p_what == NOTIFICATION_PHYSICS_PROCESS) {
        Vector2 delta = get_global_position() - m_cached_translation;
        Vector2 velocity = delta / get_physics_process_delta_time();
        m_acceleration = velocity - m_velocity;
        m_velocity = velocity;
        m_cached_translation = get_global_position();
    }
}

void godot::MovementSensor2D::_physics_process()
{
    
}

godot::MovementSensor2D::MovementSensor2D()
{
}

godot::MovementSensor2D::~MovementSensor2D()
{
}
