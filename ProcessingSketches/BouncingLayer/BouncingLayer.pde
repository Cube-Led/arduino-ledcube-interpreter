/**
 * Bouncing layer (LedCubeStreaming app). 
 * 
 * Application that streams a bouncing layer to a 4x4x4 mono-colored LED cube.
 * All LEDS on the bouncing layer are lit, the layer bounces on bottom and top, moving at 1Hz.
 */
 
import processing.serial.*;

/**
* Serial port name
*/
String PORT_NAME = "/dev/tty.usbserial-A4012Z3Q";

/**
* Baud rate
*/
int BAUD_RATE = 4800;

/**
* Milliseconds between two layer changes
*/
int BOUNCING_PERIOD_IN_MILLIS = 1000;

/**
* Milliseconds of sleep time at boot
* (this is used to let Arduino boot and send the ACK byte)
*/
int BOOT_PAUSE_IN_MILLIS = 1000;

/**
* Layers frames to stream, order from bottom to top
*/
byte[][] LAYERS = 
{
  {(byte)0xFF, (byte)0xFF, (byte)0x00, (byte)0x00, (byte)0x00, (byte)0x00, (byte)0x00, (byte)0x00},
  {(byte)0x00, (byte)0x00, (byte)0xFF, (byte)0xFF, (byte)0x00, (byte)0x00, (byte)0x00, (byte)0x00},
  {(byte)0x00, (byte)0x00, (byte)0x00, (byte)0x00, (byte)0xFF, (byte)0xFF, (byte)0x00, (byte)0x00},
  {(byte)0x00, (byte)0x00, (byte)0x00, (byte)0x00, (byte)0x00, (byte)0x00, (byte)0xFF, (byte)0xFF}
};

/**
* Serial port used to stream frames
*/
Serial serialPort;

/**
* Current number of the layer to light on
*/
int layerNumber;

/**
* Moving direction of the lit layer
*/
boolean fromBottomToTop;

/**
 * setup method, called once at startup
 */
void setup() 
{
  serialPort = new Serial(this, PORT_NAME, BAUD_RATE);
  layerNumber = 0;
  fromBottomToTop = true;
  delay(BOOT_PAUSE_IN_MILLIS);
}

/**
 * draw method, called in loop endlessly
 */
void draw() 
{  
    if (serialPort.available() > 0) 
    {     
      while (serialPort.available()>0) serialPort.read();
      
      // stream frame 
      serialPort.write(LAYERS[layerNumber]);
      
      // handle bouncing
      if (fromBottomToTop)
      {
        if (layerNumber == LAYERS.length-1) 
        {
          fromBottomToTop = false;
          layerNumber--;
        }    
        else 
        {
          layerNumber++;
        }
      }
      else
      {
         if (layerNumber == 0) 
        {
          fromBottomToTop = true;
          layerNumber++;
        }    
        else 
        {
          layerNumber--;
        }
      }     
      
      // wait a little bit
      delay(BOUNCING_PERIOD_IN_MILLIS);
    }
}

