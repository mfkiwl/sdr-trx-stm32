/*
********************************************************************************
**
**  (C) 2020 Andrii Bilynskyi <andriy.bilynskyy@gmail.com>
**
**  This code is licensed under the GPLv3.
**
********************************************************************************
    Digital controlled oscillator driver header file
    SI5351 CMOS clock generator
    https://www.silabs.com/documents/public/data-sheets/Si5351-B.pdf
    https://www.silabs.com/documents/public/application-notes/AN619.pdf
*/


#ifndef __DCO_H
#define __DCO_H


#include <stdint.h>
#include <stdbool.h>


#define DCO_MIN_FREQUENCY   1800000UL
#define DCO_MAX_FREQUENCY   30000000UL

typedef struct {
    bool    system_initing;
    bool    lost_pllb;
    bool    lost_plla;
    bool    lost_clkin;
    bool    lost_xtal;
    uint8_t revision;
} dco_status_t;


bool         dco_start(uint32_t frequency);
void         dco_stop(void);
bool         dco_set_frequency(uint32_t frequency);
dco_status_t dco_status(void);


#endif
