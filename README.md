# Simple Paint Application

A lightweight paint application built with SDL2 and C++ featuring a simple drawing interface with a color palette and brush tool.

## Features

- **Freehand Drawing**: Draw smooth lines by holding down the mouse button
- **Color Palette**: 8 built-in colors to choose from
  - Black
  - White (Eraser)
  - Red
  - Green
  - Blue
  - Yellow
  - Cyan
  - Magenta
- **Circular Brush**: Smooth round brush with configurable size
- **Clean Canvas**: Start with a white background
- **60 FPS Performance**: Smooth drawing experience with frame rate control

## Screenshots

![Ultra Paint Application](screenshot.png)

*The application features an 8-color palette at the top and a 900x600 pixel drawing canvas*

## Prerequisites

- C++ Compiler (supporting C++11 or later)
- SDL2 Library (version 2.32.8)
- Visual Studio 2022 or later (for Windows builds)

## Installation

### Windows (Visual Studio)

1. Clone the repository:
```bash
git clone https://github.com/R3ality-Architect/simple-paint-using-sdl2-and-Cpp.git
cd simple-paint-using-sdl2-and-Cpp
```

2. Open the solution file `paint.slnx` in Visual Studio

3. The project is configured to use NuGet packages for SDL2 dependencies. These should restore automatically:
   - `sdl2.nuget` (2.32.8)
   - `sdl2.nuget.redist` (2.32.8)

4. Build and run the project (F5)

## Usage

1. **Drawing**: Click and drag anywhere on the white canvas to draw
2. **Changing Colors**: Click on any color in the palette bar at the top of the window
3. **Erasing**: Select the white color from the palette to erase
4. **Exit**: Close the window or press the window's close button

## Technical Details

### Architecture

- **Window Size**: 900x600 pixels
- **Brush Size**: 10 pixels (circular)
- **Target FPS**: 60 frames per second
- **Rendering**: CPU-based rendering using SDL surfaces

### Key Components

- `draw_circle()`: Renders a filled circle at the cursor position using pixel-perfect collision detection
- `draw_palette()`: Displays the color selection palette
- `check_color_palette_chosen()`: Handles color selection from palette clicks
- Event-driven architecture using SDL's event polling system

### Performance Considerations

- Surface locking for systems that require it
- Bounds checking to prevent out-of-window drawing
- Frame rate limiting to maintain consistent 60 FPS

## Building from Source

The project uses Visual Studio project files (`.vcxproj`) and can be built for:
- Win32 (x86)
- x64

Both Debug and Release configurations are available.

## Project Structure

```
simple-paint-using-sdl2-and-Cpp/
├── paint/
│   ├── main.cpp              # Main application source
│   ├── paint.vcxproj         # Visual Studio project file
│   ├── paint.vcxproj.filters # VS project filters
│   └── packages.config       # NuGet package configuration
├── paint.slnx                # Solution file
└── README.md                 # This file
```

## License

This project is open source and available under the MIT License.

## Contributing

Contributions are welcome! Feel free to submit issues or pull requests.

## Future Enhancements

Potential features for future development:
- Adjustable brush size
- Save/Load functionality
- More drawing tools (rectangle, line, fill)
- Undo/Redo functionality
- Custom color picker
- Additional brush shapes

## Author

**R3ality-Architect**

## Acknowledgments

- Built with [SDL2 (Simple DirectMedia Layer)](https://www.libsdl.org/)
- SDL2 packages provided via NuGet