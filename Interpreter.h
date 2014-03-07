#ifndef MONITOR_h
#define MONITOR_h

#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include "LedCubeMonoExtended.h"
#include "codeOp.h"

#define TAILLE 400
#define LAYER_MASK(l) (uint16_t) (0b0000000010000000 >> l)

class Interpreter {
private:
	LedCubeMonoExtended *cube;

public:
	Interpreter(LedCubeMonoExtended const& c);

	uint16_t bufferInstruction[TAILLE];

	void interpret();
	char evaluateCodeOp(int address,uint16_t taille);
	void playInstructsLoop(int nbInstruct, int address);
	void playInstructsIterator(int valFinish, int nbInstruct, int address);
};

#endif;
