import os
import sys
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--path_to_dataset', type=str, required=True, help='Path to the dayaset with the old naming id_frame_sequenceCamera for the bounding boxes')
args, _ = parser.parse_known_args()

dataset = args.path_to_dataset

peds =  os.listdir(dataset)
# Check for .DS_Store
if ".DS_Store" in peds:
    peds.remove(".DS_Store")
peds.sort()

def folders_in(dataset_path):
    for ped in peds:
        if ped == "Dataset.txt":
            continue
        files = os.path.join(dataset_path, ped)
        for file in os.listdir(files):
            if os.path.isdir(os.path.join(files, file)):
                yield os.path.join(os.path.join(files, file))

print("Wrong subdirectories: \n", list(folders_in(dataset)))
print("End")