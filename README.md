# Corne Keyboard (CRKBD)

## Keyboard Layout (OS Configuration)

This keymap assumes the use of the International keyboard layout at the operating system level (e.g. US International or International (AltGr dead keys)).

Using a different keyboard layout may result in incorrect characters.

### Debian / Ubuntu / Derivatives

Generate the [`keyboard`](./keyboard) configuration file using the standard Debian tool and select an international keyboard layout when prompted:

```bash
sudo dpkg-reconfigure keyboard-configuration
sudo service keyboard-setup restart
```

Alternatively, you can copy the provided [`keyboard`](./keyboard) file directly to `/etc/default/` and restart the service:

```bash
sudo cp keyboard /etc/default/keyboard
sudo service keyboard-setup restart
```

Important: Make sure the selected layout is an international standard layout to match the keymap.

> See the Debian Wiki for more information: https://wiki.debian.org/Keyboard

### Remap keys

Change this line in `/usr/share/X11/xkb/symbols/us` file.

```bash
# remove
key <AC11> { [ dead_acute, dead_diaeresis, apostrophe, quotedbl ] };

# add
key <AC11> { [ apostrophe,  quotedbl, dead_acute, dead_diaeresis ] };
```

Alternatively, you can copy the [`us`](./us) file directly to `/usr/share/X11/xkb/symbols/`

```bash
sudo cp us /usr/share/X11/xkb/symbols/
```

## Layer Overview

| Layer | Purpose |
|-------|---------|
| **TEXT** | Default QWERTY layout |
| **OS** | OS-level shortcuts with GUI modifier |
| **NAVIGATE** | Arrow keys, Home/End |
| **NUMBERS_SYMBOLS** | Number row + Special characters |
| **FUNCTIONS_NUMPAD** | Function keys (F1-F12) + numpad |
| **SPECIAL** | Bootloader, reboot, RGB controls |

## Install Dependencies

### Install QMK Firmware

Follow the official QMK installation guide:

[Setting Up Your QMK Environment](https://docs.qmk.fm/newbs_getting_started)

### Install Dependencies to run this project

Run the installation script to set up system dependencies:

```bash
./install.sh
```

This installs and enables `udisks2`, which is required for automatic mounting of the keyboard bootloader.

## Flash Firmware

Run the automated flash script:

```bash
./flash.sh
```

**What it does:**
1. Copies keymap files to QMK firmware tree (`$HOME/qmk_firmware/keyboards/crkbd/keymaps/<keymap>`)
2. Compiles the firmware
3. Waits for bootloader mode (prompts you to press `QK_BOOTLOADER` or `QK_BOOT` or the physical bootloader button)
4. Auto-mounts the RPI-RP2 device
5. Flashes the `.uf2` file
6. Waits for automatic reboot

**Usage:**
- Run the script
- When prompted, press the `QK_BOOT` key on your keyboard (or the physical bootloader button)
- The script handles the rest automatically

## Keymap Configuration

### Enabled Features

The keymap includes the following QMK features (see [`rules.mk`](./keymap/rules.mk)):

- **COMBO_ENABLE**: Key combinations for additional functionality
- **TAP_DANCE_ENABLE**: Double-tap actions
- **EXTRAKEY_ENABLE**: Media keys and system controls

### Timing Configuration

Tapping term is set to **250ms** for comfortable typing (see [`config.h`](./keymap/config.h)).

### Keymap Layers

[`keymap.c`](./keymap/keymap.c) contains the layer definitions and key mappings.

## Hardware

- **Keyboard**: Corne Keyboard (CRKBD) rev4.1 standard
- **Controller**: RP2040-based (uses UF2 bootloader)

## Resources

- [QMK Documentation](https://docs.qmk.fm/)
- [Corne Keyboard GitHub](https://github.com/foostan/crkbd)
