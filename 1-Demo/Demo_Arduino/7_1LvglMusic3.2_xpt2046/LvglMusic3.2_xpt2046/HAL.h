//
// Created by root on 2022/11/13.
//


#include <Arduino.h>
#include "SPI.h"
#include "SD.h"
#include "FS.h"
#include "Audio.h"
#include <Ticker.h>

#define SD_CS         5
#define SPI_MOSI      23
#define SPI_MISO      19
#define SPI_SCK       18

extern Audio audio;

void sdcard_init();
