# TFMSX — STM32F730R8Tx Firmware

Bare-metal firmware for the **TFMSX Rev2** board (STMicroelectronics
**STM32F730R8Tx**, Cortex-M7, 64 KB flash / 256 KB RAM) with a USB Host stack.

This project builds with a plain **GNU Make + arm-none-eabi-gcc** toolchain and
is programmed over **ST-Link (SWD)**. No STM32CubeIDE is required to build or
flash the firmware.

---

## 1. Prerequisites

Install the toolchain and the flashing tools:

```bash
# Debian / Ubuntu / Linux Mint
sudo apt update
sudo apt install build-essential gcc-arm-none-eabi binutils-arm-none-eabi \
                 openocd stlink-tools
```

| Tool | Used for | Package |
|------|----------|---------|
| `arm-none-eabi-gcc` | Compile / link | `gcc-arm-none-eabi` |
| `arm-none-eabi-objcopy/size` | Generate `.bin` / `.hex`, size report | `binutils-arm-none-eabi` |
| `openocd` | Flash + GDB server (default) | `openocd` |
| `st-flash` | Alternative flasher | `stlink-tools` |
| `arm-none-eabi-gdb` | Source-level debugging | `gcc-arm-none-eabi` |

### Already have a toolchain somewhere else?

This machine already has the exact toolchain the project was generated with at
`~/Toolchain/arm-none-eabi-gcc`. Either add it to your `PATH`:

```bash
export PATH="$HOME/Toolchain/arm-none-eabi-gcc/bin:$PATH"
```

…or pass its location to Make without modifying `PATH`:

```bash
make PREFIX="$HOME/Toolchain/arm-none-eabi-gcc/bin/arm-none-eabi-"
```

Check it works:

```bash
arm-none-eabi-gcc --version
```

### ST-Link permissions (Linux)

If OpenOCD reports a permission/USB error, add the udev rules and re-plug the
ST-Link:

```bash
sudo cp /usr/share/openocd/contrib/60-openocd.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules && sudo udevadm trigger
# make sure your user is in the plugdev group:
sudo usermod -aG plugdev "$USER"   # log out / back in afterwards
```

---

## 2. Building

```bash
make            # debug build (default)  -> build/debug/
make release    # optimized build (-Os)  -> build/release/
```

Both configurations produce:

```
build/<config>/TFMSXRev2F730.elf   # ELF (for GDB / OpenOCD)
build/<config>/TFMSXRev2F730.bin   # raw binary (for flashing at 0x08000000)
build/<config>/TFMSXRev2F730.hex   # Intel HEX
build/<config>/TFMSXRev2F730.map   # linker map
```

Select a configuration explicitly for any target:

```bash
make CONFIG=release
make CONFIG=release flash
```

| Config | Optimization | Debug info | Extra define |
|--------|--------------|-----------|--------------|
| `debug` (default) | `-O0` | `-g3` | `-DDEBUG` |
| `release` | `-Os` | `-g` | – |

### Build details

- CPU/FPU: `-mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb`
- Defines: `-DUSE_HAL_DRIVER -DSTM32F730xx -DUSE_FULL_LL_DRIVER`
- Linker script: `STM32F730R8TX_FLASH.ld` (override with `LDSCRIPT=...`)
- Sources are auto-discovered, so new files in `Core/Src`, `USB_HOST/App`,
  `USB_HOST/Target` are picked up automatically — just re-run `make`.

---

## 3. Flashing the board

The default flow uses **OpenOCD** over the ST-Link:

```bash
make flash                 # debug build, program + verify + reset
make CONFIG=release flash  # build release and program it
```

Use the `stlink-tools` flasher instead if you prefer:

```bash
make stflash               # st-flash --reset write build/debug/...bin 0x08000000
```

Other useful targets:

```bash
make erase    # mass-erase the whole flash
make reset    # reset the target
```

---

## 4. Debugging (GDB + OpenOCD)

OpenOCD runs a GDB server on `localhost:3333`. Use two terminals:

```bash
# terminal 1 — start the GDB server (leave running)
make server

# terminal 2 — build and attach GDB (loads image, breaks at main)
make gdb
```

`make gdb` connects, resets/halts the target, loads the ELF, and breaks at
`main`. From there use normal GDB commands (`continue`, `next`, `bt`, …).

---

## 5. Customization

Override these variables on the command line or in your environment:

| Variable | Default | Description |
|----------|---------|-------------|
| `CONFIG` | `debug` | `debug` or `release` |
| `PREFIX` | `arm-none-eabi-` | Toolchain prefix |
| `LDSCRIPT` | `STM32F730R8TX_FLASH.ld` | Linker script |
| `GDB` | `$(PREFIX)gdb` | GDB executable |
| `OPENOCD` | `openocd` | OpenOCD executable |
| `OPENOCD_IF` | `interface/stlink.cfg` | OpenOCD interface config |
| `OPENOCD_TGT` | `target/stm32f7x.cfg` | OpenOCD target config |
| `STFLASH` | `st-flash` | stlink-tools flasher |

Example — use a custom OpenOCD target and a non-default toolchain:

```bash
make PREFIX=/opt/gcc-arm/bin/arm-none-eabi- \
     OPENOCD_IF=interface/stlink-v2.cfg flash
```

Run `make help` for the full target list.

---

## 6. Project layout

```
.
├── Makefile                 # standalone build system (this repo)
├── STM32F730R8TX_FLASH.ld   # linker script (flash)
├── STM32F730R8TX_RAM.ld     # linker script (RAM debug)
├── TFMSXRev2F730.ioc        # STM32CubeMX configuration
├── Core/
│   ├── Inc/                 # application + HAL config headers
│   ├── Src/                 # application sources
│   └── Startup/             # startup_stm32f730r8tx.s
├── Drivers/                 # STM32F7 HAL + CMSIS
├── Middlewares/             # STM32 USB Host Library
├── USB_HOST/                # USB host application + configuration
└── build/                   # generated (git-ignored)
```

> `Debug/` and `Release/` are STM32CubeIDE-generated build trees. They contain
> hard-coded Windows paths and are **not** used by this Makefile. They can be
> removed from version control once you are happy with the Make build:
>
> ```bash
> git rm -r --cached Debug Release
> ```

---

## 7. Notes on STM32CubeMX regeneration

`TFMSXRev2F730.ioc` is the CubeMX project. If you regenerate code, CubeMX/IDE
will re-create the `Debug/` and `Release/` makefiles — you can ignore them. The
top-level `Makefile` needs no regeneration: it discovers sources automatically
and only requires updates if you add new *include directories* or change MCU /
defines. Those live in the `DEFS` and `INCLUDES` sections near the top of the
`Makefile`.
