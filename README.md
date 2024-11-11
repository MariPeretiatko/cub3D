# cub3D

**cub3D** is a simple pseudo-3D game developed using the **raycasting** algorithm. This project simulates 3D-like graphics in a 2D space, creating an immersive maze-like experience where the player navigates through a world with walls, textures, and customizable floor and ceiling colors.

## Requirements

- **MiniLibX** library for rendering graphics.
- The program takes a **.cub** scene description file as its first argument.
- The map in the **.cub** file must consist of specific characters to define walls, floor, ceiling, and player spawn orientation.

## Features

### **Game Mechanics**
- **Movement:** The player can move through the maze using **W, A, S, D** keys.
- **Look Around:** Use the **left** and **right arrow** keys to change the player's viewpoint.
- **Exit:** Press **ESC** to quit or click the window's red cross to exit cleanly.

### **Map Configuration**
The map is described in a **.cub** file, where:
- **Textures:** The map allows the definition of textures for walls (North, South, East, West).
- **Colors:** You can set the floor and ceiling colors using RGB values.
- **Valid Map Characters:**  
  - `1` for walls
  - `0` for empty spaces
  - `N`, `S`, `E`, `W` for player’s start position and orientation

### **Error Handling**
- The program checks for errors in the map configuration (e.g., missing textures, invalid characters) and prints an explicit error message if something goes wrong.

This is an example of a valid map:

```
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture

F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### **Bonus Features**
- **Wall Collisions:** The player interacts with the walls, which block movement.
- **Minimap:** A small minimap is displayed to help navigate the maze.
- **Doors:** Represented by the symbol `D`, doors can open and close within the game.
- **Animated Sprites:** Added for more dynamic visual effects.
- **Mouse Support:** The player can rotate the point of view with the mouse for enhanced control.

## How to Play

1. **Compile the program**: Follow the instructions in the repository to compile the project.
2. **Prepare a `.cub` file**: Create a scene file with textures, colors, and a maze layout.
3. **Run the program**: Launch the game with your `.cub` file as the argument.

Example:  
```bash
make bonus
```
```bash
./cub3D_bonus maps/minimap_fixing.cub
```
