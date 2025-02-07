#!/bin/bash

# Directory where the .cub files are stored (change if needed)
MAP_DIR="./maps/good/"

# List of all .cub files (based on the screenshot)
MAPS=(
	"big.cub"
	"bigger.cub"
	"bigger2.cub"
	"bigger3_1080.cub"
	"cheese_maze.cub"
	"cows_2.cub"
	"cows_3.cub"
	"cows_horse_1.cub"
	"cows_horse_2.cub"
	"explotation.cub"
	"creepy.cub"
	"dungeon.cub"
	"example.cub"
	"library.cub"
	"matrix.cub"
	"order.cub"
	"sad_face.cub"
	"square_map.cub"
	"subject_map.cub"
	"test_map.cub"
	"test_pos_bottom.cub"
	"test_pos_left.cub"
	"test_pos_right.cub"
	"test_pos_top.cub"
	"test_textures.cub"
	"test_whitespace.cub"
	"test_spiral.cub"
	"works.cub"
)

# Loop through each map and run ./cub3d
for MAP in "${MAPS[@]}"; do
	echo -e "\e[31mTesting:$MAP_DIR$MAP\e[0m"
	./cub3D "$MAP_DIR$MAP"
	echo "-------------------------------------"
done
