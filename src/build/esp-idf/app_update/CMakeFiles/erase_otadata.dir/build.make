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
CMAKE_SOURCE_DIR = /home/parker/esp/robot/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/parker/esp/robot/src/build

# Utility rule file for erase_otadata.

# Include the progress variables for this target.
include esp-idf/app_update/CMakeFiles/erase_otadata.dir/progress.make

esp-idf/app_update/CMakeFiles/erase_otadata: /home/parker/esp/esp-idf/components/partition_table/partitions_two_ota.csv
	cd /home/parker/esp/robot/src/build/esp-idf/app_update && /home/parker/.espressif/python_env/idf4.1_py3.9_env/bin/python /home/parker/esp/esp-idf/components/app_update/otatool.py --esptool-args before=default_reset after=hard_reset --partition-table-file /home/parker/esp/esp-idf/components/partition_table/partitions_two_ota.csv --partition-table-offset 0x8000 erase_otadata

erase_otadata: esp-idf/app_update/CMakeFiles/erase_otadata
erase_otadata: esp-idf/app_update/CMakeFiles/erase_otadata.dir/build.make

.PHONY : erase_otadata

# Rule to build all files generated by this target.
esp-idf/app_update/CMakeFiles/erase_otadata.dir/build: erase_otadata

.PHONY : esp-idf/app_update/CMakeFiles/erase_otadata.dir/build

esp-idf/app_update/CMakeFiles/erase_otadata.dir/clean:
	cd /home/parker/esp/robot/src/build/esp-idf/app_update && $(CMAKE_COMMAND) -P CMakeFiles/erase_otadata.dir/cmake_clean.cmake
.PHONY : esp-idf/app_update/CMakeFiles/erase_otadata.dir/clean

esp-idf/app_update/CMakeFiles/erase_otadata.dir/depend:
	cd /home/parker/esp/robot/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/parker/esp/robot/src /home/parker/esp/esp-idf/components/app_update /home/parker/esp/robot/src/build /home/parker/esp/robot/src/build/esp-idf/app_update /home/parker/esp/robot/src/build/esp-idf/app_update/CMakeFiles/erase_otadata.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : esp-idf/app_update/CMakeFiles/erase_otadata.dir/depend

