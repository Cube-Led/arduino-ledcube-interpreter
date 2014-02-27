#include "Interpreter.h"
#include "LedCubeMonoExtended.h"

Interpreter::Interpreter(LedCubeMonoExtended const& c) {
	cube = new LedCubeMonoExtended(c);
}


void Interpreter::interpret() {
	bufferInstruction[0][0] = 0x4;
		bufferInstruction[0][1] = 0x4;
	bufferInstruction[1][0] = 0x1;
		bufferInstruction[1][1] = 0x7D0;
	bufferInstruction[2][0] = 0x7;
		bufferInstruction[2][1] = 0x5;
		bufferInstruction[2][2] = 0x6;
		bufferInstruction[2][3] = 0x3;
			bufferInstruction[3][0] = 0x4;
				bufferInstruction[3][1] = 0x3;
			bufferInstruction[4][0] = 0x1;
				bufferInstruction[4][1] = 0x1F4;
			bufferInstruction[5][0] = 0x30;
			bufferInstruction[6][0] = 0x1;
				bufferInstruction[6][1] = 0x1F4;
			bufferInstruction[7][0] = 0x4;
				bufferInstruction[7][1] = 0x1;
			bufferInstruction[8][0] = 0x1;
				bufferInstruction[8][1] = 0x1F4;
	bufferInstruction[9][0] = 0x30;
	bufferInstruction[10][0] = 0x1;
		bufferInstruction[10][1] = 0x7D0;


	int i =0;
	while(true){
		evaluateCodeOp(bufferInstruction[i]);
		i++;
	}
}

char Interpreter::evaluateCodeOp(uint16_t buf[]) {
	uint16_t layer;
	uint16_t ledMask[2];
	int led;

	switch (buf[0]) {
		case DELAY:
			delay(buf[1]);
			return DELAY;
		case LIGHTLAYER:
			layer = buf[1];
			ledMask[0] = buf[2];
			ledMask[1] = buf[3];
			cube->drawLayer(LAYER_MASK(layer - 1), (uint16_t *) ledMask);
			return LIGHTLAYER;
		case LIGHTONELEDBYHISNUM:
			layer = buf[1];
			led = buf[2];
			cube->lightOneLEDByHisNum(layer, led);
			return LIGHTONELEDBYHISNUM;
		case LIGHTALLLEDONLAYER:
			layer = buf[1];
			cube->lightAllLedOnLayer(layer);
			return LIGHTALLLEDONLAYER;
		case OFF:
			cube->off();
			return OFF;
		case LOOP:
			playInstructsLoop();
			return LOOP;
		case ITERATOR:
			playInstructsIterator(buf[1], buf[2], buf[3]);
			return ITERATOR;
		case ENDLOOP:
			return ENDLOOP;
		case DELAYPICTURE:
			cube->gl_timeToStay = buf[1];
			return DELAYPICTURE;
	}
}

void Interpreter::playInstructsLoop() {
	char i = 0x0;
	while (bufferInstruction[i][0] != ENDLOOP) {
		/* On compte le nombre d'instructions entre le rang 0 et le ENDLOOP
		 * Pour pouvoir lancer l'interpretation des instructions à partir de
		 * l'adresse de retour comprise dans le ENDLOOP
		 */
		i++;
	}
	/*
	 * On est sur le ENDLOOP, et on passe l'adresse de retour qu'il contient à la fonction
	 * pour le commencement de l'interpretation du LOOP
	 */
	i = bufferInstruction[i][1];

	while (true) {
		while (bufferInstruction[i][0] != ENDLOOP) {
			evaluateCodeOp(bufferInstruction[i]);
			i++;
		}
		i = bufferInstruction[i][1];
	}
}

void Interpreter::playInstructsIterator(int valFinish, int nbInstruct, int address) {
	for (char nbTour = 0; nbTour < valFinish-1; nbTour++) {
		for(int i = address; i <= (address+nbInstruct)-1; i++){
			evaluateCodeOp(bufferInstruction[i]);
		}
	}
}
