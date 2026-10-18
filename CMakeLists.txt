cmake_minimum_required(VERSION 4.0)

find_program(CLANGXX_EXECUTABLE clang++ REQUIRED)
find_program(NASM_EXECUTABLE nasm REQUIRED)

set(CMAKE_CXX_COMPILER
    "${CLANGXX_EXECUTABLE}"
    CACHE FILEPATH "C++ compiler" FORCE
)
set(CMAKE_ASM_NASM_COMPILER
    "${NASM_EXECUTABLE}"
    CACHE FILEPATH "NASM compiler" FORCE
)
set(CMAKE_ASM_NASM_OBJECT_FORMAT
    elf64
    CACHE STRING "NASM object format" FORCE
)

project(TinosNX CXX ASM_NASM)

# -------------------------------------
#        Tools
# -------------------------------------
find_program(QEMU_EXECUTABLE qemu-system-x86_64 REQUIRED)
find_program(GRUB_FILE_EXECUTABLE grub-file REQUIRED)
find_program(GRUB_MKRESCUE_EXECUTABLE grub-mkrescue REQUIRED)

#-------------------------------------
#        Sources
#-------------------------------------
file(GLOB_RECURSE TinosNXKernel_CXX_SOURCES
CONFIGURE_DEPENDS
    "kernel/*.cpp"
)

file(GLOB_RECURSE TinosNXKernel_ASM_SOURCES
CONFIGURE_DEPENDS
    "kernel/*.S"
)

#-------------------------------------
#    Build Assembly
#-------------------------------------
set(KERNEL_ASM_OBJECTS)

foreach(ASM_SOURCE ${TinosNXKernel_ASM_SOURCES})

file(RELATIVE_PATH ASM_RELATIVE
"${CMAKE_SOURCE_DIR}"
"${ASM_SOURCE}"
)

string(REPLACE "/" "_" ASM_NAME "${ASM_RELATIVE}")

set(ASM_OBJECT
"${CMAKE_BINARY_DIR}/asm/${ASM_NAME}.o"
)

add_custom_command(
OUTPUT "${ASM_OBJECT}"

COMMAND ${CMAKE_COMMAND} -E make_directory
"${CMAKE_BINARY_DIR}/asm"

COMMAND ${NASM_EXECUTABLE}
-f elf64
-g
-F dwarf
-o "${ASM_OBJECT}"
"${ASM_SOURCE}"

DEPENDS "${ASM_SOURCE}"

VERBATIM
)

list(APPEND KERNEL_ASM_OBJECTS "${ASM_OBJECT}")

endforeach()


add_executable(TinosNXKernel
${TinosNXKernel_CXX_SOURCES}
${KERNEL_ASM_OBJECTS})


set_target_properties(TinosNXKernel PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
)


target_include_directories(TinosNXKernel PRIVATE
    "${CMAKE_SOURCE_DIR}/kernel"
    "${CMAKE_SOURCE_DIR}/kernel/internal"
)


# -------------------------------------
#      Compiler flags
# -------------------------------------
target_compile_options(TinosNXKernel PRIVATE 
    -m64
    -ffreestanding
    -Wall
    -Wextra
    -nostdlib
    -fno-stack-protector
    -Wno-unused-parameter
    -fno-stack-check
    -fno-lto
    -mno-mmx
    -mno-80387
    -mno-sse
    -mno-sse2
    -mno-red-zone
    -fno-pic
    -mcmodel=kernel
    -fno-exceptions
    -fno-rtti
    -fno-use-cxa-atexit
)

target_link_options(TinosNXKernel PRIVATE
    -fuse-ld=lld
    -nostdlib
    -no-pie
    -Wl,-m,elf_x86_64
    -Wl,-T,${CMAKE_SOURCE_DIR}/kernel/linker.ld
    -Wl,-z,noexecstack
)

# ------------------------------------------------------------
# ISO
# ------------------------------------------------------------

set(ISO_ROOT
"${CMAKE_BINARY_DIR}/iso_root"
)

set(ISO_FILE
"${CMAKE_BINARY_DIR}/TinosNX.iso"
)

add_custom_command(
OUTPUT "${ISO_FILE}"

COMMAND ${CMAKE_COMMAND} -E make_directory
"${ISO_ROOT}/boot/grub"

COMMAND ${CMAKE_COMMAND} -E copy
"$<TARGET_FILE:TinosNXKernel>"
"${ISO_ROOT}/boot/TinosNXKernel"

COMMAND ${CMAKE_COMMAND} -E copy
"${CMAKE_SOURCE_DIR}/boot/grub.cfg"
"${ISO_ROOT}/boot/grub/grub.cfg"

COMMAND ${GRUB_FILE_EXECUTABLE}
--is-x86-multiboot
"$<TARGET_FILE:TinosNXKernel>"

COMMAND ${GRUB_MKRESCUE_EXECUTABLE}
-o "${ISO_FILE}"
"${ISO_ROOT}"

DEPENDS TinosNXKernel

VERBATIM
)

add_custom_target(iso ALL
DEPENDS "${ISO_FILE}"
)

# ------------------------------------------------------------
# Run in QEMU
# ------------------------------------------------------------

add_custom_target(run
COMMAND ${QEMU_EXECUTABLE}
-m 192M
-debugcon stdio
-cdrom "${ISO_FILE}"
-boot d

DEPENDS iso

USES_TERMINAL
)

# ------------------------------------------------------------
# Run QEMU with GDB
# ------------------------------------------------------------

add_custom_target(run-gdb
COMMAND ${QEMU_EXECUTABLE}
-m 192M
-debugcon stdio
-cdrom "${ISO_FILE}"
-boot d
-S
-s

DEPENDS iso

USES_TERMINAL
)