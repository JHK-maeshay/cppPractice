# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 4.0

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\HKIT\Desktop\conda\c\cppPractice

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\HKIT\Desktop\conda\c\cppPractice\build

# Utility rule file for uninstall.

# Include any custom commands dependencies for this target.
include source/glfw-master/CMakeFiles/uninstall.dir/compiler_depend.make

# Include the progress variables for this target.
include source/glfw-master/CMakeFiles/uninstall.dir/progress.make

source/glfw-master/CMakeFiles/uninstall:
	cd /d C:\Users\HKIT\Desktop\conda\c\cppPractice\build\source\glfw-master && C:\mingw64\bin\cmake.exe -P C:/Users/HKIT/Desktop/conda/c/cppPractice/build/source/glfw-master/cmake_uninstall.cmake

source/glfw-master/CMakeFiles/uninstall.dir/codegen:
.PHONY : source/glfw-master/CMakeFiles/uninstall.dir/codegen

uninstall: source/glfw-master/CMakeFiles/uninstall
uninstall: source/glfw-master/CMakeFiles/uninstall.dir/build.make
.PHONY : uninstall

# Rule to build all files generated by this target.
source/glfw-master/CMakeFiles/uninstall.dir/build: uninstall
.PHONY : source/glfw-master/CMakeFiles/uninstall.dir/build

source/glfw-master/CMakeFiles/uninstall.dir/clean:
	cd /d C:\Users\HKIT\Desktop\conda\c\cppPractice\build\source\glfw-master && $(CMAKE_COMMAND) -P CMakeFiles\uninstall.dir\cmake_clean.cmake
.PHONY : source/glfw-master/CMakeFiles/uninstall.dir/clean

source/glfw-master/CMakeFiles/uninstall.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\HKIT\Desktop\conda\c\cppPractice C:\Users\HKIT\Desktop\conda\c\cppPractice\source\glfw-master C:\Users\HKIT\Desktop\conda\c\cppPractice\build C:\Users\HKIT\Desktop\conda\c\cppPractice\build\source\glfw-master C:\Users\HKIT\Desktop\conda\c\cppPractice\build\source\glfw-master\CMakeFiles\uninstall.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : source/glfw-master/CMakeFiles/uninstall.dir/depend

