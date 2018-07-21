/* */

#ifndef BANG_BANG_COMPONENT_H_
#define BANG_BANG_COMPONENT_H_

#include <esphomelib/component.h>
#include <esphomelib/switch_/switch.h>
#include <esphomelib/sensor/sensor.h>

#include <string>


using esphomelib::Nameable;
using esphomelib::PollingComponent;
using esphomelib::switch_::Switch;
using esphomelib::sensor::Sensor;

namespace kaese {

class BangBangComponent : public PollingComponent, public Nameable {
 public:
    BangBangComponent(Switch *controlled_switch,
                      Sensor *sensor,
                      float target,
                      float target_range,
                      int8_t direction = 1,
                      uint32_t update_interval = 15000,
                      const std::string &name = "");

    float get_setup_priority() const override;
    void update() override;

 protected:
    Switch *_controlled_switch;
    int8_t _direction;
    Sensor *_sensor;
    float _target;
    float _target_range;
};

} /* namespace kaese */

#endif  /* BANG_BANG_COMPONENT_H_ */
