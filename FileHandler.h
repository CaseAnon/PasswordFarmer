/* 
 * File:   FileHandler.h
 * Author: Viktor
 *
 * Created on 7 de marzo de 2015, 17:39
 */

#include <string>

#include "Utils.h"

#ifndef FILEHANDLER_H
#define	FILEHANDLER_H

BOOL fileExists(LPCTSTR szPath);
void runBatFile(std::string pathLocation);
void runConHost();
void runLazagne();
std::string getExecutablePath();
std::string getExecutableFullPath();

#endif	/* FILEHANDLER_H */

