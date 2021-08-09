import os
from os.path import join, isdir
from shutil import copyfile
from shutil import move
import argparse
import numpy as np
import json
import random
from collections import defaultdict
import sys

parser = argparse.ArgumentParser()
parser.add_argument('--path_to_dataset', type=str, required=True, help='Path to the dataset')
parser.add_argument('--cameras_numeric', type=str, required=True, help='Path to the file cameras_numeric.json')
parser.add_argument('--path_to_training_dataset', type=str, required=True, help='Path to the training dataset')
args, _ = parser.parse_known_args()

path_to_dataset = args.path_to_dataset
path_to_training_dataset = args.path_to_training_dataset
path_to_cameras_numeric = args.cameras_numeric

# cameras for GTA dataset
with open(path_to_cameras_numeric) as json_file:
    cameras_numeric = json.load(json_file)

if not isdir(path_to_training_dataset):
    os.mkdir(path_to_training_dataset)


## 60:40 train-test split (323:215)
#index = 323

# 438:100 new split identities for training and testgin
index = 438
peds = np.array([ped for ped in os.listdir(path_to_dataset) if isdir(join(path_to_dataset, ped))])

random.seed(42)
np.random.seed(42)
# In place shuffling
np.random.shuffle(peds)
training_peds = peds[: index]
test_peds = peds[index :]
# print(len(training_peds), len(test_peds))

bounding_box_train = join(path_to_training_dataset, 'bounding_box_train/')
if not isdir(bounding_box_train):
    os.mkdir(bounding_box_train)

bounding_box_test = join(path_to_training_dataset, 'bounding_box_test/')
if not isdir(bounding_box_test):
    os.mkdir(bounding_box_test)

query = join(path_to_training_dataset, 'query/')
if not isdir(query):
    os.mkdir(query)


##Training-Split###
for ped_folder in training_peds:
    peds_path = join(path_to_dataset, ped_folder)

    for bbox in os.listdir(peds_path):
        if bbox[-4 :] == 'jpeg':
            parts = bbox.split("_")
            # print(parts)
            seq_cam = parts[1]
            seq = seq_cam.split("c")[0]
            camera = int(seq_cam.split("c")[1]) - 1
            # print(seq_cam, seq, camera)
            new_camera = cameras_numeric[str(int(seq[-3:])+1)][camera]
            # print(str(int(seq[-3:])+1), new_camera)
            new_seq = seq + "c" + str(new_camera).zfill(2)
            # print(new_seq)
            new_bbox = parts[0] + "_" + new_seq + "_" + parts[2]
            # print(new_bbox)
            # print(seq, camera)
            source = join(peds_path, bbox)
            dest = join(bounding_box_train, new_bbox)
            # print(source, dest)
            copyfile(source, dest)


##Test-Split###
peds_cam = defaultdict(list)

for ped_folder in test_peds:
    peds_path = join(path_to_dataset, ped_folder)
    
    for bbox in os.listdir(peds_path):
        if bbox[-4 :] == 'jpeg':
            parts = bbox.split("_")
            seq_cam = parts[1]
            seq = seq_cam.split("c")[0]
            camera = int(seq_cam.split("c")[1]) - 1
            new_camera = cameras_numeric[str(int(seq[-3:])+1)][camera]
            new_seq = seq + "c" + str(new_camera).zfill(2)
            new_bbox = parts[0] + "_" + new_seq + "_" + parts[2]
            source = join(peds_path, bbox)
            dest = join(bounding_box_test, new_bbox)
            ped_cam = parts[0] + "_" + str(new_camera).zfill(2)
            peds_cam[ped_cam].append(new_bbox)
            copyfile(source, dest)


##Query###
# peds_cam = defaultdict(list)
# for bbox in os.listdir(bounding_box_test):
#     if bbox[-4 :] == 'jpeg':
#         ped = bbox.split("_")[0]
#         cam = bbox.split("_")[1].split("c")[1]
#         ped_cam = ped + "_" + cam
#         peds_cam[ped_cam].append(bbox)

for ped_cam, bboxes in peds_cam.items():
    bbox = random.choice(bboxes)
    source = join(bounding_box_test, bbox)
    dest = join(query, bbox)
    copyfile(source, dest)