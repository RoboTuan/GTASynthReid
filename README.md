# GTA Dataset
## A novel synthetic dataset for pedestrian reidentification.
`WARNING: this dataset might contain nudity`
***

This synthetic dataset was generated by exploiting the graphic engine of *Grand Theft Auto V*. There are 538 individuals captured in several urban scenarios with a total of 19 different camera positions (both overlapping and non-overlapping). Every pedestrian has been recorded at least by 2 cameras with an average of 3.5 up to 5 cameras. The video sequences have been recorded both during day and night, with different kinds of weather ( blizzard, rain, clear). The pedestrians, therefore, could have been recorded with different illumination and weather settings. The assumption is that each identity maintains the same clothing in all the videos. The total number of bounding boxes is 94312 and it ranges from 29 to 496 for each pedestrian. For more statistics you can see [this](https://github.com/RoboTuan/Pedestrian_reID/blob/main/Peds/statistics.csv) file. 

To simulate a realistic scenario, the generated bounding boxes are not "perfect" an can include bodyparts of other peds or entire peds in the background. The bounding boxes also include occlusion by objects or they are recorded even if they are far away from the camera and the scenarios are relatively crowded. Below there are some examples.

![overlappings_occlusions](https://raw.githubusercontent.com/RoboTuan/Pedestrian_reID/main/Images/overlappings_occlusions.png?token=ANC4UTMKVT4MNNTGZ5J4ZTDATGOSK)

Some of the individuals share similar clothes, even if they represent different identities. This happpens especially for those who wear a uniform or a suit and in low illumination settings. In the picture below, each column represent a couple of peds with similar appearance.

![similar_peds](https://raw.githubusercontent.com/RoboTuan/Pedestrian_reID/main/Images/similar_peds.png?token=ANC4UTJXZGPF4BBCGKCHFIDATJCYO)

## Get the dataset
There are different versions of this dataset:
* Download the raw frames (and joint information) from our recorded game sequences [here]()
* Dowload the dataset with the selected bounding boxes for each individual [here]()
* Download the dataset with the selected bounding boxes splitted for training and testing [here]()

In case you would like to record your own scenarios or select different bounding boxes from our recorded sequences, visit the [home](https://github.com/RoboTuan/Pedestrian_reID/wiki) of our wiki.

## Dataset notation
A scenario is a particolar location in the map of the game. A sequence is a recorded video that can contain up to 2 camera views (recording at 1920x1080, 30 FPS each) and it can be splitted up to 2 videos. A sequence can be recorded both at day time and at night time with the same pedestrians. A camera is identified by its coordinates and axis rotation.

The following example exaplains the bounding box naming: `42647445_sd000c1_0396.jpeg` 

* `42647445` is the ped identifier
* `sd` means that the sequence was recorded during day time (`sn` for night)
* `000` is the sequence number
* `c1` means that this bounding box was recorded by the camera 1 in this sequence (there can be up to 2 cameras in each sequence)
* `0396` is the frame number

In the dataset with the training-testing splits, instead of `c1` or `c2` you will find the unique identifier of the camera (from 1 to 19), such as `c08`. There is a [script](https://github.com/RoboTuan/Pedestrian_reID/blob/main/Scripts/training_dataset.py) that transforms the dataset from the first namining convention to the second one.



