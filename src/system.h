// Spank
//
// http://nurd.se/~noname/spank
//
// File authors:
// 	Fredrik Hultin
//
// License: GPLv2

// This class contains functions returning base-class pointers to approperiate singletons.
// Like, if you're on a unix-system, getFilesInstance() returns "Files"-pointer to "FilesUnix" singleton instance

#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdexcept>

#include "singleton.h"

#include "filesunix.h"
#include "compilergcc.h"
#include "compilermcs.h"
#include "compilervala.h"
#include "exportshell.h"
#include "exportmakefile.h"

#include "installerunix.h"
#include "installerdeb.h"

#define FILES System::getFilesInstance()
#define COMPILER System::getCompilerInstance()
#define EXPORT System::getExportInstance()
#define INSTALLER System::getInstallerInstance()

// All file enviroments (only one atm.)
typedef Singleton<FilesUnix> SFilesUnix;

// All compiler systems
typedef Singleton<CompilerGcc> SCompilerGcc;
typedef Singleton<CompilerMcs> SCompilerMcs;
typedef Singleton<CompilerVala> SCompilerVala;

// All exporters
typedef Singleton<Export> SExport; 			// Default exporter (always fails)
typedef Singleton<ExportShell> SExportShell; 		// I'm bringin' sexy back (yeah)
typedef Singleton<ExportMakefile> SExportMakefile; 	// Makefile

// All installers
typedef Singleton<Installer> SInstaller;
typedef Singleton<InstallerUnix> SInstallerUnix;
typedef Singleton<InstallerDeb> SInstallerDeb;

class SystemException : public std::runtime_error {
	public:
	SystemException(std::string str) : std::runtime_error(str) {}
};

class System
{
	public:
		static Files* getFilesInstance();
		static Compiler* getCompilerInstance();
		static Export* getExportInstance();
		static Installer* getInstallerInstance();
};

#endif
