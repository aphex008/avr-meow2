#include <Arduino.h>
#include "PCM.h"
#include "meow2.h"

byte letterCodes[] = {
        B000001, // A+ 0
        B000011, // B+ 1
        B001001, // C+ 2
        B011001, // D  3
        B010001, // E  4
        B001011, // F+ 5
        B011011, // G  6
        B010011, // H  7
        B001010, // I+ 8
        B011010, // J  9
        B000101, // K+ 10
        B000111, // L+ 11
        B001101, // M+ 12
        B011101, // N  13
        B010101, // O  14
        B001111, // P+ 15
        B011111, // Q  16
        B010111, // R  17
        B001110, // S+ 18
        B011110, // T  19
        B100101, // U  20
        B100111, // V  21
        B111010, // W  22
        B101101, // X  23
        B111101, // Y  24
        B110101, // Y  25
};
char code[] = "PIFAIS";
char letterNumbers[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
unsigned int charNumber = 0;

unsigned int getLetterNumber(char letter) {
    for (unsigned int i = 0; i < sizeof(letterNumbers); i++) {
        if (letterNumbers[i] == letter) {
            return i;
        }
    }
}

byte getCodeByNumber(int letterNumber) {
    return letterCodes[letterNumber];
}

byte getCodeByLetter(char letter) {
    int letterNumber = getLetterNumber(letter);
    byte letterCode = getCodeByNumber(letterNumber);

    return letterCode;
}


void setup() {
    Serial.begin(9600);
    DDRC = B00111111; // Set pins A0-A5 output and A6-A7 input
    /* Init debug sequence */
    PORTC = B0001;
    startPlayback(meow2, sizeof(meow2));
    delay(1000);
    PORTC = B0010;
    startPlayback(meow2, sizeof(meow2));
    delay(1000);
    PORTC = B0100;
    startPlayback(meow2, sizeof(meow2));
    delay(1000);
    PORTC = B1000;
    startPlayback(meow2, sizeof(meow2));
    delay(1000);
    PORTC = B1111;
    startPlayback(meow2, sizeof(meow2));
    delay(1000);
    PORTC = B0000;
    startPlayback(meow2, sizeof(meow2));
    delay(1000);
    PORTC = B1111;
    startPlayback(meow2, sizeof(meow2));
    delay(1000);
}

void loop() {
    byte portc = getCodeByLetter(code[charNumber]);
    PORTC = portc;
    /* Print debug to serial */
    Serial.print("PORTC:");
    Serial.println(portc);
    Serial.print("CHARNUM:");
    Serial.println(charNumber);
    startPlayback(meow2, sizeof(meow2));
    Serial.println("-----------");
    charNumber++;
    if (charNumber == sizeof(code) - 1) {
        charNumber = 0;
        delay(3000);
    }

    delay(3000);
}


