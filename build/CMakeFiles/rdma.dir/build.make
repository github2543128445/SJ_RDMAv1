# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kvgroup/louzy/SJ_RDMA/rlib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kvgroup/louzy/SJ_RDMA/rlib/build

# Include any dependencies generated for this target.
include CMakeFiles/rdma.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rdma.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rdma.dir/flags.make

# Object files for target rdma
rdma_OBJECTS =

# External object files for target rdma
rdma_EXTERNAL_OBJECTS =

librdma.a: CMakeFiles/rdma.dir/build.make
librdma.a: CMakeFiles/rdma.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kvgroup/louzy/SJ_RDMA/rlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX static library librdma.a"
	$(CMAKE_COMMAND) -P CMakeFiles/rdma.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rdma.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rdma.dir/build: librdma.a

.PHONY : CMakeFiles/rdma.dir/build

CMakeFiles/rdma.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rdma.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rdma.dir/clean

CMakeFiles/rdma.dir/depend:
	cd /home/kvgroup/louzy/SJ_RDMA/rlib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kvgroup/louzy/SJ_RDMA/rlib /home/kvgroup/louzy/SJ_RDMA/rlib /home/kvgroup/louzy/SJ_RDMA/rlib/build /home/kvgroup/louzy/SJ_RDMA/rlib/build /home/kvgroup/louzy/SJ_RDMA/rlib/build/CMakeFiles/rdma.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rdma.dir/depend
