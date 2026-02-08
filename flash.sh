#!/bin/bash

set -e

# Local keymap directory
KEYMAP_DIR="./keymap"

# QMK firmware directory
QMK_DIR="$HOME/qmk_firmware"

KEYBOARD="crkbd/rev4_1/standard"
KEYMAP="fanhenrique"

# RPI-RP2 mount point (udisks)
MOUNT_POINT="/media/$USER/RPI-RP2"

# Wait for RPI-RP2 to enter BOOTLOADER (UF2) mode
wait_for_bootloader() {
    echo "==> Waiting for RPI-RP2 BOOTLOADER mode (press QK_BOOTLOADER or QK_BOOT)..."
    
    # Timeout: ~30s
    for i in {1..300}; do
        # Detect block device with label RPI-RP2  
        DEVICE=$(lsblk -nr -o NAME,LABEL | awk '$2=="RPI-RP2" {print "/dev/"$1}')
        [[ -n "$DEVICE" ]] && break
        sleep 0.1
    done

    # Abort if not detected
    if [[ -z "$DEVICE" ]]; then
        echo "ERROR: RPI-RP2 not detected. Press QK_BOOT on the MASTER side."
        exit 1
    fi

    echo "RPI-RP2 detected: $DEVICE"
}

# Wait until RPI-RP2 reboots after flashing
wait_for_reboot() {
    echo "==> Waiting for RPI-RP2 to reboot..."
    while lsblk -nr -o LABEL | grep -q RPI-RP2; do
        sleep 0.3
    done
    echo "RPI-RP2 rebooted"
}

# Copy custom keymap into QMK tree
echo "==> Copying keymap files..."
cp -r "$KEYMAP_DIR"/* "$QMK_DIR/keyboards/crkbd/keymaps/$KEYMAP"

# Compile firmware
echo "==> Compiling QMK firmware..."
if ! qmk compile --keyboard "$KEYBOARD" --keymap "$KEYMAP"; then
    echo "ERROR: QMK compilation failed"
    exit 1
fi

wait_for_bootloader

# Mount RPI-RP2
echo "==> Mounting device..."
udisksctl mount -b "$DEVICE" >/dev/null 2>&1 || true
while [ ! -d "$MOUNT_POINT" ]; do
    sleep 0.1
done
echo "Mounted at $MOUNT_POINT"

# Flash UF2 firmware
KB_SAFE="${KEYBOARD//\//_}"
UF2="$QMK_DIR/${KB_SAFE}_${KEYMAP}.uf2"
echo "==> Flashing firmware: $UF2"
cp "$UF2" "$MOUNT_POINT/"

# Write on the disc (RPI-RP2)
# Ensure data is fully written
sync

wait_for_reboot

echo "Flash completed (device will reboot automatically)"