/*
 * Copyright (c) 2013 Sebastien Jean.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU Lesser Public License v3.0
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/lgpl-3.0.html
 *
 * Contributors:
 *     Sebastien Jean - initial API and implementation
 */

/**
 * Test application for LedCubeMono library. This application waits from individual
 * frames on serial line at 4800 bauds. Each frame is supposed to be sent as raw byte sequence
 * (e.g. for a 4x4x4 cube, 8 bytes are sent, each couple of bytes representing a layer, ordered from
 * bottom to top). Each frame is acknowledged with a single byte, and displayed once
 * (with a supposed framerate of 50 FPS). If no other frame is received, the current frame is displayed
 * again.
 *
 * @author S.jean
 * @date dec. 2013
 */
#include <Arduino.h>
#include <LedCubeMono.h>

/**
 *  LED Cube SDI pin
 */
#define SDI_PIN 2

/**
 *  LED Cube Clock pin
 */
#define CLOCK_PIN 5

/**
 *  LED Cube Latch pin
 */
#define LATCH_PIN 3

#define THE_ANSWER (uint8_t) 0x42

#define BAUD_RATE 4800

#define FRAME_BYTE_SIZE 8

/**
 * FSK modulator instance
 */
LedCubeMono cube(4, SDI_PIN, CLOCK_PIN, LATCH_PIN);

uint16_t imageBuffer[] =
  { 0b00000000000000000, 0b00000000000000000, 0b00000000000000000,
      0b00000000000000000 };

/**
 * Arduino's setup function, called once at startup, after init
 */
void
setup()
{
  Serial.begin(BAUD_RATE);
  cube.off();
  Serial.write(THE_ANSWER);
}

/**
 * Arduino's loop function, called in loop (incredible, isn't it ?)
 */
void
loop() // run over and over
{
  if (Serial.available() == FRAME_BYTE_SIZE)
    {
      Serial.readBytes((char *) imageBuffer, FRAME_BYTE_SIZE);
      Serial.write(THE_ANSWER);
    }
  cube.drawFrame((uint16_t *) imageBuffer);
}

/**
 * Application's main (what else to say?)
 * @return (never)
 */
int main(void)
{
        init();

        setup();

        for (;;)
                loop();

        return 0;
}
