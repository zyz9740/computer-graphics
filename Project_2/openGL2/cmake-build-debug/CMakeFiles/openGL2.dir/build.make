# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = "/Users/listener/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/191.6707.69/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/listener/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/191.6707.69/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/listener/Desktop/openGL2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/listener/Desktop/openGL2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/openGL2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/openGL2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/openGL2.dir/flags.make

CMakeFiles/openGL2.dir/glad.c.o: CMakeFiles/openGL2.dir/flags.make
CMakeFiles/openGL2.dir/glad.c.o: ../glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/listener/Desktop/openGL2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/openGL2.dir/glad.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/openGL2.dir/glad.c.o   -c /Users/listener/Desktop/openGL2/glad.c

CMakeFiles/openGL2.dir/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/openGL2.dir/glad.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/listener/Desktop/openGL2/glad.c > CMakeFiles/openGL2.dir/glad.c.i

CMakeFiles/openGL2.dir/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/openGL2.dir/glad.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/listener/Desktop/openGL2/glad.c -o CMakeFiles/openGL2.dir/glad.c.s

CMakeFiles/openGL2.dir/main.cpp.o: CMakeFiles/openGL2.dir/flags.make
CMakeFiles/openGL2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/listener/Desktop/openGL2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/openGL2.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/openGL2.dir/main.cpp.o -c /Users/listener/Desktop/openGL2/main.cpp

CMakeFiles/openGL2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/openGL2.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/listener/Desktop/openGL2/main.cpp > CMakeFiles/openGL2.dir/main.cpp.i

CMakeFiles/openGL2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/openGL2.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/listener/Desktop/openGL2/main.cpp -o CMakeFiles/openGL2.dir/main.cpp.s

# Object files for target openGL2
openGL2_OBJECTS = \
"CMakeFiles/openGL2.dir/glad.c.o" \
"CMakeFiles/openGL2.dir/main.cpp.o"

# External object files for target openGL2
openGL2_EXTERNAL_OBJECTS =

openGL2: CMakeFiles/openGL2.dir/glad.c.o
openGL2: CMakeFiles/openGL2.dir/main.cpp.o
openGL2: CMakeFiles/openGL2.dir/build.make
openGL2: /usr/local/Cellar/glew/2.1.0/lib/libGLEW.2.1.dylib
openGL2: /usr/local/Cellar/glfw/3.3/lib/libglfw.3.dylib
openGL2: CMakeFiles/openGL2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/listener/Desktop/openGL2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable openGL2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/openGL2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/openGL2.dir/build: openGL2

.PHONY : CMakeFiles/openGL2.dir/build

CMakeFiles/openGL2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/openGL2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/openGL2.dir/clean

CMakeFiles/openGL2.dir/depend:
	cd /Users/listener/Desktop/openGL2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/listener/Desktop/openGL2 /Users/listener/Desktop/openGL2 /Users/listener/Desktop/openGL2/cmake-build-debug /Users/listener/Desktop/openGL2/cmake-build-debug /Users/listener/Desktop/openGL2/cmake-build-debug/CMakeFiles/openGL2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/openGL2.dir/depend

