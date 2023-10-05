# Risk-Swift-Sloths
COMP 345 project taken in Fall 2023 - creating the RISK game with C++

** Team: ** 

Eyal Azimov
Paulo Baaich Da Silva
Oleksiy Kasyanenko
Liora Mezirovsky 
Natasha Uwase

#How to Run For Mac
- Place Maindriver.cpp in src next to all files
- make sure all files do not have a " " at the beginning
- Adjust the paths in #include in MainDriver.cpp
- run command below in terminal/command line 
- commaind says "change directory to src > g++ min version c++14 > compule Maindriver.cpp > compile all files with .cpp in all folders >> create o files > open MainDriver exe"

cd "/Users/eyalazimov/Desktop/Risk-Swift-Sloths/src/" && g++ -std=c++14 MainDriver.cpp `find . \( -iname '*.cpp' -not -name 'MainDriver.cpp' \)` -o MainDriver && "/Users/eyalazimov/Desktop/Risk-Swift-Sloths/src/"MainDriver

#Code Runner Mac
- Go to CodeRunner Extension settings
- Look for Executor Map and open "Edit in settings.json" in blue
- replace the "cpp" code with the one below

 "cpp": "cd $dir && g++ -std=c++14 $fileName `find . \\( -iname '*.cpp' -not -name '$fileName' \\)` -o $fileNameWithoutExt && $dir$fileNameWithoutExt",