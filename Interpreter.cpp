#include "Interpreter.h"
#include "LedCubeMonoExtended.h"


Interpreter::Interpreter(LedCubeMonoExtended const& c)
{
	cube = new LedCubeMonoExtended(c);
}

char gl_rangSaveInstruction = 0x0;
int gl_countIterator = 0;
char gl_buffer[TAILLE_BUFFER];
char bufferLoop[MAX_INSTRUCT][TAILLE_BUFFER];

/* ****************************************************************************************************
   ****************************************************************************************************
   ****************************************************************************************************
                Algorithme concernant la reception des instructions transmises par la console
   ****************************************************************************************************
   ****************************************************************************************************
   **************************************************************************************************** */

/* Fonction initialisant un buffer à une dimension pour la reception d'une ligne de commande */
void Interpreter::initialiseSimpleBuffer(char buf[TAILLE_BUFFER])
{
  for(int i=0; i < TAILLE_BUFFER; i++)
	  buf[i] = 0x0;
}


/* Fonction initialisant un buffer à deux dimensions pour la reception d'une ligne de commande dans une boucle */
void Interpreter::initialiseDoubleBuffer(char buf[MAX_INSTRUCT][TAILLE_BUFFER])
{
  for(int i = 0; i < MAX_INSTRUCT; i++)
	for(int j = 0; j < TAILLE_BUFFER; j++)
		buf[i][j] = 0x0;
}


/* Fonction traduisant le contenu du buffer recu sur le lien serie,
   En une chaine de caractere */
void Interpreter::recoitInstruction()
{
      initialiseSimpleBuffer(gl_buffer);
      Serial.readBytes(gl_buffer, TAILLE_BUFFER);
}



/* Fonction ecoutant le lien serie et permettant l'execution des lignes de commandes transmises */
void Interpreter::interpret()
{
	initialiseSimpleBuffer(gl_buffer);

	/*bufferLoop[0][0] = 0x05;  // CodeOp du loop
	//bufferLoop[0][0] = 0x07;  // CodeOp du iterator
	//bufferLoop[0][1] = 0x04;
	bufferLoop[1][0] = 0x09;
	bufferLoop[1][1] = 0x64;
	bufferLoop[2][0] = 0x04;
	bufferLoop[2][1] = 0x04;
	bufferLoop[3][0] = 0x04;
	bufferLoop[3][1] = 0x03;
	bufferLoop[4][0] = 0x04;
	bufferLoop[4][1] = 0x02;
	bufferLoop[5][0] = 0x04;
	bufferLoop[5][1] = 0x01;
	bufferLoop[6][0] = 0x06;  // CodeOp Fin Loop
	//bufferLoop[6][0] = 0x08; // CodeOp Fin iterator
	gl_rangSaveInstruction = 0x00;  // Adresse Retour du iterator
	*/

	bufferLoop[0][0] = 0x05;
	/*bufferLoop[1][0] = 0x03; // lightOneLEDByHisNum(3, 4)
	bufferLoop[1][1] = 0x03;
	bufferLoop[1][2] = 0x08;*/
	/*bufferLoop[2][0] = 0x03; // lightOneLEDByHisNum(2,16)
	bufferLoop[2][1] = 0x02;
	bufferLoop[2][2] = 0x0F;*/
	bufferLoop[1][0] = 0x04;
	bufferLoop[1][1] = 0x04;
	bufferLoop[2][0] = 0x02;
	bufferLoop[2][1] = 0x01;
	bufferLoop[2][2] = 0x88;
	bufferLoop[3][0] = 0x03;
	bufferLoop[3][1] = 0x03;
	bufferLoop[3][2] = 0x0B;
	bufferLoop[4][0] = 0x04;
	bufferLoop[4][1] = 0x02;
	bufferLoop[5][0] = 0x06;

	evaluateCodeOp(bufferLoop[0],0);
	/*
    while(true)
    {
    	delay(250);
    	evaluateCodeOp(bufferLoop[0],0);
    }
    */
}




/* Fonction permettant de connaitre quelle instruction a ete envoye
   En cela, la fonction renvoie un code permettant d'execution la fonction associee*/
