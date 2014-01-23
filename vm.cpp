#include <string.h> 
#include "codeOp.h"
#include "Monitor.h"
#include "vm.h"
#include "LedCubeMono.h"

#define NB_LAYERS 4
#define SIZE_CUBE 4
/* Structures */
typedef struct image
{
  int layer;
  int numLed;
  
}image;


/* global variables */
image img;


/* Switch ON LED on a layer */
void lightAllLedOnLayer(int layer)
{
  lightLayer(layer, 65535);
}

/* Switch ON layers on loop */
void permutationCirculaire()
{
     if(img.layer != NB_LAYERS)
       img.layer++;
     else
       img.layer=1;
}

/* Refreshing display */
void update()
{
  for(int i =0; i < NB_LAYERS*NB_LAYERS;i++)
    lightLayer(img.layer, img.numLed);
}


/* Switch ON LED switch cube size */
int transformCoordInNumberOfLED(int x, int y)
{
  return ((x-1)*SIZE_CUBE+y);
}
  
/* Function who test the LED */
void testCube(int nbMillisec)
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
void lightOneLEDByHisNum(int layerNum, int num)
{
  lightLayer(layerNum, bit(num-1));
}
