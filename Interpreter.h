#ifndef MONITOR_h
#define MONITOR_h

#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include "LedCubeMonoExtended.h"
#include "codeOp.h"

#define TAILLE_BUFFER 6
#define MAX_INSTRUCT 42
#define LAYER_MASK(l) (uint16_t) (0b0000000010000000 >> l)

class Interpreter {
private:
	LedCubeMonoExtended *cube;

public:
	Interpreter(LedCubeMonoExtended const& c);

	uint16_t gl_buffer[TAILLE_BUFFER];
	uint16_t bufferInstruction[MAX_INSTRUCT][TAILLE_BUFFER];

	void interpret();
	char evaluateCodeOp(uint16_t buf[]);
	void playInstructsLoop();
	void playInstructsIterator(int valFinish, int nbInstruct, int address);
};

#endif;
