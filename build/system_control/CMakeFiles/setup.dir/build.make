# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /home/pi/winch_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/winch_ws/build

# Include any dependencies generated for this target.
include system_control/CMakeFiles/setup.dir/depend.make

# Include the progress variables for this target.
include system_control/CMakeFiles/setup.dir/progress.make

# Include the compile flags for this target's objects.
include system_control/CMakeFiles/setup.dir/flags.make

system_control/CMakeFiles/setup.dir/src/setup.cpp.o: system_control/CMakeFiles/setup.dir/flags.make
system_control/CMakeFiles/setup.dir/src/setup.cpp.o: /home/pi/winch_ws/src/system_control/src/setup.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/winch_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object system_control/CMakeFiles/setup.dir/src/setup.cpp.o"
	cd /home/pi/winch_ws/build/system_control && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/setup.dir/src/setup.cpp.o -c /home/pi/winch_ws/src/system_control/src/setup.cpp

system_control/CMakeFiles/setup.dir/src/setup.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/setup.dir/src/setup.cpp.i"
	cd /home/pi/winch_ws/build/system_control && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/winch_ws/src/system_control/src/setup.cpp > CMakeFiles/setup.dir/src/setup.cpp.i

system_control/CMakeFiles/setup.dir/src/setup.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/setup.dir/src/setup.cpp.s"
	cd /home/pi/winch_ws/build/system_control && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/winch_ws/src/system_control/src/setup.cpp -o CMakeFiles/setup.dir/src/setup.cpp.s

system_control/CMakeFiles/setup.dir/src/setup.cpp.o.requires:

.PHONY : system_control/CMakeFiles/setup.dir/src/setup.cpp.o.requires

system_control/CMakeFiles/setup.dir/src/setup.cpp.o.provides: system_control/CMakeFiles/setup.dir/src/setup.cpp.o.requires
	$(MAKE) -f system_control/CMakeFiles/setup.dir/build.make system_control/CMakeFiles/setup.dir/src/setup.cpp.o.provides.build
.PHONY : system_control/CMakeFiles/setup.dir/src/setup.cpp.o.provides

system_control/CMakeFiles/setup.dir/src/setup.cpp.o.provides.build: system_control/CMakeFiles/setup.dir/src/setup.cpp.o


# Object files for target setup
setup_OBJECTS = \
"CMakeFiles/setup.dir/src/setup.cpp.o"

# External object files for target setup
setup_EXTERNAL_OBJECTS =

/home/pi/winch_ws/devel/lib/system_control/setup: system_control/CMakeFiles/setup.dir/src/setup.cpp.o
/home/pi/winch_ws/devel/lib/system_control/setup: system_control/CMakeFiles/setup.dir/build.make
/home/pi/winch_ws/devel/lib/system_control/setup: /opt/ros/kinetic/lib/libroscpp.so
/home/pi/winch_ws/devel/lib/system_control/setup: /usr/lib/arm-linux-gnueabihf/libboost_filesystem.so
/home/pi/winch_ws/devel/lib/system_control/setup: /usr/lib/arm-linux-gnueabihf/libboost_signals.so
/home/pi/winch_ws/devel/lib/system_control/setup: /opt/ros/kinetic/lib/librosconsole.so
/home/pi/winch_ws/devel/lib/system_control/setup: /opt/ros/kinetic/lib/librosconsole_log4cxx.so
/home/pi/winch_ws/devel/lib/system_control/setup: /opt/ros/kinetic/lib/librosconsole_backend_interface.so
/home/pi/winch_ws/devel/lib/system_control/setup: /usr/lib/arm-linux-gnueabihf/liblog4cxx.so
/home/pi/winch_ws/devel/lib/system_control/setup: /usr/lib/arm-linux-gnueabihf/libboost_regex.so
/home/pi/winch_ws/devel/lib/system_control/setup: /opt/ros/kinetic/lib/libxmlrpcpp.so
/home/pi/winch_ws/devel/lib/system_control/setup: /opt/ros/kinetic/lib/libroscpp_serialization.so
/home/pi/winch_ws/devel/lib/system_control/setup: /opt/ros/kinetic/lib/librostime.so
/home/pi/winch_ws/devel/lib/system_control/setup: /opt/ros/kinetic/lib/libcpp_common.so
/home/pi/winch_ws/devel/lib/system_control/setup: /usr/lib/arm-linux-gnueabihf/libboost_system.so
/home/pi/winch_ws/devel/lib/system_control/setup: /usr/lib/arm-linux-gnueabihf/libboost_thread.so
/home/pi/winch_ws/devel/lib/system_control/setup: /usr/lib/arm-linux-gnueabihf/libboost_chrono.so
/home/pi/winch_ws/devel/lib/system_control/setup: /usr/lib/arm-linux-gnueabihf/libboost_date_time.so
/home/pi/winch_ws/devel/lib/system_control/setup: /usr/lib/arm-linux-gnueabihf/libboost_atomic.so
/home/pi/winch_ws/devel/lib/system_control/setup: /usr/lib/arm-linux-gnueabihf/libpthread.so
/home/pi/winch_ws/devel/lib/system_control/setup: /usr/lib/arm-linux-gnueabihf/libconsole_bridge.so
/home/pi/winch_ws/devel/lib/system_control/setup: system_control/CMakeFiles/setup.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/winch_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/pi/winch_ws/devel/lib/system_control/setup"
	cd /home/pi/winch_ws/build/system_control && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/setup.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
system_control/CMakeFiles/setup.dir/build: /home/pi/winch_ws/devel/lib/system_control/setup

.PHONY : system_control/CMakeFiles/setup.dir/build

system_control/CMakeFiles/setup.dir/requires: system_control/CMakeFiles/setup.dir/src/setup.cpp.o.requires

.PHONY : system_control/CMakeFiles/setup.dir/requires

system_control/CMakeFiles/setup.dir/clean:
	cd /home/pi/winch_ws/build/system_control && $(CMAKE_COMMAND) -P CMakeFiles/setup.dir/cmake_clean.cmake
.PHONY : system_control/CMakeFiles/setup.dir/clean

system_control/CMakeFiles/setup.dir/depend:
	cd /home/pi/winch_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/winch_ws/src /home/pi/winch_ws/src/system_control /home/pi/winch_ws/build /home/pi/winch_ws/build/system_control /home/pi/winch_ws/build/system_control/CMakeFiles/setup.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : system_control/CMakeFiles/setup.dir/depend
