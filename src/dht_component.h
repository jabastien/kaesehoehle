/* */

#ifndef DHT_COMPONENT_H_
#define DHT_COMPONENT_H_

#include <esphomelib/sensor/dht_component.h>
#include <esphomelib/esphal.h>

#include <string>


namespace kaese {

class DHTComponent : public esphomelib::sensor::DHTComponent {
 public:
    DHTComponent(const std::string &temperature_name,
                 const std::string &humidity_name,
                 esphomelib::GPIOPin *pin,
                 uint32_t update_interval = 15000);

    float get_setup_priority() const override {
        return esphomelib::setup_priority::HARDWARE;
    }
};

} /* namespace kaese */

#endif  /* DHT_COMPONENT_H_ */
