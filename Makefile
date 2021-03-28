# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /mnt/c/Users/Ovidiu/Desktop/3-Check-Chess

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Ovidiu/Desktop/3-Check-Chess

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/c/Users/Ovidiu/Desktop/3-Check-Chess/CMakeFiles /mnt/c/Users/Ovidiu/Desktop/3-Check-Chess/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /mnt/c/Users/Ovidiu/Desktop/3-Check-Chess/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named 3_Check_Chess

# Build rule for target.
3_Check_Chess: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 3_Check_Chess
.PHONY : 3_Check_Chess

# fast build rule for target.
3_Check_Chess/fast:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/build
.PHONY : 3_Check_Chess/fast

#=============================================================================
# Target rules for targets named run

# Build rule for target.
run: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 run
.PHONY : run

# fast build rule for target.
run/fast:
	$(MAKE) -f CMakeFiles/run.dir/build.make CMakeFiles/run.dir/build
.PHONY : run/fast

Source/AlgoPicker.o: Source/AlgoPicker.cpp.o

.PHONY : Source/AlgoPicker.o

# target to build an object file
Source/AlgoPicker.cpp.o:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/AlgoPicker.cpp.o
.PHONY : Source/AlgoPicker.cpp.o

Source/AlgoPicker.i: Source/AlgoPicker.cpp.i

.PHONY : Source/AlgoPicker.i

# target to preprocess a source file
Source/AlgoPicker.cpp.i:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/AlgoPicker.cpp.i
.PHONY : Source/AlgoPicker.cpp.i

Source/AlgoPicker.s: Source/AlgoPicker.cpp.s

.PHONY : Source/AlgoPicker.s

# target to generate assembly for a file
Source/AlgoPicker.cpp.s:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/AlgoPicker.cpp.s
.PHONY : Source/AlgoPicker.cpp.s

Source/Algorithm.o: Source/Algorithm.cpp.o

.PHONY : Source/Algorithm.o

# target to build an object file
Source/Algorithm.cpp.o:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/Algorithm.cpp.o
.PHONY : Source/Algorithm.cpp.o

Source/Algorithm.i: Source/Algorithm.cpp.i

.PHONY : Source/Algorithm.i

# target to preprocess a source file
Source/Algorithm.cpp.i:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/Algorithm.cpp.i
.PHONY : Source/Algorithm.cpp.i

Source/Algorithm.s: Source/Algorithm.cpp.s

.PHONY : Source/Algorithm.s

# target to generate assembly for a file
Source/Algorithm.cpp.s:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/Algorithm.cpp.s
.PHONY : Source/Algorithm.cpp.s

Source/ChessPiece.o: Source/ChessPiece.cpp.o

.PHONY : Source/ChessPiece.o

# target to build an object file
Source/ChessPiece.cpp.o:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/ChessPiece.cpp.o
.PHONY : Source/ChessPiece.cpp.o

Source/ChessPiece.i: Source/ChessPiece.cpp.i

.PHONY : Source/ChessPiece.i

# target to preprocess a source file
Source/ChessPiece.cpp.i:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/ChessPiece.cpp.i
.PHONY : Source/ChessPiece.cpp.i

Source/ChessPiece.s: Source/ChessPiece.cpp.s

.PHONY : Source/ChessPiece.s

# target to generate assembly for a file
Source/ChessPiece.cpp.s:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/ChessPiece.cpp.s
.PHONY : Source/ChessPiece.cpp.s

Source/EndGame.o: Source/EndGame.cpp.o

.PHONY : Source/EndGame.o

# target to build an object file
Source/EndGame.cpp.o:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/EndGame.cpp.o
.PHONY : Source/EndGame.cpp.o

Source/EndGame.i: Source/EndGame.cpp.i

.PHONY : Source/EndGame.i

# target to preprocess a source file
Source/EndGame.cpp.i:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/EndGame.cpp.i
.PHONY : Source/EndGame.cpp.i

Source/EndGame.s: Source/EndGame.cpp.s

.PHONY : Source/EndGame.s

# target to generate assembly for a file
Source/EndGame.cpp.s:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/EndGame.cpp.s
.PHONY : Source/EndGame.cpp.s

Source/Engine.o: Source/Engine.cpp.o

.PHONY : Source/Engine.o

# target to build an object file
Source/Engine.cpp.o:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/Engine.cpp.o
.PHONY : Source/Engine.cpp.o

