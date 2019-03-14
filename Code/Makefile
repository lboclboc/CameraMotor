CPU = attiny85
SERIAL = /dev/ttyUSB0
FREQ = -DF_CPU=8000000UL

CXX = avr-g++
CC = avr-gcc
INCLUDES = -I/usr/lib/avr/include -I.
CFLAGS =  -O3 -Wall \
          -fno-exceptions -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fpack-struct \
          -fshort-enums \
          -DMCUCSR=MCUSR -gdwarf-2 -mmcu=$(CPU) $(FREQ) $(INCLUDES) $(ARDUINO_CFLAGS)

CXXFLAGS = $(CFLAGS)
#AVRDUDE =  avrdude -C$(ARDUINO_HOME)/hardware/tools/avrdude.conf -p$(CPU) -carduino -P$(SERIAL) -b115200
#AVRDUDE = avrdude -p$(CPU) -carduino -P$(SERIAL) -b115200
AVRDUDE = avrdude -c buspirate -p t85 -P$(SERIAL) -b115200

TARGET = CameraMotor

all: $(TARGET).hex

#include Arduino.mk

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $@ $^
	avr-objdump -d $(TARGET) > $(TARGET).lst

$(TARGET).hex: $(TARGET)
	avr-objcopy -O ihex -R .eeprom $(TARGET) $(TARGET).hex
	avr-objcopy -O binary -R .eeprom $(TARGET) $(TARGET).bin
	@grep ":108000" $(TARGET).hex > /dev/null && { echo "! ! !  Too big  ! ! !"; false ; } || : ok


upload: $(TARGET).hex
	$(AVRDUDE) -e
	$(AVRDUDE) -D -Uflash:w:$(TARGET).hex:i

clean:
	$(RM) $(ARDUINO_LIB) $(TARGET) $(TARGET).o $(TARGET).hex $(TARGET).eep $(TARGET).lst

