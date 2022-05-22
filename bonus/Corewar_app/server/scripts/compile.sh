#!/bin/bash

while getopts f:u: option
do
  case "${option}" in
  f) FILE=${OPTARG};;
  u) UUID=${OPTARG};;
  esac
done

FILE_PATH="corewar/asm/$FILE.s"

echo "[ASM] Compiling $FILE from user $UUID..."
cp tmp/"$FILE".s corewar/asm/
./corewar/asm/asm "$FILE_PATH" 2>&1
rm -f "$FILE_PATH"

if [ -f "$FILE.cor" ]; then
  mv -f "$FILE.cor" cor_file/"$FILE.cor.$UUID"
fi
