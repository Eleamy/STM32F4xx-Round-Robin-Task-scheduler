CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size

CFLAGS = -mcpu=cortex-m4 -mthumb -O0 -Wall -Iinclude 

# Source files
C_SOURCES = my_rtos.c main.c gpio.c usart.c nvic.c terminal.c timer.c interrupts.c pwr.c systick.c 

# Object files
OBJS = startup.o $(C_SOURCES:.c=.o) 

all: main.bin

# Compile C files to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble startup.s
startup.o: startup.s
	$(AS) -mcpu=cortex-m4 -mthumb startup.s -o startup.o

# Link everything
main.elf: $(OBJS) linker.ld
	$(LD)  -Map=firmware.map -T linker.ld $(OBJS) -o main.elf

# Convert to binary
main.bin: main.elf
	$(OBJCOPY) -O binary main.elf main.bin

# Make a .hex file
main.hex: main.elf
	$(OBJCOPY) -O ihex main.elf main.hex

disassemble:
	$(OBJDUMP) -D main.elf > disassembly.txt
sections: 
	$(OBJDUMP) -h main.elf
size:
	$(SIZE) main.elf
#delet all files created
clean:
	rm -f *.o *.elf *.bin *.hex *.map
