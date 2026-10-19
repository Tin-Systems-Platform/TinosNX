# Tinos NX

Tinos NX is an open-source operating system aiming to support Windows applications and Linux binaries on a single platform.

The project aims to provide compatibility with Windows applications, including those built for Windows 11, alongside support for Linux x86-64 binaries. It will also feature a native application environment and APIs.

Tinos NX currently targets **x86-64** systems. ARM64 support may be considered in the future.

## Toolchain

Tinos NX is written primarily in C++ and uses CMake as its build system. NASM is used for assembly code, and Clang is the primary compiler.

## Building

### Prerequisites

- CMake
- Clang and LLD
- GRUB tools
- NASM
- Make or Ninja
- QEMU (for running and testing the OS)

The required tools must be available in your system's `PATH`.

### Building from source

Clone the repository and navigate to the source directory.

Create a build directory and configure the project:

```sh
mkdir build
cd build
cmake ..
```

To use Ninja instead of Make, configure the build with:

```sh
cmake -G Ninja ..
```

Build the kernel:

```sh
make
```

If you configured the project with Ninja, use:

```sh
ninja
```

### Running

To run the OS using the configured run target:

```sh
make run
```

With Ninja:

```sh
ninja run
```

The run target uses QEMU to launch Tinos NX for testing.