#!/bin/bash
if (($# != 1));
then
    echo "You must specify a data file"
    exit -1
fi
temp=`wc -l $1`
nl=${temp%' '*}
filename=${1%'.'*}'.png'
temp=${1#*'_'}
temp=${temp#*'_'}
temp=${temp%'_'*}
let ymax=temp+1
let width=90+$nl*2
if (($width < 800));
then
    width=800
fi
gnuplot -e 'set terminal pngcairo size '$width',400; set output "'$filename'"; unset key;set xrange [0:'$nl']; set yrange [0':$ymax']; p "'$1'" u 1:2 w lines ls 1, "'$1'" u 1:3 w lines ls 2;pause -1'
