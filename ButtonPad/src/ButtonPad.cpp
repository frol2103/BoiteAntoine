#include "ButtonPad.h"

void ButtonPad::scan()
{

    if (millis() >= (lastScan + SCAN_PERIOD))
    {

        static uint8_t current = 0;
        uint8_t val;
        uint8_t i, j;

        //run
        digitalWrite(btnselpins[current], LOW);
        digitalWrite(ledselpins[current], LOW);

        for (i = 0; i < NUM_LED_ROWS; i++)
        {
            uint8_t val = (LED_outputs[current][i] & 0x03);

            if (val)
            {
                digitalWrite(colorpins[i][val - 1], HIGH);
            }
        }

        delay(1);

        for (j = 0; j < NUM_BTN_ROWS; j++)
        {
            val = digitalRead(btnreadpins[j]);

            if (val == LOW)
            {
                // active low: val is low when btn is pressed
                if (debounce_count[current][j] < MAX_DEBOUNCE)
                {
                    debounce_count[current][j]++;
                    if (debounce_count[current][j] == MAX_DEBOUNCE)
                    {
                        Serial.print("Key Down ");
                        Serial.println((current * NUM_BTN_ROWS) + j);

                        eventListener -> keyPressed(current, j, *this);
                        
                    }
                }
            }
            else
            {
                // otherwise, button is released
                if (debounce_count[current][j] > 0)
                {
                    debounce_count[current][j]--;
                    if (debounce_count[current][j] == 0)
                    {
                        Serial.print("Key Up ");
                        Serial.println((current * NUM_BTN_ROWS) + j);
                    }
                }
            }
        } // for j = 0 to 3;

        delay(1);

        digitalWrite(btnselpins[current], HIGH);
        digitalWrite(ledselpins[current], HIGH);

        for (i = 0; i < NUM_LED_ROWS; i++)
        {
            for (j = 0; j < NUM_COLORS; j++)
            {
                digitalWrite(colorpins[i][j], LOW);
            }
        }

        current++;
        if (current >= NUM_BTN_COLUMNS)
        {
            current = 0;
        }
    }
}

void ButtonPad::setup()
{

    uint8_t i;

    // initialize
    // select lines
    for (i = 0; i < NUM_LED_COLUMNS; i++)
    {
        pinMode(ledselpins[i], OUTPUT);

        // with nothing selected by default
        digitalWrite(ledselpins[i], HIGH);
    }

    for (i = 0; i < NUM_BTN_COLUMNS; i++)
    {
        pinMode(btnselpins[i], OUTPUT);

        // with nothing selected by default
        digitalWrite(btnselpins[i], HIGH);
    }

    // key return lines
    for (i = 0; i < 4; i++)
    {
        pinMode(btnreadpins[i], INPUT_PULLUP);
    }

    // LED drive lines
    for (i = 0; i < NUM_LED_ROWS; i++)
    {
        for (uint8_t j = 0; j < NUM_COLORS; j++)
        {
            pinMode(colorpins[i][j], OUTPUT);
            digitalWrite(colorpins[i][j], LOW);
        }
    }

    for (uint8_t i = 0; i < NUM_BTN_COLUMNS; i++)
    {
        for (uint8_t j = 0; j < NUM_BTN_ROWS; j++)
        {
            debounce_count[i][j] = 0;
        }
    }

    // init global variables
    lastScan = 0;

    for (uint8_t i = 0; i < NUM_LED_ROWS; i++)
    {
        for (uint8_t j = 0; j < NUM_LED_COLUMNS; j++)
        {
            LED_outputs[i][j] = 0;
        }
    }
}
