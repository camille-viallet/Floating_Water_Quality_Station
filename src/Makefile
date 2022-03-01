APPLICATION = cayenne

BOARD ?= b-l072z-lrwan1

RIOTBASE ?= $(CURDIR)/../../RIOT

# Default LoRa region is Europe and default band is 868MHz
LORA_REGION ?= EU868

USEMODULE += ztimer_msec
USEMODULE += hts221
USEMODULE += sx126x_stm32wl

USEPKG += semtech-loramac
USEPKG += cayenne-lpp

include $(RIOTBASE)/Makefile.include
