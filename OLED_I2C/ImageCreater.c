/*
 * ImageCreater.c
 *
 *  Created on: 18-Jul-2020
 *      Author: bgunjan
 */

#include "ImageCreater.h"

struct image image_oled;

void initialize_Image()
{
    image_oled.cHeight = 10;
    image_oled.cWidth = 8;
    image_oled.curr_Position.x = 0;
    image_oled.curr_Position.y = 0;
    image_oled.leftmargin = 2;
    image_oled.linespacing = 2;
    image_oled.charspacing = 2;
    image_oled.rightmargin = 2;
    image_oled.currentPage = 0;
    memset(image_oled.buffer,0x00,sizeof(image_oled.buffer));
    image_oled.bufferPtr = &image_oled.buffer[0];
    image_oled.currentPageAdd = image_oled.bufferPtr;
}

void setStartPosition(){
    image_oled.curr_Position.x = image_oled.leftmargin;
    image_oled.curr_Position.y = 0;
    image_oled.bufferPtr += image_oled.leftmargin;// + ((image_oled.curr_Position.y / PAGE_HEIGHT ) * TOTAL_WIDTH);
}

void updatePosition(){

    image_oled.curr_Position.x += image_oled.cWidth + image_oled.charspacing;

    image_oled.bufferPtr += image_oled.cWidth + image_oled.charspacing;

    //if the current line gets full then move to next line
    if(image_oled.curr_Position.x > (128 - image_oled.cWidth + image_oled.charspacing))
    {
        image_oled.curr_Position.y += image_oled.cHeight + image_oled.linespacing;
        image_oled.curr_Position.x = image_oled.leftmargin;

        image_oled.currentPage = image_oled.curr_Position.y / PAGE_HEIGHT;
        image_oled.currentPageAdd += image_oled.currentPage* TOTAL_WIDTH;
        image_oled.bufferPtr = image_oled.currentPageAdd;
        image_oled.leftmargin += image_oled.leftmargin;
    }

}

void addImageToBuffer(uint16_t *ptr){

    uint8_t i;
    uint8_t j;
    uint8_t* tempbuf;

    //***********************************************************************//
    //find number of buffer i.e. number of inner loop required to add image.
    uint8_t next_page_num;
    uint8_t numPage;

    if((image_oled.curr_Position.y + image_oled.cHeight) % 8 != 0){
        next_page_num = (( image_oled.curr_Position.y + image_oled.cHeight) / PAGE_HEIGHT );
    }
    else
    {
        next_page_num = (( image_oled.curr_Position.y + image_oled.cHeight) / PAGE_HEIGHT );
    }

    numPage = (next_page_num - image_oled.currentPage) + 1;

    //***********************************************************************//

    //***********************************************************************//
    //find the number of shifts required
    uint8_t numShifts;

    numShifts = (image_oled.curr_Position.y % PAGE_HEIGHT);
    //***********************************************************************//

    tempbuf = image_oled.bufferPtr;

    for(i = 0; i < image_oled.cWidth ; i++)
    {
        for(j = 0; j < numPage; j++)
        {
            *(tempbuf + (TOTAL_WIDTH * j)) = (((*ptr) << numShifts) & (0x000000FF << (j * 8))) >> (j * 8);
        }
        ptr++;
        tempbuf++;
    }

    updatePosition();

}


