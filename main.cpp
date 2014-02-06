#include <string.h> 
#include "codeOp.h"
#include "Interpreter.h"
#include "LedCubeMono.h"


/* Constants */
#define CLK  5 // Yellow CLOCK
#define SDI 2 // Orange DATA
#define LE  3 // Green	LATCH
#define NB_LAYERS 4
#define SIZE_CUBE 4 /* It is here that we describe the size of our cube */

/* Initialization */
void setup() 
{
    Serial.begin(9600);
}


/******************************************************************
****************************MAIN PROGRAM***************************
******************************************************************/
void loop() 
{

	LedCubeMonoExtended cube(4, SDI, CLK, LE);
	Interpreter interpret = Interpreter(cube);
	while(true)
	{
		//cube.testCube(200);


		    interpret.interpret();
	}


}

int main(void)
{
        init();

        setup();

        for (;;)
                loop();

        return 0;
}


