/* This project is licensed under MIT. See `LICENSE` for details. 
*/

#include "movement_sensor_2d.h"

void godot::MovementSensor2D::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_velocity"), &MovementSensor2D::get_velocity);
    ClassDB::bind_method(D_METHOD("get_acceleration"), &MovementSensor2D::get_acceleration);
    ClassDB::bind_method(D_METHOD("_notification", "p_what"), &MovementSensor2D::_notification);
    ClassDB::bind_method(D_METHOD("set_seconds_to_sleep", "time"), &MovementSensor2D::set_seconds_to_sleep);
    ClassDB::bind_method(D_METHOD("get_seconds_to_sleep"), &MovementSensor2D::get_seconds_to_sleep);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "seconds_to_sleep"), "set_seconds_to_sleep", "get_seconds_to_sleep");

    // Emit when movement becomes 0 velocity for some period of time. Controlled by internal timer.
    ADD_SIGNAL(MethodInfo("sleep"));
    // Emit when movement becomes non-zero velocity. Happens immediately regardless.
    ADD_SIGNAL(MethodInfo("awake"));
}

godot::Vector2 godot::MovementSensor2D::get_velocity() {
    return m_velocity;
}

godot::Vector2 godot::MovementSensor2D::get_acceleration()
{
    return m_acceleration;
}

void godot::MovementSensor2D::set_seconds_to_sleep(float p_sleep_time)
{
    m_seconds_to_sleep = p_sleep_time;
}

float godot::MovementSensor2D::get_seconds_to_sleep()
{
    return m_seconds_to_sleep;
}

void godot::MovementSensor2D::_notification(int p_what)
{
    if (p_what == NOTIFICATION_PHYSICS_PROCESS) {
        Vector2 delta = get_global_position() - m_cached_translation;
        Vector2 velocity = delta / get_physics_process_delta_time();
        bool was_idle = (m_velocity.is_zero_approx());
        m_acceleration = velocity - m_velocity;
        m_velocity = velocity;
        bool is_idle = (m_velocity.is_zero_approx());
        m_cached_translation = get_global_position();

        // We should notify we're awake.
        if (was_idle && !is_idle) {
            emit_signal("awake");
        }

        if (is_idle) {
            if (!was_idle) {
                m_internal_idle_timer = 0.0;
            }

            bool was_asleep = m_internal_idle_timer > m_seconds_to_sleep; 

            m_internal_idle_timer += get_physics_process_delta_time();

            if (!was_asleep && m_internal_idle_timer > m_seconds_to_sleep) {
                emit_signal("sleep");
            }
        }
    }
}

godot::MovementSensor2D::MovementSensor2D()
{
}

godot::MovementSensor2D::~MovementSensor2D()
{
}
