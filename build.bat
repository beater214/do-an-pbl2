@echo off
chcp 65001 >nul
title BIEN DICH VA CAP NHAT HE THONG PBL2

echo ================================================================
echo       DANG CAP NHAT VA BIEN DICH MAIN.EXE (NGOAI THU MUC GOC)
echo ================================================================
echo.

:: 1. Dong chuong trinh cu neu dang chay de tranh loi khoa file
taskkill /F /IM main.exe >nul 2>&1

:: 2. Xac dinh trinh bien dich g++
set GXX=g++
if exist "C:\ming64\ucrt64\bin\g++.exe" set GXX=C:\ming64\ucrt64\bin\g++.exe

echo [*] Trinh bien dich: %GXX%
echo [*] Dang bien dich code\main.cpp -> main.exe ...
echo.

"%GXX%" -std=c++17 -Wall -Wextra -O2 -o "main.exe" "code\main.cpp"

if %ERRORLEVEL% equ 0 (
    echo.
    echo ================================================================
    echo  [THANH CONG] Da cap nhat file main.exe tai thu muc goc!
    echo ================================================================
    echo.
    echo Nhan phim bat ky de CHAY CHUONG TRINH ngay bay gio...
    pause >nul
    cls
    main.exe
) else (
    echo.
    echo ================================================================
    echo  [THAT BAI] Qua trinh bien dich gap loi. Vui long kiem tra code!
    echo ================================================================
    echo.
    pause
)

