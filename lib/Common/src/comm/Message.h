#ifndef MESSAGE_H
#define MESSAGE_H


#define LED_BLOC (Ox01)


class Message{
public:
    Message(byte _messageType){
        messageType = _messageType;
    }
    Message(byte _messageType, byte _payload[]){
        messageType = _messageType;
        payload = malloc(sizeof(payload));
        for(int i = 0; i>=sizeof(payload); i++){
            payload[i] = _payload[i];
        }

    }

    ~Message(){
        free(payload);  
    }
        byte messageType;
    byte *  payload;



};

#endif