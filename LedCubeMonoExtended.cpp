#include "LedCubeMonoExtended.h"
#include <Arduino.h>

/**
* Alias for a blank 16 bits mask
*/
#define ZERO_FILLED_REGISTER (uint16_t) 0b0000000000000000
#define ONE_FILLED_REGISTER (uint16_t) 0b1111111111111111

uint16_t imageLayer[] =
	  { 0b1000000000000000, 0b0000000000000000, 0b0000000000000000,
	      0b0000000000000000 };

LedCubeMonoExtended::LedCubeMonoExtended(uint8_t numberOfLayers, uint8_t sdiPin, uint8_t clockPin, uint8_t latchPin) : LedCubeMono(numberOfLayers, sdiPin, clockPin, latchPin)
{

}

LedCubeMonoExtended::LedCubeMonoExtended(uint8_t numberOfLayers, uint8_t sdiPin, uint8_t clockPin, uint8_t latchPin, uint8_t frameRate) : LedCubeMono(numberOfLayers, sdiPin, clockPin, latchPin, frameRate)
{

}

void LedCubeMonoExtended::afficher()
{
	drawFrame(imageLayer);
}

void LedCubeMonoExtended::lightAllLedOnLayer(uint16_t layer)
{
	uint16_t allLed[] =
	  { ZERO_FILLED_REGISTER, ZERO_FILLED_REGISTER, ZERO_FILLED_REGISTER, ZERO_FILLED_REGISTER};
	allLed[layer-1] = ONE_FILLED_REGISTER;
	drawFrame(allLed);
	allLed[layer-1] = ZERO_FILLED_REGISTER;
}

/* Switch ON layers on loop */
void LedCubeMonoExtended::permutationCirculaire()
{
	for(int i =0; i < this->numberOfLayers; i++)
	{
		imageLayer[(i+1)%this->numberOfLayers] = imageLayer[i];
	}
}


/* Switch ON LED switch cube size */
int LedCubeMonoExtended::transformCoordInNumberOfLED(int x, int y)
{
  return ((x-1)*numberOfLayers+y);
}

/* Function who test the LED */
void LedCubeMonoExtended::testCube(int nbMillisec)
{
   for (int layer=1;layer<=4; layer++)
   {
       for (int led=1;led <17;led++)
       {
         lightOneLEDByHisNum(layer, led);
         delay (nbMillisec);
       }
   }
}

/* Function who light one LED by it number */
void LedCubeMonoExtended::lightOneLEDByHisNum(int layerNum, int num)
{

	int temp = (layerNum-1) * numberOfLayers * numberOfLayers + num;
	int sizeLayer = numberOfLayers*numberOfLayers;
	for(int i=0; i< this->numberOfLayers; i++)
	{
		if(temp <= sizeLayer)
		{
			imageLayer[i] = bit(sizeLayer -1);
			imageLayer[i] = imageLayer[i] >> sizeLayer-temp;
			break;
		}
		else
		{
			temp = temp - sizeLayer;
			imageLayer[i] = 0;
		}
	}

  drawFrame(imageLayer);
}
