# CPPND: Capstone Project: Pinball Game

## Background

This repository is for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
The aim is to showcase a simple, independently developed application in C++.

## Overview and Game Control

The game implemented is a simple Pinball with left and right flippers and two elements where the ball can bounce off.
* Left and right arrow keys activate the flippers
* Space bar gives a new ball

## Limitations and Known Issues

* Very simple approximate physics
* The ball rolling down the flippers is not very realistic.
* Ball can slide down to the right edge of the frame.

<img src="pinball.png"/>

## References

This repository is forked from https://github.com/udacity/CppND-Capstone-Snake-Game, which in turn is inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl).
My game implementation is inspired by the 2D game app [Vector Pinball for Android] (https://github.com/dozingcat/Vector-Pinball)

## Licenses

* Source code (src) inherits the CC ShareAlike license from where it was forked.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Pinball`.


## Project Criteria Satisfied (examples)

* C++ control structures: loop in Game::Run
* User input processing: keyboard input in Controller::HandleInput
* Object Oriented Programming: all classes
* Access specifiers: for instance see ball.h
* Member initialization lists: Ball::Ball
* References in functions: Renderer::Render, Flipper::IsColliding
* Encapsulation: pure state accessors are declared const, for instance Flipper::GetAngle


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
