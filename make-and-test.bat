@echo off

for /f "tokens=1 delims=" %%z in ('cd') do set pwd=%%z

cd /d "C:\Program Files\Microsoft Visual Studio *\VC" && call vcvarsall.bat x86
cd /d %pwd%
cls

nmake all

pause