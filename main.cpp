#include <string.h> 
#include <EEPROM.h>
#include "codeOp.h"
#include "Interpreter.h"
#include "LedCubeMono.h"
#include "BootLoader.h"

/* Constants */
#define CLK  5 // Yellow CLOCK
#define SDI 2 // Orange DATA
#define LE  3 // Green	LATCH
#define SIZE_CUBE 8 /* It is here that we describe the size of our cube */

/* Initialization */
void setup() {
	Serial.begin(9600);
}

/******************************************************************
 ****************************MAIN PROGRAM***************************
 ******************************************************************/
int count;


void loop() {
	LedCubeMonoExtended cube(SIZE_CUBE, SDI, CLK, LE);
	Interpreter interpret = Interpreter(cube);
	mainBootLoader(interpret.bufferInstruction);
	interpret.interpret();

}

int main(void) {
	init();

	setup();

	for (;;)
		loop();

	return 0;
}

