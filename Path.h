#pragma once
#include "pch.h"

class Path
{
public:
	static vector<string> tmpNames;
public:
	static vector<string> GetFiles(const string& path){
		tmpNames.clear();
		GetFile(path);
		return tmpNames;
	}
private:
	static void GetFile(const string &path){
		string tmp = "Resources/" + path + string("\\*.*");
		WIN32_FIND_DATAA fd;
		auto hFind = FindFirstFileA(tmp.c_str(), &fd);
		if (INVALID_HANDLE_VALUE != hFind)
		{
			do{
				if (fd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY){
					tmp = path + "/" + string(fd.cFileName);
					tmpNames.push_back(tmp);
				}
			} while (FindNextFileA(hFind, &fd));
			FindClose(&fd);
		}
	}
};