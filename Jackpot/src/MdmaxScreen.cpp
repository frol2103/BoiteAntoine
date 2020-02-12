#include "MdmaxScreen.h"

unsigned char reverse(unsigned char b)
{
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

MdmaxScreen::MdmaxScreen(int _numberOfDevices, MD_MAX72XX *_mx)
{
    numberOfDevices = _numberOfDevices;
    mx = _mx;
}

void MdmaxScreen::printGraphic(const uint8_t graphic[], uint16_t offset)
{
    mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    const uint8_t dataSize = 8; //sizeof(graphic);

    for (uint8_t i = 0; i < dataSize; i++)
    {
        mx->setColumn(offset + i, graphic[i]);
    }
    mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void MdmaxScreen::blink()
{
    int light = (((millis() / BLINK_PERIOD) % 2) == 0) ? MD_MAX72XX::ON : MD_MAX72XX::OFF;
    mx->control(MD_MAX72XX::SHUTDOWN, light);
}

void MdmaxScreen::showText(char *text)
{
    currentText = text;
    textShowStart = millis();
}

boolean MdmaxScreen::showCurrentText()
{
    static uint8_t cBuf[8];
    unsigned int currentCol = 0;
    unsigned int messageColIndex = 0;
    unsigned int textFirstPartDelay = (TEXT_COL_PERIOD * 8 * numberOfDevices);
    unsigned int textStartColIndex = (millis() - textShowStart < textFirstPartDelay) ? 0 : ((millis() - textShowStart - textFirstPartDelay) / TEXT_COL_PERIOD);
    mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);
    mx->clear();
    for (int i = 0; i < strlen(currentText); i++)
    {
        int charSize = mx->getChar(currentText[i], sizeof(cBuf) / sizeof(cBuf[0]), cBuf);
        for (int j = 0; j < charSize; j++)
        {
            if (messageColIndex >= (textStartColIndex + 8 * numberOfDevices))
            {
                mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
                return false;
            }
            else if (messageColIndex >= textStartColIndex)
            {
                mx->setColumn((messageColIndex - textStartColIndex), reverse(cBuf[j]));
            }
            messageColIndex++;
        }
        messageColIndex++;
    }
    mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);

    return (messageColIndex < (textStartColIndex + 8 * numberOfDevices));
}

void MdmaxScreen::reset()
{
    mx->control(MD_MAX72XX::INTENSITY, MAX_INTENSITY);
    mx->control(MD_MAX72XX::SHUTDOWN, MD_MAX72XX::OFF);
    mx->control(MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
    mx->clear();
    
}