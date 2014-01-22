#ifndef MONITOR_h
#define MONITOR_h

#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include "LedCubeMono.h"
#include "codeOp.h"


#define TAILLE_BUFFER 30
#define MAX_INSTRUCT 30

using namespace std;
class Monitor
{
  private : int i;
  LedCubeMono::LedCubeMono *cube;
  
  public : Monitor(LedCubeMono &c);

          /* Buffer initialization */
          void initialiseBuffer(char buffer[TAILLE_BUFFER]);
          
          /* Command transmission */
          int evaluateString(String str);
          
          /* Saving loop instructions */
          void saveInstructs(int valBegin);
          
          /* Playing loop instructions */
          void playInstructsLoop();
          
          /* Cube management */
          void runMonitor();
          
          String recoitChaine();
          
          boolean playInstructsOneLoopSaveInstruction(int valBegin);
          
          void boucleFor(int valInit, String condition, int borne, int increment);
          
          String returnParameter(String action, int parameterNumber);
          
         void initialiseSaveInstructs();
};

#endif;
