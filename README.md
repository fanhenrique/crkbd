# Corne Keyboard

## QMK

### Install QMK

Follow the official QMK installation guide:

[install QMK](https://docs.qmk.fm/newbs_getting_started)

### QMK Setup

If this is your first time using QMK:

```bash
qmk setup
```

This will create the `qmk_firmware` directory in your home folder.


## Keymap Installation

Copy the keymap directory from this repository to the QMK firmware tree:


```bash
mkdir $HOME/qmk_firmware/keyboards/crkbd/keymaps/<keymap>
```

```bash
cp -r ./keymap/* $HOME/qmk_firmware/keyboards/crkbd/keymaps/<keymap>
```

Ensure the directory name matches the keymap name you intend to use.


> ### New Keymap
>Alternatively, you can create a new keymap using QMK:
>```bash
>qmk new-keymap -kb crkbd/rev4_1/standard -km <keymap>
>```

## Compile Firmware

To compile the firmware using the custom keymap:

```bash
qmk compile -kb crkbd/rev4_1/standard -km <keymap>
```

Replace `<keymap>` with the name of the keymap directory.

## Flash Firmware

Connect the keyboard in bootloader mode and flash the firmware:

```bash
qmk flash -kb crkbd/rev4_1/standard -km <keymap>
```

if the keyboard does not automatically enter bootloader mode, press the reset button or use the reset key defined in the keymap.
