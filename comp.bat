@echo off
pushd build
cl ../lake_victoria.cpp ../shader.cpp ../glad.c /I ../includes /I ./ /MD /link ../libraries/glfw3.lib gdi32.lib user32.lib shell32.lib kernel32.lib
popd