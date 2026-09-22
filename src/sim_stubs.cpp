#include <chrono>
#include <thread>
#include <vector>
#include <cstdint>
#include <initializer_list>

// Include PROS headers to inherit exact enums, types, and class declarations
#include "pros/rtos.hpp"
#include "pros/motor_group.hpp"
#include "pros/ai_vision.hpp"
#include "pros/serial.hpp"
#include "pros/misc.hpp"
#include "pros/device.hpp"

#include "sim/sim_callbacks.h"

namespace pros
{
    namespace sim
    {
        static std::function<std::vector<pros::aivision_object_s_t>()> ai_vision_callback;

        void register_ai_vision_detection_callback(std::function<std::vector<pros::aivision_object_s_t>()> callback)
        {
            ai_vision_callback = callback;
        }
    } // namespace sim
} // namespace pros

// ---------------------------------------------------------------------------
// C System Timers & Driver Functions (extern "C")
// ---------------------------------------------------------------------------
extern "C"
{

    namespace pros
    {
        namespace c
        {
            uint32_t millis(void)
            {
                static const auto start = std::chrono::steady_clock::now();
                auto now = std::chrono::steady_clock::now();
                return static_cast<uint32_t>(std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count());
            }

            uint64_t micros(void)
            {
                static const auto start = std::chrono::steady_clock::now();
                auto now = std::chrono::steady_clock::now();
                return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(now - start).count());
            }

            void delay(const uint32_t ms)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            }

            int32_t aivision_enable_detection_types(uint8_t port, uint8_t types)
            {
                return 1;
            }

            int32_t aivision_set_usb_bounding_box_overlay(uint8_t port, bool enable)
            {
                return 1;
            }
        }
    }

} // extern "C"

// ---------------------------------------------------------------------------
// PROS RTOS Stubs
// ---------------------------------------------------------------------------
namespace pros
{
    namespace rtos
    {
        Mutex::~Mutex() {}

        mutex_t Mutex::lazy_init() { return {}; }
        void Mutex::lock() {}
        void Mutex::unlock() {}
        bool Mutex::take(std::uint32_t timeout) { return true; }
        bool Mutex::give() { return true; }

        Task::Task(void (*fn)(void *), void *arg, unsigned int prio, unsigned short stack_size, char const *name)
        {
            if (fn)
            {
                std::thread(fn, arg).detach();
            }
        }

        void Task::delay_until(unsigned int *prev_time, unsigned int delta)
        {
            uint32_t now = millis();
            if (prev_time)
            {
                uint32_t target = *prev_time + delta;
                if (target > now)
                {
                    delay(target - now);
                }
                *prev_time = millis();
            }
            else
            {
                delay(delta);
            }
        }

