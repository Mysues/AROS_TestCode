#include <ArduinoRS485.h>

RS485Class rs485(Serial1, 18, 7, 6);

unsigned long prevMillis;
int iteration = 0;
void setup()
{
    Serial.begin(115200);
    rs485.begin(115200);
    
    rs485.receive();
}

void loop()
{
    // reSendingText();
    receiveText();
}

void reSendingText(){
unsigned long now = millis();
    if (now - prevMillis > 1000)
    {
        sendText(iteration);
        iteration++;
        if(iteration == 10)
            iteration = 0;
        prevMillis = now;
    }
}

void sendText(int number)
{
    rs485.noReceive();
    rs485.beginTransmission();
    rs485.print("hello ");
    rs485.println(number);
    rs485.endTransmission();
    rs485.receive();
}

void receiveText()
{
    if (rs485.available())
    {
        Serial.write(rs485.read());
    }
}