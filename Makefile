ARMGNU ?= aarch64-linux-gnu
COPS = -Wall -nostdlib -nostartfiles -ffreestanding -Iinclude
ASMOPS = -Iinclude

BUILD_DIR = build
SRC_DIR = src
FAT_DIR? = sdc1

all: kernel8.img

install: clean kernel8.img
	sudo mount /dev/$(FAT_DIR) /mnt/fat32
	sudo rm /mnt/fat32/kernel8.img
	sudo cp kernel8.img /mnt/fat32/
	sudo umount /dev/$(FAT_DIR)

clean:
	rm -rf $(BUILD_DIR) *.img libfdt/*.{d,o,a}

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

kernel8.img: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	cd libfdt && $(MAKE)
	$(ARMGNU)-ld -T $(SRC_DIR)/linker.ld -Llibfdt -o $(BUILD_DIR)/kernel8.elf  $(OBJ_FILES) -lfdt
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary kernel8.img