        void Task::delay(const std::uint32_t millis)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(millis));
        }

    } // namespace rtos

    // ---------------------------------------------------------------------------
    // PROS Serial Stubs
    // ---------------------------------------------------------------------------

    Serial::Serial(std::uint8_t port, std::int32_t baudrate)
        : Device(port)
    {
    }

    Serial::Serial(std::uint8_t port)
        : Device(port)
    {
    }

    std::int32_t Serial::set_baudrate(std::int32_t baudrate) const
    {
        return 1;
    }

    std::int32_t Serial::flush() const
    {
        return 1;
    }

    std::int32_t Serial::get_read_avail() const
    {
        return 0;
    }

    std::int32_t Serial::get_write_free() const
    {
        return 0;
    }

    std::int32_t Serial::peek_byte() const
    {
        return -1;
    }

    std::int32_t Serial::read_byte() const
    {
        return -1;
    }

    std::int32_t Serial::read(std::uint8_t *buffer, std::int32_t length) const
    {
        return 0;
    }

    std::int32_t Serial::write_byte(std::uint8_t byte) const
    {
        return 1;
    }

    std::int32_t Serial::write(std::uint8_t *buffer, std::int32_t length) const
    {
        return length;
    }

    // ---------------------------------------------------------------------------
    // PROS V5 Device & Subsystem Stubs
    // ---------------------------------------------------------------------------
    namespace v5
    {
        Device::Device(std::uint8_t port) : _port(port) {}

        // Device
        std::uint8_t Device::get_port() const
        {
            return _port;
        }

        bool Device::is_installed()
        {
            return true;
        }

        // MotorGroup
        MotorGroup::MotorGroup(std::initializer_list<signed char> ports, pros::v5::MotorGears gearset, pros::v5::MotorEncoderUnits encoder_units) {}

        MotorGroup::MotorGroup(const std::vector<signed char> &ports, pros::v5::MotorGears gearset, pros::v5::MotorEncoderUnits encoder_units) {}

        int32_t MotorGroup::move_voltage(int voltage) const
        {
            return 1;
        }

        std::int32_t MotorGroup::move(std::int32_t voltage) const
        {
            return 1;
        }

        std::int32_t MotorGroup::move_absolute(const double position, const std::int32_t velocity) const
        {
            return 1;
        }

        std::int32_t MotorGroup::move_relative(const double position, const std::int32_t velocity) const
        {
            return 1;
        }

        std::int32_t MotorGroup::move_velocity(const int32_t velocity) const
        {
            return 1;
        }

        std::int32_t MotorGroup::brake() const
        {
            return 1;
        }

        std::int32_t MotorGroup::modify_profiled_velocity(const std::int32_t velocity) const
        {
            return 1;
        }

        double MotorGroup::get_target_position(const std::uint8_t index) const
        {
            return 0.0;
        }

        std::vector<double> MotorGroup::get_target_position_all(void) const
        {
            return {};
        }

        std::int32_t MotorGroup::get_target_velocity(const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<std::int32_t> MotorGroup::get_target_velocity_all(void) const
        {
            return {};
        }

        double MotorGroup::get_actual_velocity(const std::uint8_t index) const
        {
            return 0.0;
        }

        std::vector<double> MotorGroup::get_actual_velocity_all(void) const
        {
            return {};
        }

        std::int32_t MotorGroup::get_current_draw(const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<std::int32_t> MotorGroup::get_current_draw_all(void) const
        {
            return {};
        }

        std::int32_t MotorGroup::get_direction(const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<std::int32_t> MotorGroup::get_direction_all(void) const
        {
            return {};
        }

        double MotorGroup::get_efficiency(const std::uint8_t index) const
        {
            return 0.0;
        }

        std::vector<double> MotorGroup::get_efficiency_all(void) const
        {
            return {};
        }

        std::uint32_t MotorGroup::get_faults(const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<std::uint32_t> MotorGroup::get_faults_all(void) const
        {
            return {};
        }

        std::uint32_t MotorGroup::get_flags(const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<std::uint32_t> MotorGroup::get_flags_all(void) const
        {
            return {};
        }

        double MotorGroup::get_position(const std::uint8_t index) const
        {
            return 0.0;
        }

        std::vector<double> MotorGroup::get_position_all(void) const
        {
            return {};
        }

        double MotorGroup::get_power(const std::uint8_t index) const
        {
            return 0.0;
        }

        std::vector<double> MotorGroup::get_power_all(void) const
        {
            return {};
        }

        std::int32_t MotorGroup::get_raw_position(std::uint32_t *const timestamp, const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<std::int32_t> MotorGroup::get_raw_position_all(std::uint32_t *const timestamp) const
        {
            return {};
        }

        double MotorGroup::get_temperature(const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<double> MotorGroup::get_temperature_all(void) const
        {
            return {};
        }

        double MotorGroup::get_torque(const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<double> MotorGroup::get_torque_all(void) const
        {
            return {};
        }

        std::int32_t MotorGroup::get_voltage(const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<std::int32_t> MotorGroup::get_voltage_all(void) const
        {
            return {};
        }

        std::int32_t MotorGroup::is_over_current(const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<std::int32_t> MotorGroup::is_over_current_all(void) const
        {
            return {};
        }

        std::int32_t MotorGroup::is_over_temp(const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<std::int32_t> MotorGroup::is_over_temp_all(void) const
        {
            return {};
        }

        MotorBrake MotorGroup::get_brake_mode(const std::uint8_t index) const
        {
            return pros::v5::MotorBrake::coast;
        }

        std::vector<MotorBrake> MotorGroup::get_brake_mode_all(void) const
        {
            return {};
        }

        std::int32_t MotorGroup::get_current_limit(const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<std::int32_t> MotorGroup::get_current_limit_all(void) const
        {
            return {};
        }

        MotorUnits MotorGroup::get_encoder_units(const std::uint8_t index) const
        {
            return pros::v5::MotorUnits::counts;
        }

        std::vector<MotorUnits> MotorGroup::get_encoder_units_all(void) const
        {
            return {};
        }

        MotorGears MotorGroup::get_gearing(const std::uint8_t index) const
        {
            return pros::v5::MotorGears::green;
        }

        std::vector<MotorGears> MotorGroup::get_gearing_all(void) const
        {
            return {};
        }

        std::vector<std::int8_t> MotorGroup::get_port_all(void) const
        {
            return {};
        }

        std::int32_t MotorGroup::get_voltage_limit(const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<std::int32_t> MotorGroup::get_voltage_limit_all(void) const
        {
            return {};
        }

        std::int32_t MotorGroup::is_reversed(const std::uint8_t index) const
        {
            return 0;
        }

        std::vector<std::int32_t> MotorGroup::is_reversed_all(void) const
        {
            return {};
        }

        MotorType MotorGroup::get_type(const std::uint8_t index) const
        {
            return pros::v5::MotorType::v5;
        }

        std::vector<MotorType> MotorGroup::get_type_all(void) const
        {
            return {};
        }

        std::int32_t MotorGroup::set_brake_mode(const MotorBrake mode, const std::uint8_t index) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_brake_mode(const pros::motor_brake_mode_e_t mode, const std::uint8_t index) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_brake_mode_all(const MotorBrake mode) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_brake_mode_all(const pros::motor_brake_mode_e_t mode) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_current_limit(const std::int32_t limit, const std::uint8_t index) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_current_limit_all(const std::int32_t limit) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_encoder_units(const MotorUnits units, const std::uint8_t index) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_encoder_units(const pros::motor_encoder_units_e_t units, const std::uint8_t index) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_encoder_units_all(const MotorUnits units) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_encoder_units_all(const pros::motor_encoder_units_e_t units) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_gearing(const MotorGears gearset, const std::uint8_t index) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_gearing(const pros::motor_gearset_e_t gearset, const std::uint8_t index) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_gearing_all(const MotorGears gearset) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_gearing_all(const pros::motor_gearset_e_t gearset) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_reversed(const bool reverse, const std::uint8_t index)
        {
            return 1;
        }

        std::int32_t MotorGroup::set_reversed_all(const bool reverse)
        {
            return 1;
        }

        std::int32_t MotorGroup::set_voltage_limit(const std::int32_t limit, const std::uint8_t index) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_voltage_limit_all(const std::int32_t limit) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_zero_position(const double position, const std::uint8_t index) const
        {
            return 1;
        }

        std::int32_t MotorGroup::set_zero_position_all(const double position) const
        {
            return 1;
        }

        std::int32_t MotorGroup::tare_position(const std::uint8_t index) const
        {
            return 1;
        }

        std::int32_t MotorGroup::tare_position_all(void) const
        {
            return 1;
        }

        std::int8_t MotorGroup::get_port(const std::uint8_t index) const
        {
            return 1;
        }

        std::int8_t MotorGroup::size(void) const
        {
            return 1;
        }

        // Controller
        Controller::Controller(pros::controller_id_e_t id) {}

        int32_t Controller::get_digital(pros::controller_digital_e_t button)
        {
            return 0;
        }

        int32_t Controller::get_analog(pros::controller_analog_e_t channel)
        {
            return 0;
        }

        int32_t Controller::rumble(char const *str)
        {
            return 1;
        }

        // AIVision
        AIVision::AIVision(uint8_t port) : Device(port)
        {
        }

        int32_t AIVision::reset()
        {
            return 1;
        }

        int32_t AIVision::start_awb()
        {
            return 1;
        }

        int32_t AIVision::set_tag_family(pros::v5::AivisionTagFamily family, bool enable)
        {
            return 1;
        }

        int32_t AIVision::set_color(pros::aivision_color_s const &color)
        {
            return 1;
        }

        uint32_t AIVision::set_code(const pros::aivision_code_s &code)
        {
            return 1;
        }

        std::vector<pros::aivision_object_s_t> AIVision::get_all_objects()
        {
            return pros::sim::ai_vision_callback ? pros::sim::ai_vision_callback() : std::vector<pros::aivision_object_s_t>();
        }
    } // namespace v5
} // namespace pros