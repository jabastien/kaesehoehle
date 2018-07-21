/* */

#include <esphomelib.h>
#include <esphomelib/esppreferences.h>
#include <esphomelib/log.h>
#include <esphomelib/sensor/dht_component.h>

#include "config.h"
#include "dht_aggregate.h"
#include "dht_component.h"
#include "time_protected_switch.h"
#include "bang_bang_component.h"


using esphomelib::App;
using esphomelib::global_preferences;
using esphomelib::GPIOOutputPin;
using esphomelib::output::GPIOBinaryOutputComponent;
using esphomelib::sensor::DHTModel;


struct DHT_CONFIGS {
    const char *temp_name;
    const char *humid_name;
    const int pin;
    const int update_interval;
    const DHTModel model;
};


void setup() {
    DHTAggregate *dht_agg;

    App.set_name(APP_NAME);
    App.init_log();

#ifdef SSID
    App.init_wifi(SSID,
                  SSID_PASSWORD)->set_reboot_timeout(0);

#ifdef ENABLE_OTA
#ifdef OTA_PASSPHRASE
    auto *ota = App.init_ota();
    ota->set_auth_plaintext_password(OTA_PASSPHRASE);
#else
    App.init_ota();
#endif  /* OTA_PASSPHRASE */
#endif  /* ENABLE_OTA */


#ifdef MQTT_HOST
    App.init_mqtt(MQTT_HOST,
                  MQTT_USERNAME,
                  MQTT_PASSWORD)->set_reboot_timeout(0);
#endif  /* ENABLE_OTA */


#ifdef ENABLE_WEB_SERVER
    App.init_web_server();
#endif  /* ENABLE_WEB_SERVER */

#endif  /* SSID */

    App.make_status_led(LED_BUILTIN);

    struct DHT_CONFIGS dht_config[] = {
        {
            DHT_1_NAME " Temperature",
            DHT_1_NAME " Humidity",
            DHT_1_PIN,
            15000,
            DHT_1_MODEL
        },
        {
            DHT_2_NAME " Temperature",
            DHT_2_NAME " Humidity",
            DHT_2_PIN,
            15000,
            DHT_2_MODEL
        },
        {
            DHT_3_NAME " Temperature",
            DHT_3_NAME " Humidity",
            DHT_3_PIN,
            15000,
            DHT_3_MODEL
        },
        {
            DHT_4_NAME " Temperature",
            DHT_4_NAME " Humidity",
            DHT_4_PIN,
            15000,
            DHT_4_MODEL
        },
    };

    dht_agg = new DHTAggregate(CAVE_NAME " Temperature",
                               CAVE_NAME " Humidity");
    App.register_component(dht_agg);

    App.register_sensor(dht_agg->get_temperature_sensor());
    App.register_sensor(dht_agg->get_humidity_sensor());

    for (uint8_t i=0; i < NUM_DHT; i++) {
        auto dht = App.register_component(
                new kaese::DHTComponent(dht_config[i].temp_name,
                                        dht_config[i].humid_name,
                                        new GPIOOutputPin(dht_config[i].pin),
                                        dht_config[i].update_interval));

        App.register_sensor(dht->get_temperature_sensor());
        App.register_sensor(dht->get_humidity_sensor());
        dht->set_dht_model(dht_config[i].model);

        /* NOTE(jkoelker) run the update to get rid of the NAN's */
        // dht.dht->update();

        dht_agg->add_dht_component(dht);
    }


    auto *fridge_binary_output = App.make_gpio_output(
            GPIOOutputPin(FRIDGE_PIN, OUTPUT, true));

    auto *fridge_switch = App.register_component(
            new kaese::TimeProtectedSwitch(CAVE_NAME " Fridge",
                                           fridge_binary_output,
                                           FRIDGE_MIN_CYCLE_TIME));

    /* NOTE(jkoelker) force state to off, it will be turned on if needed */
    if (global_preferences.get_bool(fridge_switch->get_name(),
                                    "state", false)) {
        global_preferences.put_bool(fridge_switch->get_name(),
                                    "state", false);
    }

    App.register_switch(fridge_switch);

    auto *fridge_temp_sensor = dht_agg->get_temperature_sensor();
    auto *fridge = new kaese::BangBangComponent(fridge_switch,
                                                fridge_temp_sensor,
                                                DEFAULT_TARGET_TEMP,
                                                1,
                                                -1,
                                                15000);
    App.register_component(fridge);

#if ENABLE_HUMIDIFIER
    auto *humidifier_binary_output = App.make_gpio_output(
            GPIOOutputPin(HUMIDIFIER_PIN, OUTPUT, true));
    auto humidifier_switch = App.make_simple_switch(HUMIDIFIER_NAME,
                                                    humidifier_binary_output);

    /* NOTE(jkoelker) force state to off, it will be turned on if needed */
    if (global_preferences.get_bool(humidifier_switch.switch_->get_name(),
                                    "state", false)) {
        global_preferences.put_bool(humidifier_switch.switch_->get_name(),
                                    "state", false);
    }

    auto *fridge_humid_sensor = dht_agg->get_humidity_sensor();
    auto *humidifier = new kaese::BangBangComponent(humidifier_switch.switch_,
                                                    fridge_humid_sensor,
                                                    DEFAULT_TARGET_HUMID,
                                                    1,
                                                    1,
                                                    15000);
    App.register_component(humidifier);
#endif

    App.setup();
}


void loop() {
    App.loop();
}
