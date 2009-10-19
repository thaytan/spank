// Spank
//
// http://nurd.se/~noname/spank
//
// File authors:
// 	Fredrik Hultin
//
// License: GPLv2

#include "exporters/exportmakefile.h"

#include <fstream>
#include <string>

#include "log.h"
#include "system.h"
#include "settings.h"
#include "tools.h"

bool ExportMakefile::exp(std::string fileName)
{
	std::vector<CList> cList = COMPILER->compileList(false);

	LOG("Makefile exporter", LOG_DEBUG);
	LOG("Number of source files: " << cList.size(), LOG_DEBUG);

	if(fileName == ""){
		fileName = "Makefile";
	} 

	std::ofstream file(fileName.c_str());

	if(!file.good()){
		file.close();
		return false;
	}

	file << "# This file was automatically generated by " SPANK_NAME << " " << SPANK_VERSION << std::endl;
	file << "# See " << SPANK_HOMEPAGE << " for more information" << std::endl;
	file << std::endl;


	// Compiliation list

	file << "SRCS=";

	for(int i=0; i < (int)cList.size(); i++){
		file << " " << cList.at(i).src.c_str();
	}
	
	file << std::endl << "OBJS=";

	for(int i=0; i < (int)cList.size(); i++){
		file << " " << cList.at(i).obj.c_str();
	}
	file << std::endl << "CFLAGS= " << Tools::genCFlags() << std::endl;
	file << "LDFLAGS= " << Tools::genLdFlags() << std::endl;
	file << "COMPILER=" << PROJECT->getValueStr("compiler", 0) << std::endl;
	file << "TARGET=" << PROJECT->getValueStr("target", 0) << std::endl << std::endl;
	file << "all: " << PROJECT->getValueStr("target", 0) << std::endl << std::endl;

	for(int i=0; i < (int)cList.size(); i++){
		file << cList.at(i).obj.c_str() << ": " << cList.at(i).src.c_str() << std::endl;
		file << "\t@-mkdir -p " << FILES->getTmpDir() << std::endl;
		file << "\t$(COMPILER) -c " << cList.at(i).src.c_str() << " -o " << cList.at(i).obj.c_str() << " $(CFLAGS)" << std::endl << std::endl;
	}
//	file << "$(SRCS):" << std::endl << "\t$(COMPILER) -c $(CFLAGS) -c $(SRCS)" << std::endl << std::endl;
	
	file << PROJECT->getValueStr("target", 0) << ": $(OBJS)" << std::endl;
	file << std::endl << "\t$(COMPILER) $(OBJS) $(LDFLAGS) -o $(TARGET)" << std::endl << std::endl;
	
	file << "clean:" << std::endl;
	
	for(int i=0; i < (int)cList.size(); i++){
		file << "\t@-rm -f " << cList.at(i).obj.c_str() << std::endl;
	}
	file << "\t@-rm -f $(TARGET)" << std::endl;

	file.close();

	return true;
}


