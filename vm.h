#ifndef WM_h
#define WM_h

void lightAllLedOnLayer(int layer);
void permutationCirculaire();
void update();
int transformCoordInNumberOfLED(int x, int y);
void testCube(int nbMillisec);
void lightOneLEDByHisNum(int layerNum, int num);
uint16_t lightLayer(int layerNum, int leds16);

#endif


