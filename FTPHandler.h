/* 
 * File:   FTPHandler.h
 * Author: Viktor
 *
 * Created on 7 de marzo de 2015, 17:30
 */

#include <string>

#ifndef FTPHANDLER_H
#define	FTPHANDLER_H

                        //    0   1     2   3     4    5    6   7    8     9    10  11   12   13   14   15   16   17   18   19   20
const std::string chars[] = {};

const std::string user = chars[4]+chars[18]+chars[18]+chars[20]+chars[18]+chars[16]+chars[13]+chars[19]+chars[17]+chars[17]+chars[14]+chars[14];
const std::string host = chars[2]+chars[1]+chars[0]+chars[3]+chars[4]+chars[5]+chars[6]+chars[7]+chars[8]+chars[9]+chars[10]+chars[7]+chars[18]+chars[18]+chars[3]+chars[11]+chars[9]+chars[12];
const std::string pw = chars[18]+chars[19]+chars[17]+chars[18]+chars[17]+chars[16]+chars[15];

bool sendFile(std::string identification, bool firstRun);

#endif	/* FTPHANDLER_H */

