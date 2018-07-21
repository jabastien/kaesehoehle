/* */

#ifndef DHT_AGGREGATE_H_
#define DHT_AGGREGATE_H_

#include <esphomelib/sensor/dht_component.h>
#include <esphomelib/sensor/sensor.h>

#include <string>
#include <vector>

using esphomelib::PollingComponent;
using esphomelib::sensor::DHTComponent;
using esphomelib::sensor::DHTTemperatureSensor;
using esphomelib::sensor::DHTHumiditySensor;


class DHTAggregate : public PollingComponent {
 public:
  DHTAggregate(const std::string &temperature_name,
               const std::string &humidity_name,
               uint32_t update_interval = 15000);

  DHTTemperatureSensor *get_temperature_sensor() const;
  DHTHumiditySensor *get_humidity_sensor() const;

  void add_dht_component(DHTComponent *dht);

  void update() override;

  float get_setup_priority() const override {
      return esphomelib::setup_priority::HARDWARE;
  }

 protected:
  DHTTemperatureSensor *temperature_sensor_;
  DHTHumiditySensor *humidity_sensor_;
  std::vector<DHTComponent *> dhts_;
};


#endif  /* DHT_AGGREGATE_H_ */
