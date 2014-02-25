#include "Interpreter.h"
#include "LedCubeMonoExtended.h"

Interpreter::Interpreter(LedCubeMonoExtended const& c) {
	cube = new LedCubeMonoExtended(c);
}


void Interpreter::interpret() {
	bufferInstruction[0][0] = 0x05;  // CodeOp du loop
	bufferInstruction[1][0] = 0x30;
	bufferInstruction[2][0] = 0x02;  //LightLayer sur
	bufferInstruction[2][1] = 0x04;  //couche 4
	bufferInstruction[2][2] = 0xFFF;  //nombre 129 en decimal
	bufferInstruction[3][0] = 0x02;  //LightLayer sur
	bufferInstruction[3][1] = 0x01;  //couche 1
	bufferInstruction[3][2] = 0x10;  //nombre 126 en decimal
	bufferInstruction[4][0] = 0x06;  // CodeOp Fin Loop
	gl_rangSaveInstruction = 0x00;  // Adresse Retour du iterator

	evaluateCodeOp(bufferInstruction[0]);
}

char Interpreter::evaluateCodeOp(uint16_t buf[]) {
	uint16_t layer;
	uint16_t ledMask[2];
	int led;

	switch (buf[0]) {
		case DELAY:
			delay(buf[1] + buf[2] * 256);
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
			playInstructsIterator(buf[1]);
			return ITERATOR;
		case ENDLOOP:
			return ENDLOOP;
		case ENDITERATOR:
			return ENDITERATOR;
		case DELAYPICTURE:
			cube->gl_timeToStay = buf[1];
			return DELAYPICTURE;
	}
}

void Interpreter::playInstructsLoop() {
	char i = 0x1;
	while (true) {
		while (bufferInstruction[i][0] != ENDLOOP) {
			evaluateCodeOp(bufferInstruction[i]);
			i++;
		}
		i = 0x1;
	}
}

void Interpreter::playInstructsIterator(char valFinish) {
	char valBegin = gl_rangSaveInstruction;
	char i = valBegin;
	for (char nbTour = 0; nbTour < valFinish; nbTour++) {
		while (bufferInstruction[i][0] != ENDITERATOR) {
			evaluateCodeOp(bufferInstruction[i]);
			i++;
		}
		i = valBegin;
	}
}
