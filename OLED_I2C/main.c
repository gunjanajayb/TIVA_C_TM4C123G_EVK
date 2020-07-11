#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/i2c.h"
#include "CommandMacros.h"

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

#define SLAVE_ADDRESS 0x3C

int sendDataSingle_I2C(uint8_t ui8Data)
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

    return 0;
}

int sendDataMulti_I2C(uint8_t *ui8Data, uint32_t len, bool isCmd)
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

    len--;
    ui8Data++;

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

    return ui8Data;

}



int
main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0); //enable clock for I2C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);    //enable clock for GPIOB
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2); //afsl
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);    //open drain
    GPIOPinConfigure(GPIO_PB2_I2C0SCL); //PCTL
    GPIOPinConfigure(GPIO_PB3_I2C0SDA); //PCTL


    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0))
    {
    }

    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);    //enable master module & set the clock
    SysCtlDelay(2000000);


 // initialization
    uint8_t cmd1[] = {0x78, //need to check
                      0xAE, //display off
                      0xD5, //
                      0x80,
                      0x00,
                      0x3F,
                      0xD3,
                      0x00,
                      0x40,
                      0x8D,
                      0x14,
                      0x20,
                      0x00,
                      0xA1,
                      0xC8,
                      0xDA,
                      0x12,
                      0x81,
                      0xF0,
                      0xD9,
                      0xF1,
                      0xDB,
                      0x40,
                      0xA4,
                      0xA6,
                      0xAF};
    sendDataMulti_I2C(cmd1,sizeof(cmd1),true);

#if 0
    uint8_t cmd7[] = {0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
                      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                      0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
                      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                      0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
                      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                      0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
                      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                      0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
                      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                      0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
                      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                      0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
                      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

    };
    sendDataMulti_I2C(cmd7,sizeof(cmd7),false);
#endif

    while(1)
    {
    }
}
