#include <string.h> 
#include "codeOp.h"
#include "Interpreter.h"
#include "LedCubeMono.h"


/* Constants */
#define CLK  5 // Yellow CLOCK
#define SDI 2 // Orange DATA
#define LE  3 // Green	LATCH
#define NB_LAYERS 4
#define SIZE_CUBE 4 /* It is here that we describe the size of our cube */

/* Initialization */
void setup() 
{
    pinMode(CLK, OUTPUT);
    pinMode(SDI, OUTPUT);
    pinMode(LE, OUTPUT);    
    digitalWrite(CLK, LOW);  
    digitalWrite(SDI, LOW);
    digitalWrite(LE, LOW);
    Serial.begin(9600);
}


/******************************************************************
****************************MAIN PROGRAM***************************
******************************************************************/
void loop() 
{
    LedCubeMono *cube = new LedCubeMono(4, SDI, CLK, LE);
    Interpreter interpret = Interpreter(*cube);
    interpret.interpret();
}
