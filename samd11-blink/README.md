samd11-blink
============

This is a very basic "blink" test program for a bare-bones Atmel SAMD11D MCU.

Requirements
------------

This test requires a SAMD11D14AM MCU (either a bare chip on a breadboard or a SAMD11 Xplained will work). It should be easy to adapt this to other variants of the D11 or, other even other SAM chips. You'll also need a Segger J-Link programmer (with the software installed). You can use another programmer, such as an Atmel ICE or a JTAG device of some sort, but you'll need to adjust the upload process to match your hardware.

The MCU should be wired up with the proper power and SWD connections in place. If you're using an Xplained or similar ready-made device, just provide power via USB and connect your programmer to debug header EXT1. If you're using a bare chip, consult the datasheet to wire your chip up correctly. Ensure there's an LED attached to PA16 (physical pin 13 on the QFN). If you're using a variant or chip that don't have PA16 (the SOIC-14 doesn't), then pick another pin and adjust the code.

Lastly, you need the [Atmel Software Framework](www.atmel.com/asf) installed. Adjust the Makefile to point to the correct path. You can also download [CMSIS](https://github.com/ARM-software/CMSIS_5/) and the [Atmel SAMD11 DFP](http://packs.download.atmel.com/) separately and configure the Makefile to locate the necessary includes. 

Compile and run
---------------

You need two terminals. 

In terminal 0 run:

	$ jlink.sh

This launches JLinkGDBServerCL. You could write an openocd script to do the same thing with a different programmer. The key is that we have a running GDB server attached to the chip. We can now connect to GDB and work with the device.

In terminal 1 run:

	$ make
	$ make debug

This will compile the software and launch a GDB client to connect to the server running in the other terminal. If everything is connected correctly, then you'll be presented with a GDB prompt. Run this in your GDB session:

	(gdb) monitor halt
	(gdb) load
	(gdb) monitor reset

These commands halt the chip, load the newly compiled firmware, and then reset the chip. To execute it, run this:

	(gdb) continue

If all has gone to plan, you will be rewarded with a blinking LED.
