# Sudoku

### Goals

- make sudoku game without step-by-step tutorials
- learn some cpp basics and SDK using
- learn basics of SDL (https://www.libsdl.org/)

### Summary

-

### Build issues

It may be tricky to link SDL extensions (SDL2_ttf, SDL2_Image, etc.).
If you have troubles after installing some of them, try to google for files like `FindSDL2_ttf.cmake` (or make yours...)
and copy them into /Modules of your cmake like in `.../clion-2021.2/bin/cmake/linux/share/cmake-3.20/Modules/`. 
It shows cmake how to find necessary extension.
