# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\dbiton\CLionProjects\Matam

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\dbiton\CLionProjects\Matam\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\Matam.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Matam.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Matam.dir\flags.make

CMakeFiles\Matam.dir\main.c.obj: CMakeFiles\Matam.dir\flags.make
CMakeFiles\Matam.dir\main.c.obj: ..\main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\dbiton\CLionProjects\Matam\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Matam.dir/main.c.obj"
	C:\PROGRA~2\MICROS~1\2017\COMMUN~1\VC\Tools\MSVC\1415~1.267\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\Matam.dir\main.c.obj /FdCMakeFiles\Matam.dir\ /FS -c C:\Users\dbiton\CLionProjects\Matam\main.c
<<

CMakeFiles\Matam.dir\main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matam.dir/main.c.i"
	C:\PROGRA~2\MICROS~1\2017\COMMUN~1\VC\Tools\MSVC\1415~1.267\bin\Hostx86\x86\cl.exe > CMakeFiles\Matam.dir\main.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\dbiton\CLionProjects\Matam\main.c
<<

CMakeFiles\Matam.dir\main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matam.dir/main.c.s"
	C:\PROGRA~2\MICROS~1\2017\COMMUN~1\VC\Tools\MSVC\1415~1.267\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\Matam.dir\main.c.s /c C:\Users\dbiton\CLionProjects\Matam\main.c
<<

CMakeFiles\Matam.dir\map.c.obj: CMakeFiles\Matam.dir\flags.make
CMakeFiles\Matam.dir\map.c.obj: ..\map.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\dbiton\CLionProjects\Matam\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Matam.dir/map.c.obj"
	C:\PROGRA~2\MICROS~1\2017\COMMUN~1\VC\Tools\MSVC\1415~1.267\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoCMakeFiles\Matam.dir\map.c.obj /FdCMakeFiles\Matam.dir\ /FS -c C:\Users\dbiton\CLionProjects\Matam\map.c
<<

CMakeFiles\Matam.dir\map.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Matam.dir/map.c.i"
	C:\PROGRA~2\MICROS~1\2017\COMMUN~1\VC\Tools\MSVC\1415~1.267\bin\Hostx86\x86\cl.exe > CMakeFiles\Matam.dir\map.c.i @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\dbiton\CLionProjects\Matam\map.c
<<

CMakeFiles\Matam.dir\map.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Matam.dir/map.c.s"
	C:\PROGRA~2\MICROS~1\2017\COMMUN~1\VC\Tools\MSVC\1415~1.267\bin\Hostx86\x86\cl.exe @<<
 /nologo $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) /FoNUL /FAs /FaCMakeFiles\Matam.dir\map.c.s /c C:\Users\dbiton\CLionProjects\Matam\map.c
<<

# Object files for target Matam
Matam_OBJECTS = \
"CMakeFiles\Matam.dir\main.c.obj" \
"CMakeFiles\Matam.dir\map.c.obj"

# External object files for target Matam
Matam_EXTERNAL_OBJECTS =

Matam.exe: CMakeFiles\Matam.dir\main.c.obj
Matam.exe: CMakeFiles\Matam.dir\map.c.obj
Matam.exe: CMakeFiles\Matam.dir\build.make
Matam.exe: CMakeFiles\Matam.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\dbiton\CLionProjects\Matam\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Matam.exe"
	"C:\Program Files\JetBrains\CLion 2019.1\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Matam.dir --manifests  -- C:\PROGRA~2\MICROS~1\2017\COMMUN~1\VC\Tools\MSVC\1415~1.267\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Matam.dir\objects1.rsp @<<
 /out:Matam.exe /implib:Matam.lib /pdb:C:\Users\dbiton\CLionProjects\Matam\cmake-build-debug\Matam.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Matam.dir\build: Matam.exe

.PHONY : CMakeFiles\Matam.dir\build

CMakeFiles\Matam.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Matam.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Matam.dir\clean

CMakeFiles\Matam.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\dbiton\CLionProjects\Matam C:\Users\dbiton\CLionProjects\Matam C:\Users\dbiton\CLionProjects\Matam\cmake-build-debug C:\Users\dbiton\CLionProjects\Matam\cmake-build-debug C:\Users\dbiton\CLionProjects\Matam\cmake-build-debug\CMakeFiles\Matam.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\Matam.dir\depend

