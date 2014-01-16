/**
 * Game of Life (LedCubeStreaming app). 
 * 
 * Application that streams a conway's game-of-life to a 4x4x4 mono-colored LED cube.
 * Cells evolve at 1Hz, with the following rules :
 * - each cell has 6 neighbours (North, South, East, West, Up, Down)
 * - rows/columns/layers neighbour cells are considered modulo their size
 *   (the top neighbour of the top-left corner of the top layer is 
 *     the top-left corner of the bottom layer, ...)
 * - a living cell survives if and only if  3 of its neighbours are living
 * - a dead cell resurrects if and only if 1 or 2 of its neighbours are living
 */

import processing.serial.*;

/**
* Serial port name
*/
String SERIAL_PORT_NAME = "/dev/tty.usbserial-A4012Z3Q";

/**
* Baud rate
*/
int BAUD_RATE = 4800;

/**
* Milliseconds between two computations of GOL
*/
int EVOLUTION_PERIOD_IN_MILLIS = 1000;

/**
* Number of cells per row (or column or layer)
*/
int NUMBER_OF_CELLS_PER_ROW = 4;

/**
* Number of cells per layer (16 for a 4x4x4 cube)
*/
int NUMBER_OF_CELLS_PER_LAYER= NUMBER_OF_CELLS_PER_ROW * NUMBER_OF_CELLS_PER_ROW;

/**
* Number of cells per world (64 for a 4x4x4 cube)
*/
int NUMBER_OF_CELLS_PER_WORLD = NUMBER_OF_CELLS_PER_ROW*NUMBER_OF_CELLS_PER_ROW*NUMBER_OF_CELLS_PER_ROW;

/**
* Game-of-life world, and its initial state (layer by layer from bottom to top). First value is the bottom-left corner
* of the bottom layer. Last value is the top-right corner of the top layer.
*/
boolean[][][] world = 
{
  // Layer 1
  {
    // Row 1
    {true /* column 1 */, false /* column 2 */, false /* column 3 */, false /* column 4 */},
    // Row 2 
    {false, false, false, false},
    // Row 3 
    {false, false, false, false},
    // Row 4 
    {false, false, false, false}
  },
  // Layer 2
  {
    {true, true, true, true}, 
    {true, true, true, false}, 
    {true, true, true, true}, 
    {true, false, true, false}
  },
  // Layer 3
  {
    {false, false, false, false}, 
    {false, false, false, false}, 
    {false, false, false, false}, 
    {false, false, false, false}
  },
  // Layer 4
  {
    {false, false, false, false}, 
    {false, false, false, false}, 
    {false, false, false, false}, 
    {false, false, true, true}
  }
};

/**
* Swap buffer used for world computation
*/
boolean[][][] previousWorld;

/**
* Frame buffer. 
* First bit is bottom-left corner of the bottom layer, 
* last bit is the top-right corner of the top layer
*/
byte[] frameBuffer = new byte[NUMBER_OF_CELLS_PER_WORLD/8];

/**
* Serial port used to stream frames
*/
Serial serialPort;  

/**
* Internal method used to compute the sum of the living neighbours of a given cell.
* (when computing the next world, only cells from the previous world are taken into account)
*/
int sumOfLivingNeighbours(int row, int column, int layer)
{
  int sum = 0;
  if (previousWorld[layer][(row+1)%NUMBER_OF_CELLS_PER_ROW][column]) sum++;
  if (previousWorld[layer][(row-1+NUMBER_OF_CELLS_PER_ROW)%NUMBER_OF_CELLS_PER_ROW][column]) sum++;
  if (previousWorld[layer][row][(column+1)%NUMBER_OF_CELLS_PER_ROW]) sum++;
  if (previousWorld[layer][row][(column-1+NUMBER_OF_CELLS_PER_ROW)%NUMBER_OF_CELLS_PER_ROW]) sum++;
  if (previousWorld[(layer+1)%NUMBER_OF_CELLS_PER_ROW][row][column]) sum++;
  if (previousWorld[(layer-1+NUMBER_OF_CELLS_PER_ROW)%NUMBER_OF_CELLS_PER_ROW][row][column]) sum++;
  return sum;
}

/**
* Compute the evolution of the world
*/
void computeWorld()
{
  previousWorld = world;
  world = new boolean[NUMBER_OF_CELLS_PER_ROW][NUMBER_OF_CELLS_PER_ROW][NUMBER_OF_CELLS_PER_ROW];
  for (int layer=0; layer <NUMBER_OF_CELLS_PER_ROW; layer++)
  {
     for (int row = 0; row <NUMBER_OF_CELLS_PER_ROW; row ++)
     {
       for (int column = 0; column <NUMBER_OF_CELLS_PER_ROW; column ++)
       {
         int sum = sumOfLivingNeighbours(row, column, layer);
         if (previousWorld[layer][row][column])  
           world[layer][row][column] = (sum == 3) ;           
         else
           world[layer][row][column] = (sum == 1) || (sum == 2) ;
       }
     }
  }
}

/**
* Update the frame buffer so that it maps the current state of the world 
*/
void updateFrameBuffer()
{
  for (int layer=0; layer <NUMBER_OF_CELLS_PER_ROW; layer++)
     for (int row = 0; row <NUMBER_OF_CELLS_PER_ROW; row ++)
       for (int column = 0; column <NUMBER_OF_CELLS_PER_ROW; column ++)
       {
         int cellIndex = (layer*NUMBER_OF_CELLS_PER_LAYER)+(row*NUMBER_OF_CELLS_PER_ROW)+ column;
         int cellByteIndex = cellIndex / 8;
         int cellBitIndex = cellIndex % 8;
         if (world[layer][row][column])
           frameBuffer[cellByteIndex] |= (0x01 << (8 - cellBitIndex));          
         else
           frameBuffer[cellByteIndex] &= ~(0x01 << (8 - cellBitIndex));     
       }
}

/**
 * setup method, called once at startup
 */
void setup() 
{ 
  serialPort = new Serial(this, SERIAL_PORT_NAME, BAUD_RATE);
}

/**
 * draw method, called in loop endlessly
 */
void draw() 
{  
    while (true)
    {
      if (serialPort.available() > 0) 
      {     
      while (serialPort.available()>0) serialPort.read();
        updateFrameBuffer();
        serialPort.write(frameBuffer);
        computeWorld();             
      }
      delay(EVOLUTION_PERIOD_IN_MILLIS);
    }
}

