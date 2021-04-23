#!/bin/bash

while getopts l:c:d:p:s: flag
do
    case "${flag}" in
        l) logs=${OPTARG};;
        c) cameras=${OPTARG};;
        d) dataset=${OPTARG};;
        p) peds=${OPTARG};;
        s) statistics=${OPTARG};;
    esac
done

if [[ ! -d "$dataset" ]]; then
    echo "Dataset directory does not exist!"
    exit 1
fi

# Activate environment
source ~/JTA_Dataset/bin/activate

python ./cameras.py --path_to_logs $logs --output_file $cameras
python ./peds_statistics.py --path_to_dataset $dataset --cameras_file $cameras --path_to_admitted_peds $peds --output $statistics