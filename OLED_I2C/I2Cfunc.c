/*
 * I2C.c
 *
 *  Created on: 18-Jul-2020
 *      Author: bgunjan
 */
#include "I2Cfunc.h"

void sendDataSingle_I2C(uint8_t ui8Data)
{
    I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDRESS, false); //false means write operation and ture means read operation
    I2CMasterDataPut(I2C0_BASE, 0x00);   //data to be sent

    while(I2CMasterBusBusy(I2C0_BASE))
    {
    }

    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C0_BASE))
    {
    }
    while(I2CMasterErr(I2C0_BASE))
    {
    }

    I2CMasterDataPut(I2C0_BASE, ui8Data);   //data to be sent
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(I2C0_BASE))
    {
    }
    while(I2CMasterErr(I2C0_BASE))
    {
    }

}

void sendDataMulti_I2C(uint8_t *ui8Data, uint32_t len, bool isCmd)
{
    uint8_t CoByte;
    I2CMasterSlaveAddrSet(I2C0_BASE, SLAVE_ADDRESS, false); //false means write operation and ture means read operation

    if(isCmd == true)
        CoByte = 0x00;
    else
        CoByte = 0x40;


    I2CMasterDataPut(I2C0_BASE, CoByte);   //data to be sent

    while(I2CMasterBusBusy(I2C0_BASE))
    {
    }

    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    while(I2CMasterBusy(I2C0_BASE))
    {
    }
    while(I2CMasterErr(I2C0_BASE))
    {
    }

    while(len > 1)
    {
        I2CMasterDataPut(I2C0_BASE, *ui8Data);   //data to be sent
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
        while(I2CMasterBusy(I2C0_BASE))
        {
        }
        while(I2CMasterErr(I2C0_BASE))
        {
        }
        ui8Data++;
        len--;
    }

    I2CMasterDataPut(I2C0_BASE, *ui8Data);   //data to be sent
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    while(I2CMasterBusy(I2C0_BASE))
    {
    }
    while(I2CMasterErr(I2C0_BASE))
    {
    }

}

