# ----------------------------------------------------------------------------
#  Toolchain CMake file for configure the LLVM tools setup
#
#  Find more details on the README.md of the project
#
#  Zero Day Code, 2023
#  
#  Contributors:
#   -  Alex Vergara (@Pyzyrab)
# ----------------------------------------------------------------------------

# Assuming that you already have a LLVM installation in your path...
set(CMAKE_C_COMPILER "clang.exe")
set(CMAKE_CXX_COMPILER "clang++.exe")

# Set the triple-target
set(TRIPLE_TARGET x86_64-windows-gnu)
set(CMAKE_CXX_COMPILER_TARGET ${TRIPLE_TARGET})

# CXX flags
set(LIBCPP          -stdlib=libc++)
set(CPPABI          -lc++abi)
set(LUNWIND         -lunwind)
set(UNWIND_TABLES   -funwind-tables)
set(EXCEPTS         -fexceptions)
set(RTTI            -frtti)

# Append the cfg flags to the CXX flags
set(CMAKE_CXX_FLAGS "${LIBCPP} ${UNWIND_TABLES} ${RTTI}")

# Linker flags
set(USE_LLD -fuse-ld=lld)

set(CMAKE_EXE_LINKER_FLAGS_INIT "${USE_LLD} ${LIBCPP} ${UNWIND_TABLES} ${RTTI}")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT}")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "${CMAKE_EXE_LINKER_FLAGS_INIT}")
