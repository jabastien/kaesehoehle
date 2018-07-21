/* */

#include "time_protected_switch.h"

#include <esphomelib/log.h>

namespace kaese {

static const char *TAG = "switch.time_protect";


TimeProtectedSwitch::TimeProtectedSwitch(const std::string &name,
                                         BinaryOutput *output,
                                         uint32_t min_off_time) :
        SimpleSwitch(name, output),
        min_off_time_(min_off_time),
        last_off_time_(0) {
}


void TimeProtectedSwitch::loop() {
    if (this->want_on_ && !this->value) {
        uint32_t now = millis();
        uint32_t elapsed = now - last_off_time_;

        if (elapsed >= this->min_off_time_) {
            if (!this->inverted_) {
                SimpleSwitch::turn_on();
            } else {
                SimpleSwitch::turn_off();
            }
        } else if (now % 5000 == 0) {
            ESP_LOGD(TAG, "Waiting to turn on: %d seconds left",
                     (this->min_off_time_ - elapsed) / 1000);
        }
    } else if (!this->want_on_ && this->value) {
        if (this->inverted_) {
            SimpleSwitch::turn_on();
        } else {
            SimpleSwitch::turn_off();
        }

        this->last_off_time_ = millis();
    }
}


void TimeProtectedSwitch::turn_on() {
    this->want_on_ = true != this->inverted_;
}


void TimeProtectedSwitch::turn_off() {
    this->want_on_ = false != this->inverted_;
}

} /* namespace kaese */
