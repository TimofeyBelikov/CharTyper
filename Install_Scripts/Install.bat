cmd /c "g++ -Wall -fexceptions -g -std=c++11 -c CharTyper.cpp FilesFunc.cpp SettingsUp.cpp && g++ -o CharTyper.exe CharTyper.o FilesFunc.o SettingsUp.o && del CharTyper.o && del FilesFunc.o && del SettingsUp.o"