/*
 * BootLoader.cpp
 *
 *  Created on: 27 févr. 2014
 *      Author: Etudiants
 */

#include <BootLoader.h>

void mainBootLoader(uint16_t buf[MAX_INSTRUCT][TAILLE_BUFFER]) {

	initialize(buf);
	if(Serial.available())
	{
		//Serial.println("lien serie ok");
		transfer();
		loadEEPROMDataInBuffer(buf);
	}
	else
	{
		Serial.println("on va ecrire");
		if(EEPROM.read(0) != CARACTERE_VIDE_EEPROM)
		{
			Serial.println("eeprom non vide");
			loadEEPROMDataInBuffer(buf);
		}
		else
		{
			defaultAnimation(buf);
		}
	}
}

void loadEEPROMDataInBuffer(uint16_t buf[MAX_INSTRUCT][TAILLE_BUFFER])
{
	uint16_t current;
	byte premierOctetLu = 0;
	byte deuxiemeOctetLu = 0;
	int count = 0;
	while(count < MAX_INSTRUCT && (premierOctetLu != 0xFF && deuxiemeOctetLu != 0xFF))
	{
		for(int i = 0; i < TAILLE_BUFFER*2; i+=2)
		{
			current = 0;
			premierOctetLu = EEPROM.read(i);
			deuxiemeOctetLu = EEPROM.read(i+1);
			current = deuxiemeOctetLu << 8;
			current = current || premierOctetLu;
			buf[count][i/2] = current;
		}
		count++;
	}
}

void initialize(uint16_t buf[MAX_INSTRUCT][TAILLE_BUFFER]) {
	int i, j;
	for (i = 0 ; i < MAX_INSTRUCT ; i++)
	{
		for (j = 0 ; j < TAILLE_BUFFER ; j++)
		{
			buf[i][j] = 0x0;
		}
	}
}

void transfer() {
	int i = 0;
	Serial.println("transfer");
	Serial.setTimeout(5000);
	int r=1;
	while (r > 0) {
		Serial.println(Serial.read());
		EEPROM.write(i, 0xFF);
		i++;
	}
}

void defaultAnimation(uint16_t buf[MAX_INSTRUCT][TAILLE_BUFFER]) {
	    buf[0][0] = 0x5;
	    buf[1][0] = 0x2;
	    buf[1][1] = 0x4;
	    buf[1][2] = 0xF99F;
	    buf[2][0] = 0x1;
	    buf[2][1] = 0x4;
	    buf[3][0] = 0x2;
	    buf[3][1] = 0x3;
	    buf[3][2] = 0x9009;
	    buf[4][0] = 0x1;
	    buf[4][1] = 0x4;
	    buf[5][0] = 0x2;
	    buf[5][1] = 0x2;
	    buf[5][2] = 0x9009;
	    buf[6][0] = 0x1;
	    buf[6][1] = 0x4;
	    buf[7][0] = 0x2;
	    buf[7][1] = 0x1;
	    buf[7][2] = 0xF99F;
	    buf[8][0] = 0x1;
	    buf[8][1] = 0x4;
	    buf[9][0] = 0x6;
	    buf[9][1] = 0x1;
}
