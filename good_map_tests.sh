#!/bin/bash

# Directory where the .cub files are stored (change if needed)
MAP_DIR="./maps/good/"

# List of all .cub files (based on the screenshot)
MAPS=(
	"cheese_maze.cub"
	"creepy.cub"
	"dungeon.cub"
	"library.cub"
	"matrix.cub"
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
	"example.cub"
)

# Loop through each map and run ./cub3d
for MAP in "${MAPS[@]}"; do
	echo -e "\e[31mTesting:$MAP_DIR$MAP\e[0m"
	./cub3D "$MAP_DIR$MAP"
	echo "-------------------------------------"
done
