MCU=__SAMD11D14AM__

CC=arm-none-eabi-gcc
LD=arm-none-eabi-gcc
AR=arm-none-eabi-ar
AS=arm-none-eabi-as

ELF=$(notdir $(CURDIR)).elf

ASF_ROOT=~/Workspace/xdk-asf-3.46.0

INCLUDES= \
          sam0/utils/cmsis/samd11/include \
          sam0/utils/cmsis/samd11/source \
          thirdparty/CMSIS/Include \
          thirdparty/CMSIS/Lib/GCC 

OBJS = blink.o

LDSCRIPT = $(ASF_ROOT)/sam0/utils/linker_scripts/samd11/gcc/samd11d14am_flash.ld

LDFLAGS+= -T $(LDSCRIPT) -mthumb -mcpu=cortex-m0 -Wl,--gc-sections

CFLAGS+= -mcpu=cortex-m0 -mthumb -g
CFLAGS+= $(INCLUDES:%=-I $(ASF_ROOT)/%) -I .
CFLAGS+= -D$(MCU)
CFLAGS+=-pipe -Wall -Wstrict-prototypes -Wmissing-prototypes -Werror-implicit-function-declaration \
-Wpointer-arith -std=gnu99 -fno-strict-aliasing -ffunction-sections -fdata-sections \
-Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int -Wmain -Wparentheses -Wsequence-point \
-Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas -Wfloat-equal \
-Wundef -Wshadow -Wbad-function-cast -Wwrite-strings -Wsign-compare -Waggregate-return \
-Wmissing-declarations -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations \
-Wpacked -Wredundant-decls -Wnested-externs -Wlong-long -Wunreachable-code -Wcast-align \
--param max-inline-insns-single=500

$(ELF): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

%.o:    %.c
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< > $*.d

%.o:    %.s
	$(AS) $< -o $@

info:       
	@echo CFLAGS=$(CFLAGS)
	@echo OBJS=$(OBJS)

clean:
	rm -f $(OBJS) $(OBJS:.o=.d) $(ELF) $(CLEANOTHER)

debug:  $(ELF)
	arm-none-eabi-gdb -iex "target extended-remote localhost:2331" $(ELF)

.PHONY: clean

-include    $(OBJS:.o=.d)
