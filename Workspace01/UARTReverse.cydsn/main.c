/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"


uint8 getValidByte(){
    uint8 retval = 0u;
    while(UART_GetRxBufferSize() < 1);
    retval = UART_GetByte();
    return retval;
}


uint8 read(char* obuf){
    char strung[32];
    uint8 i = 0;
    while(1){
        char thisByte = getValidByte();
        UART_PutChar(thisByte);
        if (thisByte == '!'){
            strung[i] = thisByte;
            break;
        }
        strung[i] = thisByte;
        i++;
    }
    
    memcpy(obuf, strung, i -1);
    return i;
}

void get_flag(){
    while(1){
        UART_PutString("YOU WIN!!!");
    }
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();

    for(;;)
    {
      char strunged[32];
      uint8 i = read(strunged);
      char strung2electricboogaloo[i + 1];
      for(int j = i-2; j >= 0; j--){
        strung2electricboogaloo[i-j-1] = strunged[j];
      }
      strung2electricboogaloo[i] = '!';
      strung2electricboogaloo[i + 1] = '\x00';
      UART_PutChar('\n');
      UART_PutString(strung2electricboogaloo);
      
    }
}

/* [] END OF FILE */
