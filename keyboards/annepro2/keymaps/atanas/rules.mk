# Other featues
CONSOLE_ENABLE = yes
COMMAND_ENABLE = no
DEBUG_EEPROM = yes
LEADER_ENABLE = yes
TAP_DANCE_ENABLE = yes
COMBO_ENABLE = yes
# AUTO_SHIFT_ENABLE = yes

ifeq ($(strip $(BOARD)), ANNEPRO2_C18)
ANNEPRO2_EEPROM = yes
endif

ifeq ($(strip $(ANNEPRO2_EEPROM)), yes)
    OPT_DEFS += -DANNEPRO2_EEPROM
    SRC += spi_master.c eeprom_w25x20cl.c
endif

# Options
MOUSEKEY_ENABLE = yes

# Keys
