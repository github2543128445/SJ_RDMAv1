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
include CMakeFiles/RC_WRITE_client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RC_WRITE_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RC_WRITE_client.dir/flags.make

CMakeFiles/RC_WRITE_client.dir/RC_WRITE/client.cpp.o: CMakeFiles/RC_WRITE_client.dir/flags.make
CMakeFiles/RC_WRITE_client.dir/RC_WRITE/client.cpp.o: ../RC_WRITE/client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kvgroup/louzy/SJ_RDMA/rlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RC_WRITE_client.dir/RC_WRITE/client.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RC_WRITE_client.dir/RC_WRITE/client.cpp.o -c /home/kvgroup/louzy/SJ_RDMA/rlib/RC_WRITE/client.cpp

CMakeFiles/RC_WRITE_client.dir/RC_WRITE/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RC_WRITE_client.dir/RC_WRITE/client.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kvgroup/louzy/SJ_RDMA/rlib/RC_WRITE/client.cpp > CMakeFiles/RC_WRITE_client.dir/RC_WRITE/client.cpp.i

CMakeFiles/RC_WRITE_client.dir/RC_WRITE/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RC_WRITE_client.dir/RC_WRITE/client.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kvgroup/louzy/SJ_RDMA/rlib/RC_WRITE/client.cpp -o CMakeFiles/RC_WRITE_client.dir/RC_WRITE/client.cpp.s

# Object files for target RC_WRITE_client
RC_WRITE_client_OBJECTS = \
"CMakeFiles/RC_WRITE_client.dir/RC_WRITE/client.cpp.o"

# External object files for target RC_WRITE_client
RC_WRITE_client_EXTERNAL_OBJECTS =

RC_WRITE_client: CMakeFiles/RC_WRITE_client.dir/RC_WRITE/client.cpp.o
RC_WRITE_client: CMakeFiles/RC_WRITE_client.dir/build.make
RC_WRITE_client: librdma.a
RC_WRITE_client: ../ralloc/libssmalloc.a
RC_WRITE_client: CMakeFiles/RC_WRITE_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kvgroup/louzy/SJ_RDMA/rlib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RC_WRITE_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RC_WRITE_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RC_WRITE_client.dir/build: RC_WRITE_client

.PHONY : CMakeFiles/RC_WRITE_client.dir/build

CMakeFiles/RC_WRITE_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RC_WRITE_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RC_WRITE_client.dir/clean

CMakeFiles/RC_WRITE_client.dir/depend:
	cd /home/kvgroup/louzy/SJ_RDMA/rlib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kvgroup/louzy/SJ_RDMA/rlib /home/kvgroup/louzy/SJ_RDMA/rlib /home/kvgroup/louzy/SJ_RDMA/rlib/build /home/kvgroup/louzy/SJ_RDMA/rlib/build /home/kvgroup/louzy/SJ_RDMA/rlib/build/CMakeFiles/RC_WRITE_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RC_WRITE_client.dir/depend
