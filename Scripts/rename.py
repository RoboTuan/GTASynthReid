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

for ped in peds:
    if ped == "Dataset.txt":
        continue
    bboxes_path = os.path.join(dataset, ped)
    bboxes = os.listdir(bboxes_path)
    # print(bboxes)
    # Check for .DS_Store
    if ".DS_Store" in bboxes:
        bboxes.remove(".DS_Store")
    bboxes.sort()

    for bbox in bboxes:
        # print(bbox)
        extension = bbox.split(".")[-1]
        old_naming = bbox.split(".")[0] # Remove the .jpeg extension
        id = old_naming.split("_")[0]
        seq_camera = old_naming.split("_")[-1]

        # print(seq_camera)
        seq = seq_camera.split("c")[0]
        # print(seq)
        seq_number = ''.join([s for s in seq if s.isdigit()])
        # print(seq_number)
        seq_camera = "s" + seq[1] + seq_number.zfill(3) + "c" +  seq_camera.split("c")[-1]
        # print(seq_camera)

        frame = old_naming.split("_")[1]
        new_naming = id + "_" + seq_camera + "_" + frame + "." + extension
        os.rename(os.path.join(bboxes_path, bbox), os.path.join(bboxes_path, new_naming))
        # print(new_naming)
        # print()
    # sys.exit()
    