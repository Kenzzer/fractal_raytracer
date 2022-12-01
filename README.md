# ISIM - ANDRE Benoist, HUSAK Ihor, HARRIS ERWANN

![fractal image preview](https://cdn.discordapp.com/attachments/552909803933007928/1047827220879659038/output.png)

## Dependencies

- LibPNG
- ZLib

Don't forget to init the submodules. This will pull latest libpng & zlib from their official git repository.
Simply run `git submodule update --init`

## Requirements

- Linux/MacOs (The project can be compiled on windows, but it hasn't been tested there)
- Clang/Gcc (C++20 or higher)

## How to compile

- `mkdir build`
- `cd build`
- `cmake ..`
- `make`

## How to use
You must be in the project root dir, leave the build folder if you're still in it.

Scene files are located in the `resources` directory. Take a look at `resources/light_scene.json` if you're interested in how to make a scene for yourself. (Hint: the available object types are `sphere` `cube_box` `menger`).

Let's render our basic raytracer scene.
`./build/isim ./resources/light_scene.json ./build/output_light.png`

If you want to render our sponge fractal.
`./build/isim ./resources/result_scene_1.json ./build/output_sponge.png`

## How to watch results ?
Open the png file you generated.

## What about animated results ?
Unfortunately, we didn't have time to code camera movement in the json file. Therefore it has to be done in code, and repeatedly call the function `snapshot` in main.cpp. Of course this is less than ideal, and we don't recommend that you bother doing this.
