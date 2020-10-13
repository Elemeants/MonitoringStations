PROGRAMMER = usbasp
MCU = m2560
UPLOADER = avrdude
BAUDRATE = 115200
ARGS_PROGRAMMER = -v -c ${PROGRAMMER} -p ${MCU}

ifeq (${MCU}, m2560)
BOOTLOADER_FILE = bootloader/bootloader_m2560.hex
endif
ifeq (${MCU}, m328)
BOOTLOADER_FILE = bootloader/bootloader_m328.hex
endif

PROJECT_NAME = KernelMega
FLASH_PILE = .pio/build/${PROJECT_NAME}/firmware.hex

PRODUCTION_STATION = 
ifeq (${PRODUCTION_STATION},)
EEPROM_FILE = eeprom.eep
else
EEPROM_FILE = ./stations/${PRODUCTION_STATION}.eep
endif
EEPROM_READ_FILE = eeprom.hex


help:
	@echo USAGE:
	@echo -- make build         - Builds and generate firmware.hex
	@echo -- make update        - Builds and uploads
	@echo -- make boot          - Programming the bootloader
	@echo -- make fuse          - Programming the fuses
	@echo -- make flash         - Programming the firmware

build: 
	@echo Building firmware with platformio
	@pio run 

boot:
	@echo Uploading bootloader to MCU
	@${UPLOADER} ${ARGS_PROGRAMMER} -e -Ulock:w:0xff:m -Uefuse:w:0xFD:m -Uhfuse:w:0xD8:m -Ulfuse:w:0xFF:m -B 11
	@${UPLOADER} ${ARGS_PROGRAMMER} -Uflash:w:${BOOTLOADER_FILE}:i -Ulock:w:0xcf:m

flash: fuse
	@echo Uploading flash to MCU
	@${UPLOADER} ${ARGS_PROGRAMMER} -Uflash:w:${FLASH_PILE}:i

fuse:
	@echo Updating fuses to MCU
	@${UPLOADER} ${ARGS_PROGRAMMER} -U hfuse:w:0xD1:m

eeprom:
	@echo Updating eeprom data
	@${UPLOADER} ${ARGS_PROGRAMMER} -U eeprom:w:${EEPROM_FILE}

read_eeprom:
	@echo Updating eeprom data
	@${UPLOADER} ${ARGS_PROGRAMMER} -U eeprom:r:${EEPROM_READ_FILE}:i

monitor:
	@echo Enabling monitor
ifndef PORT
	@pio device monitor -b ${BAUDRATE}
else
	@pio device monitor -b ${BAUDRATE} -p ${PORT}
endif

clean:
	@echo Clean files
	@pio run -t clean

update:	build flash

full_update: build flash eeprom