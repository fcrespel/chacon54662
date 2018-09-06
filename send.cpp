#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
     
int main(int argc, char *argv[]) {
    // This pin is not the first pin on the RPi GPIO header!
    // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
    // for more information.
    int PIN = 0;

    // If no command line argument is given, print the help text
    if (argc == 1) {
        printf("Usage: %s <code word>\n", argv[0]);
        return -1;
    }

    // Get code to send
    char *codeWord = argv[1];

    // Configure RCSwitch
    if (wiringPiSetup () == -1) return 1;
    printf("sending code word [%s]\n", codeWord);
    RCSwitch mySwitch = RCSwitch();
    mySwitch.setRepeatTransmit(4);
    mySwitch.enableTransmit(PIN);

    // Send first group
    mySwitch.setProtocol(7); 
    mySwitch.send(codeWord);

    // Send second group
    mySwitch.setProtocol(8);
    mySwitch.send(codeWord);

    return 0;
}
