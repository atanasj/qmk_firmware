# Other featues
CONSOLE_ENABLE = yes
COMMAND_ENABLE = no
DEBUG_EEPROM = yes
LEADER_ENABLE = yes
TAP_DANCE_ENABLE = yes

# keep path to combos local to my keymap
VPATH  +=  keyboards/annepro2/keymaps/atanas/gboards/
# SRC    +=  g/engine.c
COMBO_ENABLE = yes

ifeq ($(strip $(BOARD)), ANNEPRO2_C18)
ANNEPRO2_EEPROM = yes
endif

ifeq ($(strip $(ANNEPRO2_EEPROM)), yes)
    OPT_DEFS += -DANNEPRO2_EEPROM
    SRC += spi_master.c eeprom_w25x20cl.c
endif

MOUSEKEY_ENABLE = yes
