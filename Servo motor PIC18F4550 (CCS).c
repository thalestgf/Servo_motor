#include <18F2550.h>
#device ADC=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES WDT128                   //Watch Dog Timer uses 1:128 Postscale
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOXINST                  //Extended set extension and Indexed Addressing mode disabled (Legacy mode)

#use delay(clock=48MHz,crystal=20MHz)

#define servo_pin    PIN_d0

#define ch1 pin_a4
#define ch2 pin_e0
#define ch3 pin_e1
#define ch4 pin_e2

int servo_garra=0; //Controla posição do servo variando de 0~46
int1 flag_garra=0;//habilita o servo

#INT_TIMER0
void  TIMER0_isr(void) //21,3 us
{
   int16 contador1=contador1+1;

   if(flag_garra){
      if(contador1>=30+servo_pos){
         output_low(servo_pin);
         if(contador1>=1000){
            output_high(servo_pin);
            contador1=0;
         }
      }
   }
  
}


void main()
{

   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1|RTCC_8_bit);      //21,3 us overflow

   enable_interrupts(INT_TIMER0);
   enable_interrupts(GLOBAL);
 
   while(TRUE)
   {
   
      if(input(ch1)==0){
         while(input(ch1)==0);
         servo_pos++;
      }
      
      if(input(ch2)==0){
         while(input(ch1)==0);
         servo_pos--;
      }
   
   }

}
