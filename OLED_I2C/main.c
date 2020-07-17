#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/i2c.h"
#include "symbols.h"

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
    uint8_t cmd1[] = {0xAE, //display off
                      0xD5, //Set Oscillator Freq and clock devide ration
                      0x80, //set to default value 0x80
                      0x00,
                      0x3F,
                      0xD3, // set display offset
                      0x00, // no offset
                      0x40, //set display start line at 40
                      0x8D, //charge pump setting
                      0x14, //enable charge pump
                      0x20, //set Memory addressing mode
                      0x00, //horizontal addressing mode
                      0x21,
                      0x00,
                      0x7F,
                      0x22,
                      0x00,
                      0x07,
                      0xA1, //column address 127 is mapped to SEG0
                      0xC8, //Set COM output scan direction - remapped mode Scan from COM[N-1] to COM0
                      0xDA, //set COM pin hardware configuration
                      0x12, //value of COM pin hardware config (alternative COM pin)
                      0x81, //set contrast
                      0x3F, //value of contrast control register
                      0xD9, //set Pre charge period
                      0xF1, //value of pre charge period
                      0xDB, //set Vcomh deselect level
                      0x40, //0.77 x Vcc
                      0xA4, //resume to RAM content display.
                      0xA6, //Normal mode display
                      0xAF}; //Make display ON
    sendDataMulti_I2C(cmd1,sizeof(cmd1),true);


    sendDataMulti_I2C(logo_main,sizeof(logo_main),false);

    while(1)
    {
    }

    return 0;
}
