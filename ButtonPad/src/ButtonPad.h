#ifndef ButtonPad_h
#define ButtonPad_h

#include <Arduino.h>

#define NUM_LED_COLUMNS (4)
#define NUM_LED_ROWS (4)
#define NUM_BTN_COLUMNS (4)
#define NUM_BTN_ROWS (4)
#define NUM_COLORS (3)

#define MAX_DEBOUNCE (3)
#define SCAN_PERIOD (1)

#define RED (1)
#define GREEN (2)
#define BLUE (3)

class ButtonPad
{

public:
    class EventListener
    {
    public:
        virtual void keyPressed(unsigned int col, unsigned int row, ButtonPad &pad){};
    };
    typedef unsigned char colorPins[3];
    typedef void(*ButtonEvent);

    void scan();
    void setup();
    unsigned int LED_outputs[NUM_LED_COLUMNS][NUM_LED_ROWS];
    EventListener *eventListener;

private:
    unsigned long lastScan;

    // unsigned int *btnselpins[NUM_BTN_COLUMNS];
    // uint8_t ledselpins[NUM_LED_COLUMNS];
    // uint8_t btnreadpins[NUM_BTN_ROWS];
    // colorPins colorpins[NUM_LED_ROWS];

    unsigned int btnselpins[NUM_BTN_COLUMNS] = {46, 48, 50, 52};
    uint8_t ledselpins[NUM_LED_COLUMNS] = {47, 49, 51, 53};
    uint8_t btnreadpins[NUM_BTN_ROWS] = {36, 37, 44, 45};
    colorPins colorpins[NUM_LED_ROWS] = {{30, 32, 34}, {31, 33, 35}, {38, 40, 42}, {39, 41, 43}};

    int8_t debounce_count[NUM_BTN_COLUMNS][NUM_BTN_ROWS];
};

#endif