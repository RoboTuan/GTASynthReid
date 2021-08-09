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
parser.add_argument('--path_to_training_dataset', type=str, required=True, help='Path to the training dataset')
args, _ = parser.parse_known_args()

path_to_training_dataset = args.path_to_training_dataset

if not isdir(path_to_training_dataset):
    raise FileNotFoundError("Folder not valid!")

training_path = os.path.join(path_to_training_dataset, "bounding_box_train")
testing_path = os.path.join(path_to_training_dataset, "bounding_box_test")
query_path = os.path.join(path_to_training_dataset, "query")

directories = [training_path, testing_path, query_path]

for directory in directories:
    print(directory.split("/")[-1].upper())
    cnt = 0
    ids = set()
    for image in os.listdir(directory):
        # Consider only images
        if image[-4:] == 'jpeg':
            cnt += 1
            id = image.split("_")[0]
            ids.add(id)

    print(f"Number of images: {cnt}")
    print(f"Number of identities: {len(ids)}")
    print()
