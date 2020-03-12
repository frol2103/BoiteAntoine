#ifndef SpeedPush_h
#define SpeedPush_h

#include <Arduino.h>

#include "step/GameStep.h"
#include "../part/ButtonPad.h"

#include <log/LoggerFactory.hpp>
#include <Wire.h>

#define RED_PERIOD (30)
#define GREEN_PERIOD (5)

LoggerFactory lf = LoggerFactory();


class SpeedPush : public GameStep, ButtonPad::EventListener
{

public:
    SpeedPush(ButtonPad *_pad)
    {
        pad = _pad;
    }
    SpeedPush()
    {
    }
    ButtonPad *pad;
    bool run()
    {

        
        if(lostMillis != 0 && millis() > (lostMillis+3000)){
            init();
        } else if(lostMillis==0) {
            if (millis() > (lastAction + period))
                    {
                        lastAction = millis();
                        bool result = runAction(iter);
                        iter++;
                        return result;
                    }
        }

        
        return false;
    }
    void init()
    {
        for (int i = 0; i < 16; i++)
        {
            cellState[i] = 0;
            cellStateSetIter[i] = 0;
        }
        lastAction = 0;
        iter = 0;
       
        Serial.println(lostMillis);
        this->lostMillis=0L;
        Serial.println("init");
        pad->eventListener = this;
        period=500;
        score=0;
    }

    void setLost(){
        Serial.print("Set lost millis ");
        Serial.println(millis());
        this->lostMillis = millis();
        for(int i = 0; i< 16;i++){updateCell(i,RED);}
        updatePad();
    }

    bool runAction(long iter)
    {
        
        updateStates(iter);
        if(isLost()){
            setLost();
            return false;
        }
        
  
        if(iter > 0 && iter%10 == 0){
            addGreen((iter/10)%5);
        } else {
            addGreen(1);
        }
  
        period--; 
        updatePad();
        return false;
    }

    bool isLost(){
        int countRed=0;
        for(int i = 0; i<= 16;i++){
            if(cellState[i]==RED){
                countRed++;
            }
        }
        return countRed>5;
    }

    void addGreen(int n){
        for(int i = 0; i< n;i++){
            int r = randomFree();
            updateCell(r,GREEN);
        }
    }

    void updateStates(long iter)
    {
        for (int i = 0; i < 16; i++)
        {
            if (cellState[i] == GREEN && iter - cellStateSetIter[i] > GREEN_PERIOD)
            {
                updateCell(i, RED);
            }
            else if (cellState[i] == RED && iter - cellStateSetIter[i] > RED_PERIOD)
            {
                cellState[i] = 0;
                cellStateSetIter[i] = iter;
            }
        }
    }

    void keyPressed(unsigned int col, unsigned int row, ButtonPad &pad)
    {
        int cellIndex = col * 4 + row;
        if (cellState[cellIndex] == GREEN)
        {
            updateCell(cellIndex, 0);
            score++;
            Serial.print("score");
            Serial.println(score);
            Wire.beginTransmission(4);
            Wire.write(score); 
            Wire.write(score>>8);
            Wire.endTransmission(); 
        } 
        else if (cellState[cellIndex] ==0)
        {
            updateCell(cellIndex, RED);
        } 
        else if (cellState[cellIndex] == RED)
        {
            setLost();
        } 
        updatePad();
    }

    void updateCell(int index, int state)
    {
        cellState[index] = state;
        cellStateSetIter[index] = iter;
    }

    void updatePad()
    {
        for (int i = 0; i < 16; i++)
        {
            pad->LED_outputs[i / 4][i % 4] = (cellState[i] == 0) ? BLUE : cellState[i];
        }
    }

    int randomFree()
    {
        int r = random(16);
        for (int i = 0; i < 16; i++)
        {
            int candidate = (r + i) % 16;
            if (cellState[candidate] == 0)
            {
                return candidate;
            }
        }
        return 0;
    }

private:
    unsigned long period = 500;
    unsigned long lastAction = 0;
    unsigned long iter = 0;
    unsigned int score = 0;
    unsigned int cellState[16];
    unsigned long cellStateSetIter[16];
    unsigned long lostMillis;
};

#endif