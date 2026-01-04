UF2_DEVICE_TYPE_ID = 0x35446147
UF2CONV_ARGS = --device-type $(UF2_DEVICE_TYPE_ID)

SRC += lib/common.c lib/mux.c
SRC += alt/keymaps/chunga2020/emacs_editing.c

ANALOG_DRIVER_REQUIRED = yes
COMBO_ENABLE = yes
