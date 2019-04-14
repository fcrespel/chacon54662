#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
     
int main(int argc, char *argv[]) {
    // If no command line argument is given, print the help text
    if (argc < 3) {
        printf("Usage:  %s <gpio pin> <code word> [repeat count]\n", argv[0]);
        printf("Sample: %s 0 010111110010101011100011 3\n", argv[0]);
        return -1;
    }

    // Parse arguments
    int pin = atoi(argv[1]);    // see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
    char *codeWord = argv[2];   // 24-bit binary code to send
    int repeat = 1;             // number of times to repeat the message
    if (argc >= 4) {
        repeat = atoi(argv[3]);
    }

    // Configure RCSwitch
    if (wiringPiSetup () == -1) return 1;
    printf("sending code word [%s] via GPIO pin %i\n", codeWord, pin);
    RCSwitch mySwitch = RCSwitch();
    mySwitch.setRepeatTransmit(4);
    mySwitch.enableTransmit(pin);

    // Send message
    for (int i = 0; i < repeat; ++i) {
        // Send first group
        mySwitch.setProtocol(7); 
        mySwitch.send(codeWord);
        // Send second group
        mySwitch.setProtocol(8);
        mySwitch.send(codeWord);
    }

    return 0;
}
