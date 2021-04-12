from os.path import isdir
import pandas as pd
import numpy as np
import sys
import os
import argparse

from pandas.core import base

parser = argparse.ArgumentParser()
parser.add_argument('--path_to_admitted_peds', type=str, required=True, help='Path to the file with all the admitted peds in the game')
parser.add_argument('--scenario', type=str, required=True, help='Scenario type, like airport_entrance, ferris, ...')
parser.add_argument('--starting_name', type=int, required=True, help='Integer from which you want to name the ped files such as peds_1.txt, peds_10.txt, ...')
args, _ = parser.parse_known_args()

path_to_admitted_peds = args.path_to_admitted_peds
scenario = args.scenario
starting_name = args.starting_name

admitted_peds = pd.read_csv(path_to_admitted_peds, header=None)
print(f"There are currently {admitted_peds.shape[0]} admitted peds")

base_path = path_to_admitted_peds.split("admitted_peds")[0]

if scenario.lower() == "airport_entrance":
    subfolder = "airport_entrance"
    folder = base_path + "/" + subfolder
    if not os.path.isdir(folder):
        os.makedirs(folder)
    # Randomize the admitted peds with a random state different from the other scenarios
    rnd_admitted_peds = admitted_peds.sample(frac=1, random_state=0).reset_index(drop=True)
    rnd_admitted_peds.to_csv(folder + "/rnd_admitted_peds.txt", index=False, header=False)

    # Divide the dataframe in 6 chunks and save them in their scenario directory
    for i in range(6):
        file_name = folder + "/peds_" + str(starting_name) + ".txt"
        start = 90*i
        end = 90*(i+1)

        if i == 5:
            rnd_admitted_peds_restricted = rnd_admitted_peds.iloc[start :]
        else:
            rnd_admitted_peds_restricted = rnd_admitted_peds.iloc[start : end]
        
        rnd_admitted_peds_restricted.to_csv(file_name, index=False, header=False)
        starting_name +=1
else:
    print("Scenario not admitted!")