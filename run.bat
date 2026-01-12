@echo off
echo Compiling the study planner...
g++ -std=c++11 main.cpp Scheduler.cpp input.cpp Models.cpp -o study_planner.exe

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful! Running the program...
    echo --------------------------------------------
    study_planner.exe
) else (
    echo Compilation failed. Please check for errors.
    pause
)