APPLICATION = cayenne

BOARD ?= b-l072z-lrwan1

RIOTBASE ?= $(CURDIR)/../../RIOT

# Default LoRa region is Europe and default band is 868MHz
LORA_REGION ?= EU868

FEATURES_REQUIRED = periph_adc
USEMODULE += ztimer
USEMODULE += ztimer_msec
USEMODULE += ds18
USEMODULE += sx126x_stm32wl

USEPKG += semtech-loramac
USEPKG += cayenne-lpp

include $(RIOTBASE)/Makefile.include
