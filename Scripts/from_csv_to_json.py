import pandas as pd
import numpy as np
import json
import argparse
import sys

# ~/Desktop/JTA/seq_0/coords.csv

parser = argparse.ArgumentParser()
parser.add_argument('--path_to_coords', type=str, required=True, help='Path to the coords.csv file for annotations')
args, _ = parser.parse_known_args()

# path = '~/Desktop/JTA/seq_0_60/coords.csv'
path = args.path_to_coords

usecols=["frame", "pedestrian_id", "joint_type", "2D_x", "2D_y", "3D_x", "3D_y", "3D_z", "occluded", "self_occluded"]

seq = path.split("/")[-2].split("_")[1]
day_night = path.split("/")[-2].split("_")[2]
FPS = int(path.split("/")[-2].split("_")[-1])
coords = pd.read_csv(path, usecols=usecols)

if FPS == 60:
    annotations = path.split("coords.csv")[0] + "seq_"
    json_coords1 = open(annotations + seq + "_" + day_night + "_cam1.json", 'w')
    json_coords2 = open(annotations + seq + "_" + day_night + "_cam2.json", 'w')
    print(annotations)
    print(annotations + seq + "_" + "cam1.json")
    print(annotations + seq + "_" + "cam2.json")

    cam1 = coords.loc[(coords["frame"]%2 != 0), :]
    # print(cam1["frame"].drop_duplicates().shape)  
    cam1["frame"] = cam1.loc[:, "frame"].div(2).apply(np.ceil)
    #n_rows = cam1.shape[0]
    # print(f"Number of rows in cam1: {n_rows}")
    result = cam1.to_json(orient="split")
    parsed = json.loads(result)['data']
    final = json.dumps(parsed, indent=None)
    json_coords1.write("%s" % final)

    cam2 = coords.loc[(coords["frame"]%2 == 0), :]
    # print(cam2["frame"].drop_duplicates().shape)
    cam2["frame"] = cam2.loc[:, "frame"].div(2)
    #n_rows = cam1.shape[0]
    # print(f"Number of rows in cam2: {n_rows}")
    result = cam2.to_json(orient="split")
    parsed = json.loads(result)['data']
    final = json.dumps(parsed, indent=None)
    json_coords2.write("%s" % final)


else:
    annotations = "./annotations/reID/seq_"
    json_coords1 = open(annotations + seq + "_" + "cam1.json", 'w')
    cam1 = coords
    # print(cam1["frame"].drop_duplicates().shape)
    #n_rows = cam1.shape[0]
    # print(f"Number of rows in cam1: {n_rows}")
    result = cam1.to_json(orient="split")
    parsed = json.loads(result)['data']
    final = json.dumps(parsed, indent=None)
    json_coords1.write("%s" % final)





# n_rows = cam1.shape[0]
# # # n_rows = 2
# print(f"Number of rows: {n_rows}")

# result = cam1.to_json(orient="split")
# parsed = json.loads(result)['data']
# final = json.dumps(parsed, indent=None)
# # final.replace(',', '; ')
# myfile.write("%s" % final)


#myfile.write("[")

# for i in range(n_rows):
#     line = coords.iloc[i].to_list()
#     #print(line)
#     if i == n_rows-1:
#         myfile.write("%s" % line)
#     else:
#         myfile.write("%s, " % line)

# myfile.write("]")

# myfile.close()
