#include<LPC21XX.H>
typedef unsigned int u32;
void s_delay(u32 s)
{	 
	T0PR=15000000-1;
 	T0TCR=0x01;
	while(T0TC<s);
	T0TCR=0x03;
	T0TCR=0x00;
}
void ms_delay(u32 ms)
{
	T0PR=15000-1; 
 	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}
