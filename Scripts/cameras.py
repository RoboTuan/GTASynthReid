import os
from collections import defaultdict
import functools
import argparse
import json
import sys

parser = argparse.ArgumentParser()
parser.add_argument('--path_to_logs', type=str, required=True, help='Path the folder with all the logs files')
parser.add_argument('--output_file', type=str, required=True, help='Path for the output cameras file')
args, _ = parser.parse_known_args()

path_to_logs = args.path_to_logs
output_file = args.output_file

logs_folder = os.listdir(path_to_logs)

cameras = defaultdict(list)

if ".DS_Store" in logs_folder:
    logs_folder.remove(".DS_Store")

# TODO: DEBUG THEN REMOVE THIS LINE
# logs_folder.remove("vinehood_boulevard_old")

# print(logs_folder)

for scenario in logs_folder:
    scenario_path = os.path.join(path_to_logs, scenario)
    logs = os.listdir(scenario_path)
    if ".DS_Store" in logs:
        logs.remove(".DS_Store")
    # print(logs)
    for log in logs:
        log_path = os.path.join(scenario_path, log)
        with open(log_path) as f:
            lines = f.readlines()

            log_name = log.split("_")[1].split(".")[0]

            lines[3] = lines[3].replace("\n", "")  
            cam1 = lines[3].split()[1:]
            del cam1[3]
            cam1 = ' '.join(cam1)
            cameras[log_name].append(cam1)

            if lines[2][0] == str(1):
                lines[2] = lines[2].replace("\n", "")
                cam2 = lines[2].split(" ")[1:]
                cam2 = ' '.join(cam2)
                cameras[log_name].append(cam2)

            # print(log)
            # print(cam1, "\n", cam2)
        # print()

# print(cameras)
print(f"There are {len(set(functools.reduce(lambda a,b: a+b, cameras.values())))} cameras")

with open(output_file, 'w') as f:
     f.write(json.dumps(cameras))