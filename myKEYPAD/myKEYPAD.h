#ifndef myKEYPAD

#define myKEYPAD

#include <Keypad.h>

const byte _ROWS = 3; //four rows
const byte _COLS = 4; //three columns

char _keys[_ROWS][_COLS] = {
  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'}
};
byte _colPins[_COLS] = {D8, D7, D6, D5}; // row pinouts of the keypad R1 = D8, R2 = D7, R3 = D6, R4 = D5
byte _rowPins[_ROWS] = {D4, D3, D2};    // column pinouts of the keypad C1 = D4, C2 = D3, C3 = D2

Keypad _keypad = Keypad( makeKeymap(_keys), _rowPins, _colPins, _ROWS, _COLS );
// const String _CONST_Code = "4321"; // The Master-Code
String _VAR_Code = ""; // Temporary Variable for the code inputs, after timeout, it will be deleted

#endif