char Interpreter::evaluateCodeOp(char buf[], int rangInstruction)
{
	uint16_t layer;
	uint16_t ledMask[2];
	int led;
  switch(buf[0])
    {
		case DELAY :
			delay(buf[1]*256+buf[2]);
			return DELAY;
		case LIGHTLAYER :
			layer = buf[1];
			ledMask[0] = buf[2];
			ledMask[1] = buf[3];
			cube->drawLayer(layer,ledMask);
			return LIGHTLAYER;
		case LIGHTONELEDBYHISNUM :
			layer = buf[1];
			led = buf[2];
			cube->lightOneLEDByHisNum(layer, led);
			return LIGHTONELEDBYHISNUM;
		case LIGHTALLLEDONLAYER :
			layer = buf[1];
			cube->lightAllLedOnLayer(layer);
			return LIGHTALLLEDONLAYER;
		case OFF :
			cube->off();
			return OFF;
		case LOOP :
			Serial.println("Debut loop, envoyez 6 pour arreter et commencer l'animation");
			playInstructsLoop();
			return LOOP;
		case ITERATOR :
			Serial.println("Debut iterator, envoyez 9 pour arreter et commencer l'animation");
			gl_countIterator++;
			gl_rangSaveInstruction = rangInstruction;
			playInstructsWhile(buf[1]);
			return ITERATOR;
		case ENDLOOP :
			Serial.println("Fin du loop");
			return ENDLOOP;
		case ENDITERATOR :
			Serial.println("Fin du iterator");
			gl_countIterator--;
			return ENDITERATOR;
		case DELAYPICTURE :
			cube->gl_timeToStay = buf[1];
			return DELAYPICTURE;
		}
 }



/* Fonction faisant un "tour du tableau", a partir de la valeur passee en parametre,
   Jusqu'a la premiere instruction ENDLOOP */
boolean Interpreter::playInstructsOneLoopSaveInstruction()
{
   byte i = 0x0;
   char str[TAILLE_BUFFER];
   for(int j =0; j<TAILLE_BUFFER; j++)
	   str[j] = bufferLoop[i][j];
   while(str[0] != ENDLOOP)
   {
	   for(int j =0; j<TAILLE_BUFFER; j++)
	   	   str[j] = bufferLoop[i][j];
	   if(str[0] != LOOP)
		   evaluateCodeOp(bufferLoop[i],i);
	   Serial.setTimeout(3);
	   recoitInstruction();
	   if(gl_buffer[0] != 0x0)return false;
	   i++;
   }  
   Serial.setTimeout(1000);
   return true;
}

/* Fonction jouant un tour de boucle du while,
   Toutes les instructions entre le rang de départ et le ENDITERATOR sont executées*/
void Interpreter::playInstrucsOneWhileSaveInstruction(char valBegin)
{
   char i = valBegin;
   char str[TAILLE_BUFFER];
   for(int j =0; j<TAILLE_BUFFER; j++)
   	   str[j] = bufferLoop[i][j];
   while(str[0] != ENDITERATOR)
   {
	   for(int j =0; j<TAILLE_BUFFER; j++)
	   	   str[j] = bufferLoop[i][j];
	   if(str[0] != ITERATOR)
		   evaluateCodeOp(bufferLoop[i],i);
	   i++;
   }
}

/* Fonction qui execute les instructions stockees dans le tableau de sauvegarde,
   Et ce en boucle infiniment jusqu'a ce que l'on envoie un caractere */
void Interpreter::playInstructsLoop()
{
  boolean continuer = true;
  //initialiseDoubleBuffer(bufferLoop);
  while(continuer)
  {
   continuer = playInstructsOneLoopSaveInstruction();
  }
}

/* Fonction qui execute des instructions un certains nombre de fois,
   Donné en paramètre de la fonction */
void Interpreter::playInstructsWhile(char valFinish)
{
  String msg = "On est au tour ";
  String msgResult;
  char valBegin = gl_rangSaveInstruction;
  for(char valWhile =0; valWhile < valFinish; valWhile++)
  {
    msgResult = msg + (valWhile+1);
    Serial.println(msgResult);
    playInstrucsOneWhileSaveInstruction(valBegin);
  }
}
