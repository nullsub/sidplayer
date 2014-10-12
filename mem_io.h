#ifndef MEM_IO_H
#define MEM_IO_H

#define MEM_RAM_START		0x0000
#define MEM_RAM_SIZE  		0x7FFF
#define MEM_FLASH_START		0x8000
#define MEM_FLASH_SIZE		0x7FFF

#define SID_START		0x7FE0
#define UART_START  		0x7FD0

void mem_init();

extern char data[] = {0};

#endif
