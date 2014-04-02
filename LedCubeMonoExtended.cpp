#include "LedCubeMonoExtended.h"
#include <Arduino.h>

LedCubeMonoExtended::LedCubeMonoExtended(uint8_t numberOfLayers, uint8_t sdiPin, uint8_t clockPin, uint8_t latchPin) :
		LedCubeMono(numberOfLayers, sdiPin, clockPin, latchPin) {
}

LedCubeMonoExtended::LedCubeMonoExtended(uint8_t numberOfLayers, uint8_t sdiPin, uint8_t clockPin, uint8_t latchPin, uint8_t frameRate) :
		LedCubeMono(numberOfLayers, sdiPin, clockPin, latchPin, frameRate) {
}

void LedCubeMonoExtended::lightAllLedOnLayer(uint16_t layerNum) {
	uint16_t ledMask[4];
	ledMask[0] = bit(16) - 1;
	ledMask[1] = bit(16) - 1;
	ledMask[2] = bit(16) - 1;
	ledMask[3] = bit(16) - 1;
	drawLayer(LAYER_MASK(layerNum - 1), (uint16_t *) ledMask);
}

/* Function who light one LED by it number */
void LedCubeMonoExtended::lightOneLEDByHisNum(int layerNum, int num) {
	uint16_t ledMask[4];
	for(int i = 0; i<4;i++)
		ledMask[i] = 0;
	if(num <=16)
		ledMask[0] = bit(num-1);
	else if(num <= 32)
		ledMask[1] = bit(num-17);
	else if(num <= 48)
			ledMask[2] = bit(num-33);
	else if(num <= 64)
			ledMask[3] = bit(num-49);

	drawLayer(LAYER_MASK(layerNum - 1), (uint16_t *)ledMask);
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

void LedCubeMonoExtended::drawImage(unsigned long nbMili, uint16_t *frameMask) {
	unsigned long prec = millis();
	while (millis() < prec + nbMili) {
		drawFrame(frameMask);
		off();
	}
}
