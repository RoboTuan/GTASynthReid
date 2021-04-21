# -*- coding: utf-8 -*-
# ---------------------

import json
import sys
from typing import *
import os
import cv2

import click
import matplotlib.pyplot as plt
import numpy as np
from path import Path

from joint import Joint
from pose import Pose

MAX_COLORS = 42

# check python version
assert sys.version_info >= (3, 6), '[!] This script requires Python >= 3.6'


def get_colors(number_of_colors, cmap_name='rainbow'):
	# type: (int, str) -> List[List[int]]
	"""
	:param number_of_colors: number of colors you want to get
	:param cmap_name: name of the colormap you want to use
	:return: list of 'number_of_colors' colors based on the required color map ('cmap_name')
	"""
	colors = plt.get_cmap(cmap_name)(np.linspace(0, 1, number_of_colors))[:, :-1]*255
	return colors.astype(int).tolist()


def get_pose(frame_data, person_id):
	# type: (np.ndarray, int) -> Pose
	"""
	:param frame_data: data of the current frame
	:param person_id: person identifier
	:return: list of joints in the current frame with the required person ID
	"""
	pose = [Joint(j) for j in frame_data[frame_data[:, 1] == person_id]]
	pose.sort(key=(lambda j: j.type))
	return Pose(pose)


H1 = 'path of the video you want to visualize annotations'
H2 = 'path of JSON containing the annotations you want to visualize'
H3 = 'path of the output video with the annotations'
H4 = 'if `hide` the annotations of people completely occluded by objects will not be displayed in the output video'


@click.command()
@click.option('--in_frames_path', type=click.Path(exists=True), prompt='Enter \'jpeg_frames_path\'', help=H1)
@click.option('--json_file_path', type=click.Path(exists=True), prompt='Enter \'json_file_path\'', help=H2)
@click.option('--out_bboxes_path', type=click.Path(), prompt='Enter \'out_bboxes_path\'', help=H3)
@click.option('--hide/--no-hide', default=True, help=H4)
def main(in_frames_path, json_file_path, out_bboxes_path, hide):
	# type: (str, str, str, bool) -> None
	"""
	Script that provides a visual representation of the annotations
	"""

	# Replacing double slashes since I need to index with slashes
	in_frames_path = in_frames_path.replace("//", "/")

	# Example in_frames_path: ~/Desktop/JTA/airport_entrance/seq_0_day_60/cam1/
	# in_frames_path.split("/")[-1] is "" since it's on the right of cam1
	camera = in_frames_path.split("/")[-2]
	seq = in_frames_path.split("/")[-3].split("_")[1]
	day_night = in_frames_path.split("/")[-3].split("_")[2][0]

	out_bboxes_path = Path(out_bboxes_path)
	if not out_bboxes_path.parent.exists() and out_bboxes_path.parent != Path(''):
		out_bboxes_path.parent.makedirs()

	with open(json_file_path, 'r') as json_file:
		data = json.load(json_file)
		data = np.array(data)

	colors = get_colors(number_of_colors=MAX_COLORS, cmap_name='jet')

	# CHECK FOR THE .DS_Store
	images = [item for item in sorted(os.listdir(in_frames_path)) if item != ".DS_Store"]

	print(f'▸ bounding boxes of \'{Path(in_frames_path).abspath()}\'')
	for frame_number, image in enumerate(images):

		# NOTE: frame #0 does NOT exists: first frame is #1
		frame_data = data[data[:, 0] == frame_number + 1]  # type: np.ndarray
		image = cv2.imread(in_frames_path + image)

		frame_boxes = np.empty((0,4), int)
		frame_box_ids = []

		for p_id in set(frame_data[:, 1]):
			# p_id = 3118269184
			pose = get_pose(frame_data=frame_data, person_id=p_id)
			# for p in pose:
			# 	print(pose)

			# if the "hide" flag is set, ignore the "invisible" poses
			# (invisible pose = pose of which I do not see any joint)
			if hide and pose.invisible:
				continue
			if hide and pose.occluded_percentage:
				continue
			

			p_id_folder = out_bboxes_path + "/" + str(int(p_id)) + "/"
			if not os.path.exists(p_id_folder):
				os.makedirs(p_id_folder)

			# select pose color base on its unique identifier
			color = colors[int(p_id)%len(colors)]

			str_frame_number = str(frame_number).zfill(4)
			bbox_name = p_id_folder + str(int(p_id)) + "_s" + day_night + seq.zfill(3) + "c" + camera[-1] + "_" +  str_frame_number + ".jpeg"
			points = pose.draw(image=image, color=color, bbox_name=bbox_name)
			if points is not None:
				frame_box_ids.append(bbox_name)
				# start_point_y, end_point_y, start_point_x, end_point_x = points
				# print(frame_boxes.shape, np.array([points]).shape)
				frame_boxes = np.append(frame_boxes, np.array([points]), axis=0)
				# bbox = image[start_point_y:end_point_y, start_point_x:end_point_x]
				# bbox_resized = cv2.resize(bbox, (64, 128), interpolation = cv2.INTER_AREA)
				# cv2.imwrite(bbox_name, bbox_resized)
		
		# # Save the bounding boxes of the frame
		# for box, ped in zip(frame_boxes, frame_box_ids):
		# 	# The notation is different from that of pose.py but more clear
		# 	# since in pose.py end_point_y < start_point_y but here we
		# 	# can redefine the variable names in a clearer way
		# 	end_point_y, start_point_y , start_point_x, end_point_x = box		
		# 	bbox = image[end_point_y:start_point_y, start_point_x:end_point_x]
		# 	bbox_resized = cv2.resize(bbox, (64, 128), interpolation = cv2.INTER_AREA)
		# 	name = ped
		# 	cv2.imwrite(name, bbox_resized)


		# Save the bounding boxes of the frame
		for box1, ped1 in zip(frame_boxes, frame_box_ids):
			end_point_y1, start_point_y1, start_point_x1, end_point_x1 = box1
			intersection = False	
			for box2, ped2 in zip(frame_boxes, frame_box_ids):
				if ped1 == ped2:
					continue
				end_point_y2, start_point_y2, start_point_x2, end_point_x2 = box2
				
				start_point_x_inter = max(start_point_x1, start_point_x2)
				start_point_y_inter = min(start_point_y1, start_point_y2)
				end_point_x_inter = min(end_point_x1, end_point_x2)
				end_point_y_inter = max(end_point_y1, end_point_y2)

				width_inter = end_point_x_inter - start_point_x_inter
				hight_inter = start_point_y_inter - end_point_y_inter

				if width_inter > 0 or hight_inter > 0:
					area1 = abs(end_point_x1-start_point_x1) * abs(end_point_y1-start_point_y1)
					# area2 = abs(end_point_x2-start_point_x2) * abs(end_point_y2-start_point_y2)
					# max_area = max(area1, area2)
					area_inter = width_inter * hight_inter
					if area_inter > area1*0.6:
						intersection = True
						break			
			
			if intersection is True:
				break
			else:
				bbox = image[end_point_y1:start_point_y1, start_point_x1:end_point_x1]
				bbox_resized = cv2.resize(bbox, (64, 128), interpolation = cv2.INTER_AREA)
				name = ped1
				cv2.imwrite(name, bbox_resized)


		#writer.append_data(np.vstack([image, image[-8:, :]]))
		print(f'\r▸ progress: {100*(frame_number/899):6.2f}%', end='')

	#writer.close()
	print(f'\n▸ video with annotations: \'{out_bboxes_path.abspath()}\'\n')


if __name__ == '__main__':
	main()