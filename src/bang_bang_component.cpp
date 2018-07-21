/* */

#include <esphomelib/component.h>
#include <esphomelib/esppreferences.h>
#include <esphomelib/log.h>
#include <esphomelib/switch_/switch.h>
#include <esphomelib/sensor/sensor.h>

#include <string>

#include "bang_bang_component.h"


using esphomelib::global_preferences;
using esphomelib::Nameable;
using esphomelib::PollingComponent;
using esphomelib::switch_::Switch;
using esphomelib::sensor::Sensor;


static const char *TAG = "bangbang";


namespace kaese {

BangBangComponent::BangBangComponent(Switch *controlled_switch,
                                     Sensor *sensor,
                                     float target,
                                     float target_range,
                                     int8_t direction,
                                     uint32_t update_interval,
                                     const std::string &name) :
        PollingComponent(update_interval),
        Nameable(name),
        _controlled_switch(controlled_switch),
        _direction(direction),
        _sensor(sensor),
        _target(target),
        _target_range(target_range) {
    if (name.empty()) {
        this->set_name(controlled_switch->get_name() + " Bang-Bang");
    }
}


float BangBangComponent::get_setup_priority() const {
    return esphomelib::setup_priority::HARDWARE;
}


void BangBangComponent::update() {
    float value = this->_sensor->get_raw_value();
    float dir_value = _direction * value;
    float target_max = _direction * _target + _direction * _target_range;
    float target_min = _direction * _target - _direction * _target_range;

    if (isnan(value)) {
        return;
    }


    if (_controlled_switch->value) {
        if ((_direction < 0 && dir_value > target_min) ||
                (_direction > 0 && dir_value > target_max)) {
            ESP_LOGD(TAG, "%s turning off (value: %.1f target: %.1f)",
                     this->get_name().c_str(), value, _target);
            this->_controlled_switch->write_state(false);
        }
    } else {
        if ((_direction < 0 && dir_value < target_max) ||
               (_direction > 0 && dir_value < target_min)) {
            ESP_LOGD(TAG, "%s turning on (value: %.1f target: %.1f)",
                     this->get_name().c_str(), value, _target);
            this->_controlled_switch->write_state(true);
        }
    }
}

} /* namespace kaese */
