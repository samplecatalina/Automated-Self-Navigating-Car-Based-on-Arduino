# Automated Self-Navigating Car, Based on Arduino

*C, Self-Navigating Car, Arduino*

Completed in Oct, 2022

## Table of Contents

- [Automated Self-Navigating Car, Based on Arduino](#automated-self-navigating-car-based-on-arduino)
  - [Table of Contents](#table-of-contents)
  - [Structure of repo](#structure-of-repo)
  - [Dependencies](#dependencies)

## Structure of repo

- `.vscode/` - various adjustments for Visual Studio Code users for easier coding, such as updating `includePath` property so that VS Code can recognise our header files. Configurations available for Windows, macOS and Linux.
  - If you are developing on Windows, it is important to run 
    ```powershell
    git config --global core.autocrlf false
    ```
    to avoid any strange conflicts that might come in commit diffs based on how Windows handle end-of-line characters, as well as setting your end-of-line sequence in your IDE to "LF" rather than "CRLF".
- `include/` - folder containing header files (files that have the `.h` extension) - these usually contain code we want to import in other files.
- `os/` - folder which contains OS-specific files for compilation - for our case, this contains the SDL2 and SDL2_gfx files required just for Windows users.
- `src/` - folder containing source code files (files that have the `.c` extension) - these control how various components of our program work.
- `Makefile` - automatically compiles program and allows for easy checking of source code changes by using the Make build automation program.
- `build_run_clean.sh` - Bash shell script to to easily build, run, and clean up files after building program in one step for macOS and Linux - a really handy shortcut!
- `build_run_clean.sh` - a Batch script for Windows that does the same things as `build_run_clean.sh`, just, well, for Windows.

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

