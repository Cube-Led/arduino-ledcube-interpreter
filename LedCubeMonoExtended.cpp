#include "LedCubeMonoExtended.h"
#include <Arduino.h>

LedCubeMonoExtended::LedCubeMonoExtended(uint8_t numberOfLayers, uint8_t sdiPin, uint8_t clockPin, uint8_t latchPin) :
		LedCubeMono(numberOfLayers, sdiPin, clockPin, latchPin) {
}

LedCubeMonoExtended::LedCubeMonoExtended(uint8_t numberOfLayers, uint8_t sdiPin, uint8_t clockPin, uint8_t latchPin, uint8_t frameRate) :
		LedCubeMono(numberOfLayers, sdiPin, clockPin, latchPin, frameRate) {
}

void LedCubeMonoExtended::lightAllLedOnLayer(uint16_t layerNum) {
	uint16_t mask = bit(16) - 1;
	drawLayer(LAYER_MASK(layerNum - 1), &mask);
}

/* Function who light one LED by it number */
void LedCubeMonoExtended::lightOneLEDByHisNum(int layerNum, int num) {
	uint16_t mask = bit(num - 1);
	drawLayer(LAYER_MASK(layerNum - 1), &mask);
}

/* Function who test the LED */
void LedCubeMonoExtended::testCube(int nbMillisec) {
	for (int layer = 1; layer <= this->numberOfLayers; layer++) {
		for (int led = 1; led <= (this->numberOfLayers * this->numberOfLayers);
				led++) {
			lightOneLEDByHisNum(layer, led);
			delay(nbMillisec);
		}
	}
}

void LedCubeMonoExtended::drawImage(int nbMili, uint16_t *frameMask) {
	long int prec = millis();
	while (millis() < prec + nbMili) {
		drawFrame(frameMask);
		off();
	}
}
