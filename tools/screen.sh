#!/bin/bash

PORT=${1:-"/dev/ttyUSB1"}
RATE="${2:-"38400"}"

screen $PORT $RATE