Source/Engine.i: Source/Engine.cpp.i

.PHONY : Source/Engine.i

# target to preprocess a source file
Source/Engine.cpp.i:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/Engine.cpp.i
.PHONY : Source/Engine.cpp.i

Source/Engine.s: Source/Engine.cpp.s

.PHONY : Source/Engine.s

# target to generate assembly for a file
Source/Engine.cpp.s:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/Engine.cpp.s
.PHONY : Source/Engine.cpp.s

Source/Table.o: Source/Table.cpp.o

.PHONY : Source/Table.o

# target to build an object file
Source/Table.cpp.o:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/Table.cpp.o
.PHONY : Source/Table.cpp.o

Source/Table.i: Source/Table.cpp.i

.PHONY : Source/Table.i

# target to preprocess a source file
Source/Table.cpp.i:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/Table.cpp.i
.PHONY : Source/Table.cpp.i

Source/Table.s: Source/Table.cpp.s

.PHONY : Source/Table.s

# target to generate assembly for a file
Source/Table.cpp.s:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/Table.cpp.s
.PHONY : Source/Table.cpp.s

Source/Tree.o: Source/Tree.cpp.o

.PHONY : Source/Tree.o

# target to build an object file
Source/Tree.cpp.o:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/Tree.cpp.o
.PHONY : Source/Tree.cpp.o

Source/Tree.i: Source/Tree.cpp.i

.PHONY : Source/Tree.i

# target to preprocess a source file
Source/Tree.cpp.i:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/Tree.cpp.i
.PHONY : Source/Tree.cpp.i

Source/Tree.s: Source/Tree.cpp.s

.PHONY : Source/Tree.s

# target to generate assembly for a file
Source/Tree.cpp.s:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/Tree.cpp.s
.PHONY : Source/Tree.cpp.s

Source/main.o: Source/main.cpp.o

.PHONY : Source/main.o

# target to build an object file
Source/main.cpp.o:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/main.cpp.o
.PHONY : Source/main.cpp.o

Source/main.i: Source/main.cpp.i

.PHONY : Source/main.i

# target to preprocess a source file
Source/main.cpp.i:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/main.cpp.i
.PHONY : Source/main.cpp.i

Source/main.s: Source/main.cpp.s

.PHONY : Source/main.s

# target to generate assembly for a file
Source/main.cpp.s:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/main.cpp.s
.PHONY : Source/main.cpp.s

Source/tools.o: Source/tools.cpp.o

.PHONY : Source/tools.o

# target to build an object file
Source/tools.cpp.o:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/tools.cpp.o
.PHONY : Source/tools.cpp.o

Source/tools.i: Source/tools.cpp.i

.PHONY : Source/tools.i

# target to preprocess a source file
Source/tools.cpp.i:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/tools.cpp.i
.PHONY : Source/tools.cpp.i

Source/tools.s: Source/tools.cpp.s

.PHONY : Source/tools.s

# target to generate assembly for a file
Source/tools.cpp.s:
	$(MAKE) -f CMakeFiles/3_Check_Chess.dir/build.make CMakeFiles/3_Check_Chess.dir/Source/tools.cpp.s
.PHONY : Source/tools.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... 3_Check_Chess"
	@echo "... run"
	@echo "... Source/AlgoPicker.o"
	@echo "... Source/AlgoPicker.i"
	@echo "... Source/AlgoPicker.s"
	@echo "... Source/Algorithm.o"
	@echo "... Source/Algorithm.i"
	@echo "... Source/Algorithm.s"
	@echo "... Source/ChessPiece.o"
	@echo "... Source/ChessPiece.i"
	@echo "... Source/ChessPiece.s"
	@echo "... Source/EndGame.o"
	@echo "... Source/EndGame.i"
	@echo "... Source/EndGame.s"
	@echo "... Source/Engine.o"
	@echo "... Source/Engine.i"
	@echo "... Source/Engine.s"
	@echo "... Source/Table.o"
	@echo "... Source/Table.i"
	@echo "... Source/Table.s"
	@echo "... Source/Tree.o"
	@echo "... Source/Tree.i"
	@echo "... Source/Tree.s"
	@echo "... Source/main.o"
	@echo "... Source/main.i"
	@echo "... Source/main.s"
	@echo "... Source/tools.o"
	@echo "... Source/tools.i"
	@echo "... Source/tools.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

