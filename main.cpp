#include <string.h> 
#include <EEPROM.h>
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
void setup() {
	Serial.begin(9600);
}

/******************************************************************
 ****************************MAIN PROGRAM***************************
 ******************************************************************/
int count;
void bootloader() {
	count = 0;
	char value = EEPROM.read(0);
	bool isEmpty = (value == 0xFF);
	/*if(isEmpty)
	 {*/
	Serial.setTimeout(30000);
	byte b[750];

	while (Serial.available() > 0) {
		b[count] = Serial.read();
		count++;
	}
	for (int i = 0; i < count; i++) {
		EEPROM.write(i, b[i]);
	}
	/*}
	 else{
	 Serial.println("eeprom non vide");
	 }*/
}

void loop() {
	//bootloader();
	LedCubeMonoExtended cube(4, SDI, CLK, LE);
	cube.testCube(100);
	//Interpreter interpret = Interpreter(cube);
	//interpret.interpret();

	/*char value = EEPROM.read(0);
	 bool isEmpty = (value == 0xFF);
	 if(!isEmpty)
	 {
	 for(int i =0; i < count; i+=5)
	 {
	 byte b[5];
	 interpret.bufferLoop[i][0] = EEPROM.read(i);
	 interpret.bufferLoop[i][1] = EEPROM.read(i+1);
	 interpret.bufferLoop[i][2] = EEPROM.read(i+2);
	 interpret.bufferLoop[i][3] = EEPROM.read(i+3);
	 interpret.bufferLoop[i][4] = EEPROM.read(i+4);
	 Serial.println(interpret.bufferLoop[i]);
	 }

	 }*/
	/*uint16_t ledMask[2];
	 ledMask[0] = 0x0000;*/
	/*while (true) {

		/*cube.drawLayer(LAYER_MASK(3),(uint16_t *) ledMask);
		 delay(250);
		 ledMask[0]++;*/
	//}
}

int main(void) {
	init();

	setup();

	for (;;)
		loop();

	return 0;
}

