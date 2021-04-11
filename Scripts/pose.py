# -*- coding: utf-8 -*-
# ---------------------

from typing import *

import cv2
import numpy as np

from joint import Joint

import sys


class Pose(list):
	"""
	a Pose is a list of Joint(s) belonging to the same person.
	"""

	LIMBS = [
		(0, 1),  # head_top -> head_center
		(1, 2),  # head_center -> neck
		(2, 3),  # neck -> right_clavicle
		(3, 4),  # right_clavicle -> right_shoulder
		(4, 5),  # right_shoulder -> right_elbow
		(5, 6),  # right_elbow -> right_wrist
		(2, 7),  # neck -> left_clavicle
		(7, 8),  # left_clavicle -> left_shoulder
		(8, 9),  # left_shoulder -> left_elbow
		(9, 10),  # left_elbow -> left_wrist
		(2, 11),  # neck -> spine0
		(11, 12),  # spine0 -> spine1
		(12, 13),  # spine1 -> spine2
		(13, 14),  # spine2 -> spine3
		(14, 15),  # spine3 -> spine4
		(15, 16),  # spine4 -> right_hip
		(16, 17),  # right_hip -> right_knee
		(17, 18),  # right_knee -> right_ankle
		(15, 19),  # spine4 -> left_hip
		(19, 20),  # left_hip -> left_knee
		(20, 21)  # left_knee -> left_ankle
	]

	SKELETON = [[l[0] + 1, l[1] + 1] for l in LIMBS]


	def __init__(self, joints):
		# type: (List[Joint]) -> None
		super().__init__(joints)


	@property
	def invisible(self):
		# type: () -> bool
		"""
		:return: True if all the joints of the pose are occluded, False otherwise
		"""
		for j in self:
			if not j.occ:
				return False
		return True


	@property
	def bbox_2d(self):
		# type: () -> List[int]
		"""
		:return: bounding box around the pose in format [x_min, y_min, width, height]
			- x_min = x of the top left corner of the bounding box
			- y_min = y of the top left corner of the bounding box
		"""
		x_min = int(np.min([j.x2d for j in self]))
		y_min = int(np.min([j.y2d for j in self]))
		x_max = int(np.max([j.x2d for j in self]))
		y_max = int(np.max([j.y2d for j in self]))
		width = x_max - x_min
		height = y_max - y_min
		return [x_min, y_min, width, height]
	
	
	@property
	def bbox_2d_padded(self, h_inc_perc=0.15, w_inc_perc=0.1):
		x_min = int(np.min([j.x2d for j in self]))
		y_min = int(np.min([j.y2d for j in self]))
		x_max = int(np.max([j.x2d for j in self]))
		y_max = int(np.max([j.y2d for j in self]))
		width = x_max - x_min
		height = y_max - y_min

		inc_h = (height * h_inc_perc) / 2
		inc_w = (width * w_inc_perc) / 2

		x_min = x_min - inc_w
		x_max = x_max + inc_w

		y_min = y_min - inc_h
		y_max = y_max + inc_h

		width = x_max - x_min
		height = y_max - y_min

		return [x_min, y_min, width, height]

	
	@property
	def coco_annotation(self):
		# type: () -> Dict
		"""
		:return: COCO annotation dictionary of the pose
		==========================================================
		NOTE#1: in COCO, each keypoint is represented by its (x,y)
		2D location and a visibility flag `v` defined as:
			- `v=0` ==> not labeled (in which case x=y=0)
			- `v=1` ==> labeled but not visible
			- `v=2` ==> labeled and visible
		==========================================================
		NOTE#2: in COCO, a keypoint is considered visible if it
		falls inside the object segment. In JTA there are no
		object segments and every keypoint is labelled, so we
		v=2 for each keypoint.
		==========================================================
		"""
		keypoints = []
		for j in self:
			keypoints += [j.x2d, j.y2d, 2]
		annotation = {
			'keypoints': keypoints,
			'num_keypoints': len(self),
			'bbox': self.bbox_2d
		}
		return annotation


	def draw(self, image, color, bbox_name=None):
		# type: (np.ndarray, List[int], str) -> np.ndarray
		"""
		:param image: image on which to draw the pose
		:param color: color of the limbs make up the pose
		:return: image with the pose
		"""
		# # draw limb(s) segments
		# for (j_id_a, j_id_b) in Pose.LIMBS:
		# 	joint_a = self[j_id_a]  # type: Joint
		# 	joint_b = self[j_id_b]  # type: Joint
		# 	t = 1 if joint_a.cam_distance > 25 else 2
		# 	if joint_a.is_on_screen and joint_b.is_on_screen:
		# 		cv2.line(image, joint_a.pos2d, joint_b.pos2d, color=color, thickness=t)

		# # draw joint(s) circles
		# for joint in self:
		# 	image = joint.draw(image)


		# Get bounding box
		x_min, y_min, width, height = self.bbox_2d
		#print(x_min, y_min, width, height)
		# If padding is selected for the bounding box,
		# convert the box to np.float32 in order to be able to
		# draw it with "cv2.rectangle"
		x_min = np.float32(x_min)
		y_min = np.float32(y_min)
		width = np.float32(width)
		height = np.float32(height)

		# Start coordinate, here (x_min, y_min + height) 
		# represents the top left corner of rectangle 
		start_point = (x_min, y_min + height)
		
		# Ending coordinate, here (x_min + width, y_min) 
		# represents the bottom right corner of rectangle 
		end_point = (x_min + width, y_min)
		
		# Purple color in RGB
		# Comment to used default person color
		#color = (255, 0, 255)

		# Line thickness of 2 px 
		thickness = 2
		
		# Using cv2.rectangle() method 
		# Draw a rectangle with blue line borders of thickness of 2 px 
		#print(start_point, end_point)
		# print(image.shape)
		# print([j.person_id for j in self])
		# import sys
		# sys.exit()
		# start_point = (np.float32(1841.3), np.float32(1422.425))
		# end_point = (np.float32(2164.7), np.float32(986.575))
		# print(start_point, end_point)
		
		if bbox_name is not None:
			# Save bbox without drawing the rectangle and the id
			# print(image[1080-1, 1920-1])

			# Image shape: (1080, 1920, 3)-> (heigh, width, channels)

			# If the width or height are gigantic, don't save this boundin box
			if width >= image.shape[1]/2 or height >= image.shape[0]/2:
				return image

			# If the leftmost point of the bbox is outside the rightmost
			# point of the image, don't save this bounding box
			if start_point[0] >= image.shape[1]:
				# print(start_point[0], image.shape[1])
				return image

			# If the rightmost point of the bbox is outside the leftmost
			# point of the image, don't save this bounding box
			if end_point[0] < 0:
				# print(start_point[0], image.shape[1])
				return image

			# If the bottommost point of the bbox is above the topmost
			# point of the image, don't save this bounding box
			if end_point[1] >= image.shape[0]:
				# print(end_point[1], start_point[1], image.shape)
				return image

			# If the topmost point of the bbox is under the bottommost
			# point of the image, don't save this bounding box
			if start_point[1] < 0:
				return image


			# If the leftmost point of the bbox is outside the leftmost
			# point of the image, put the former equal to the latter
			if start_point[0] < 0:
				start_point = (0, start_point[1])

			# If the rightmost point of the bbox is outside the rightmost
			# point of the image, put the former equal to the latter
			if end_point[0] >= image.shape[1]:
				# print(end_point[0])
				original_area = (start_point[1]-end_point[1]) * (end_point[0]-start_point[0])
				end_point = (image.shape[1] - 1, end_point[1])
				# print(end_point[0])
				new_area = (start_point[1]-end_point[1]) * (end_point[0]-start_point[0])	

			# If the topmost point of the bbox is outside the topmost
			# point of the image, put the former equal to the latter
			if start_point[1] >= image.shape[0]:
				start_point = (start_point[0], image.shape[0]-1)

			# If the bottommost point of the bbox is outside the bottommost
			# point of the image, put the former equal to the latter
			if end_point[1] < 0:
				end_point = (end_point[0], 0)

			# If the image is a line or the starting and end point coincide,
			# don't save this bounding box
			if start_point[0] == end_point[0] or start_point[1] == end_point[1]:
				return image

			new_width = end_point[0] - start_point[0]
			new_height = start_point[1] - end_point[1]

			# If the current aspect ration is too "strange" (like a horizotal
			# line), don't save this bounding box
			if new_width > new_height:
				return image

			# If the new width or the new height are gigantic, don't save this boundin box
			if new_width >= image.shape[1]/2 or new_height >= image.shape[0]/2:
				return image
			
			# print half image for debug
			#bbox = image[0:int(image.shape[0]/2), 0:int(image.shape[1]/2)]
			
			# Enlarge or narrow image in order to have the desired
			# aspect ratio (in this case we want height/width=2),
			# suppose the most significance dimension is the height,
			# we have to adjust the width accordingly.
			proportional_width = new_height * 64 / 128

			# Take a bbox with the same aspect ratio of 64x128 (wxh).
			residual_width = proportional_width - new_width
			fractional, integral = np.modf(residual_width/2)

			# Ensure not to go outside of the image by means of width,
			# put <= 0 and not < 0 otherwise the 0 case is not controlled
			# and in the last "else" it could go outside the image with the 2*fractional.
			if start_point[0] - integral <= 0:
				diff = integral - start_point[0]
				start_point = (0, start_point[1])
				end_point = (end_point[0] + diff + integral + int(2*fractional), end_point[1])
			
			elif end_point[0] + integral >= image.shape[1]:
				diff = end_point[0]+integral - (image.shape[1]-1)
				end_point = (image.shape[1]-1, end_point[1])
				# If fractional is < 0.5, since we then use integer, it will go to 0,
				# but is not so dramatic for the resizing
				start_point = (start_point[0] - diff - integral - int(2*fractional), start_point[1])

			else:
				# Put the 2*fractional only on one of the 2 points, it will be at maximum 1
				# so it won't affect much the result
				start_point = (start_point[0] - integral - int(2*fractional), start_point[1])
				end_point = (end_point[0] + integral, end_point[1])


			new_width = end_point[0] - start_point[0]
			new_height = start_point[1] - end_point[1]

			# If the new width or the new height are gigantic, don't save this boundin box
			if new_width >= image.shape[1]/2 or new_height >= image.shape[0]/2:
				return image

			# print(bbox_name, start_point, end_point)
			bbox = image[int(end_point[1]):int(start_point[1]), int(start_point[0]):int(end_point[0])]
			bbox_resized = cv2.resize(bbox, (64, 128), interpolation = cv2.INTER_AREA)
			cv2.imwrite(bbox_name, bbox_resized)

		else:
			# Draw rectangle and text
			image = cv2.rectangle(image, start_point, end_point, color, thickness)
			# Draw text with person id
			# font
			font = cv2.FONT_HERSHEY_SIMPLEX
			
			# org 
			org = start_point
			
			# fontScale 
			fontScale = 1

			# text
			# each person has 22 joints, see if the person_id is the same if I select different joints
			index = np.random.randint(0, 22)
			text = str(self[index].person_id)

			image = cv2.putText(image, text, org, font,
					fontScale, color, thickness, cv2.LINE_AA)

		return image


	def __iter__(self):
		# type: () -> Iterator[Joint]
		return super().__iter__()
