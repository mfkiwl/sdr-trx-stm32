/*
********************************************************************************
**
**  (C) 2020 Andrii Bilynskyi <andriy.bilynskyy@gmail.com>
**
**  This code is licensed under the GPLv3.
**
********************************************************************************
    WM8731 i2s interface driver header file
    https://statics.cirrus.com/pubs/proDatasheet/WM8731_v4.9.pdf
*/

#ifndef __WM8731_I2S_H
#define __WM8731_I2S_H


#include "codec_types.h"


void                            wm8731_i2s_start(codec_sample_rate_t sr, bool reset_cb);
void                            wm8731_i2s_stop(void);
void                            wm8731_i2s_set_callback(codec_data_ready_cb_t adc_data_ready);
volatile codec_sample_t * const wm8731_i2s_get_audio_buf(void);

#endif
