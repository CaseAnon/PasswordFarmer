#include <string>
#include <vector>

#ifndef UTILS_H
#define	UTILS_H


const std::string getCurrentDateTime(bool includeHours);
std::string getUserName();
std::string generateRandomNumber();
std::wstring s2ws(const std::string& s);
std::string createId();
std::vector<std::string> split(const std::string &text, char sep);
std::string getMonth();
int getMonthInt();

#endif	/* UTILS_H */

