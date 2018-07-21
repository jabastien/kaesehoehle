/* */

#include "dht_aggregate.h"

#include <esphomelib/log.h>
#include <esphomelib/sensor/dht_component.h>

using esphomelib::sensor::DHTComponent;


static const char *TAG = "sensor.dht_agg";


DHTAggregate::DHTAggregate(const std::string &temperature_name,
                           const std::string &humidity_name,
                           uint32_t update_interval) :
        PollingComponent(update_interval),
        temperature_sensor_(new DHTTemperatureSensor(temperature_name, this)),
        humidity_sensor_(new DHTHumiditySensor(humidity_name, this)) {
}


DHTTemperatureSensor *DHTAggregate::get_temperature_sensor() const {
      return this->temperature_sensor_;
}


DHTHumiditySensor *DHTAggregate::get_humidity_sensor() const {
    return this->humidity_sensor_;
}


void DHTAggregate::add_dht_component(DHTComponent *dht) {
    this->dhts_.push_back(dht);
}


void DHTAggregate::update() {
    float temp = 0;
    float humid = 0;

    for (DHTComponent *dht : this->dhts_) {
        temp = dht->get_temperature_sensor()->get_raw_value() + temp;
        humid = dht->get_humidity_sensor()->get_raw_value() + humid;
    }

    temp = temp / this->dhts_.size();
    humid = humid / this->dhts_.size();

    ESP_LOGD(TAG, "Aggregated Temperature=%.1f°C Humidity=%.1f%%", temp, humid);

    this->temperature_sensor_->push_new_value(temp);
    this->humidity_sensor_->push_new_value(humid);
}
