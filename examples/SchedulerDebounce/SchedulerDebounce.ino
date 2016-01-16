/**
 * @file SchedulerDebounce.ino
 * @version 1.0
 *
 * @section License
 * Copyright (C) Mikael Patel, 2015
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * @section Description
 * This Arduino sketch shows how to use the Scheduler library;
 * Software debounce a button.
 */

#include <Scheduler.h>

unsigned int count = 0;

void setup()
{
  Serial.begin(57600);
  Serial.println(F("SchedulerDebounce: started"));
  Scheduler.begin();
  Scheduler.start(debounceLoop);
}

void loop()
{
  Serial.print(millis());
  Serial.print(F(":loop::count="));
  Serial.println(count);
  delay(1000);
}

void debounceLoop()
{
  const unsigned int DEBOUNCE = 50;
  const int BUTTON = 4;
  pinMode(BUTTON, INPUT_PULLUP);
  int state = digitalRead(BUTTON);
  while (1) {
    await(digitalRead(BUTTON) != state);
    state = !state;
    if (state)
      buttonUp();
    else
      buttonDown();
    delay(DEBOUNCE);
  }
}

void buttonDown()
{
  Serial.print(millis());
  Serial.println(F(":buttonDown"));
  count += 1;
}

void buttonUp()
{
  Serial.print(millis());
  Serial.println(F(":buttonUp"));
}