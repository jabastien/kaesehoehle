/* */

#ifndef CONFIG_H_
#define CONFIG_H_


#ifdef CONFIG_USER
    #include "config.user.h"
#endif


#ifndef APP_NAME
    #define APP_NAME "cheesecave"
#endif


#ifndef SSID
    #warning "SSID not defined. All network will be disabled."
    #warning "Did you forget to copy config.user.h.sample to config.user.h?"
#endif


#ifndef SSID_PASSWORD
    #define SSID_PASSWORD ""
#endif


#ifndef ENABLE_OTA
    #define ENABLE_OTA 1
#endif


#if ENABLE_OTA
#ifndef OTA_PASSPHRASE
    #warning "OTA_PASSPHRASE not defined. OTA server will accept any firmware."
#endif
#endif


#ifndef ENABLE_WEB_SERVER
    #define ENABLE_WEB_SERVER 1
#endif


#ifndef MQTT_HOST
    #define MQTT_HOST "mqtt"
#endif


#ifndef MQTT_PORT
    #define MQTT_PORT 1883
#endif


#ifndef MQTT_USERNAME
    #define MQTT_USERNAME ""
#endif


#ifndef MQTT_PASSWORD
    #define MQTT_PASSWORD ""
#endif


#ifndef CAVE_NAME
    #define CAVE_NAME "Cheese Cave"
#endif


#ifndef NUM_DHT
    #define NUM_DHT 4
#endif


#ifndef DHT_1_PIN
    #define DHT_1_PIN 16
#endif


#ifndef DHT_1_NAME
    #define DHT_1_NAME CAVE_NAME " 1"
#endif


#ifndef DHT_1_MODEL
    #define DHT_1_MODEL esphomelib::sensor::DHT_MODEL_AUTO_DETECT
#endif


#ifndef DHT_2_PIN
    #define DHT_2_PIN 17
#endif


#ifndef DHT_2_NAME
    #define DHT_2_NAME CAVE_NAME " 2"
#endif


#ifndef DHT_2_MODEL
    #define DHT_2_MODEL esphomelib::sensor::DHT_MODEL_AUTO_DETECT
#endif


#ifndef DHT_3_PIN
    #define DHT_3_PIN 18
#endif


#ifndef DHT_3_NAME
    #define DHT_3_NAME CAVE_NAME " 3"
#endif


#ifndef DHT_3_MODEL
    #define DHT_3_MODEL esphomelib::sensor::DHT_MODEL_AUTO_DETECT
#endif


#ifndef DHT_4_PIN
    #define DHT_4_PIN 19
#endif


#ifndef DHT_4_NAME
    #define DHT_4_NAME CAVE_NAME " 4"
#endif


#ifndef DHT_4_MODEL
    #define DHT_4_MODEL esphomelib::sensor::DHT_MODEL_AUTO_DETECT
#endif


#ifndef DEFAULT_TARGET_HUMID
    #define DEFAULT_TARGET_HUMID 90
#endif


#ifndef DEFAULT_TARGET_TEMP
    #define DEFAULT_TARGET_TEMP 10
#endif


#ifndef FRIDGE_PIN
    #define FRIDGE_PIN 13
#endif

#ifndef FRIDGE_MIN_CYCLE_TIME
    #define FRIDGE_MIN_CYCLE_TIME 600000
#endif

#ifndef ENABLE_HUMIDIFIER
    #define ENABLE_HUMIDIFIER 1
#endif

#ifndef HUMIDIFIER_PIN
    #define HUMIDIFIER_PIN 12
#endif

#ifndef HUMIDIFIER_NAME
    #define HUMIDIFIER_NAME CAVE_NAME " Humidifier"
#endif


#endif  /* CONFIG_H_ */
