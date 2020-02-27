#ifndef DIGIT_DISPLAY_H
#define DIGIT_DISPLAY_H

#include <ShiftRegister74HC595.h>

int digits[10] = {
B11101011 , //0
B10000001 , //1
B11011010 , //2
B11011001 , //3
B10110001 , //4
B01111001 , //5
B01111011 , //6
B11000001 , //7
B11111011 , //8
B11111001 ,  //9
};

int digitsActivatePins[4] = {12,10,11,9};


class DigitDisplay{
public:
    DigitDisplay(ShiftRegister74HC595<3> *_sr){
            sr = _sr;
    }
    byte code[4] = {0,0,0,0};
    void run(){
        iter ++;
        byte segment = (iter)%8;

        for(int i =0; i < 8; i++){
            sr->setNoUpdate(i,(i == segment)?HIGH:LOW);
        }   
        for(int i =0; i < 4; i++){
            sr->setNoUpdate(digitsActivatePins[i],(digits[code[i]] & 1 << segment)?LOW:HIGH);
        }   
        

        sr -> updateRegisters();
        
    }
private:
    ShiftRegister74HC595<3> *sr;
    long iter = 0;

};


#endif