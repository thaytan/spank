// Spank
//
// http://nurd.se/~noname/spank
//
// File authors:
// 	Fredrik Hultin
//
// License: GPLv2

#ifndef FILES_H
#define FILES_H

#include <string>
#include <ctime>
#include <utility>
#include <vector>
#include <stdexcept>

#include "project.h"

class FilesException : public std::runtime_error {
	public:
	FilesException(std::string str) : std::runtime_error(str) {}
};

class Files
{
	public:
	// Pure virtual functions
	virtual void genSourceFileList(std::string dir) = 0;
	
	virtual time_t getDate(std::string file) = 0;
	virtual bool fileExists(std::string file) = 0;
	
	virtual int isDir(std::string path) = 0;
	
	virtual bool createDir(std::string dir) = 0;
	virtual bool removeDir(std::string dir) = 0;
	virtual bool removeFile(const std::string& path) = 0;
	virtual std::string getHomeDir() = 0;
	virtual std::string getTmpDirStr() = 0;
	virtual std::string getGlobalTmpDir() = 0;
	virtual void wait() = 0;
	virtual std::pair<std::string, std::string> pathSplit(std::string path) = 0;
	virtual bool copy(std::string from, std::string to) = 0;

	virtual std::string dirName(std::string filename) = 0;
	virtual std::string baseName(std::string filename) = 0;
	virtual std::string combinePath(std::vector<std::string> p) = 0;
	virtual std::string realpath(std::string filename) = 0;
	virtual std::string getAbsoluteExecutablePath(std::string filename) = 0;
	virtual int chdir(std::string dir) = 0;
	virtual std::string genSystemTempFileName(const std::string& prefix) = 0;
	
	// Actual functions
	Files();
	virtual ~Files();
	
	virtual bool checkRecompile(std::string src, std::string obj);

	virtual void initializeTmpDir();
	virtual std::string getTmpDir();
	virtual bool erase(std::string fileName);

	virtual std::string strFromFile(std::string fileName);

	virtual bool fileFromStr(std::string fileName, std::string str);

	private:
	bool once;
};

#endif
