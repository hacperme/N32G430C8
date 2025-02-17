:: Copyright (C) 2025 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
:: Quectel Wireless Solution Proprietary and Confidential.
::

@echo off

echo=

set ql_tool_dir=%CD%\quectel_build\tools
set ql_gcc_name=gcc-arm-none-eabi-10.3-2021.10-win32
set cmd_7z=%ql_tool_dir%\7z\7z.exe
set python_dir=%ql_tool_dir%\python-3.7.6rc1-embed-amd64
set python_scripts_dir=%python_dir%\Scripts
set python_libs_dir=%python_dir%\Lib\site-packages


set ql_mingw_name=winlibs-x86_64-posix-seh-gcc-13.2.0-mingw-w64msvcrt-11.0.1-r2



set ARMGCC_DIR=%ql_tool_dir%\%ql_gcc_name%


@REM call :add_path %ql_tool_dir%\%ql_cmake_name%\bin
:: MinGW only for Windows
call :add_path %ql_tool_dir%\%ql_mingw_name%\mingw64\bin

:: add python path
call :add_path %python_dir%
call :add_path %python_scripts_dir%
call :add_path %python_libs_dir%


echo %PATH%
echo=

set buildtype_src=%1
set buildproject=%2
set buildvesion=%3
set buildsubversin=%4
set buildtype=%5


set buildoption=
if "%buildtype_src%"=="" (
	set buildoption=r
) else if /i "%buildtype_src%"=="r" (
	set buildoption=r
) else if /i "%buildtype_src%"=="new" (
	set buildoption=new
) else if /i "%buildtype_src%"=="n" (
	set buildoption=new
) else if /i "%buildtype_src%"=="clean" (
	set buildoption=clean
) else if /i "%buildtype_src%"=="c" (
	set buildoption=clean
) else if /i "%buildtype_src%"=="menuconfig" (
	set buildoption=menuconfig
) else if /i "%buildtype_src%"=="ninja" (
	set buildoption=ninja
) else if /i "%buildtype_src%"=="ninja_r" (
	set buildoption=ninja_r
) else if /i "%buildtype_src%"=="h" (
	set buildoption=h
) else if /i "%buildtype_src%"=="-h" (
	set buildoption=h
) else if /i "%buildtype_src%"=="help" (
	set buildoption=h
) else if /i "%buildtype_src%"=="/h" (
	set buildoption=h
) else if /i "%buildtype_src%"=="/?" (
	set buildoption=h
) else if /i "%buildtype_src%"=="?" (
	set buildoption=h
) else (
	echo !!!unknown build type: %buildtype_src%, should be r/new/clean/h/-h!!!
	echo=
	goto helpinfo
)

if "%buildtype%"=="" (
	set buildtype=release
)

if "%buildproject%"=="" (
	set buildproject=QEM25FANA
)

if "%buildvesion%"=="" (
	set buildvesion=R01A01
)

if "%buildsubversin%"=="" (
	set buildsubversin=V01
)

echo=

if /i "%buildoption%"=="h" (
	goto buildinfo
)

if /i "%buildoption%"=="clean" (
	goto buildstart
)

:buildstart
cd /d %CD%\quectel
echo %cd%

if /i "%buildoption%"=="clean" (
	echo=
	mingw32-make options=clean project=%buildproject% version=%buildvesion% subversion=%buildsubversin% bulid_type=%buildtype%
	goto exit
) else if /i "%buildoption%"=="r" (
	echo=
	@REM mingw32-make build_r
	mingw32-make options=ninja_r project=%buildproject% version=%buildvesion% subversion=%buildsubversin% bulid_type=%buildtype%
	goto exit
) else if /i "%buildoption%"=="menuconfig" (
	echo=
	mingw32-make app options=menuconfig
	goto exit
) else if /i "%buildoption%"=="ninja" (
	echo=
	mingw32-make options=ninja project=%buildproject% version=%buildvesion% subversion=%buildsubversin% bulid_type=%buildtype%
	goto exit
) else if /i "%buildoption%"=="ninja_r" (
	echo=
	mingw32-make options=ninja_r project=%buildproject% version=%buildvesion% subversion=%buildsubversin% bulid_type=%buildtype%
	goto exit
) else if /i "%buildoption%"=="new" (
	echo cleaning...
	echo=
	mingw32-make options=clean project=%buildproject% version=%buildvesion% subversion=%buildsubversin% bulid_type=%buildtype%
	@REM mingw32-make build
	mingw32-make options=ninja project=%buildproject% version=%buildvesion% subversion=%buildsubversin% bulid_type=%buildtype%
	goto exit
) else (
	goto exit
)


:helpinfo
echo=
echo ********************************************************************
echo !!!!!!!!!!!      Please input right build option      !!!!!!!!!!!!!!
echo ********************************************************************
echo=
:buildinfo
echo For your information:
echo.Usage: %~n0 r/new project version subversion debug/release
echo.       %~n0 clean
echo.       %~n0 h/-h
echo.Example:
echo.       %~n0 new
echo=
echo=

:exit
exit /B %ret%

:add_path
(echo ";%PATH%;" | find /C /I ";%1;" > nul) || set "PATH=%1;%PATH%"
goto :eof
