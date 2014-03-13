/*
 * BootLoader.h
 *
 *  Created on: 27 févr. 2014
 *      Author: Etudiants
 */

#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_
#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include <EEPROM.h>
#define TAILLE 400
#define CARACTERE_VIDE_EEPROM 0xFF

void initialize(uint16_t buf[TAILLE]);
void mainBootLoader(uint16_t buf[TAILLE]);
void defaultAnimation(uint16_t buf[TAILLE]);
void loadEEPROMDataInBuffer(uint16_t buf[TAILLE]);
bool transfer();
#endif /* BOOTLOADER_H_ */
