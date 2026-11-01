echo off
clang *.c -o m -lglad -luser32 -lopengl32 -lgdi32 -g
m.exe
pause
