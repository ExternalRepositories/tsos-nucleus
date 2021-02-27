#!/usr/bin/env bash
# https://github.com/tsuki-superior/tsos-nucleus/blob/master/documents/TSOS-Ports.md

# Travel to the parent directory
cd "$(basename "$(dirname "$0")")"

# This simple function checks if a command exists
exists() {
    command -v "$1" >/dev/null 2>&1
}

CODE_DIR=$(pwd)

# Make sure the required tools are here
case $1 in
help)
    echo "Please choose a system to compile the TS/OS nucleus for."
    echo "Valid systems:"
    echo ""
    echo "pc  - i686 or higher IBM compatible Personal Computer"
    echo "gba - Nintendo Gameboy Advanced"
    exit 0
    ;;
pc)
    NEEDED_COMMANDS=(tsos-i686-gcc tsos-i686-g++ tsos-i686-ld.gold make xorriso grub-mkrescue)
    ;;
gba)
    NEEDED_COMMANDS=(tsos-armeabi-gcc tsos-armeabi-g++ tsos-armeabi-ld.gold make)
    ;;
psp)
    NEEDED_COMMANDS=(tsos-mipsel-gcc tsos-mipsel-g++ tsos-mipsel-ld.gold make)
    echo "This system is not supported yet."
    exit 1
    ;;
nspire)
    NEEDED_COMMANDS=(make)
    echo "This system is not supported yet."
    exit 1
    ;;
rpi3)
    NEEDED_COMMANDS=(make)
    echo "This system is not supported yet."
    exit 1
    ;;
pc98)
    NEEDED_COMMANDS=(make)
    echo "This system is not supported yet."
    exit 1
    ;;
pcxt)
    NEEDED_COMMANDS=(make)
    echo "This system is not supported yet."
    exit 1
    ;;
pcat)
    NEEDED_COMMANDS=(make)
    echo "This system is not supported yet."
    exit 1
    ;;
nds)
    NEEDED_COMMANDS=(make)
    echo "This system is not supported yet."
    exit 1
    ;;
psx)
    NEEDED_COMMANDS=(make)
    echo "This system is not supported yet."
    exit 1
    ;;
*)
    echo "Choose a valid system...."
    exit 1
    ;;
esac

for i in "${NEEDED_COMMANDS[@]}"; do
    if ! exists "$i"; then
        echo "Error: $i is not installed."
        exit 1
    fi
done

# Prepare the filesystem root for TS/OS
FILESYSTEM_ROOT="$CODE_DIR/filesystem"
rm -rfv "$FILESYSTEM_ROOT"
mkdir -pv "$FILESYSTEM_ROOT/"{bin,boot,cfg,lib,sys,sys/tmp,sys/headers,sys/info,sys/trash,tmp}

# Make the target nucleus
mkdir -pv "$CODE_DIR/build/"
cd "$CODE_DIR/build/"
cp -v "../Makefile.$1.mk" "./Makefile"
cp -v "../config/$1.hpp" "./current_config.hpp"
make clean
make -j$(nproc)

# Lets deploy these images
case $1 in
pc)
    if ! grub-file --is-x86-multiboot "./nucleus.tse"; then
        echo "Compiling failed"
        exit 1
    fi
    cp -v "./nucleus.tse" "$FILESYSTEM_ROOT/bin/nucleus.tse"
    mkdir -pv "$FILESYSTEM_ROOT/boot/grub/"
    cp -v "$CODE_DIR/config/grub.cfg" "$FILESYSTEM_ROOT/boot/grub/grub.cfg"
    grub-mkrescue -o "./tsos.iso" "$FILESYSTEM_ROOT"
    ;;

esac

case $2 in
test)
    case $1 in
    pc)
        echo "Launching with qemu"
        if ! exists "qemu-system-i386"; then
            echo "Error: qemu is not installed, which is needed for testing and debugging TS/OS"
            exit 1
        fi
        qemu-system-i386 -kernel "./nucleus.tse"
        ;;
    gba) ;;

    esac
    ;;
debug)
    case $1 in
    pc)
        if ! exists "qemu-system-i386"; then
            echo "Error: qemu is not installed, which is needed for testing and debugging TS/OS"
            exit 1
        fi
        echo "Set you debugger to localhost:1234 with the nucleus.tse as your executable"
        qemu-system-i386 -kernel "./nucleus.tse" -s -S
        ;;
    gba) ;;

    esac
    ;;

esac
