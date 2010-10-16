/* -*- tab-width: 4 -*- */

/*

SoOnCon Badge Test Program

Copyright (C) 2010 Jonathan Lamothe <jonathan@jlamothe.net>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see: http://www.gnu.org/licenses/

*/

#include "SoonCon2010Badge.h"

#define BLINK_TIME 200
#define TIMEOUT 2000
#define NUM_SWITCHES 4

const int button[] = { SWITCH_1, SWITCH_2, SWITCH_0, SWITCH_4 };

void blink(unsigned n)
{
  int i = 0;
  for(i = 0; i < n; i++)
	{
	  digitalWrite(LIGHT_1_RED, HIGH);
	  delay(BLINK_TIME);
	  digitalWrite(LIGHT_1_RED, LOW);
	  delay(BLINK_TIME);
	}
  delay(TIMEOUT);
}

void setup()
{

  /* Set the inputs: */
  pinMode(SWITCH_0, INPUT);
  pinMode(SWITCH_1, INPUT);
  pinMode(SWITCH_2, INPUT);
  pinMode(SWITCH_4, INPUT);

  /* Set the outputs: */
  pinMode(LIGHT_1_RED, OUTPUT);
  pinMode(LIGHT_1_GREEN, OUTPUT);
  pinMode(LIGHT_1_BLUE, OUTPUT);
  pinMode(LIGHT_2_RED, OUTPUT);
  pinMode(LIGHT_2_GREEN, OUTPUT);
  pinMode(LIGHT_2_BLUE, OUTPUT);
  digitalWrite(LIGHT_1_RED, LOW);
  digitalWrite(LIGHT_1_GREEN, LOW);
  digitalWrite(LIGHT_1_BLUE, LOW);
  digitalWrite(LIGHT_2_RED, LOW);
  digitalWrite(LIGHT_2_GREEN, LOW);
  digitalWrite(LIGHT_2_BLUE, LOW);

}

void loop()
{
  int i = 0;
  for(i = 0; i < NUM_SWITCHES; i++)
	if(digitalRead(button[i]) == LOW)
	  blink(i + 1);
}

/* jl */
