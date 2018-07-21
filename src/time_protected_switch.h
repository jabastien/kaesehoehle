/* */

#ifndef TIME_PROTECTED_SWITCH_H_
#define TIME_PROTECTED_SWITCH_H_

#include <esphomelib/output/binary_output.h>
#include <esphomelib/switch_/simple_switch.h>

#include <string>

using esphomelib::switch_::SimpleSwitch;
using esphomelib::output::BinaryOutput;

namespace kaese {

class TimeProtectedSwitch : public SimpleSwitch {
 public:
  /** Construct this TimeProtectedSwitch with the provided BinaryOutput.
   *
   * @param min_off_time The minimum amount of time the switch must be off
   *                     until it can be turned on again. Requests to turn
   *                     on will be queued until the time is elapsed.
   */
  TimeProtectedSwitch(const std::string &name,
                      BinaryOutput *output,
                      uint32_t min_off_time = 0);

  void loop() override;

 protected:
  void turn_on() override;
  void turn_off() override;

  uint32_t min_off_time_;
  uint32_t last_off_time_;
  bool want_on_{false};
};

} /* namespace kaese */

#endif  /* TIME_PROTECTED_SWITCH_H_ */
