/* */

#include <esphomelib/sensor/dht_component.h>
#include <esphomelib/esphal.h>

#include <string>

#include "dht_component.h"


namespace kaese {

DHTComponent::DHTComponent(const std::string &temperature_name,
                           const std::string &humidity_name,
                           esphomelib::GPIOPin *pin,
                           uint32_t update_interval) :
        esphomelib::sensor::DHTComponent(temperature_name,
                                         humidity_name,
                                         pin->copy(),
                                         update_interval) {
}

} /* namespace kaese */
