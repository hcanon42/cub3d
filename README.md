# Cub3D
Welcome to the first graphic project from 42!

## Table of Content

* [Technologies](#technologies)
* [Description](#description)
* [Installation](#installation)
* [Usage](#usage)
* [Utility](#utility)
* [Contributing](#contributing)

## Technologies

Project is created with:
* gcc 9.3.0
* minilibx-linux latest

## Description

The aim of the project is to create a maze from a .cub map.\
The process of creating a visual aspect for the maze is done by raycasting, which is launching virtual rays for every pixel of the window from the character point of view.\
The ray stops when it hits a wall, then returns the distance it travelled.
The bigger the distance, the further the wall is from the character and so we just have to scale the size of the wall for it to be realistic.\
I also implemented sprites, textures, a HUD, Hitpoints, an end to the maze and a score to beat !

## Installation

Just pull the project !

## Usage

Classic 42 Makefile:
````sh
make add	#compiles everything
make clean	#removes all the .o files
make erase	#removes all the .o files and executable binary
make reset	#cleans everything in the project and compiles everything again
````

Particular to this project:
````sh
./Cub3D [path_to_map] #let's play !
````

## Utility

Great project overall, with some playful goal which is always rewarding while working !

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
