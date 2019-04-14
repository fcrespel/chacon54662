# Chacon 54662 RCSwitch

This project extends the [RCSwitch](https://github.com/sui77/rc-switch/) library to support the Chacon 54662 power outlet sockets, and provides a simple program to send binary codes. It has only been tested on a Raspberry Pi.

## Compilation

To compile this program, make sure you have built and installed the [WiringPi](https://projects.drogon.net/raspberry-pi/wiringpi/download-and-install/) library first.

Then execute `make` in the code directory and you should obtain the `send` program.

The `send.sh` wrapper script makes use of `flock` to prevent concurrent calls using a file lock.

## Usage

Connect a 433MHz transmitter to the GPIO pin of your choice on a Raspberry Pi (see the [pin numbering](https://projects.drogon.net/raspberry-pi/wiringpi/pins/) documentation).

Then execute `./send.sh <gpio pin> <code word> [repeat count]` where the code word is a 24-bit binary code (see protocol and samples below).

For example: `./send.sh 0 010111110010101011100011 3`

## Protocol

The following information has been deduced from captures of an original remote control, and may not be 100% correct. See the RCSwitch [Add New Remote](https://github.com/sui77/rc-switch/wiki/Add_New_Remote_Part_1) tutorial for more information.

The Chacon 54662 protocol as emitted by the original remote control is made of:

* 4 frames encoded with "A" timings
* 4 frames encoded with "B" timings

Each frame starts with a sync bit followed by 24 bits:

* 4 bits static code 0101
* 16 bits rotating code
* 4 bits socket code

Rotating codes likely depend on the remote control (see samples below), and each button has 4 rotating codes. Codes are reused between buttons/states:

* A/ON = C/OFF
* B/ON = D/OFF
* C/ON = A/OFF
* D/ON = B/OFF

Socket codes:

* A: 0011
* B: 1010
* C: 0001
* D: 1000

Timings observed during capture, in microseconds:

 Bit  | "A" timings | "B" timings
------|---------------------|---------------------
 Sync | 290 HIGH + 2400 LOW | 3000 HIGH + 7300 LOW
Bit 0 | 1070 HIGH + 470 LOW | 940 HIGH + 600 LOW
Bit 1 | 290 HIGH + 1250 LOW | 420 HIGH + 1120 LOW

## Samples

The following codes have been captured from an original remote:

| Button | ON | OFF |
|--------|----|-----|
| A | 010111110010101011100011 010111000110111010100011 010101010011001001010011 010100100100101110010011 | 010101100000010001000011 010100111100100010000011 010111011101001111010011 010110101111110001110011 |
| B | 010101000101110111001010 010110111000011100001010 010111101011011000011010 010100001010000111111010 | 010110001001100101101010 010100011110010100101010 010101110001000010111010 010110010111111100111010 |
| C | 010101100000010001000001 010100111100100010000001 010111011101001111010001 010110101111110001110001 | 010111110010101011100001 010111000110111010100001 010101010011001001010001 010100100100101110010001 |
| D | 010110001001100101101000 010100011110010100101000 010101110001000010111000 010110010111111100111000 | 010101000101110111001000 010110111000011100001000 010111101011011000011000 010100001010000111111000 |

For example, use:

* `/send.sh 0 010111110010101011100011` to simulate Button A ON
* `/send.sh 0 010101100000010001000011` to simulate Button A OFF
