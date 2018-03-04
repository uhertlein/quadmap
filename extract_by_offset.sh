#!/bin/sh

in_file="world.qmp"

grep -v ^# offsets.txt | while read name offset length ; do
    out_file="level_$name.jpg"
    offset_dec=$(($offset))
    length_dec=$(($length))
    echo $out_file $offset_dec $length_dec
    dd if=$in_file of=$out_file bs=1 skip=$offset_dec count=$length_dec
done
