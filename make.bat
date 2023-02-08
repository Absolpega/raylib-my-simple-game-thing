set RAYLIB_PATH=C:\raylib
set PATH=%RAYLIB_PATH%\w64devkit\bin;%PATH%
set CFLAGS=%RAYLIB_PATH%\raylib\src\raylib.rc.data -s -static -O2 -std=c99 -Wall -I%RAYLIB_PATH%\raylib\src -Iexternal -DPLATFORM_DESKTOP
set LDFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm
gcc -o binary.exe collisions.c custom.c main.c player.c %CFLAGS% %LDFLAGS%
