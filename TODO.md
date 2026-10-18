# Tinos NX

This TODO outlines the requirements and planned features for each subsystem of the operating system.

## Kernel

- [ ] Boot and kernel initialization
- [ ] Global Descriptor Table (GDT)
- [ ] Interrupt Descriptor Table (IDT)
- [ ] Exception and interrupt handling
- [ ] Timer subsystem
- [ ] Physical memory manager
- [ ] Virtual memory manager
- [ ] Thread scheduler
- [ ] Process and thread management
- [ ] Kernel synchronization primitives
- [ ] System call interface
- [ ] Handle and object management
- [ ] Kernel debugging and logging

## HAL

- [ ] CPU and architecture initialization
- [ ] Interrupt controller support
- [ ] Timer hardware abstraction
- [ ] Memory-map integration
- [ ] PCI and PCIe enumeration
- [ ] Storage controller support
- [ ] USB support
- [ ] Graphics hardware support
- [ ] Ethernet drivers
- [ ] Wireless and Bluetooth support

## Executive and I/O

- [ ] Native object and handle management
- [ ] I/O request management
- [ ] Device management
- [ ] Virtual filesystem (VFS)
- [ ] Filesystem drivers
- [ ] Storage and block-device layer
- [ ] IPC and synchronization APIs

## Binaries and Compatibility

### Windows

- [ ] PE32+ executable loader
- [ ] Windows API compatibility implementation
- [ ] Native API compatibility layer (NT API)
- [ ] Route supported Windows API calls through the compatibility subsystem to native Tinos NX services
- [ ] Windows process and thread semantics
- [ ] Windows-compatible DLL loading
- [ ] Windows application environment

### Linux

- [ ] ELF64 executable loader
- [ ] Linux x86-64 syscall compatibility
- [ ] Map supported Linux syscalls to native Tinos NX services
- [ ] Linux process and thread semantics
- [ ] Linux-compatible signal handling
- [ ] Linux-compatible filesystem conventions
- [ ] Shared library loading
- [ ] Linux application environment

### Native

- [ ] Native executable format and loader
- [ ] Native application API
- [ ] Native process and thread APIs
- [ ] Native filesystem APIs
- [ ] Native graphics and windowing APIs
- [ ] Native IPC APIs
- [ ] Native development SDK

## Bootloader

- [ ] Custom x86-64 bootloader
- [ ] UEFI boot support
- [ ] Kernel image loading
- [ ] Memory-map handoff
- [ ] Boot information structure
- [ ] Transfer control to the kernel
