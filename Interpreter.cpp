#include "Interpreter.h"
#include "LedCubeMonoExtended.h"

Interpreter::Interpreter(LedCubeMonoExtended const& c) {
	cube = new LedCubeMonoExtended(c);
}

void Interpreter::interpret() {

	int i = 0;
	while (true) {
		evaluateCodeOp(i + 1, bufferInstruction[i]);
		i+=(bufferInstruction[i]+1);
	}
}

char Interpreter::evaluateCodeOp(int address, uint16_t taille) {
	uint16_t layer;
	uint16_t ledMask[4];
	for(int tab =0; tab < 4; tab++)
		ledMask[tab]=0x0;

	uint16_t led;

	long milli;
	int taille_mask;
	switch (bufferInstruction[address]) {
	case DELAY:
		milli = 0;
		if (taille = 2)
			milli = bufferInstruction[address + 1];
		else
			milli = bufferInstruction[address + 1]
					+ bufferInstruction[address + 2] * bit(16);

		delay(milli);
		return DELAY;
	case LIGHTLAYER:
		layer = bufferInstruction[address + 1];
		taille_mask = taille - 2;
		for (int i = 2; i <= (1 + taille_mask); i++) {
			ledMask[i - 2] = bufferInstruction[address + i];
		}
		cube->drawLayer(LAYER_MASK(layer - 1), (uint16_t *) ledMask);
		return LIGHTLAYER;
	case LIGHTONELEDBYHISNUM:
		layer = bufferInstruction[address + 1];
		led = bufferInstruction[address + 2];
		cube->lightOneLEDByHisNum(layer, led);
		return LIGHTONELEDBYHISNUM;
	case LIGHTALLLEDONLAYER:
		layer = bufferInstruction[address + 1];
		cube->lightAllLedOnLayer(layer);
		return LIGHTALLLEDONLAYER;
	case OFF:
		cube->off();
		return OFF;
	case LOOP:
		playInstructsLoop(bufferInstruction[address + 1], bufferInstruction[address + 2]);
		return LOOP;
	case ITERATOR:
		playInstructsIterator(bufferInstruction[address + 1], bufferInstruction[address + 2], bufferInstruction[address + 3]);
		return ITERATOR;
	}
}

void Interpreter::playInstructsLoop(int nbInstruct, int address) {
	int i = address;
	while (true) {
		i = address;
		for (int count = 0; count < nbInstruct; count++) {
			evaluateCodeOp(i+1, bufferInstruction[i]);
			i += (bufferInstruction[i] + 1);
		}
	}
}

void Interpreter::playInstructsIterator(int valFinish, int nbInstruct, int address) {
	int i = address;
	for (char nbTour = 0; nbTour < valFinish - 1; nbTour++) {
		i = address;
		for (int count = 0; count < nbInstruct; count++) {
			evaluateCodeOp(i + 1, bufferInstruction[i]);
			i += (bufferInstruction[i] + 1);
		}
	}
}
