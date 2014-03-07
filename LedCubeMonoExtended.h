/*
 * LedCubeMonoExtended.h
 *
 *  Created on: 3 févr. 2014
 *      Author: Etudiants
 */

#ifndef LEDCUBEMONOEXTENDED_H_
#define LEDCUBEMONOEXTENDED_H_

#include <inttypes.h>
#include "LedCubeMono.h"

#define LAYER_MASK(l) (uint16_t) (0b0000000010000000 >> l)

class LedCubeMonoExtended : public LedCubeMono
{
public :
	unsigned long gl_timeToStay;

	LedCubeMonoExtended(uint8_t numberOfLayers, uint8_t sdiPin, uint8_t clockPin, uint8_t latchPin);
	LedCubeMonoExtended(uint8_t numberOfLayers, uint8_t sdiPin, uint8_t clockPin, uint8_t latchPin, uint8_t frameRate);
	void lightOneLEDByHisNum(int layerNum, int num);
	void lightAllLedOnLayer(uint16_t layer);
	void permutationCirculaire();
	void testCube(int nbMillisec);
	void drawImage(unsigned long nbMili, uint16_t *frameMask);

};

#endif /* LEDCUBEMONOEXTENDED_H_ */
