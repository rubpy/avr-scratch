#!/bin/sh

mmcu=""
program=""
clockfreq=16000000

print_usage() {
  printf "Usage:\n"
  printf "  ./$(basename $0)\n"
  printf "  -m mmcu\n"
  printf "  -i program_name\n"
  printf "  -f clock_freq\n"
}

print_example() {
  printf "For example:\n"
  printf "  ./$(basename $0) -m atmega328p -i program -f 16000000\n"
}

while getopts 'm:i:f:' flag; do
  case "${flag}" in
    m) mmcu="${OPTARG}" ;;
    i) program="${OPTARG}" ;;
    f) clockfreq=${OPTARG} ;;
    *) print_usage
       exit 1 ;;
  esac
done

if [ -z "${mmcu}" ]; then
  printf "MMCU is required!\n"
  print_example

  exit 1
fi
if [ -z "${program}" ]; then
  printf "Program name is required!\n"
  print_example

  exit 1
fi

avr-gcc -c \
  -std=gnu99 \
  -Os \
  -Wall -Wextra -pedantic \
  -ffunction-sections -fdata-sections \
  -mmcu="$mmcu" \
  -DF_CPU=$clockfreq \
  "src/${program}.c" -o "build/${program}.o" \
  && \
avr-gcc \
  -Os \
  -mmcu="$mmcu" \
  -ffunction-sections -fdata-sections \
  -Wl,--gc-sections \
  "build/${program}.o" -o "build/${program}.elf" \
  && \
avr-objcopy \
  -O ihex \
  -R .eeprom \
  "build/${program}.elf" "build/${program}.ihex"
