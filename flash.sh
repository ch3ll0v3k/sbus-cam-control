#!/bin/bash

sync
clear

SKETCH=${1:-"RX/RX.ino"}
PORT=${2:-"/dev/ttyUSB0"}
BOARD=${3:-"arduino:avr:nano:cpu=atmega328old"}

# BOARD="arduino:sam:arduino_due_x_dbg"     # DUE (x32) prog port
# BOARD="arduino:avr:nano:cpu=atmega328old" # NANO (old boot loader)
# BOARD="arduino:avr:mega:cpu=atmega1280" # ATmega 1280
# BOARD="arduino:avr:nano:cpu=atmega328old" # NANO (old boot loader)
# BOARD="arduino:avr:mega:cpu=atmega2560" # ATmega 2560 (Mega 2560)     
# PORT=${2:-"/dev/ttyUSB0"}

echo " Using: sketch: ${SKETCH}, device: ${PORT}"

#  Can only pass one of: --upload, --verify, --get-pref, --install-boards, --version, --install-library
ACTTION="--verify";
ACTTION="--upload";

arduino \
$ACTTION \
--board $BOARD \
--preserve-temp-files \
--port $PORT \
$SKETCH
