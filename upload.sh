#!/bin/sh

avrdude_conf="/usr/local/etc/avrdude.conf"

mcu=""
programmer=""
program=""

print_usage() {
  printf "Usage:\n"
  printf "  ./$(basename $0)\n"
  printf "  -p microcontroller_type\n"
  printf "  -c programmer_type\n"
  printf "  -i program_name\n"
}

print_example() {
  printf "For example:\n"
  printf "  ./$(basename $0) -p m328p -c usbtiny -i program\n"
}

list_mcus() {
  avrdude \
  -C "$avrdude_conf" \
  -p "?"
}

list_programmers() {
  avrdude \
  -C "$avrdude_conf" \
  -c "?"
}

while getopts 'p:c:i:' flag; do
  case "${flag}" in
    p) mcu="${OPTARG}" ;;
    c) programmer="${OPTARG}" ;;
    i) program="${OPTARG}" ;;
    *) print_usage
       exit 1 ;;
  esac
done

if [ -z "${program}" ]; then
  printf "Program name is required!\n"
  print_example

  exit 1
fi
if [ -z "${mcu}" ]; then
  printf "Microcontroller type is required!\n"
  print_example

  list_mcus
  exit 1
fi
if [ -z "${programmer}" ]; then
  printf "Programmer type is required!\n"
  print_example

  list_programmers
  exit 1
fi

avrdude \
-C "$avrdude_conf" \
-p "$mcu" \
-c "$programmer" \
-U "flash:w:build/${program}.ihex:i"
