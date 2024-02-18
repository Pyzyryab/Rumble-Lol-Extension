<h1 align="center">The Rumble Lol Plugin for Rumble-AI</h1>

<h3 align="center"> Welcome to the Rumble LoL Plugin, or **RLP** for short.

This is the documentation (developer oriented) for the project.
</h3>

<div align="center">

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)

[![Build Rumble LoL Plugin](https://img.shields.io/github/actions/workflow/status/zerodaycode/Rumble-Lol-Plugin/build_cmake.yml?style=for-the-badge)](https://github.com/zerodaycode/Rumble-LoL-Plugin/actions/workflows/build_cmake.yml)
[![Windows Installer](https://img.shields.io/github/release/zerodaycode/Rumble-LoL-Plugin.svg?style=for-the-badge)](https://github.com/zerodaycode/Rumble-LoL-Plugin/actions/workflows/release.yml)
[![Code Quality](https://img.shields.io/github/code-quality/zerodaycode/Rumble-LoL-Plugin.svg?style=for-the-badge)](https://github.com/zerodaycode/Rumble-LoL-Plugin/actions/workflows/code-quality.yml)
[![Coverage CD/CI](https://img.shields.io/github/index/zerodaycode/Rumble-LoL-Plugin.svg?style=for-the-badge)](https://zerodaycode.github.io/Rumble-LoL-Plugin/index.html)

[![GitHub Issues](https://img.shields.io/github/issues/zerodaycode/Rumble-LoL-Plugin?style=for-the-badge)](https://github.com/zerodaycode/Rumble-LoL-Plugin/issues)
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/zerodaycode/Rumble-LoL-Plugin?style=for-the-badge)](https://github.com/zerodaycode/Rumble-LoL-Plugin/pulls)
[![License](https://img.shields.io/github/license/zerodaycode/Rumble-LoL-Plugin?style=for-the-badge)](/LICENSE)

</div>

# 📝 Table of Contents

<div align="center">

[Building the project](#building-the-project) | [CMake and LLVM tools on Windows](#cmake-and-llvm-tools-on-windows) | [Getting Started](#getting-started) | [Configuring and building the project](#configuring-and-building-the-project) | [Running the project](#running-the-project) | [Legacy build system way](#legacy-build-system-way) | [Technical specification overview](#technical-specification-overview) | [Building process (setuptools and (CMake?), maybe Zork++)]() | [Contributing](./CONTRIBUTING.md) | [License](./LICENSE)

</div>

## TODO make a deep explanation of the project

## Building the project

In order to build this project, we provide two different options for you to consider what's the best approach while building the project.

### A bit of history of our setup

In the early times, this was developed on Microsoft's `Visual Studio`, using all its power to generate the `C++` library, and
glue the code to generate the `Python` module, that ultimately will run as a plugin of `Rumble-AI`, but we liked to move
towards a more **Open Source** type of tools.

So, later, we started to use the `setuptools` Python's module to build the project. This approach is really nice, and an
easy one to set up, so it was really convenient at that time. That allowed us to use other editors, and a build system that didn't
depend on the many configuration files that come attached with `VS` projects. Altough it was a nice step, we felt like we still needed the
Microsoft compiler, their `STD library` implementation, so on and so forth...

## CMake and LLVM tools on Windows

This is our main way of build and compile the project. In `Zero Day Code`, we are big fans of the `LLVM` project.
For that reason, we set up an intricate way of building the project, however, in exchange, we are building it with zero proprietary
dependencies.

After a long time with the project unmaintained, we decided to come back and this time we bring with us a new approach.
We managed to base our build process in the following components:

- Make
- CMake
- The LLVM project, for getting the clang compiler frontend and its **C++** marvelous tools, like code formatters, static analyzers, address sanitizers...
- Python

>[!NOTE]
>
> This approach will require a **MSYS2** installation, and get all the components through the `Clang64` environment.
> It's technically possible to make the same job that we will explain below with other type of installations,
> tools or environments besides the ones that we share on the documentation steps and that we will support.
> Nonetheless, feel free to play as much as you want with other tools, and propose any if yopu find them better and increase the project by cointributing to it.

We will be using those three, and no others, from the `Clang64` environment of **MSYS2**.

> [!NOTE] 
>
> We found tons of problems with this setup, until we managed to make it work consistently and
> productively. The thing is that other installations may silently interfere in your development journey, like other Python
> versions installed in your machine. Not for sure, but keep that in mind.

### Gather the dependencies required

Open the **MSYS2** **Clang64** terminal and download the following tools

```bash
pacman -S mingw-w64-clang-x86_64-cmake
pacman -S mingw-w64-clang-x86_64-ninja
pacman -S mingw-w64-clang-x86_64-clang
pacman -S mingw-w64-clang-x86_64-llvm (already gathered with `pacman -S mingw-w64-clang-x86_64-clang`)
pacman -S mingw-w64-clang-x86_64-llvm-libs (already gathered with `pacman -S mingw-w64-clang-x86_64-clang`)
pacman -S mingw-w64-clang-x86_64-clang-analyzer (non required, but nice to have)
pacman -S mingw-w64-clang-x86_64-lld (already gathered with `pacman -S mingw-w64-clang-x86_64-clang`)
pacman -S mingw-w64-clang-x86_64-libc++ (already gathered)
pacman -S mingw-w64-x86_64-libunwind
pacman -S mingw-w64-clang-x86_64-clang-tools-extra
pacman -S pacman -S mingw-w64-clang-x86_64-compiler-rt (already gathered with `pacman -S mingw-w64-clang-x86_64-clang`)
pacman -S mingw-w64-clang-x86_64-gcc-compat
```

> Feel free to merge them in just one command.

### Optimizing your development workflow with `Make` (recommended)

If you want to take advantage of working with the `Makefiles` configured for the project, you'll need the following one:

```bash
pacman -S mingw-w64-clang-x86_64-make
```

#### Renaming the `Make` binary (optional)

The downloaded binary comes named as `ming32-make.exe`.

For convenience, you can go to the `clang64` **bin** folder of your **MSYS2** installation, and just rename the binary by strip
the prefix before the hyphen (and the hyphen itself) so you end up having a `make.exe` binary.

From this:

![Alt text](/docs/assets/mingw32-make.png)

To this:

![Alt text](/docs/assets/make.png)

> We'll assume that you did this optional step when explain *make* commands. If not, you'll must use original binary name.

You have a more in-depth description of the tools in a toy project used as example
on how to integrate this setup with OpenCV on Windows [here](https://github.com/Pyzyryab/OpenCV-Clang-Windows)

> With this build system we aren't able to compile **OpenCV** from scratch with `Clang`, because `Clang` refuses to compile certain parts of `OpenCV` (while other
> compilers are just fine). Don't worry, we stand on the side of the `Clang's` perspective. But we are just able to provide an `OpenCV` version up until the `4.6.0` (included).
> This is the one that is downloaded, built and installed directly by `CMake`. Don't worry about it, but we just want to let you know.

### Add them to your path (optional)

To make things easier, we just add the **MinGW** `Clang64` environment to our *PATH* in our personal
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

3. Finally:

```bash
cmake --build .
```
> [!IMPORTANT] 
>
> The first time that you configure and build the project, you must be patient. It took a bit
> to download and configure `OpenCV`, and the first time also takes a long time to build it.

### Do it in one line

Those steps above are the classical way of configure and build a `CMake` based project. But you can create the `build` directory
and run `CMake` configure and build process from the project's root in a nice one-liner with the following command:

```bash
cmake -S . -B ./build -G "Ninja" -DCMAKE_TOOLCHAIN_FILE=./clang-x86_64_windows_gnu.cmake && cmake --build ./build
```

> By default, the project is build in *Debug* mode. If you want to test a **release** version, just add to
> the command line `-DCMAKE_BUILD_TYPE=Release`, or use the `make build_release`
>[!NOTE]
>
> Project's dependencies are built in **release** mode always.

### Make support

We've recently added support for `Make` via Makefiles. This allows us to have a nice and better workflow while we're
working on the project. Available `Make` commands are:

- `make configure` or `make configure_r` for work targeting release builds
- `make compile`
- `make run`

#### Cleaning the project

Sometimes comes in handy to have a fresh clean. You can just delete the `build` and `install` folders, or just

- `make clean`

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

or with `Make`:

```bash
make run
```

And you should see the application running directly in your terminal.

To see what options are available to control, you might want to take a look to the
source code where they are defined, in [this translation unit](./code/rumble_lol_plugin/league_client/api_buttons.hpp)

### TODO make a real list with the available actions (through buttons)

### Running as a Rumble-AI plugin (#TODO)

#### TODO ideas for the description

- Get Rumble-AI
- Install the RLP plugin
- Or maybe generate a Python package with all the deps and DLLs?

## Legacy build system way

We already discussed the `setuptools` way. This one is the easiest way possible of building the project, and it's configured out of the
box to work immediately. On the other hand, its code and configuration aren't as accurate as possible, and you won't use what we consider
the best technologies available.

But it could be a solution if you don't want to have the **MinGW** setup, or if you already have an installation of `OpenCV` or whatever
good reason is.

> [!NOTE] 
>
> Take in consideration that this method could be deprecated soon, as we are planning to change our way to interact with
> the **League of Legends** client, and instead as parse it as image and manually click handling the mouse pointer, we will change
> to directly make REST API calls. This will probably introduce `***The Rust Programming Language*** into the ecosystem,
> and will be glued with some existent C++ code in the codebase.

For now, our project heavy relies on [OpenCV](https://opencv.org), specifically in this release [4.8.0](https://opencv.org/releases/),
so, for you to be able to run the project, you'll need an installation of `OpenCV`.

> To build the project with this approach, we support up until OpenCV <= 4.8.1.

We assume up until this point, that you already installed `OpenCV`. Where you installed it, it's completely up to you,
but remember to modify the `include` paths accordingly in the [setup.py](./python/c++_bindings/setup.py),
as well as the ones to the dependent libraries and DLL's.

The best part of this procedure is that is extremely straightforward. You just need to literally use *Python's pip* package manager
to get the job done.

> Is possible that we're missing certain Python packages. So, while installing, if some package is missing just `pip install <package_name>`
> and try again.

From the root of the project, you just need to invoke:

```bash
pip install ./python/c++_bindings/setup.py
```

You'll see the process build starting. If everything goes well, `pip` will automatically make the `C++` code a library that will be generated
in a way that `Python` will specifically understand and therefore consume.

Additionally, it will install directly `RLP` in your *Python* installation, so the only thing that you'll need to start to use it is:

```Python
import rlp

# Rest of your Python code...
```

## Technical specifications overview

### Project layout

For this project, at this time of writing (11/2023), and after two years without develop nor maintaining this codebase,
we are adapting our project layout [to this specification](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html)
just for the sake of having a good internal structure and coherence in the project layout, but introducing an intermediate
folder named code, mixing the modern GitHub CI typical configurations and furthermore, to hide our `includePath` from the
root of the project, taking as "root" `<rumble_league_plugin/...>`

### C++

TODO - Language level, build system, compilation process?

### Python

## Building process (setuptools and (CMake?), maybe Zork++)
