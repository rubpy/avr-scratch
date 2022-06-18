## avr-scratch 🤖

An example minimal compile/deploy setup (**build system**) for Atmel/Microchip ATmega (**AVR**) microcontrollers. \
`💡 With some extra tips & tricks.`

Compiles plain C code (does not require *Arduino IDE*) using `avr-gcc`, and supports deploying to devices (with `avrdude`) lacking native USB support (e.g., boards that rely on`bit-bang/V-USB` & `USBtinyISP`).

Also, **works on macOS**! (even via a `microUSB to USB-B` + `USB-B to USB-C` adapter combo)

## Why?
> ☝️ I have personally found *Arduino IDE* and the *Arduino* platform to be somewhat muddled, confusing, and a rather superfluous layer of abstraction. Getting the IDE to work properly, especially on a Linux/macOS machine, can be far from straightforward; hence, this setup tells you how to avoid the use of the *Arduino* platform completely, when dealing with common development boards.

This repository serves as an entry point (or, really an example of how `avr-gcc` & `avrdude` can be used) for beginner microcontroller programmers, especially those with a C/C++ background, to the AVR ecosystem.

As these simple shell scripts are by no means exhaustive, it is highly recommended to create a custom build system (e.g., using *Makefile*, *CMake*, *Bash*, etc.) for your own project.

## Requirements
- `avr-gcc`
- `avrdude`

#### How to install
----------

**Linux** (Ubuntu/Debian):
```console
$ sudo apt-get install gcc-avr avr-libc avrdude
```
For more information, see: [avr-gcc](https://gcc.gnu.org/wiki/avr-gcc) on `gcc.gnu.org`, [avr-libc](https://www.nongnu.org/avr-libc/) on `nongnu.org`, and [avrdudes/avrdude](https://github.com/avrdudes/avrdude) on GitHub.

**macOS** (*Homebrew* required):
```console
$ xcode-select --install
$ brew tap osx-cross/avr
$ brew install avr-gcc avrdude
```
For more information, see: [osx-cross/homebrew-avr](https://github.com/osx-cross/homebrew-avr) on GitHub.

## Build
```console
$ chmod +x compile.sh upload.sh
```

To compile a program (e.g., `src/blink.c` for *ATmega328p* running @ 16 MHz clock frequency):
```console
$ ./compile.sh -m atmega328p -i blink -f 16000000
```

To deploy the output binary (e.g., `build/blink.ihex`) to a microcontroller (e.g., an *ATmega328p* connected via *USBtinyISP/V-USB*):
```console
$ ./upload.sh -p m328p -c usbtiny -i blink
avrdude: AVR device initialized and ready to accept instructions

[...]

avrdude: verifying ...
avrdude: 182 bytes of flash verified
avrdude: safemode: Fuses OK (E:FD, H:D0, L:FF)

avrdude done.  Thank you.
```

## Tips

- A list of MMCU's (AVR instruction set architectures, or microcontroller types) supported by `avr-gcc` (or the `compile.sh` script) can be found here: [AVR Options (Using the GNU Compiler Collection (GCC))](https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html).

- Likewise, a list of all microcontroller types supported by `avrdude` (or the `upload.sh` script) can be revealed *(alternatively, check out the [AVRDUDE user manual](https://www.nongnu.org/avrdude/user-manual/avrdude_3.html))*:
```console
$ avrdude -p "?"

Valid parts are:
  uc3a0512 = AT32UC3A0512
  c128     = AT90CAN128
  c32      = AT90CAN32
  c64      = AT90CAN64
  pwm2     = AT90PWM2
  pwm216   = AT90PWM216
  pwm2b    = AT90PWM2B
  pwm3     = AT90PWM3
  pwm316   = AT90PWM316
  pwm3b    = AT90PWM3B
  1200     = AT90S1200
  2313     = AT90S2313
  2333     = AT90S2333
  2343     = AT90S2343

  [... (144 more)]
```

- All programmer types supported by `avrdude` can be listed as well *(alternatively, check out the [AVRDUDE user manual](https://www.nongnu.org/avrdude/user-manual/avrdude_3.html))*:
```console
$ avrdude -c "?"

Valid programmers are:
  2232HIO          = FT2232H based generic programmer
  4232h            = FT4232H based generic programmer
  arduino          = Arduino
  arduino-ft232r   = Arduino: FT232R connected to ISP
  atmelice         = Atmel-ICE (ARM/AVR) in JTAG mode
  atmelice_dw      = Atmel-ICE (ARM/AVR) in debugWIRE mode
  atmelice_isp     = Atmel-ICE (ARM/AVR) in ISP mode
  atmelice_pdi     = Atmel-ICE (ARM/AVR) in PDI mode
  avr109           = Atmel AppNote AVR109 Boot Loader
  avr910           = Atmel Low Cost Serial Programmer
  avr911           = Atmel AppNote AVR911 AVROSP
  avrftdi          = FT2232D based generic programmer
  avrisp           = Atmel AVR ISP
  avrisp2          = Atmel AVR ISP mkII

  [... (68 more)]
```

- Listing paths to AVR headers/libraries can sometimes be helpful:
```console
$ avr-gcc -print-search-dirs
install: /usr/local/Cellar/avr-gcc@9/9.3.0_3/lib/avr-gcc/9/gcc/avr/9.3.0/
programs: =/usr/local/Cellar/avr-gcc@9/9.3.0_3/libexec/gcc/avr/9.3.0/:[...]
libraries: =/usr/local/Cellar/avr-gcc@9/9.3.0_3/lib/avr-gcc/9/gcc/avr/9.3.0/:[...]
```

----------

- Other useful resources:
  - [`amirbawab/AVR-cheat-sheet`](https://github.com/amirbawab/AVR-cheat-sheet) — a quick reference for AVR internals, with some examples
  - [`fffaraz/awesome-avr`](https://github.com/fffaraz/awesome-avr) — a curated list of awesome AVR tools, libraries, resources...
  - [(PDF) avr-libc user manual](https://www.nongnu.org/avr-libc/user-manual/pages.html) — standard AVR library documentation
  - [(PDF) AVR instruction set manual](https://ww1.microchip.com/downloads/en/DeviceDoc/AVR-Instruction-Set-Manual-DS40002198A.pdf) — an overview and explanation of every instruction available for 8-bit AVR devices, from *Microchip*
  - [(PDF) ATmega328P datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf) — an absolute must-have, full of low-level details, code examples, memory structure & I/O description, CPU design overview, full instruction set, etc. *(note: table of contents is at the bottom)*
  - [Wokwi - online Arduino and ESP32 simulator](https://wokwi.com/) — test your AVR coding abilities in a virtual environment!
    > Note: *\*.ino* files are really just *\*.cpp*. \
    > *Arduino IDE* defines its own `main` function, which calls the user-defined `setup` once, and then invokes `loop` in an infinite loop. \
    > Even in the simulator, you can include standard AVR header files at the top of a *sketch.ino*, for example: \
    > `#include <avr/io.h>`.
