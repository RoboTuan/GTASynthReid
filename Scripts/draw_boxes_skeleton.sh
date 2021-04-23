#!/bin/bash

first_seq=0
last_seq=5

for (( i = 124 ; i <= 130 ; i += 1 )) ; do
    python visualize.py --in_mp4_file_path='videos/train/seq_'$i'.mp4' --json_file_path='annotations/train/seq_'$i'.json' --out_mp4_file_path='vis_ann/seq_'$i'.mp4'
done

# Parallel processes in background
# for (( i = 0 ; i <= 5 ; i += 1 )) ; do
#     python visualize.py --in_mp4_file_path='videos/train/seq_'$i'.mp4' --json_file_path='annotations/train/seq_'$i'.json' --out_mp4_file_path='vis_ann/seq_'$i'.mp4' &
# done