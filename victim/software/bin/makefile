TARGET 		:= victim
F_CPU 	 	:= 1000000 #Hz
PLATFORM 	:= atmega328p
PROGRAMMER 	:= arduino#atmelice_isp
PORT        := COM11#usb
BAUD 		:= 115200#125000

# /Project Name/
#   ├── /bin/
#   │    ├── main.elf
#   │    ├── main.hex
#   │    └── makefile
#   ├── /inc/
#   │    └── header files
#   ├── /src/
#   │    ├── main.c
#   │    └── any other source files
#   └── /ext/
#        └── external libraries

BIN_DIR := ../bin
INC_DIR := ../inc
SRC_DIR := ../src
EXT_DIR := ../ext

# Find all .c files in the src and ext directories
SRC = $(wildcard $(SRC_DIR)/*.c)
SRC += $(wildcard $(EXT_DIR)/*.c)

begin: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $(BIN_DIR)/$(TARGET).elf $(BIN_DIR)/$(TARGET).hex
	avr-size --format=avr --mcu=$(PLATFORM) $(BIN_DIR)/$(TARGET).elf

$(TARGET).elf: $(SRC)
	avr-gcc -Wall -std=gnu99 -Os -DF_CPU=$(F_CPU) -mmcu=$(PLATFORM) -I $(INC_DIR) -o $(BIN_DIR)/$(TARGET).elf $(SRC)

flash: begin
	avrdude -c $(PROGRAMMER) -P $(PORT) -p $(PLATFORM) -b $(BAUD) -U flash:w:$(TARGET).hex:i

debug: debug.exe 
debug.exe: $(SRC)
	gcc -I ../inc -o debug.exe ../src/aes-128.c ../test/debug.c

# Remove all .hex and .elf files
clean:
	@rm -f $(wildcard *.hex)
	@rm -f $(wildcard *.elf)
	@rm -f $(wildcard *.exe)