# The Rumble LoL Plugin for Rumble-AI

Welcome to the Rumble LoL Plugin, or **RLP** for short.
This is the documentation (developer oriented) for the project.

#### TODO 

Add CI status badges (when actions are configured) and a index summary with hyperlinks

## Dependencies

> Note that you can replace our dependencies with the one that you want to use, but that's mean that we won't accept
> any kind of *PR* which modifies the versions of the dependencies of the project

### C++

For now, our project heavy relies on [OpenCV](https://opencv.org), concretely in this release [4.8.0](https://opencv.org/releases/),
so, for you to be able to run the project, you'll need that installation.

We are using `C:` as the root for the `OpenCV` installation. You'll find this on the installation scripts, pointing towards
those locations concretely.

### Python

TODO - Install via pip with pip freeze?
TODO - Add a venv?

## Get started

We assume up until this point, that you already installed `OpenCV`. Where you installed it, it's completely up to you,
but remember to modify the `include` paths accordingly in the [setup.py](./python_mod/c++_bindings/setup.py),
as well the ones to the dependent libraries and dll's

## Technical specification overview

### Project layout

For this project, at this time of writing (11/2023), and after two years without develop nor maintaining this codebase,
we are adapting our project layout [to this specification](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html)
just for the sake of having a good internal structure and coherence in the project layout, but introducing an intermediate
folder named code, mixing the modern GitHub CI typical configurations and furthermore, for hide our `includePath` from the
root of the project, taking as "root" `<rumble_league_plugin/...>`

### C++

TODO - Language level, build system, compilation process?

### Python

## Building process (setuptools and (CMake?), maybe Zork++)