
void delay_us(int delay)
{
  while(delay--)
  {
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
      __asm ("NOP");
  }
}

void delay_ms(int delay)
{
	for(int i= 0; i< delay; i++) {
		delay_us(1000);
	}

}
