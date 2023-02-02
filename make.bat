set PATH=C:\raylib\w64devkit\bin;%PATH%
set CFLAGS=C:\raylib\raylib\src\raylib.rc.data -s -static -O2 -std=c99 -Wall -IC:\raylib\raylib\src -Iexternal -DPLATFORM_DESKTOP
set LDFLAGS=-lraylib -lopengl32 -lgdi32 -lwinmm
gcc -o binary.exe collisions.c custom.c main.c player.c %CFLAGS% %LDFLAGS%
