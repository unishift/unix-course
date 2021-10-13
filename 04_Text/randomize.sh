#!/bin/sh

latency_time=${1:-1.}

OLDIFS=$IFS
IFS=''
FILE=
while read line;do
    line=$(echo -n "$line" | tr ' ' "\001")
    if [ -z "$FILE" ]; then
        FILE=$line
    else
        FILE="${FILE}\n${line}"
    fi
done

as_hex=$(echo -n $FILE | od -t x1 --address-radix=n --width=1 -v - | tr -d ' ' | tr "\n" " ")

IFS=$OLDIFS

y=0
x=0
for ch in $as_hex;do
    if [ "$ch" = "01" ]; then # space
        :
    elif [ "$ch" = "0a" ]; then # newline
        x=$(($x + 1))
        y=-1
    else
        s="${x} ${y} ${ch}"
        if [ -z "${positions}" ]; then
            positions=${s}
        else
            positions="${positions}\n${s}"
        fi
    fi
    y=$(($y + 1))
done

IFS=''
shuffled_position="$(echo -n "$positions" | shuf)"

IFS=$OLDIFS
tput clear
echo "$shuffled_position" |
while read x y ch;do
    sleep $latency_time
    tput cup $x $y
    /bin/echo -ne "\x${ch}"
done 

tput cup $(tput lines) 0