#!/bin/bash

while getopts p:s: flag
do
    case "${flag}" in
        p) path=${OPTARG};;
        s) seq=${OPTARG};;
        # f) fullname=${OPTARG};;
    esac
done

if [[ ! -d "$path" ]]; then
    echo "Base directory does not exist!"
    exit 1
fi

# if [[ ! -d "$path" ]]; then
#     echo "Creating directory: $path"
#     mkdir $path
# fi

echo "Base directory: $path"
seq_splits=(${seq//_/ })
FPS=${seq_splits[3]}
day_night=${seq_splits[2]}
seq_number=${seq_splits[1]}
echo "FPS: $FPS"
sequence="$path/$seq/"
coords="$path/$seq/coords.csv"

if [[ ! -f "$coords" ]]; then
    echo "$coords does not exist!"
    exit 1
fi

# Activate environment
source ~/JTA_Dataset/bin/activate

sh ./double_camera.sh -p $sequence -f $FPS
python ./from_csv_to_json.py --path_to_coords $coords

if [[ "$FPS" -eq 60 ]]; then
    input="$sequence/cam1/"
    output="$sequence/cam1.mp4"
    json="$sequence/seq_${seq_number}_${day_night}_cam1.json"
    bboxes="$sequence/bboxes_cam1"
    annotation_vid="$sequence/ann_cam1.mp4"
    python ./from_frame_to_mp4.py --input $input --output $output
    python ./save_bboxes.py --in_frames_path=$input --json_file_path=$json --out_bboxes_path=$bboxes
    python ./visualize.py --in_mp4_file_path $output --json_file_path $json --out_mp4_file_path $annotation_vid

    input="$sequence/cam2/"
    output="$sequence/cam2.mp4"
    json="$sequence/seq_${seq_number}_${day_night}_cam2.json"
    bboxes="$sequence/bboxes_cam2"
    annotation_vid="$sequence/ann_cam2.mp4"
    python ./from_frame_to_mp4.py --input $input --output $output
    python ./save_bboxes.py --in_frames_path=$input --json_file_path=$json --out_bboxes_path=$bboxes
    python ./visualize.py --in_mp4_file_path $output --json_file_path $json --out_mp4_file_path $annotation_vid

elif [[ "$FPS" -eq 30 ]]; then
    input="$sequence/cam1/"
    output="$sequence/cam1.mp4"
    json="$sequence/seq_${seq_number}_${day_night}_cam1.json"
    bboxes="$sequence/bboxes_cam1"
    annotation_vid="$sequence/ann_cam1.mp4"
    python ./from_frame_to_mp4.py --input $input --output $output
    python ./save_bboxes.py --in_frames_path=$input --json_file_path=$json --out_bboxes_path=$bboxes
    python ./visualize.py --in_mp4_file_path $output --json_file_path $json --out_mp4_file_path $annotation_vid
fi




