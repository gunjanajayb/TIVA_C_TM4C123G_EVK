/*
 * ImageCreater.h
 *
 *  Created on: 18-Jul-2020
 *      Author: bgunjan
 */

#ifndef IMAGECREATER_H_
#define IMAGECREATER_H_

#include <stdint.h>
#include <stdbool.h>

#define TOTAL_WIDTH     128
#define TOTAL_HEIGHT    64
#define TOTAL_PAGE      8
#define PAGE_HEIGHT     8

struct co_ordinates{
    uint8_t x;
    uint8_t y;
};

typedef struct image {
    uint8_t linespacing;
    uint8_t charspacing;
    uint8_t leftmargin;
    uint8_t rightmargin;
    uint8_t currentPage;
    struct co_ordinates curr_Position;
    uint8_t cHeight;
    uint8_t cWidth;
    uint8_t buffer[128*8];
    uint8_t* bufferPtr;
    uint8_t* currentPageAdd;
};

extern struct image image_oled;

void initialize_Image();

void addImageToBuffer(uint16_t *ptr);

void setStartPosition();



#endif /* IMAGECREATER_H_ */
