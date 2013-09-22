// Spank
//
// http://nurd.se/~noname/spank
//
// File authors:
// 	Fredrik Hultin
//
// License: GPLv2

#ifndef TOOLS_H
#define TOOLS_H

#include <queue>

// TODO: no unix dependencies in tools
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <string>
#include <sstream>		
#include <vector>

typedef std::vector<std::string> StrVec;

class ForkResult
{
	public:
		ForkResult(){
			error = true;
			done = false;
			noResult = true;
			pid = 0;
			id = -1;
		}

		bool noResult;
		bool error;
		bool done;
		int id;
		std::string cmd;
		pid_t pid;
};

typedef std::queue<ForkResult> PidList;

class Tools
{
	public:
	static std::string nameEnc(std::string ext, std::string name);
	static std::string stripSrcDir(std::string name);
	static std::string toLower(std::string in);
	static std::string toUpper(std::string in);
	static std::string filenameify(std::string str);
	static std::string getLineStream(std::istream& stream);
	static std::string trim(std::string str);
	static std::string rtrim(std::string str);
	static std::string ltrim(std::string str);
	static bool endsWith(std::string str, std::string suffix);

	static int execute(std::string cmd, std::string* std = NULL, std::string* out = NULL, bool supress = true);
	static int execute(std::string cmd, std::string stdFile, std::string errFile = "/dev/null");
	static std::string deEscape(std::string str);
	static std::string joinStrings(std::vector<std::string> & strs, std::string separator = " ");
	static std::vector<std::string> splitString(std::string str, char separator = ' ');
	static std::string restOfString(std::string str, std::string startsWith);

	static std::vector<std::string> makeStrVector(std::string a);
	static std::vector<std::string> makeStrVector(std::string a, std::string b);
	static std::vector<std::string> makeStrVector(std::string a, std::string b, std::string c);
	static std::vector<std::string> makeStrVector(std::string a, std::string b, std::string c, std::string d);

	// Unix stuff
	static void forkDo(std::string cmd, PidList& pidList, int id=0);
	static ForkResult wait(PidList& pidList, unsigned int max);

	static bool executeAll(std::string configItem, std::string prefix = "", bool fake = false);
};

#endif
