#!/bin/sh
JLinkGDBServerCL -select USB -device ATSAMD11D14AM -endian little -if SWD -speed 4000 -noir -LocalhostOnly
