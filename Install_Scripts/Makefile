all: CharTyper

CharTyper: checkChar.o FilesFunc.o SettingsUp.o
			g++ -o CheckChar.exe checkChar.o FilesFunc.o SettingsUp.o && del *.o && wget -O Texts.zip --no-check-certificate https://www.dropbox.com/sh/iuhj4794t4qcvwy/AACZk1uvyfPrAfMunCZ1qJP3a?dl=0 && tar -xf Texts.zip && del Texts.zip

checkChar.o: checkChar.cpp
			g++ --std=c++11 -Wall -fexceptions -g -c checkChar.cpp
	
FilesFunc.o: FilesFunc.cpp
			g++ --std=c++11 -Wall -fexceptions -g -c FilesFunc.cpp
	
SettingsUp.o: SettingsUp.cpp
			g++ --std=c++11 -Wall -fexceptions -g -c SettingsUp.cpp

clean:
	rm -rf *.o
	

	

	