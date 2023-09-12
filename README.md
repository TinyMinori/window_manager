# Window Manager


## Description

This project is for now a test but I want to make it bigger with an entire graphical interface and it could be usable on ArchLinux.


## Build & Test

Before building the project you will need the `libx11`, a g++ compiler, and `xorg-xinit`, `xorg-server-xephyr`, `xclock`, `xeyes` and `xterm` for the testing part.

``` bash
# Build the Project
$ make all

# Clean Object Files
$ make clean

# Clean Object Files and Binary
$ make fclean

# Clean Object Files, Binary and Build the Project
$ make re

# Test the Project
$ make test
```

## Have Fun Testing

🌱

## Features

#### 2020-06-28 | First Steps
- Can show an xorg app
- Can only close xterm 'cause X button isn't yet available for windows
