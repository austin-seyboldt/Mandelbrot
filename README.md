# INFORMATION

This program will simulate the mandelbrot equation.  
There is no ui; all values, such as simulation iteration-count and display resolution must be edited in the code.  
Written for x86 machines, using SFML.


## BUILD

I have only tested this on ubuntu and do not know how it will behave on other systems.

SFML is not packaged with the distribution and must be installed on your system.

Make sure you have the required dependencies:
```
sudo apt update
sudo apt install g++ build-essential libsfml-dev
```

To build, run `make`. The executable will be in the `dist/` directory.

To run: `./dist/mandelbrot`


## CONTROLS

**Mouse**:
Put the cursor where you would like to zoom in, scroll to zoom in or out.

**Keyboard Controls:**
| Key  | Action                  |
|------|-------------------------|
| A    | Zoom Out               |
| D    | Zoom In                |
| F    | Enter/Exit fullscreen  |
| R    | Reset to default view  |
| S    | Take a screenshot      |
| ESC  | Close the window       |

# Future Ideas:

1. Change Color Scheme While Running
2. Offload Rendering to gpu shaders
3. Smooth scroll
4. Drag to move around

## Example Images

![](./example_images/Mandelbrot_x-0.108989_-0.108935y-0.897852_-0.897822.jpg)
![](./example_images/Mandelbrot_x-0.233312_-0.233282y-0.233297_-0.651734.jpg)
![](./example_images/Mandelbrot_x-0.374000_-0.373947y-0.659786_-0.659756.jpg)
![](./example_images/Mandelbrot_x-0.530234_-0.526038y-0.510855_-0.508495.jpg)
![](./example_images/Mandelbrot_x-0.548899_-0.548845o-0.548872_-0.552938.png)