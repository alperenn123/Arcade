@echo off
if not exist ..\build mkdir ..\build
pushd ..\build
del *.pdb > NUL 2> NUL
echo WAITING FOR PDB > lock.tmp

set warnings_to_ignore=-wd4201 -wd4204 -wd4255 -wd4668 -wd4820 -wd4100 -wd4189 -wd4711 -wd4710 -wd4101 -wd4296 -wd4311 -wd4115 -wd4702 -wd4456 -wd4555

REM Asset Cooker Build
REM cl -nologo -O2 -Zi -FC -WX -Wall %warnings_to_ignore% ..\code\cooker.c /link user32.lib gdi32.lib -incremental:no -opt:ref

REM Game Build
cl -nologo -O2 -FC -WX -Wall -Zi -DDEVELOPMENT=0 -DPROFILER=0 %warnings_to_ignore% ..\code\win32_platform.cpp /link user32.lib gdi32.lib winmm.lib -incremental:no -opt:ref


del lock.tmp
del *.obj

popd