@echo off
chcp 65001 >nul
title HE THONG QUAN LY PHONG TRO (PBL2)
cls
if exist "main.exe" (
    main.exe
) else (
    echo [!] Khong tim thay main.exe tai thu muc goc.
    echo [*] Vui long chay build.bat truoc de tao main.exe!
    pause
)

