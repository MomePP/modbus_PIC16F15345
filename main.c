#include <16F15345.h>
#device ADC=10 *=16

#FUSES BROWNOUT // brownout reset
#FUSES BORV24
#FUSES LVP 

#use delay(internal=8000000)
#PIN_SELECT U1RX=PIN_C5
#PIN_SELECT U1TX=PIN_C4
#use rs232(baud=115200, UART1, ERRORS, stream=PORT1)

//!#use rs232(baud=9600,parity=N,xmit=PIN_C4,rcv=PIN_C5,bits=8,stream=PORT1)

#PIN_SELECT U2RX=PIN_C6
#PIN_SELECT U2TX=PIN_C7

//!#include <main.h>
#define MODBUS_BUS SERIAL
#define MODBUS_TYPE MODBUS_TYPE_MASTER
#define MODBUS_SERIAL_TYPE MODBUS_RTU
#define MODBUS_SERIAL_INT_SOURCE MODBUS_INT_RDA2
#define MODBUS_PARITY "NONE"
#define MODBUS_SERIAL_RX_PIN PIN_C6
#define MODBUS_SERIAL_TX_PIN PIN_C7
#define MODBUS_SERIAL_BAUD 2400
//!#define MODBUS_REMOTE_ADDRESS 0x01
#include "modbus.c"

#define MODBUS_SLAVE_ADDRESS 0x01
#define Power_Address 12
#define Current_Address 6
#define Unit_Address 342
#define Voltage_Address 0

void main()
{
   int i;
   modbus_init();
   fprintf(PORT1,"Modbus Rs485 RTU \n");
   delay_ms(2000);
   
   while(TRUE)
   {
      delay_ms(200);
  
      if(!(modbus_read_input_registers(MODBUS_SLAVE_ADDRESS,Current_Address,2)))
      {
         printf("Current: ");
         /*Started at 1 since 0 is quantity of coils*/
         for(i=1; i < (modbus_rx.len); ++i){
            /*BufferRegister[i-1] = modbus_rx.data[i]; //! Start Address 0*/
            printf("%X ", modbus_rx.data[i]);
         }
         printf("\r\n\r\n");
      }
      else
      {
         printf("<-**Exception %X**->\r\n\r\n", modbus_rx.error);
      }
          
      delay_ms(200);
      
      if(!(modbus_read_input_registers(MODBUS_SLAVE_ADDRESS,Unit_Address,2)))
      {
         printf("Unit: ");
         /*Started at 1 since 0 is quantity of coils*/
         for(i=1; i < (modbus_rx.len); ++i){
            /*BufferRegister[i+7] = modbus_rx.data[i]; //! Start Address 8*/
            printf("%X ", modbus_rx.data[i]);
         }
         printf("\r\n\r\n");
      }
      else
      {
         printf("<-**Exception %X**->\r\n\r\n", modbus_rx.error);
      }
      
      delay_ms(200);
      
      if(!(modbus_read_input_registers(MODBUS_SLAVE_ADDRESS,Power_Address,2)))
      {
         printf("Power: ");
         /*Started at 1 since 0 is quantity of coils*/
         for(i=1; i < (modbus_rx.len); ++i){
            /*BufferRegister[i+15] = modbus_rx.data[i]; //! Start Address 16*/
            printf("%X ", modbus_rx.data[i]);
         }
         printf("\r\n\r\n");
      }
      else
      {
         printf("<-**Exception %X**->\r\n\r\n", modbus_rx.error);
      }
      
      delay_ms(200);
      
      if(!(modbus_read_input_registers(MODBUS_SLAVE_ADDRESS,Voltage_Address,2)))
      {
         printf("Voltage: ");
         /*Started at 1 since 0 is quantity of coils*/
         for(i=1; i < (modbus_rx.len); ++i){
//!            BufferRegister[i+7] = modbus_rx.data[i]; //! Start Address 8
            printf("%X ", modbus_rx.data[i]);
         }
         printf("\r\n\r\n");
      }
      else
      {
         printf("<-**Exception %X**->\r\n\r\n", modbus_rx.error);
      }
      //TODO: User Code
   }

}
