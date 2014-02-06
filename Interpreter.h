#ifndef MONITOR_h
#define MONITOR_h

#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include "LedCubeMonoExtended.h"
#include "codeOp.h"


#define TAILLE_BUFFER 5
#define MAX_INSTRUCT 30

using namespace std;
class Interpreter
{
  private : int i;
  	  	  	  LedCubeMonoExtended *cube;
  
  public : Interpreter(LedCubeMonoExtended const& c);


  	  	void initialiseSimpleBuffer(char buf[TAILLE_BUFFER]);
  		/* Fonction initialisant un buffer à deux dimensions pour la reception d'une ligne de commande dans une boucle */
  		void initialiseDoubleBuffer(char buf[MAX_INSTRUCT][TAILLE_BUFFER]);
  		/* Fonction traduisant le contenu du buffer recu sur le lien serie, En une chaine de caractere */
  		void recoitInstruction();
  		/* Fonction ecoutant le lien serie et permettant l'execution des lignes de commandes transmises */
  		void interpret();
  		/* Fonction permettant de connaitre quelle instruction a ete envoye
  		   En cela, la fonction renvoie un code permettant d'execution la fonction associee*/
  		char evaluateCodeOp(char buf[]);
  		/* Fonction faisant un "tour du tableau", a partir de la valeur passee en parametre,
  		   Jusqu'a la premiere instruction ENDLOOP */
  		boolean playInstructsOneLoopSaveInstruction();
  		/* Fonction jouant un tour de boucle du while,
  		   Toutes les instructions entre le rang de départ et le ENDITERATOR sont executées*/
  		void playInstrucsOneWhileSaveInstruction(char valBegin);
  		/* Fonction qui execute les instructions stockees dans le tableau de sauvegarde,
  		   Et ce en boucle infiniment jusqu'a ce que l'on envoie un caractere */
  		void playInstructsLoop();
  		/* Fonction qui execute des instructions un certains nombre de fois,
  		   Donné en paramètre de la fonction */
  		void playInstructsWhile(char valFinish);
};

#endif;
