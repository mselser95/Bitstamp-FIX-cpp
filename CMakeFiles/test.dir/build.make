# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/matias/Software/clion-2020.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/matias/Software/clion-2020.2.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/connector/fix/Connector.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/connector/fix/Connector.cpp.o: connector/fix/Connector.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.dir/connector/fix/Connector.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/connector/fix/Connector.cpp.o -c /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/connector/fix/Connector.cpp

CMakeFiles/test.dir/connector/fix/Connector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/connector/fix/Connector.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/connector/fix/Connector.cpp > CMakeFiles/test.dir/connector/fix/Connector.cpp.i

CMakeFiles/test.dir/connector/fix/Connector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/connector/fix/Connector.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/connector/fix/Connector.cpp -o CMakeFiles/test.dir/connector/fix/Connector.cpp.s

CMakeFiles/test.dir/brain.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/brain.cpp.o: brain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test.dir/brain.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/brain.cpp.o -c /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/brain.cpp

CMakeFiles/test.dir/brain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/brain.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/brain.cpp > CMakeFiles/test.dir/brain.cpp.i

CMakeFiles/test.dir/brain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/brain.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/brain.cpp -o CMakeFiles/test.dir/brain.cpp.s

CMakeFiles/test.dir/connector/Bitstamp.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/connector/Bitstamp.cpp.o: connector/Bitstamp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test.dir/connector/Bitstamp.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.dir/connector/Bitstamp.cpp.o -c /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/connector/Bitstamp.cpp

CMakeFiles/test.dir/connector/Bitstamp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/connector/Bitstamp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/connector/Bitstamp.cpp > CMakeFiles/test.dir/connector/Bitstamp.cpp.i

CMakeFiles/test.dir/connector/Bitstamp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/connector/Bitstamp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/connector/Bitstamp.cpp -o CMakeFiles/test.dir/connector/Bitstamp.cpp.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/connector/fix/Connector.cpp.o" \
"CMakeFiles/test.dir/brain.cpp.o" \
"CMakeFiles/test.dir/connector/Bitstamp.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

test: CMakeFiles/test.dir/connector/fix/Connector.cpp.o
test: CMakeFiles/test.dir/brain.cpp.o
test: CMakeFiles/test.dir/connector/Bitstamp.cpp.o
test: CMakeFiles/test.dir/build.make
test: /usr/local/lib/libquickfix.so
test: /usr/lib/x86_64-linux-gnu/libcurl.so
test: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: test

.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	cd /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp /home/matias/CLionProjects/Public/Bitstamp-FIX-cpp/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.dir/depend

