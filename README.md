# Cubo-rubick

This repository contains the Computer Graphics ( **CS251** ) class at *Universidad Católica San Pablo*  final assignment that was to write write througth the semester a Rubick's cube that could solve itself and has unique animations that we came up with.

## Authors

- **Jhorel Kevin Revilla Calderon** - [Profile](https://github.com/jhorelrevilla)

- **Rafael Isaac Cano Guitton** - [Profile](https://github.com/rafaelcanoguitton)

- **Jeisson Edgard Yato Tintaya** - [Profile](https://github.com/JYato)

## Requirements

It's a **C++** project that uses CMake to be compiled, you can find project structure in ` CMakeLists.txt` file [here](CMakeLists.txt). The dependencies are the following and depending on the operating system that you want to compile it installing may vary. If you want to compile it on windows need to set up some enviroment variables on the entire operating system for it to work. Luckily we all used Linux so we didn't need to do any of that, although `CMakeLists.txt` is modified to run conflict free on Linux. You need to have the following installed to run the project: 

* [GLFW](https://www.glfw.org/)
* [GLAD](https://github.com/Dav1dde/glad)
* [GLM](https://github.com/g-truc/glm) (**We use it for camera movement but we have our own-made library for every transformation refer to `Matrices.h`**)
* [FREEIMAGE](https://freeimage.sourceforge.io/)
* [FREEGLUT](http://freeglut.sourceforge.net/)
* [GLEW](http://glew.sourceforge.net/)

## Instructions

After all dependencies have been installed and the correct enviroment you can compile the project simply by issuing a cmake command

```bash
cmake .
```

Or use your own parameters for your preferred **IDE** and project structure.

## Demo

Part of the assignment was to show the following views:

- **First view** : Which shows the Rubik's Cube in it's original form showing the textures applied to each face.
  
  ![](https://media.giphy.com/media/DFXnvH0v14d1YR323U/giphy.gif)

- **Second view** : Shows the cube and it's movements.
  
  ![](https://media.giphy.com/media/rZ9dcvcAZbEr5roWUb/giphy.gif)

- **Third view** : That shows the cube solving itself using the solver we attached to the project.
  
  ![](https://media.giphy.com/media/TdXsvvPIlxD8PqVpyq/giphy.gif)

- **Fourth view** : Showing our unique animation .
  
  ![](https://media.giphy.com/media/pWuPqLuHqYD90HEKYl/giphy.gif)

## Solver

We used Kociemba's two phase algorithm modified to get the solution in 20 movents or less found [here](https://github.com/muodov/kociemba/tree/master/kociemba/ckociemba).
