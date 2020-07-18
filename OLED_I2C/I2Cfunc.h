/*
 * I2C.h
 *
 *  Created on: 18-Jul-2020
 *      Author: bgunjan
 */
#ifndef I2CFUNC_H_
#define I2CFUNC_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/i2c.h"

#define SLAVE_ADDRESS 0x3C

void sendDataSingle_I2C(uint8_t ui8Data);
void sendDataMulti_I2C(uint8_t *ui8Data, uint32_t len, bool isCmd);


#endif /* I2CFUNC_H_ */
