# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\libraries\SFML-2.5.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\libraries\SFML-2.5.1\build

# Include any dependencies generated for this target.
include src/SFML/Network/CMakeFiles/sfml-network.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.make

# Include the progress variables for this target.
include src/SFML/Network/CMakeFiles/sfml-network.dir/progress.make

# Include the compile flags for this target's objects.
include src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make

src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj: ../src/SFML/Network/Ftp.cpp
src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\libraries\SFML-2.5.1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj -MF CMakeFiles\sfml-network.dir\Ftp.cpp.obj.d -o CMakeFiles\sfml-network.dir\Ftp.cpp.obj -c C:\libraries\SFML-2.5.1\src\SFML\Network\Ftp.cpp

src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/Ftp.cpp.i"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\libraries\SFML-2.5.1\src\SFML\Network\Ftp.cpp > CMakeFiles\sfml-network.dir\Ftp.cpp.i

src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/Ftp.cpp.s"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\libraries\SFML-2.5.1\src\SFML\Network\Ftp.cpp -o CMakeFiles\sfml-network.dir\Ftp.cpp.s

src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj: ../src/SFML/Network/Http.cpp
src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\libraries\SFML-2.5.1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj -MF CMakeFiles\sfml-network.dir\Http.cpp.obj.d -o CMakeFiles\sfml-network.dir\Http.cpp.obj -c C:\libraries\SFML-2.5.1\src\SFML\Network\Http.cpp

src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/Http.cpp.i"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\libraries\SFML-2.5.1\src\SFML\Network\Http.cpp > CMakeFiles\sfml-network.dir\Http.cpp.i

src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/Http.cpp.s"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\libraries\SFML-2.5.1\src\SFML\Network\Http.cpp -o CMakeFiles\sfml-network.dir\Http.cpp.s

src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj: ../src/SFML/Network/IpAddress.cpp
src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\libraries\SFML-2.5.1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj -MF CMakeFiles\sfml-network.dir\IpAddress.cpp.obj.d -o CMakeFiles\sfml-network.dir\IpAddress.cpp.obj -c C:\libraries\SFML-2.5.1\src\SFML\Network\IpAddress.cpp

src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/IpAddress.cpp.i"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\libraries\SFML-2.5.1\src\SFML\Network\IpAddress.cpp > CMakeFiles\sfml-network.dir\IpAddress.cpp.i

src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/IpAddress.cpp.s"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\libraries\SFML-2.5.1\src\SFML\Network\IpAddress.cpp -o CMakeFiles\sfml-network.dir\IpAddress.cpp.s

src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj: ../src/SFML/Network/Packet.cpp
src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\libraries\SFML-2.5.1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj -MF CMakeFiles\sfml-network.dir\Packet.cpp.obj.d -o CMakeFiles\sfml-network.dir\Packet.cpp.obj -c C:\libraries\SFML-2.5.1\src\SFML\Network\Packet.cpp

src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/Packet.cpp.i"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\libraries\SFML-2.5.1\src\SFML\Network\Packet.cpp > CMakeFiles\sfml-network.dir\Packet.cpp.i

src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/Packet.cpp.s"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\libraries\SFML-2.5.1\src\SFML\Network\Packet.cpp -o CMakeFiles\sfml-network.dir\Packet.cpp.s

src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj: ../src/SFML/Network/Socket.cpp
src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\libraries\SFML-2.5.1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj -MF CMakeFiles\sfml-network.dir\Socket.cpp.obj.d -o CMakeFiles\sfml-network.dir\Socket.cpp.obj -c C:\libraries\SFML-2.5.1\src\SFML\Network\Socket.cpp

src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/Socket.cpp.i"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\libraries\SFML-2.5.1\src\SFML\Network\Socket.cpp > CMakeFiles\sfml-network.dir\Socket.cpp.i

src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/Socket.cpp.s"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\libraries\SFML-2.5.1\src\SFML\Network\Socket.cpp -o CMakeFiles\sfml-network.dir\Socket.cpp.s

src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj: ../src/SFML/Network/SocketSelector.cpp
src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\libraries\SFML-2.5.1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj -MF CMakeFiles\sfml-network.dir\SocketSelector.cpp.obj.d -o CMakeFiles\sfml-network.dir\SocketSelector.cpp.obj -c C:\libraries\SFML-2.5.1\src\SFML\Network\SocketSelector.cpp

src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/SocketSelector.cpp.i"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\libraries\SFML-2.5.1\src\SFML\Network\SocketSelector.cpp > CMakeFiles\sfml-network.dir\SocketSelector.cpp.i

src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/SocketSelector.cpp.s"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\libraries\SFML-2.5.1\src\SFML\Network\SocketSelector.cpp -o CMakeFiles\sfml-network.dir\SocketSelector.cpp.s

src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj: ../src/SFML/Network/TcpListener.cpp
src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\libraries\SFML-2.5.1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj -MF CMakeFiles\sfml-network.dir\TcpListener.cpp.obj.d -o CMakeFiles\sfml-network.dir\TcpListener.cpp.obj -c C:\libraries\SFML-2.5.1\src\SFML\Network\TcpListener.cpp

src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/TcpListener.cpp.i"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\libraries\SFML-2.5.1\src\SFML\Network\TcpListener.cpp > CMakeFiles\sfml-network.dir\TcpListener.cpp.i

