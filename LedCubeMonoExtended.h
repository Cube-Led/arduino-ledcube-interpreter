/*
 * LedCubeMonoExtended.h
 *
 *  Created on: 3 févr. 2014
 *      Author: Etudiants
 */

#ifndef LEDCUBEMONOEXTENDED_H_
#define LEDCUBEMONOEXTENDED_H_


#include "LedCubeMono.h"

class LedCubeMonoExtended : public LedCubeMono
{
public :
	LedCubeMonoExtended(uint8_t numberOfLayers, uint8_t sdiPin, uint8_t clockPin, uint8_t latchPin, uint8_t frameRate);
	LedCubeMonoExtended(uint8_t numberOfLayers, uint8_t sdiPin, uint8_t clockPin, uint8_t latchPin);
	int transformCoordInNumberOfLED(int x, int y);
	void lightOneLEDByHisNum(int layerNum, int num);
	void lightAllLedOnLayer(uint16_t layer);
	void permutationCirculaire();
	void testCube(int nbMillisec);
	void afficher();

};

#endif /* LEDCUBEMONOEXTENDED_H_ */
