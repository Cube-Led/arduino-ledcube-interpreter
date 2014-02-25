#ifndef CODE_OP_h
#define CODE_OP_h

#define OFF 0x30
#define DELAY 0x01 				/* NbMs. 			Soit un seul paramètre correspondant au nombre de millisecondes que nous voulons attendre */
#define LIGHTLAYER 0x02 		/* Layer Nb, 		Deux paramètres correspondant au numéro de la couche à allumer et le nombre que nous voulons afficher qui sera traduit en binaire */
#define LIGHTONELEDBYHISNUM 0x03 /* Layer numLed, 	Deux paramètres correspondant au numéro de la couche à allumer et au numéro de la led que nous voullons allumer */
#define LIGHTALLLEDONLAYER 0x04 /* Layer, 			un paramètre correspondant au numéro de la couche à allumer */
#define LOOP 0x05 				/* Aucun paramètre, Lancant la procédure d'acquisition des instructions à jouer en boucle */
#define ENDLOOP 0x06 			/* Aucun paramètre, stoppant la procédure d'acquisition précédemment lancée */
#define ITERATOR 0x07 			/* nbTour, un paramètre permettant de passer le nombre de tour que l'on veut faire */
#define ENDITERATOR 0x08 		/* Aucun paramètre */
#define DELAYPICTURE 0x09 		/* Time, un paramètre, le temps en millisecondes */

#endif;
