/*
 Copyright (c) 2015 Mathieu Laurendeau <mat.lau@laposte.net>
 License: GPLv3
 */

#ifndef XONEPAD2EVENT_H_
#define XONEPAD2EVENT_H_

#include <ginput.h>
#include "../../../shared/gimxcontroller/include/controller.h"

void xOnePad2event(int adapter_id, s_report* current, s_report* previous,
    int joystick_id, int (*callback)(GE_Event*));

#endif /* XONEPAD2EVENT_H_ */
