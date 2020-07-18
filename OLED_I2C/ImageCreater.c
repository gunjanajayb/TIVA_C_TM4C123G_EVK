/*
 * ImageCreater.c
 *
 *  Created on: 18-Jul-2020
 *      Author: bgunjan
 */

#include "ImageCreater.h"


uint8_t buffer[128*8];
uint8_t* bufferPtr;

void initialize_Imagebuf()
{
    memset(buffer,0x00,sizeof(buffer));
    bufferPtr = &buffer[0];

}

void addImageToBuffer(uint16_t *ptr){

    uint8_t i;
    uint8_t* tempbuf;

    tempbuf = bufferPtr;

    for(i = 0; i < 8; i++)
    {
        *tempbuf = (*ptr & 0x00FF);
        *(tempbuf + 128) = (*ptr & 0xFF00) >> 8;

        tempbuf++;
        ptr++;

    }

    bufferPtr += 10;
}


