file build/alarm.elf
# connect to the J-Link gdb server
target remote localhost:2331
# Select flash device
monitor flash device = AT91SAM7S256
# Set JTAG speed to 30 kHz
monitor endian little
monitor speed 30
# Reset the target
monitor reset 8
monitor sleep 10
# Perform peripheral reset
monitor long 0xFFFFFD00 = 0xA5000004
monitor sleep 10
# Disable watchdog
monitor long 0xFFFFFD44 = 0x00008000
monitor sleep 10
# Initialize PLL
monitor long 0xFFFFFC20 = 0x00000601
monitor sleep 10
monitor long 0xFFFFFC2C = 0x00480a0e
monitor sleep 10
monitor long 0xFFFFFC30 = 0x00000007
monitor sleep 10
monitor long 0xFFFFFF60 = 0x00480100
monitor sleep 100
# Setup GDB for faster downloads
#set remote memory-write-packet-size 1024
set remote memory-write-packet-size 4096
set remote memory-write-packet-size fixed
monitor speed 12000
#break main
load
#jump _startup
continue
