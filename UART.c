#include <avr/io.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART.h"

#define F_CPU       16000000UL
#define BAUD_RATE   9600UL

void UART_Init(u16 baud_rate)
{
	u16 local_BR;

	local_BR = (F_CPU / (16UL * baud_rate)) - 1;

	UBRR0H = (u8)(local_BR >> 8);
	UBRR0L = (u8)local_BR;

	/* Enable TX and RX */
	SET_BIT(UCSR0B,TXEN0);
	SET_BIT(UCSR0B,RXEN0);

	/* 8-bit Data */
	SET_BIT(UCSR0C,UCSZ00);
	SET_BIT(UCSR0C,UCSZ01);

	/* 1 Stop bit */
	CLR_BIT(UCSR0C,USBS0);

}


void UART_SendChar(u8 data)
{
	while(GET_BIT(UCSR0A,UDRE0) == 0)
	{
	}

	UDR0 = data;
}


u8 UART_ReceiveChar(void)
{
	while(GET_BIT(UCSR0A,RXC0) == 0)
	{
	}

	return UDR0;
}


void UART_SendString(u8 *str)
{


	while(str!= '\0')
	{
		UART_SendChar(*str);
		str++;
	}
}
