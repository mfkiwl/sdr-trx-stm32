/*
********************************************************************************
**
**  (C) 2020 Andrii Bilynskyi <andriy.bilynskyy@gmail.com>
**
**  This code is licensed under the GPLv3.
**
********************************************************************************
    UI notify widget header file
*/


#ifndef __UI_NOTYFY_H
#define __UI_NOTIFY_H


#include <stdint.h>
#include <stdbool.h>


void ui_notify(uint8_t argc, const char * argv[], const char * button, volatile bool * run);


#endif
