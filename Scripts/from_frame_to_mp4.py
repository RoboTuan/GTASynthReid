import ffmpeg
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--input', type=str, required=True, help='Path to the coords.csv file for annotations')
parser.add_argument('--output', type=str, required=True, help='Path to the coords.csv file for annotations')
args, _ = parser.parse_known_args()

input = args.input
output = args.output

# input example: '/path/to/sequences/seq_0_60/cam2/*.jpeg'
# output example: '/path/to/sequences/seq_0_60/cam2.mp4'

(
    ffmpeg
    .input(input + '/*.jpeg', pattern_type='glob', framerate=30)
    .output(output)
    .run()
)