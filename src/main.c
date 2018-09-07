#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#define Rx_Buffer_Size 64
#define Tx_Buffer_Size 1024
uint8_t __tx_buffer[Tx_Buffer_Size];
uint8_t __rx_buffer[Rx_Buffer_Size];
static uint16_t __tx_buffer_head = 0, __tx_buffer_tail = 0;
static uint16_t __rx_buffer_head = 0, __rx_buffer_tail = 0;

// TxD Functions
static void __tx_buffer_putc(uint8_t data)
{
	__tx_buffer[__tx_buffer_head++] = data;
	__tx_buffer_head %= Tx_Buffer_Size;
	
}

static void __tx_buffer_puts(const uint8_t *msg)
{
	while(*msg){
		__tx_buffer_putc((uint8_t)*msg);
		msg++;
	}
}

static uint8_t __tx_buffer_getc(void)
{
	uint8_t data;
	
	
	
	data = __tx_buffer[__tx_buffer_tail++];
	__tx_buffer_tail %= Tx_Buffer_Size;
	
	return data;
}

//static uint16_t __tx_buffer_used(void)
//{
//	if(__tx_buffer_head > __tx_buffer_tail)
//		return __tx_buffer_head - __tx_buffer_tail;
//	else if(__tx_buffer_head < __tx_buffer_tail)
//		return Tx_Buffer_Size - (__tx_buffer_tail - __tx_buffer_head);
//	else
//		return 0;
//}

//static uint16_t __tx_buffer_space(void)
//{
//	return Tx_Buffer_Size - __tx_buffer_used();
//}
//
//static void __wait_for_tx_buffer_space(void)
//{
//	uint16_t head = __tx_buffer_head;
//	uint32_t timeout = 2 * 1000;
//	
//	while(((head+1)%Tx_Buffer_Size) == __tx_buffer_tail) {
//		if(--timeout == 0)
//			break;
//	}
//}
int hal_printf(const signed char* fmt, ...)
{
	va_list args;
	int len;
	signed char buff[Tx_Buffer_Size];
	
	va_start(args, fmt);
	len = vsnprintf((char*)buff, sizeof(buff)-1, (char const*)fmt, args);
	va_end(args);
	
	buff[len] = 0;
	__tx_buffer_puts(buff);
	return len;
}

int main(int argc, char *argv[])
{
	int i, cnt = 0;
	for(i = 0; i < 512; i++){
		cnt += hal_printf("%d ", i);
	}
	printf("%s\n", __tx_buffer);
	printf("%d\n", cnt);
	return 0;
}
