import os
import sys
import argparse


parser = argparse.ArgumentParser()
parser.add_argument('--path_to_dataset', type=str, required=True, help='Path to the dataset with the old naming id_frame_sequenceCamera for the bounding boxes')
parser.add_argument('--output', type=str, required=True, help='Path to the output file with all the names of the selected bounding boxes')
args, _ = parser.parse_known_args()

dataset = args.path_to_dataset
output = args.output

peds =  os.listdir(dataset)
# Check for .DS_Store
if ".DS_Store" in peds:
    peds.remove(".DS_Store")
#peds.sort()

# bboxes = set()
count = 0
with open(output, 'w') as f:
    for ped in peds:
        ped_folders = os.path.join(dataset, ped)
        # Skip dataset.txt and statistics.csv
        if not os.path.isdir(ped_folders):
            continue     
        for bbox in os.listdir(ped_folders):
            if bbox == ".DS_Store":
                continue
            f.write(bbox + "\n")
            count += 1
            # bboxes.add(bbox)

print(f"There are {count} bounding boxes")


