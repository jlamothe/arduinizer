/* -*- tab-width: 4 -*- */

/*

Alternate SoOnCon Badge Program

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

#define DUTY_CYCLE 200			/* The duty cycle of the blink. */
#define PERIOD1	2000   			/* The period of the first LED. */
#define PERIOD2	2050			/* The period of the second LED. */

#define CLR_CHG_TIME 100		/* The timeout between colour
								   changes. */

byte red,						/* The red intensity. */
  green,						/* The green intensity. */
  blue;							/* The blue intensity. */

unsigned last_colour_change;	/* Last time at which the colour was
								   changed. */

enum
  {
	red_increase,				/* Red increasing in intensity. */
	red_decrease,				/* Red decreaseing in intensity. */
	green_increase,				/* Green increasing in intensity. */
	green_decrease,				/* Green decreasing in intensity. */
	blue_increase,				/* Blue increasing in intensity. */
	blue_decrease				/* Blue decreasing in intensity. */
  } state;						/* The colour change state. */

/* Calculates the LED colour: */
void set_colour()
{
  unsigned time = millis();

  /* Make sure enough time has elapsed before changing the colour
	 again: */
  if(time < last_colour_change + CLR_CHG_TIME)
	return;
  last_colour_change = time;

  /* Colour change state: */
  switch(state)
	{

	  /* Red increasing: */
	case red_increase:
	  red++;
	  if(red == 0xff)
		state = blue_decrease;
	  break;

	  /* Red decreasing: */
	case red_decrease:
	  red--;
	  if(red == 0)
		state = blue_increase;
	  break;

	  /* Green increasing: */
	case green_increase:
	  green++;
	  if(green == 0xff)
		state = red_decrease;
	  break;

	  /* Green decreasing: */
	case green_decrease:
	  green--;
	  if(green == 0)
		state = red_increase;
	  break;

	  /* Blue increasing: */
	case blue_increase:
	  blue++;
	  if(blue == 0xff)
		state = green_decrease;
	  break;

	  /* Blue decreasing: */
	case blue_decrease:
	  blue--;
	  if(blue == 0)
		state = green_increase;
	  break;

	  /* Can't happen: */
	default:
	  state = red_increase;

	}

}

void setup()
{

  /* Set the pins: */
  pinMode(LIGHT_1_RED, OUTPUT);
  pinMode(LIGHT_1_GREEN, OUTPUT);
  pinMode(LIGHT_1_BLUE, OUTPUT);
  pinMode(LIGHT_2_RED, OUTPUT);
  pinMode(LIGHT_2_GREEN, OUTPUT);
  pinMode(LIGHT_2_BLUE, OUTPUT);

  /* Set the initial colour state: */
  red = 0xff;
  green = 0;
  blue = 0;
  state = green_increase;

  /* Set the timer: */
  last_colour_change = millis();

}

void loop()
{
  unsigned time = millis();
  boolean led1 = time % PERIOD1 < DUTY_CYCLE,
	led2 = time % PERIOD2 < DUTY_CYCLE;
  int i;
  for(i = 0; i < 0xff; i++)
	{
	  digitalWrite(LIGHT_1_RED, (led1 && i < red) ? HIGH : LOW);
	  digitalWrite(LIGHT_1_GREEN, (led1 && i < green) ? HIGH : LOW);
	  digitalWrite(LIGHT_1_BLUE, (led1 && i < blue) ? HIGH : LOW);
	  digitalWrite(LIGHT_2_RED, (led2 && i < red) ? HIGH : LOW);
	  digitalWrite(LIGHT_2_GREEN, (led2 && i < green) ? HIGH : LOW);
	  digitalWrite(LIGHT_2_BLUE, (led2 && i < blue) ? HIGH : LOW);
	}
  set_colour();
}

/* jl */
