#include<LPC214X.h>
#include<stdio.h>


void delay1(void);
void serial(void);
void cmd(unsigned int);
void data(unsigned int);
void function(unsigned char array1[], unsigned int n1);
unsigned int i,m;
//void delay(unsigned int);
void extint0_ISR(void)__irq;
void delay(unsigned int );
unsigned char msg[] = {"LED ON"};
unsigned  int c[]={0x30,0x30,0x20,0x20,0x28,0x01,0x06,0x0e,0x89};



unsigned clock[4]=    {0x00030000,0x00090000,0x000c0000,0x00060000};
unsigned anticlock[4]={0x00060000,0x000c0000,0x00090000,0x00030000};

unsigned clock1[4]=    {0x00000300,0x00000900,0x00000c00,0x00000600};
unsigned anticlock1[4]={0x00000600,0x00000c00,0x00000900,0x00000300};

void clockwise(int speed,int rev,int mode);
void anticlockwise(int speed1,int rev1,int mode1);
void delayA(int);
int k=0;
void delayB();
unsigned long int var1,var2;


int main(void)
{
	
	PINSEL1=0x00000001;
		
	EXTMODE=0x00000001;
	VICVectAddr0=(unsigned long)extint0_ISR;
	VICVectCntl0=0x20|14;
	VICIntEnable|=0x00004000;
	

	while(1);
}

void extint0_ISR(void)__irq
{
	
	unsigned int result,temp;
	
	//PINSEL0 = 0x00000000;
	PINSEL1 |= 0x00040000;    //p0.25   pin is selected as as ad0.4
//	IODIR0 = 0xf0000c00;
	IODIR1 = 0x000f0000;
	
	
	PINSEL0=0x00000000;
	IO0DIR |=0x000000fc;
	IOCLR0 |=0x000000fc;
	for(i=0; i<9; i++)
  {
  cmd(c[i]);
  delay1();
  }
	IODIR0|=0x000f0f00;
	
	
	
	IOCLR0|=0X000f0f00; 	// ON LEDS
	
	delay(10000);
	//clockwise(10,100,1);					//Motor A
	anticlockwise(10,100,1);
	delay(10000000);

	for(i=0;i<10;i++)
	
	{
		result=0x00;
		AD0CR = 0x09200010;   //control register for adc     ad.04
		while((temp = AD0GDR) == 0x80000000);
		result = AD0GDR;   //to get the adc values in result
		AD0CR &= ~0x01000000; //stop adc
		result = (result >> 6);
		result = result & 0x000003FF;
	}
	
	if(result>0x00 && result<=0x0310){
	
		
			if(var2!=0x0000000f)
			{
				//IOCLR0 = 0xffffffff;
		//var1= 0x08000000;
			//var1<<=1;
			//IOSET0 = 0x00000800;
			//IOSET1 = 0x00030000;
			//	IOCLR0 = 0x00000400;
				
				delayB();
				
			//IOCLR0 = 0xffffffff;
			clockwise(10,25,2);    //Motor B
				delayA(10);
			// IOCLR1 = 0xffffffff;
			var1<<=1;
			//IOSET0 = 0x60000800;
			//IOSET1 = 0x00060800;
				//IOCLR0 = 0x00000400;
				var2=0x0000000f;
		}
			
	}
		

		else if(result>0x312 && result<=0x03ff){
	
			
			if(var2!=0x10000000)
			{
		//IOCLR0 = 0xffffffff;
		//IOCLR1 = 0xffffffff;
		//var1= 0x20000800;
			//var1<<=1;
			//IOSET0 = 0xc0000800;
			//	IOCLR0 = 0x00000400;
				delayB();
			//	IOCLR0 = 0xfffff7ff;
			// IOCLR1 = 0xfffff7ff;
		//	anticlockwise (10,25,2);    //Motor B
			clockwise(10,25,2);
			var1<<=1;
			//IOSET0 = 0x90000800;
			//	IOCLR0 = 0x00000400;
				var2=0x10000000;
				delayB();
			//	IOCLR0 = 0xfffff4ff;
			//IOCLR1 = 0xfffff4ff;	
		}
			
		
	}
		
		else{
		//IOSET0 = 0x00000800;
		//		IOCLR0 = 0x00000400;
	
			delayB();
		//	IOCLR0 = 0xfffff4ff;
			IOCLR1 = 0xfffff4ff;
		}
	delay(10000000);
	anticlockwise(10,155,1);       // motor A
	delay(1000);
	clockwise(10,255,1); 
		
		
		
		
		//cmd(0x80);
	//for(m=0;m<65000;m++);
  //for(m=0;m<65000;m++);
  //for(m=0;m<65000;m++);
	
	//function(msg,6);

	
	
	delay(100000000);	  
	IOSET0=0X000f0000; 	// OFF LEDS
	delay(100);
	 
	
//	cmd(0x01);
//	for(m=0;m<65000;m++);
//  for(m=0;m<65000;m++);
//  for(m=0;m<65000;m++);
	
		IO0CLR|=0xffffffff;
		IO1CLR|=0xffffffff;
EXTINT|=0X00000001;	//Clear interrupt flag
	VICVectAddr=0;		// End of interrupt execution
}


 void function(unsigned char array1[], unsigned int n1)
{
	{
        for (i = 0; i < n1; i++)
        {
					data(array1[i]);
  for(m=0;m<500;m++);
  } 
  for(m=0;m<65000;m++);
  for(m=0;m<65000;m++);
  for(m=0;m<65000;m++);
}
}

