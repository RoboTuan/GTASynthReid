import argparse
import os
import pandas as pd
import sys

parser = argparse.ArgumentParser()
parser.add_argument('--path_to_peds', type=str, required=True, help='Path the folder with all the logs files')
args, _ = parser.parse_known_args()

path_to_peds = args.path_to_peds

peds_folder = os.listdir(path_to_peds)

for el in peds_folder:
    scenario = os.path.join(path_to_peds, el)
    # print(scenario)
    if os.path.isdir(scenario):
        peds_folder = os.listdir(scenario)
        # print(peds_folder)
        for peds in peds_folder:
            if peds == ".DS_Store":
                continue
            peds_file = os.path.join(scenario, peds)
            # print(peds_file)
            df = pd.read_csv(peds_file, header=None)
            print(peds_file)
            print(df[df.duplicated(keep=False)])
