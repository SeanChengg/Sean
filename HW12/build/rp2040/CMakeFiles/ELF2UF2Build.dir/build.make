# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.29.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.29.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/SeanChneg/Desktop/Sean1/HW12

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/SeanChneg/Desktop/Sean1/HW12/build

# Utility rule file for ELF2UF2Build.

# Include any custom commands dependencies for this target.
include rp2040/CMakeFiles/ELF2UF2Build.dir/compiler_depend.make

# Include the progress variables for this target.
include rp2040/CMakeFiles/ELF2UF2Build.dir/progress.make

rp2040/CMakeFiles/ELF2UF2Build: rp2040/CMakeFiles/ELF2UF2Build-complete

rp2040/CMakeFiles/ELF2UF2Build-complete: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-install
rp2040/CMakeFiles/ELF2UF2Build-complete: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-mkdir
rp2040/CMakeFiles/ELF2UF2Build-complete: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-download
rp2040/CMakeFiles/ELF2UF2Build-complete: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-update
rp2040/CMakeFiles/ELF2UF2Build-complete: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-patch
rp2040/CMakeFiles/ELF2UF2Build-complete: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-configure
rp2040/CMakeFiles/ELF2UF2Build-complete: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-build
rp2040/CMakeFiles/ELF2UF2Build-complete: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-install
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/SeanChneg/Desktop/Sean1/HW12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'ELF2UF2Build'"
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -E make_directory /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040/CMakeFiles
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -E touch /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040/CMakeFiles/ELF2UF2Build-complete
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -E touch /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-done

rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-build: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/SeanChneg/Desktop/Sean1/HW12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Performing build step for 'ELF2UF2Build'"
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/elf2uf2 && $(MAKE)

rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-configure: rp2040/elf2uf2/tmp/ELF2UF2Build-cfgcmd.txt
rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-configure: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/SeanChneg/Desktop/Sean1/HW12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Performing configure step for 'ELF2UF2Build'"
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/elf2uf2 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -DCMAKE_MAKE_PROGRAM:FILEPATH=/usr/bin/make "-GUnix Makefiles" -S /Users/SeanChneg/Desktop/Pico/pico-sdk/tools/elf2uf2 -B /Users/SeanChneg/Desktop/Sean1/HW12/build/elf2uf2
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/elf2uf2 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -E touch /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-configure

rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-download: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-source_dirinfo.txt
rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-download: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/SeanChneg/Desktop/Sean1/HW12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "No download step for 'ELF2UF2Build'"
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -E echo_append
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -E touch /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-download

rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-install: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-build
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/SeanChneg/Desktop/Sean1/HW12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'ELF2UF2Build'"
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/elf2uf2 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -E echo_append

rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/SeanChneg/Desktop/Sean1/HW12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'ELF2UF2Build'"
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -Dcfgdir= -P /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040/elf2uf2/tmp/ELF2UF2Build-mkdirs.cmake
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -E touch /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-mkdir

rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-patch: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-patch-info.txt
rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-patch: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-update
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/SeanChneg/Desktop/Sean1/HW12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'ELF2UF2Build'"
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -E echo_append
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -E touch /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-patch

rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-update: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-update-info.txt
rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-update: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-download
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/Users/SeanChneg/Desktop/Sean1/HW12/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No update step for 'ELF2UF2Build'"
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -E echo_append
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040 && /usr/local/Cellar/cmake/3.29.0/bin/cmake -E touch /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-update

ELF2UF2Build: rp2040/CMakeFiles/ELF2UF2Build
ELF2UF2Build: rp2040/CMakeFiles/ELF2UF2Build-complete
ELF2UF2Build: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-build
ELF2UF2Build: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-configure
ELF2UF2Build: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-download
ELF2UF2Build: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-install
ELF2UF2Build: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-mkdir
ELF2UF2Build: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-patch
ELF2UF2Build: rp2040/elf2uf2/src/ELF2UF2Build-stamp/ELF2UF2Build-update
ELF2UF2Build: rp2040/CMakeFiles/ELF2UF2Build.dir/build.make
.PHONY : ELF2UF2Build

# Rule to build all files generated by this target.
rp2040/CMakeFiles/ELF2UF2Build.dir/build: ELF2UF2Build
.PHONY : rp2040/CMakeFiles/ELF2UF2Build.dir/build

rp2040/CMakeFiles/ELF2UF2Build.dir/clean:
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040 && $(CMAKE_COMMAND) -P CMakeFiles/ELF2UF2Build.dir/cmake_clean.cmake
.PHONY : rp2040/CMakeFiles/ELF2UF2Build.dir/clean

rp2040/CMakeFiles/ELF2UF2Build.dir/depend:
	cd /Users/SeanChneg/Desktop/Sean1/HW12/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/SeanChneg/Desktop/Sean1/HW12 /Users/SeanChneg/Desktop/Sean1/HW12/rp2040 /Users/SeanChneg/Desktop/Sean1/HW12/build /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040 /Users/SeanChneg/Desktop/Sean1/HW12/build/rp2040/CMakeFiles/ELF2UF2Build.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : rp2040/CMakeFiles/ELF2UF2Build.dir/depend

