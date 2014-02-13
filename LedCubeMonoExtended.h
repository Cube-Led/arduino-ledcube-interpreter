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
	uint8_t gl_timeToStay;

	LedCubeMonoExtended(uint8_t numberOfLayers, uint8_t sdiPin, uint8_t clockPin, uint8_t latchPin, uint8_t frameRate);
	LedCubeMonoExtended(uint8_t numberOfLayers, uint8_t sdiPin, uint8_t clockPin, uint8_t latchPin);
	void lightOneLEDByHisNum(int layerNum, int num);
	void lightAllLedOnLayer(uint16_t layer);
	void permutationCirculaire();
	void testCube(int nbMillisec);
	void afficher(int timeout);
	void drawImage(int nbMili, uint16_t *frameMask);

};

#endif /* LEDCUBEMONOEXTENDED_H_ */
