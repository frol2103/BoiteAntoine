#ifndef RGB_LED_ARRAY_H
#define RGB_LED_ARRAY_H

#define RED_PIN (10)
#define GREEN_PIN (9)
#define BLUE_PIN (8)

#define IN_RED_PIN (A2)
#define IN_GREEN_PIN (A1)
#define IN_BLUE_PIN (A0)

#define LIGHT_POWER (A5)
#define LIGHT_NUMBER (A6)

#define NPINS (6)

class RgbLedArray
{


private:
    int pinSelect[6] = {22,23,24,25,26,27};
public:

    long i = 0;
    void init(){
        for(int j = 0; j < sizeof(pinSelect); j++){
            digitalWrite(pinSelect[j], (j==3)?HIGH:LOW);
        }
    }

    void run(){
        i++;
        
        int lightNumberOfPins=map(1023-analogRead(LIGHT_NUMBER), 0, 1000, 0, 6);
        
        for(int j = lightNumberOfPins; j < NPINS; j++){
            digitalWrite(pinSelect[j],LOW);
        }
        for(int j = 0; j < lightNumberOfPins; j++){
            digitalWrite(pinSelect[j],HIGH);
        }


      //  Serial.print(analogRead(IN_RED_PIN)); Serial.print(" - ");
      //  Serial.print(analogRead(IN_GREEN_PIN)); Serial.print(" - ");
      //  Serial.print(analogRead(IN_BLUE_PIN)); Serial.println("");
/*         if(i%3==0){
            analogWrite(RED_PIN, map(analogRead(IN_RED_PIN), 0, 1023, 0, 255));
            analogWrite(GREEN_PIN, 255);
            analogWrite(BLUE_PIN, 255);
        
        }
                if(i%3==1){
            analogWrite(GREEN_PIN, map(analogRead(IN_GREEN_PIN), 0, 1023, 0, 255));
            analogWrite(RED_PIN, 255);
            analogWrite(BLUE_PIN, 255);
        
        }
                        if(i%3==2){
            analogWrite(GREEN_PIN, map(analogRead(IN_BLUE_PIN), 0, 1023, 0, 255));
            analogWrite(RED_PIN, 255);
            analogWrite(BLUE_PIN, 255);
        
        }
        //analogWrite(GREEN_PIN,  map(analogRead(IN_GREEN_PIN), 0, 1023, 0, 255));
        //analogWrite(BLUE_PIN,  map(analogRead(IN_BLUE_PIN), 0, 1023, 0, 255));
        */
       analogWrite(GREEN_PIN,  map(1023-analogRead(LIGHT_POWER), 0, 1023, 0, 255));
        
    } 
};



#endif