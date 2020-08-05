/*----------------------------------------------------------------------*
   Arduino Button Library v1.0
   Jack Christensen Mar 2012
 *                                                                      *
   This work is licensed under the Creative Commons Attribution-
   ShareAlike 3.0 Unported License. To view a copy of this license,
   visit http://creativecommons.org/licenses/by-sa/3.0/ or send a
   letter to Creative Commons, 171 Second Street, Suite 300,
   San Francisco, California, 94105, USA.
  ----------------------------------------------------------------------*/

#ifndef __M5StackButton_H__
#define __M5StackButton_H__

class M5StackButton {
  public:
    void begin(uint8_t pin, uint8_t invert, uint32_t dbTime) {
      _pin = pin;
      if (_pin == 255) {
        return;
      }
      _invert = invert;
      _dbTime = dbTime;
      pinMode(_pin, INPUT);
      _state = digitalRead(_pin);
      if (_invert != 0) _state = !_state;
      _time = millis();
      _lastState = _state;
      _changed = 0;
      _hold_time = -1;
      _lastTime = _time;
      _lastChange = _time;
      _pressTime = _time;
    }

    uint8_t read() {
      if (_pin == 255) {
        return 0;
      }
      static uint32_t ms;
      static uint8_t pinVal;

      ms = millis();
      pinVal = digitalRead(_pin);
      if (_invert != 0) pinVal = !pinVal;
      if (ms - _lastChange < _dbTime) {
        _lastTime = _time;
        _time = ms;
        _changed = 0;
        return _state;
      }
      else {
        _lastTime = _time;
        _time = ms;
        _lastState = _state;
        _state = pinVal;
        if (_state != _lastState) {
          _lastChange = ms;
          _changed = 1;
          if (_state) {
            _pressTime = _time;
          }
        }
        else {
          _changed = 0;
        }
        return _state;
      }
    }
    uint8_t isPressed() {
      if (_pin == 255) {
        return 0;
      }
      return _state == 0 ? 0 : 1;
    }
    uint8_t isReleased() {
      if (_pin == 255) {
        return 0;
      }
      return _state == 0 ? 1 : 0;
    }
    uint8_t wasPressed() {
      if (_pin == 255) {
        return 0;
      }
      return _state && _changed;
    }
    uint8_t wasReleased() {
      if (_pin == 255) {
        return 0;
      }
      return !_state && _changed && millis() - _pressTime < _hold_time;
    }
    uint8_t pressedFor(uint32_t ms) {
      if (_pin == 255) {
        return 0;
      }
      return (_state == 1 && _time - _lastChange >= ms) ? 1 : 0;
    }
    uint8_t releasedFor(uint32_t ms) {
      if (_pin == 255) {
        return 0;
      }
      return (_state == 0 && _time - _lastChange >= ms) ? 1 : 0;
    }
    uint8_t wasReleasefor(uint32_t ms) {
      if (_pin == 255) {
        return 0;
      }
      _hold_time = ms;
      return !_state && _changed && millis() - _pressTime >= ms;
    }
    uint32_t lastChange() {
      if (_pin == 255) {
        return 0;
      }
      return _lastChange;
    }

  private:
    uint8_t _pin;           //arduino pin number
    uint8_t _puEnable;      //internal pullup resistor enabled
    uint8_t _invert;        //if 0, interpret high state as pressed, else interpret low state as pressed
    uint8_t _state;         //current button state
    uint8_t _lastState;     //previous button state
    uint8_t _changed;       //state changed since last read
    uint32_t _time;         //time of current state (all times are in ms)
    uint32_t _lastTime;     //time of previous state
    uint32_t _lastChange;   //time of last state change
    uint32_t _dbTime;       //debounce time
    uint32_t _pressTime;    //press time
    uint32_t _hold_time;    //hold time call wasreleasefor
};

#endif
