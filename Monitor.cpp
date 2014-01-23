#include "Monitor.h"
#include "LedCubeMono.h"
#include "vm.h"


Monitor::Monitor(LedCubeMono const& c)
{
	cube = new LedCubeMono(c);
}

String saveInstruction[MAX_INSTRUCT];
int rangSaveInstructs, valBegin;
boolean firstLoop = true;

/* Buffer initialization */
void Monitor::initialiseBuffer(char buffer[TAILLE_BUFFER])
{
  for(int i=0; i < TAILLE_BUFFER; i++)
    buffer[i] = '\0';
}

/* Command transmission */
int Monitor::evaluateString(String str)
{
  int op = returnParameter(str,1).toInt();
  Serial.println(str);
  switch(op)
    {
      case DELAY :
          delay(returnParameter(str,2).toInt());
          return DELAY;
          break;
      case LIGHTLAYER :
          cube->lightLayer(returnParameter(str,2).toInt(), returnParameter(str,3).toInt());
          return LIGHTLAYER;
          break;
      case LIGHTONELEDBYHISNUM :
          lightOneLEDByHisNum(returnParameter(str,2).toInt(), returnParameter(str,3).toInt());
          return LIGHTONELEDBYHISNUM;
          break;
      case LIGHTALLLEBONLAYER :
          lightAllLedOnLayer(returnParameter(str,2).toInt());
          return LIGHTALLLEBONLAYER;
          break;
      case OFF : 
          cube->off();
          return OFF;
          break;
      case LOOP :Serial.println("Debut loop, envoyez 6 pour arreter et commencer l'animation");
      	  	  	  saveInstructs(0);
                playInstructsLoop();
          return LOOP;
          break;
      case ENDLOOP :
          return ENDLOOP;
          break;
      case FOR :
          Serial.println("Debut for, envoyez 6 pour arreter et commencer l'animation");
          boucleFor(returnParameter(str,2).toInt(), returnParameter(str,3), returnParameter(str,4).toInt(), returnParameter(str,5).toInt());
          return FOR;
          break;
   }
   Serial.println("Commande enregistree");
 }

void Monitor::initialiseSaveInstructs()
{
  for(int i=0; i<MAX_INSTRUCT; i++)
   saveInstruction[i] ='\0';  
}

/* Saving loop instructions */
void Monitor::saveInstructs(int valInit)
{
  String str;
  for(rangSaveInstructs=valInit; rangSaveInstructs<MAX_INSTRUCT; rangSaveInstructs++)
  {
    while((str = recoitChaine())[0] == '\0');
    
    saveInstruction[rangSaveInstructs] = str;
    str[0] = '\0';
    if(evaluateString(saveInstruction[rangSaveInstructs]) == ENDLOOP)
      break;
  }
}


/* Playing loop instructions */
void Monitor::playInstructsLoop()
{
  int i=0;
  boolean continuer = true;
  initialiseSaveInstructs();
  saveInstructs(i);
  while(continuer)
  {
   continuer = playInstructsOneLoopSaveInstruction(i);
   i=0;
  }
}

String Monitor::recoitChaine()
{
  String str;
  char buffer[TAILLE_BUFFER];
  size_t t = TAILLE_BUFFER;
      initialiseBuffer(buffer);
      Serial.readBytes(buffer, t);
      if(buffer[0] != '\0')
      {
        str = buffer;
      }
  return str;
}

/* Cube management */
void Monitor::runMonitor()
{
  char buffer[TAILLE_BUFFER];
  delay(1000);
    while(true)
    {
      //permutationCirculaire();
      //update();
      delay(1000);
      String str = recoitChaine();
      if(str[0] != '\0')
      {
        evaluateString(str);
      }
    }
}

void Monitor::boucleFor(int valInit, String condition, int borne, int increment)
{
  int i, j;
  if(firstLoop)
  {
    initialiseSaveInstructs();
    firstLoop = false;
    valBegin = 0;
  }
  else
  {
    valBegin = rangSaveInstructs+1;
  }
  saveInstructs(valBegin);
  if(condition == "<")
  {
      for(i=valInit; i < borne ; i +=increment)
        {
          playInstructsOneLoopSaveInstruction(valBegin);
        }
  }
  else if(condition == ">")
  {
      for(i=valInit; i > borne ; i +=increment)
        {
          playInstructsOneLoopSaveInstruction(valBegin);
        }
  }
  else if(condition == ">=")
  {
      for(i=valInit; i >= borne ; i +=increment)
        {
          playInstructsOneLoopSaveInstruction(valBegin);
        }
  }
  else
      for(i=valInit; i <= borne ; i +=increment)
        {
          playInstructsOneLoopSaveInstruction(valBegin);
        }  
}

boolean Monitor::playInstructsOneLoopSaveInstruction(int valBegin)
{
  String str = saveInstruction[i];
   int op = returnParameter(str,1).toInt();
   i=valBegin;
   while(op != ENDLOOP)
   {
     //Serial.println(saveInstruction[i]);
     str = saveInstruction[i];
     op = returnParameter(str,1).toInt(); //saveInstruction[i].substring(0,saveInstruction[i].indexOf(' ')).toInt();
     if(op != LOOP)
     evaluateString(saveInstruction[i]);
     Serial.setTimeout(3);
     if(recoitChaine()[0] != '\0')return false;
     i++;
   }  
   Serial.setTimeout(1000);
   return true;
}

/* Récupérer partie de chaine */
String Monitor::returnParameter(String action, int parameterNumber)
{
  int i;
  String str = action;
  for (i = 0 ; i < parameterNumber-1 ; i++)
  {
   str = str.substring(str.indexOf(' ')+1); 
  }
  str = str.substring(0, str.indexOf(' '));
  //Serial.println(str);
  return str;
}


