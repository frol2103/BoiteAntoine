#ifndef COMM_H
#define COMM_H

#include <Wire.h>
#include <comm/Message.h>

#define LED_BLOC (1)

Message messageToSend = Message(0);

void requestEvent()
{
    byte data[2] = {messageToSend.messageType, byte(sizeof(messageToSend.payload))};
    Wire.write(data,2);
    
}

void init(byte adress){
    Wire.begin(adress);
    Wire.onRequest(requestEvent);
}




void send(byte address, byte messageId, byte content[]){
    Wire.beginTransmission(address);
    Wire.write(messageId);
    Wire.write(content,sizeof(content));
    Wire.endTransmission();
}

void send(Message message){

messageToSend = message;
}

#endif
