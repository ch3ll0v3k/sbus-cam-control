#!/bin/bash


PORT=${1:-"/dev/ttyUSB0"}
RATE="${2:-"38400"}"
SETUP="-s";

minicom -D $PORT -b $RATE --color=on
