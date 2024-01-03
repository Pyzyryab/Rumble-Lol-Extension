# The Rumble LoL Plugin for Rumble-AI

Welcome to the Rumble LoL Plugin, or **RLP** for short.
This is the documentation (developer oriented) for the project.

#### TODO

- Add CI status badges (when actions are configured)
- An index summary with hyperlinks

## TODO make a deep explanation of the project

## Building the project

In order to build this project, we provide two different options that you may want to choose.

### A bit of history of our setup

In the early times, this was developed on Microsoft's `Visual Studio`, using all its power for generate the `C++` library, and
glue the code to generate the `Python` module, that ultimately will run as a plugin of `Rumble-AI`, but we liked to move
towards a more **Open Source** kind of tools.

So, later, we started to use the `setuptools` Python's module to build the project. This approach is really nice, and an
easy one to set up, so it was really welcome at that time. That allowed us to use other editors, and a build system that didn't
depend on the many configuration files that come attached with `VS` projects. Even tho, was a nice step, but we still need the
Microsoft compiler, their `STD library` implementation, so on and so forth...

## CMake and LLVM tools on Windows

This is our main way of build and compile the project. Here, in `Zero Day Code`, we are big fans of the `LLVM` project.
For that reason, we set up an intricate way of building the project, but, in exchange, we are building it with zero proprietary
dependencies.

After a long time with the project unmaintained, we decided to came back. And this time we bring with us other approach.
And we managed to base our build process in the following components:

- CMake
- LLVM tools
- Python

> *Note*: This approach will require a **MSYS2** installation, and get all the components through the `Clang64` environment.
> Even tho is technically possible to make the same job that we will explain below with other kind of installations,
> tools or environments, that's the one that we prefer, that we will document and will support.
> But feel free to play as much as you want with other tools, and propose any if better.

We will be using those three, and no others, from the `Clang64` environment of **MSYS2**.

> *Note*: We found tons of problems with this setup, until we managed to make it work consistently and
> productively. The thing is that other installations may silently interfere in your development journey, like other Python
> versions installed in your machine. Not for sure, but keep that in mind.

### Gather the dependencies required

Open the **MSYS2** **Clang64** terminal and download the following tools

```bash
pacman -S mingw-w64-clang-x86_64-cmake
pacman -S mingw-w64-clang-x86_64-ninja
pacman -S mingw-w64-clang-x86_64-clang
pacman -S mingw-w64-clang-x86_64-llvm
pacman -S mingw-w64-clang-x86_64-llvm-libs
pacman -S mingw-w64-clang-x86_64-clang-analyzer
pacman -S mingw-w64-clang-x86_64-lld
pacman -S mingw-w64-clang-x86_64-libc++
pacman -S mingw-w64-x86_64-libunwind
pacman -S mingw-w64-clang-x86_64-clang-tools-extra
pacman -S pacman -S mingw-w64-clang-x86_64-compiler-rt
pacman -S mingw-w64-clang-x86_64-gcc-compat
```

> Feel free to merge them in just one command.

You have a more in-depth description of the tools in a toy project used as example
on how to integrate this setup with OpenCV on Windows [here](https://github.com/Pyzyryab/OpenCV-Clang-Windows)

> With this build system we aren't able to compiling **OpenCV** from scratch with `Clang`, because `Clang` refuses to compile certain parts of `OpenCV` (while other
> compilers are just fine). Don't worry, we stand on the side of the `Clang's` perspective. But we are just able to provide a `OpenCV` version up until the `4.6.0` (included).
> This is the one that is downloaded, built and installed directly by `CMake`. Don't worry about it, but we just want to let you know.

### Add them to your path (optional)

For making the things easier, we just add the **MinGW** `Clang64` environment to our *PATH* in our personal
computers. Take this in consideration, because certain elements are configured assuming this premise.

## Configuring and building the project

With all the dependencies that we need gathered, now is straightforward to configure and build the project.

1. Create a new `build` directory and move inside it.

This is where all the elements of the compilation process will be placed, and from where the build process will be triggered.

```bash
mkdir build
cd build
```

2. From the build directory, call `CMake` to configure and build the project

```bash
cmake -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=./clang-x86_64_windows_gnu.cmake
```

and then:

```bash
cmake --build .
```

> **IMPORTANT:* The first time that you configure and build the project, you must be patient. It took a bit
> to download and configure `OpenCV`, and the first time also takes a long time to build it.

## Running the project

Now that finally the project has been built, it's time to finally use the `Rumble-LoL-Plugin`.

### Running in STANDALONE mode

For developers, we create a small custom script that takes care of setting up the plugin in standalone mode.
This means, without being a `plugin` working inside `Rumble-AI`.

The main purpose of this mode is to let the developers quickly debug changes made without having to worry about
to plugin it into the virtual assistant.

This mode just takes text directly by the command line to perform actions that match voice patterns. i.e, the same
as you would say to the virtual assistant, but directly from terminal, so you can quickly debug changes and speed
up the introduction of new functionalities.

For this, from the root of the project, just run:

```bash
python ./python/run_rlp.py
```

And you should see the application running directly in your terminal.

For see what options are available to control, you main want to take a look to the
source code where they are defined, in [this translation unit](./code/rumble_lol_plugin/league_client/api_buttons.hpp)

### TODO make a real list with the available actions (through buttons)

### Running as a Rumble-AI plugin (#TODO)

#### TODO ideas for the description

- Get Rumble-AI
- Install the RLP plugin
- Or maybe generate a Python package with all the deps and DLLs?

## Legacy build system way

We already discussed the `setuptools` way. This one is the easiest way possible of building the project, and it's configured out of the
box for work immediately. On the other hand, it's code and configuration aren't as accurate as possible, and you won't use what we consider
the best technologies available.

But it could be a solution if you don't want to have the **MinGW** setup, or if you already have an installation of `OpenCV` or whatever
good reason is.

> *NOTE:* Take in consideration that this method could be deprecated soon, as we are planning to change our way to interact with
> the **League of Legends** client, and instead as parse it as image and manually click handling the mouse pointer, we will change
> to directly make REST API calls. This will probably introduce `***The Rust Programming Language*** into the ecosystem,
> and will be glued with some existent C++ code in the codebase.

For now, our project heavy relies on [OpenCV](https://opencv.org), concretely in this release [4.8.0](https://opencv.org/releases/),
so, for you to be able to run the project, you'll need an installation of `OpenCV`.

> For building the project in this way, we support up until OpenCV <= 4.8.1.

We assume up until this point, that you already installed `OpenCV`. Where you installed it, it's completely up to you,
but remember to modify the `include` paths accordingly in the [setup.py](./python/c++_bindings/setup.py),
as well the ones to the dependent libraries and DLL's.

The best part of this procedure is that is extremely straightforward. You just need to literally use *Python's pip* package manager
to get the job done.

> Is possible that we're missing certain Python packages. So, while installing, if some package is missing just `pip install <package_name>`
> and try again.

From the root of the project, you just need to invoke:

```bash
pip install ./python/c++_bindings/setup.py
```

You'll see the process build starting. If everything goes well, `pip` will automatically make the `C++` code a library that will be generated
in a way that `Python` will specifically understand and therefore, that can consume.

Also, it will install directly `RLP` in your *Python* installation, so the only thing that you'll need to start to use it is:

```Python
import rlp

# Rest of your Python code...
```

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
