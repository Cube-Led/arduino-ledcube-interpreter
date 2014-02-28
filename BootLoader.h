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
#define TAILLE_BUFFER 6
#define MAX_INSTRUCT 42
#define CARACTERE_VIDE_EEPROM 0xFF

void transfer();
void initialize(uint16_t buf[MAX_INSTRUCT][TAILLE_BUFFER]);
void mainBootLoader(uint16_t buf[MAX_INSTRUCT][TAILLE_BUFFER]);
void defaultAnimation(uint16_t buf[MAX_INSTRUCT][TAILLE_BUFFER]);
void loadEEPROMDataInBuffer(uint16_t buf[MAX_INSTRUCT][TAILLE_BUFFER]);
void transfer();
#endif /* BOOTLOADER_H_ */
