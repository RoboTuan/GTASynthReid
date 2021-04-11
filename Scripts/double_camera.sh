#!/bin/bash

# /Users/lpdef/Desktop/JTA/seq_1/

while getopts p: flag
do
    case "${flag}" in
        p) base_folder=${OPTARG};;
    esac
done

# read -p 'Input  path/to/files: ' base_folder

echo "Directory of sequence: " $base_folder

if [[ ! -d "$base_folder" ]]; then
    echo "Directory of sequence does not exist!"
    exit 1
fi

# first frame is 1
START=1
shopt -s nullglob
END=($base_folder/*.jpeg)
END=${#END[@]}
echo "Number of images:" $END

ext=".jpeg"

cam1=$base_folder/cam1
cam2=$base_folder/cam2
# make dirs if they do not exist
mkdir -p $cam1
mkdir -p $cam2

frame_counter=1
frame_counter=$(printf "%04d" $frame_counter)

# include last frame
for ((i=START;i<=END;i++)); do
    # if current crame is not 1 and is not even increment frame counter
    if [[ $i -ne 1 ]] && [[ $(($i%2)) -ne 0 ]]; then
        frame_counter=$((10#$frame_counter+1))
        frame_counter=$(printf "%04d" $frame_counter)
    fi

    if [[ $(($i%2)) -ne 0 ]]; then
        # it is odd
        mv $base_folder/${i}${ext} $cam1/${frame_counter}${ext}
    else
        # it is evne
        mv $base_folder/${i}${ext} $cam2/${frame_counter}${ext}
    fi

done