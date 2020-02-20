#ifndef Controller_h
#define Controller_h

#include <Arduino.h>

//Button (Pin Number, Command, Note Number, Channel, Debounce Time)
class Button
{
  public:
    Button(byte pin, byte command, byte value, byte channel, byte debounce);
    byte getValue();
    byte Bcommand;
    byte Bvalue;
    byte Bchannel;
    byte Btoggle;

  private:
    unsigned long _time;
    int _debounce;
    byte _pin;
    byte _value;
    byte _command;
    bool _busy;
    byte _status;
    byte _last;
};
#endif
