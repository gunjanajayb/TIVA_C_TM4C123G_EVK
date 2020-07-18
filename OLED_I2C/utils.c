/*
 * utils.c
 *
 *  Created on: 18-Jul-2020
 *      Author: bgunjan
 */

#include "utils.h"
#include "symbols.h"
#include "ImageCreater.h"
#include "I2Cfunc.h"

void display(char *str, uint32_t len)
{
    uint8_t i;
    char c;

    initialize_Imagebuf();

    for(i = 0; i < len; i++)
    {
        c = str[i];
        addImageToBuffer(&charset[c - 0x41][0]);
    }

    sendDataMulti_I2C(buffer,sizeof(buffer),false);



}