src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/TcpListener.cpp.s"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\libraries\SFML-2.5.1\src\SFML\Network\TcpListener.cpp -o CMakeFiles\sfml-network.dir\TcpListener.cpp.s

src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj: ../src/SFML/Network/TcpSocket.cpp
src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\libraries\SFML-2.5.1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj -MF CMakeFiles\sfml-network.dir\TcpSocket.cpp.obj.d -o CMakeFiles\sfml-network.dir\TcpSocket.cpp.obj -c C:\libraries\SFML-2.5.1\src\SFML\Network\TcpSocket.cpp

src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/TcpSocket.cpp.i"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\libraries\SFML-2.5.1\src\SFML\Network\TcpSocket.cpp > CMakeFiles\sfml-network.dir\TcpSocket.cpp.i

src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/TcpSocket.cpp.s"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\libraries\SFML-2.5.1\src\SFML\Network\TcpSocket.cpp -o CMakeFiles\sfml-network.dir\TcpSocket.cpp.s

src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj: ../src/SFML/Network/UdpSocket.cpp
src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\libraries\SFML-2.5.1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj -MF CMakeFiles\sfml-network.dir\UdpSocket.cpp.obj.d -o CMakeFiles\sfml-network.dir\UdpSocket.cpp.obj -c C:\libraries\SFML-2.5.1\src\SFML\Network\UdpSocket.cpp

src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/UdpSocket.cpp.i"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\libraries\SFML-2.5.1\src\SFML\Network\UdpSocket.cpp > CMakeFiles\sfml-network.dir\UdpSocket.cpp.i

src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/UdpSocket.cpp.s"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\libraries\SFML-2.5.1\src\SFML\Network\UdpSocket.cpp -o CMakeFiles\sfml-network.dir\UdpSocket.cpp.s

src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/flags.make
src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/includes_CXX.rsp
src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj: ../src/SFML/Network/Win32/SocketImpl.cpp
src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj: src/SFML/Network/CMakeFiles/sfml-network.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\libraries\SFML-2.5.1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj -MF CMakeFiles\sfml-network.dir\Win32\SocketImpl.cpp.obj.d -o CMakeFiles\sfml-network.dir\Win32\SocketImpl.cpp.obj -c C:\libraries\SFML-2.5.1\src\SFML\Network\Win32\SocketImpl.cpp

src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.i"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\libraries\SFML-2.5.1\src\SFML\Network\Win32\SocketImpl.cpp > CMakeFiles\sfml-network.dir\Win32\SocketImpl.cpp.i

src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.s"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\libraries\SFML-2.5.1\src\SFML\Network\Win32\SocketImpl.cpp -o CMakeFiles\sfml-network.dir\Win32\SocketImpl.cpp.s

# Object files for target sfml-network
sfml__network_OBJECTS = \
"CMakeFiles/sfml-network.dir/Ftp.cpp.obj" \
"CMakeFiles/sfml-network.dir/Http.cpp.obj" \
"CMakeFiles/sfml-network.dir/IpAddress.cpp.obj" \
"CMakeFiles/sfml-network.dir/Packet.cpp.obj" \
"CMakeFiles/sfml-network.dir/Socket.cpp.obj" \
"CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj" \
"CMakeFiles/sfml-network.dir/TcpListener.cpp.obj" \
"CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj" \
"CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj" \
"CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj"

# External object files for target sfml-network
sfml__network_EXTERNAL_OBJECTS =

lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/Ftp.cpp.obj
lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/Http.cpp.obj
lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/IpAddress.cpp.obj
lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/Packet.cpp.obj
lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/Socket.cpp.obj
lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/SocketSelector.cpp.obj
lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/TcpListener.cpp.obj
lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/TcpSocket.cpp.obj
lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/UdpSocket.cpp.obj
lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/Win32/SocketImpl.cpp.obj
lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/build.make
lib/sfml-network-2.dll: lib/libsfml-system.a
lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/linklibs.rsp
lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/objects1.rsp
lib/sfml-network-2.dll: src/SFML/Network/CMakeFiles/sfml-network.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\libraries\SFML-2.5.1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX shared library ..\..\..\lib\sfml-network-2.dll"
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\sfml-network.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/SFML/Network/CMakeFiles/sfml-network.dir/build: lib/sfml-network-2.dll
.PHONY : src/SFML/Network/CMakeFiles/sfml-network.dir/build

src/SFML/Network/CMakeFiles/sfml-network.dir/clean:
	cd /d C:\libraries\SFML-2.5.1\build\src\SFML\Network && $(CMAKE_COMMAND) -P CMakeFiles\sfml-network.dir\cmake_clean.cmake
.PHONY : src/SFML/Network/CMakeFiles/sfml-network.dir/clean

src/SFML/Network/CMakeFiles/sfml-network.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\libraries\SFML-2.5.1 C:\libraries\SFML-2.5.1\src\SFML\Network C:\libraries\SFML-2.5.1\build C:\libraries\SFML-2.5.1\build\src\SFML\Network C:\libraries\SFML-2.5.1\build\src\SFML\Network\CMakeFiles\sfml-network.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src/SFML/Network/CMakeFiles/sfml-network.dir/depend

