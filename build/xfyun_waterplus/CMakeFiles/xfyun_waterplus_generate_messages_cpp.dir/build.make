# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/zzy/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zzy/catkin_ws/build

# Utility rule file for xfyun_waterplus_generate_messages_cpp.

# Include the progress variables for this target.
include xfyun_waterplus/CMakeFiles/xfyun_waterplus_generate_messages_cpp.dir/progress.make

xfyun_waterplus/CMakeFiles/xfyun_waterplus_generate_messages_cpp: /home/zzy/catkin_ws/devel/include/xfyun_waterplus/IATSwitch.h


/home/zzy/catkin_ws/devel/include/xfyun_waterplus/IATSwitch.h: /opt/ros/melodic/lib/gencpp/gen_cpp.py
/home/zzy/catkin_ws/devel/include/xfyun_waterplus/IATSwitch.h: /home/zzy/catkin_ws/src/xfyun_waterplus/srv/IATSwitch.srv
/home/zzy/catkin_ws/devel/include/xfyun_waterplus/IATSwitch.h: /opt/ros/melodic/share/gencpp/msg.h.template
/home/zzy/catkin_ws/devel/include/xfyun_waterplus/IATSwitch.h: /opt/ros/melodic/share/gencpp/srv.h.template
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/zzy/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating C++ code from xfyun_waterplus/IATSwitch.srv"
	cd /home/zzy/catkin_ws/src/xfyun_waterplus && /home/zzy/catkin_ws/build/catkin_generated/env_cached.sh /home/zzy/anaconda3/envs/ros/bin/python /opt/ros/melodic/share/gencpp/cmake/../../../lib/gencpp/gen_cpp.py /home/zzy/catkin_ws/src/xfyun_waterplus/srv/IATSwitch.srv -Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg -p xfyun_waterplus -o /home/zzy/catkin_ws/devel/include/xfyun_waterplus -e /opt/ros/melodic/share/gencpp/cmake/..

xfyun_waterplus_generate_messages_cpp: xfyun_waterplus/CMakeFiles/xfyun_waterplus_generate_messages_cpp
xfyun_waterplus_generate_messages_cpp: /home/zzy/catkin_ws/devel/include/xfyun_waterplus/IATSwitch.h
xfyun_waterplus_generate_messages_cpp: xfyun_waterplus/CMakeFiles/xfyun_waterplus_generate_messages_cpp.dir/build.make

.PHONY : xfyun_waterplus_generate_messages_cpp

# Rule to build all files generated by this target.
xfyun_waterplus/CMakeFiles/xfyun_waterplus_generate_messages_cpp.dir/build: xfyun_waterplus_generate_messages_cpp

.PHONY : xfyun_waterplus/CMakeFiles/xfyun_waterplus_generate_messages_cpp.dir/build

xfyun_waterplus/CMakeFiles/xfyun_waterplus_generate_messages_cpp.dir/clean:
	cd /home/zzy/catkin_ws/build/xfyun_waterplus && $(CMAKE_COMMAND) -P CMakeFiles/xfyun_waterplus_generate_messages_cpp.dir/cmake_clean.cmake
.PHONY : xfyun_waterplus/CMakeFiles/xfyun_waterplus_generate_messages_cpp.dir/clean

xfyun_waterplus/CMakeFiles/xfyun_waterplus_generate_messages_cpp.dir/depend:
	cd /home/zzy/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zzy/catkin_ws/src /home/zzy/catkin_ws/src/xfyun_waterplus /home/zzy/catkin_ws/build /home/zzy/catkin_ws/build/xfyun_waterplus /home/zzy/catkin_ws/build/xfyun_waterplus/CMakeFiles/xfyun_waterplus_generate_messages_cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : xfyun_waterplus/CMakeFiles/xfyun_waterplus_generate_messages_cpp.dir/depend

