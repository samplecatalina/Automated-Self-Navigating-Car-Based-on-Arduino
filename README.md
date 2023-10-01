# Automated Self-Navigating Car, Based on Arduino

*C, Self-Navigating Car, Arduino*

Completed in Oct, 2022

## Table of Contents

- [Automated Self-Navigating Car, Based on Arduino](#automated-self-navigating-car-based-on-arduino)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Structure of repo](#structure-of-repo)
  - [Dependencies](#dependencies)

## Overview
This project represents a sophisticated and well-architected solution for an Automated Self-Navigating Car utilizing Arduino as the core component. The car is capable of navigating through intricate mazes and avoiding obstacles, demonstrating advanced robotics and automation principles.

## Key Features
- **Advanced Navigation:** Employs complex algorithms to navigate through mazes and avoid obstacles efficiently.
- **Modular Design:** Structured with clear and concise code, segregated into multiple files for easy understanding and modification.
- **Comprehensive Documentation:** Detailed comments and documentation are provided to understand the intricacies of the project.
- **Cross-Platform Compatibility:** Accompanied by build scripts for both Windows and Unix-based systems, ensuring ease of use across different platforms.
- **Robust Error Handling:** Implemented with meticulous error handling to manage unforeseen situations and ensure smooth operation.

## Structure of repo

- `.vscode/` - various adjustments for Visual Studio Code users for easier coding, such as updating the `includePath` property so that VS Code can recognize our header files. Configurations are available for Windows, macOS, and Linux.
  - If you are developing on Windows, it is important to run 
    ```PowerShell
    git config --global core.autocrlf false
    ```
    to avoid any strange conflicts that might come in commit diffs based on how Windows handles end-of-line characters, as well as setting your end-of-line sequence in your IDE to "LF" rather than "CRLF".
- `include/` - folder containing header files (files that have the `.h` extension) - these usually contain code we want to import into other files.
- `os/` - folder which contains OS-specific files for compilation - for our case, this contains the SDL2 and SDL2_gfx files required just for Windows users.
- `src/` - folder containing source code files (files that have the `.c` extension) - these control how various components of our program work.
- `Makefile` - automatically compiles the program and allows for easy checking of source code changes by using the Make build automation program.
- `build_run_clean.sh` - Bash shell script to to easily build, run, and clean up files after building a program in one step for macOS and Linux - a really handy shortcut!
- `build_run_clean.sh` - a Batch script for Windows that does the same things as `build_run_clean.sh`, just, well, for Windows.

- **src/**
  - **main.c:** Entry point of the application.
  - **robot.c:** Contains the logic related to the robot's movements and actions.
  - **wall.c:** Manages the wall and obstacle-related functionalities.
  - **formulas.c:** Houses mathematical formulas used in the project.
  - **mazeSetup.txt, mazeSetup2.txt, mazeSetup3.txt:** Maze configuration files.
- **include/**
  - **robot.h, wall.h, formulas.h, structures.h:** Header files containing declarations and documentation.

## Technical Stack
- **Programming Language:** C
- **Platform:** Arduino
- **Build Tools:** Makefile, build_run_clean.bat (Windows), build_run_clean.sh (Unix)

## Dependencies

- GCC compiler for code
  - On Windows, you will have to install a toolkit which supports this. The most common one is Mingw-w64 - instructions for installing are below.
  - On macOS, if you have Command Line Tools for Xcode installed, `gcc` points to Clang to compile C programs, which effecitvely produces the same output.
  - On Linux, `gcc` should be available from most distro's repositories.
- SDL2 (included in repository for Windows)
- SDL2_gfx (included in repository for Windows)
- Make program for interpreting makefiles
  - On Windows, we will use `mingw32-make` from Mingw-w64
  - On macOS, this is usually preinstalled as `make`
  - On Linux, this is available in most distro repositories as `make`


