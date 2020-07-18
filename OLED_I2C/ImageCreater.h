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

extern uint8_t buffer[128*8];
extern uint8_t* bufferPtr;

void initialize_Imagebuf();
void addImageToBuffer(uint16_t *ptr);



#endif /* IMAGECREATER_H_ */