void delay(unsigned int x)
{
 unsigned int i;
 for(i=0;i<x;i++) ;
}

void cmd(unsigned int value)
 {
 unsigned int y,m;
 y=value;
 y=y & 0xf0;
 IOCLR0=0x000000fc;
 IOCLR0=0X00000004;
 IOSET0=y;

 IOSET0=0x00000008;
 for(m=0;m<10;m++);
 IOCLR0=0x00000008; 

 y=value;
 y=y&0x0f;
 y=y<<4;
 IOCLR0=0x000000fc;
 IOCLR0=0X00000004;
 IOSET0=y; 

 IOSET0=0x00000008;
 for(m=0;m<10;m++);
 IOCLR0=0x00000008;

 }
void data(unsigned int data)
 {
 unsigned int y,m;
 y=data;
 y=y & 0xf0;
 IOCLR0=0x000000fc;
 IOSET0=0X00000004;
 IOSET0=y; 

 IOSET0=0x00000008;
 for(m=0;m<10;m++);
 IOCLR0=0x00000008;

 y=data;
 y=y & 0x0f;
 y=y<<4;
 IOCLR0=0x000000fc;	
 IOSET0=0X00000004;
 IOSET0=y;

 IOSET0=0x00000008;
 for(m=0;m<10;m++);
 IOCLR0=0x00000008;
 }

void delay1()
 {
 unsigned int l;
 for(l=0;l<10000;l++);
 }
 
 void delayB(){
	 unsigned int i;
	for(i=0; i<1000000; i++); 
	 }

void clockwise(int speed,int rev,int mode)
{
	unsigned char I,J;
	if(mode==1)
	{
	for(J=0;J<rev;J++)
	{
		for(I=0;I<4;I++)
		{
		IOSET1 |=clock[I];
		IOCLR1 |=~clock[I]; 
		delayA(speed);
		}
	}
	}
	else if(mode==2)
	{	
	for(J=0;J<rev;J++)
	{
		for(I=0;I<4;I++)
		{
		IOSET0 |=clock1[I];
		IOCLR0 |=~clock1[I]; 
		delayA(speed);
		}
	}
	}				
	else
	{
	delay(1000);
	}									  
}

void anticlockwise(int speed1,int rev1,int mode1)
{
	unsigned char I,J;
	if(mode1==1)
	{
	for(J=0;J<rev1;J++)
	{
		for(I=0;I<4;I++)
		{
		IOSET1 |=anticlock[I];
		IOCLR1 |=~anticlock[I]; 
		delayA(speed1);
		}
	}
	}
	else if(mode1==2)
	{
	 for(J=0;J<rev1;J++)
	{
		for(I=0;I<4;I++)
		{
		IOSET0 |=anticlock1[I];
		IOCLR0 |=~anticlock1[I]; 
		delayA(speed1);
		}
	}
	}
	else
	{
	delay(1000);
	}
}

void delayA(int n)
{
	int i,j;
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=10000;j++)
		{;}
	}
}	
