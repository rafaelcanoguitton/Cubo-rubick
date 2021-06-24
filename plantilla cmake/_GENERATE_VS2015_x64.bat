@echo off

mkdir build
chdir build

mkdir mak.vc14
chdir mak.vc14

mkdir x64
chdir x64

del CMakeCache.txt

cmake -DCMAKE_CONFIGURATION_TYPES="Debug;Release" -G "Visual Studio 14 Win64" ../../../

if %errorlevel% NEQ 0 goto error
goto end

:error
echo Houve um erro. Pressione qualquer tecla para finalizar.
pause >nul

:end

echo Pressione qualquer tecla para finalizar.
pause >nul

cd ../../../