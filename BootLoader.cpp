/*
 * BootLoader.cpp
 *
 *  Created on: 27 févr. 2014
 *      Author: Etudiants
 */

#include <BootLoader.h>

bool transferReussit = false;
int len;

void mainBootLoader(uint16_t buf[TAILLE]) {
	initialize(buf);
	len =0;
	transferReussit = transfer();
	if (transferReussit)
		Serial.write(0x31);
	else
		Serial.write(0x30);

	if(!transferReussit){
		if(EEPROM.read(0) != CARACTERE_VIDE_EEPROM)
		{
			loadEEPROMDataInBuffer(buf);
		}
		else
		{
			Serial.write(128);
			defaultAnimation(buf);
		}
	}
	else
	{
		loadEEPROMDataInBuffer(buf);
	}
}

void loadEEPROMDataInBuffer(uint16_t buf[TAILLE])
{
	uint16_t current;
	byte premierOctetLu = 0;
	byte deuxiemeOctetLu = 0;
	int count = 0;
	int numberOfFF = 0;
	int i=0;
	if (len == 0){
		len = TAILLE*2; //Si on a rien recu, on met len à la bonne taille pour ne pas bloquer la boucle suivante
	}
	while((count < TAILLE) && (count < len/2))
	{
		premierOctetLu = EEPROM.read(i);
		deuxiemeOctetLu = EEPROM.read(i+1);
		buf[count] = premierOctetLu;
		buf[count] = (buf[count] <<8) | deuxiemeOctetLu;
		i=i+2;
		Serial.write(buf[count]);
		if (buf[count] == 0xFFFF)
			numberOfFF +=2;
		else {
			numberOfFF = 0;
		}
		count++;
	}
	if (numberOfFF > 8){
		for(int k = 0; k < 4;  k++){
			buf[count - k] = 0x0;
		}
	}
}

void initialize(uint16_t buf[TAILLE]) {
	int i;
	for (i = 0 ; i < TAILLE ; i++)
	{
		buf[i] = 0;
	}
}

bool transfer() {
	int incomingByte = 0;
	int i = 0;
	len = 0;
	unsigned long prec = millis();

	while (1){
		while (Serial.available() == 0 )
		{
			if(millis() > prec + 5000)
				{return false;}
		}
	    incomingByte = Serial.read();
	    if (incomingByte == 0x02) break;
	}

	Serial.write(0x05);

	while (1){
		while (Serial.available() == 0);
		len = Serial.read();
		if (len > 0) break;
	}
	Serial.write(len);

	for (i = 0;i<len;i++)
	{
		while (Serial.available() == 0);
		incomingByte = Serial.read();
		EEPROM.write(i, incomingByte);
		Serial.write(incomingByte);
		delay(5);
	}
	Serial.write(0x12);
	Serial.write(0x10);
	/*delay(2000);
	for (i = 0;i<=len;i++)
	{
		incomingByte = EEPROM.read(i);
		Serial.write(incomingByte);
	}*/
	return true;
}

void defaultAnimation(uint16_t buf[TAILLE]) {
	buf[0] = 0x3;
	buf[1] = 0x5;
	buf[2] = 0x4;
	buf[3] = 0x4;

	buf[4] = 0x3;
	buf[5] = 0x2;
	buf[6] = 0x4;
	buf[7] = 0xF99F;

	buf[8] = 0x3;
	buf[9] = 0x2;
	buf[10] = 0x3;
	buf[11] = 0x9009;

	buf[12] = 0x3;
	buf[13] = 0x2;
	buf[14] = 0x2;
	buf[15] = 0x9009;

	buf[16] = 0x3;
	buf[17] = 0x2;
	buf[18] = 0x1;
	buf[19] = 0xF99F;

}
