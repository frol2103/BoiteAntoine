#ifndef MdmaxScreen_h
#define MdmaxScreen_h

#include <MD_MAX72xx.h>

const uint8_t graphics[][8] = {
    {B00111000, B01111100, B01111110, B00111111, B00111111, B01111110, B01111100, B00111000},
    {B00111000, B01000100, B01000010, B00100001, B00100001, B01000010, B01000100, B00111000},
    {B00111100, B01111110, B11111111, B11111111, B11100111, B11100111, B01000010, B00000000},
    {B01111111, B11011110, B11001111, B11111110, B11011111, B11001110, B01111111, B00000000},
    {B00011001, B00111010, B01101101, B11111010, B11111010, B01101101, B00111010, B00011001},
    {B00111100, B01000010, B10101001, B10000101, B10000101, B10101001, B01000010, B00111100},
    {B00111100, B01000010, B10100101, B10001001, B10001001, B10100101, B01000010, B00111100},
    {B00111100, B01000010, B10101001, B10001001, B10001001, B10101001, B01000010, B00111100}
};

 #define HEART_FULL 0 
 #define HEART_EMPTY 1 
 #define PACMAN 2 
 #define FANTOM 3 
 #define INVADER 4 
 #define SMILE 5 
 #define SAD 6 
 #define FLAT 7 


#define NUM_GRAPHICS 8

#define BLINK_PERIOD 100
#define TEXT_COL_PERIOD 100

class MdmaxScreen
{
public:
   struct Position{
        uint8_t x;
        uint8_t y;
        Position(uint8_t _x, uint8_t _y){x = _x; y = _y;}
    };
    MdmaxScreen(int _numberOfDevices, MD_MAX72XX *mx);
    int numberOfDevices;
    void printGraphic(const uint8_t graphic[], uint16_t offset);
    MD_MAX72XX *mx;
    void blink();
    void showText(char* text);
    boolean showCurrentText();
    void reset();
private:
    char* currentText;
    unsigned long textShowStart;    
};

#endif