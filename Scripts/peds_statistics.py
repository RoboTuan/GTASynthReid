import os
import json
from os.path import isdir
from typing import Sequence
import pandas as pd
import argparse
import re
import sys

parser = argparse.ArgumentParser()
parser.add_argument('--path_to_dataset', type=str, required=True, help='Path to the dayaset with the old naming id_frame_sequenceCamera for the bounding boxes')
parser.add_argument('--cameras_file', type=str, required=True, help='Path to json file with the different cameras')
parser.add_argument('--path_to_admitted_peds', type=str, required=True, help='Path to the admitted_peds.txt file')
parser.add_argument('--output', type=str, required=True, help='Path to the csv output')
args, _ = parser.parse_known_args()

dataset = args.path_to_dataset
cameras_file = args.cameras_file
path_to_admitted_peds = args.path_to_admitted_peds
output = args.output

columns = ["Ped", "#sequences", "#sequences_day", "#sequences_nigth", "#bboxes",  "#bboxes_day", "#bboxes_nigth", "#cams", "#cams_day", "#cams_night"]
statistics = pd.DataFrame(columns=columns)

with open(cameras_file) as json_file:
    cameras = json.load(json_file)

peds =  os.listdir(dataset)
# Check for .DS_Store
if ".DS_Store" in peds:
    peds.remove(".DS_Store")
peds.sort()

for ped in peds:
    bboxes_path = os.path.join(dataset, ped)
    # Skip dataset.txt and statistics.csv
    if not os.path.isdir(bboxes_path):
        continue
    bboxes = os.listdir(bboxes_path)
    # print(bboxes)
    # Check for .DS_Store
    if ".DS_Store" in bboxes:
        bboxes.remove(".DS_Store")
    bboxes.sort()

    # print(ped)
    
    n_bboxes = len(bboxes)
    n_bboxes_day = 0
    n_bboxes_night = 0

    for bbox in bboxes:
        if "d" in bbox:
            n_bboxes_day += 1
        elif "n" in bbox:
            n_bboxes_night += 1


    sequences = set([bbox.split("_")[1].split("c")[0] for bbox in bboxes])
    # print(sequences)    
    n_sequences = len(sequences)
    n_sequences_day = 0
    n_sequences_night = 0

    for sequence in sequences:
        if "d" in sequence:
            n_sequences_day += 1
        elif "n" in sequence:
            n_sequences_night += 1
        
    
    sequences_cam = set([bbox.split("_")[1] for bbox in bboxes])
    # print(sequences_cam)
    uniques_cameras = set()
    uniques_cameras_day = set()
    uniques_cameras_night = set()

    for camera in sequences_cam:
        # Index used to retrieve the camera in the cameras dictionary
        # print(ped, camera.split("c"))
        cam = int(camera.split("c")[1]) - 1
        log = camera.split("c")[0]
        # Key of the cameras dictionary
        log = str(int(re.findall("\d+", log)[0]) + 1)
        if "d" in camera:
            # print(log, cam, "d")
            # print(cameras[str(log)][cam])
            uniques_cameras_day.add(cameras[str(log)][cam])
            uniques_cameras.add(cameras[str(log)][cam])
        elif "n" in camera:
            # print(log, cam, "n")
            # print(cameras[str(log)][cam])
            uniques_cameras_night.add(cameras[str(log)][cam])
            uniques_cameras.add(cameras[str(log)][cam])

    n_cams = len(uniques_cameras)
    n_cams_day = len(uniques_cameras_day)
    n_cams_night = len(uniques_cameras_night)

    # columns = ["Ped", "#sequences", "#sequences_day", "sequences_nigth", "#bboxes",  "#bboxes_day", "#bboxes_nigth", "#cams", "#cams_day", "#cams_night"]
    statistics.loc[len(statistics)] = [int(ped), n_sequences, n_sequences_day, n_sequences_night, n_bboxes, n_bboxes_day, n_bboxes_night, n_cams, n_cams_day, n_cams_night]
    # print(statistics)
    # sys.exit()


admitted_peds = pd.read_csv(path_to_admitted_peds, header=None)
admitted_peds.columns = ["Ped"]
# print(admitted_peds)
# print(type(admitted_peds))
# print(type(statistics.loc[:, ["Ped"]]))

missing_peds = admitted_peds.merge(statistics.loc[:, ["Ped"]], how="left", indicator=True) \
                .query("_merge == 'left_only'") \
                .drop('_merge',1) \
                .reset_index(drop=True)

# print(missing_peds)
for column in columns:
    if column == "Ped":
        continue
    missing_peds[column] = 0

# print(missing_peds)
statistics = statistics.append(missing_peds)
# print(statistics)
statistics.to_csv(output, index=False)


