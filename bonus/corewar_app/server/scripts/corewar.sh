#!/bin/bash

while getopts a:x:b:y: option
do
  case "${option}" in
  a) PLAYER1=${OPTARG};;
  x) UUID1=${OPTARG};;
  b) PLAYER2=${OPTARG};;
  y) UUID2=${OPTARG};;
  esac
done

PATHP1="cor_file/$PLAYER1.$UUID1"
PATHP2="cor_file/$PLAYER2.$UUID2"

echo "[COREWAR] $PLAYER1 fighting against $PLAYER2 ..."
./corewar/corewar/corewar "$PATHP1" "$PATHP2" >&1
