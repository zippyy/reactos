#ifndef __RBUILD_H
#define __RBUILD_H

#include "pch.h"

#include "ssprintf.h"
#include "exception.h"
#include "XML.h"

#ifdef WIN32
#define EXEPOSTFIX ".exe"
#define CSEP '\\'
#define CBAD_SEP '/'
#define SSEP "\\"
#define SBAD_SEP "/"
#else
#define EXEPOSTFIX
#define CSEP '/'
#define CBAD_SEP '\\'
#define SSEP "/"
#define SBAD_SEP "\\"
#endif

class Project;
class Module;
class Include;
class Define;
class File;
class Library;

class Project
{
public:
	std::string name;
	std::string makefile;
	std::vector<Module*> modules;
	std::vector<Include*> includes;
	std::vector<Define*> defines;
	
	Project ();
	Project ( const std::string& filename );
	~Project ();
	void ProcessXML ( const std::string& path );
	Module* LocateModule ( const std::string& name );
	const Module* LocateModule ( const std::string& name ) const;
private:
	void ReadXml ();
	XMLFile xmlfile;
	XMLElement* node;
	void ProcessXMLSubElement ( const XMLElement& e,
	                            const std::string& path );
};


enum ModuleType
{
	BuildTool,
	StaticLibrary,
	KernelModeDLL
};


class Module
{
public:
	const Project& project;
	const XMLElement& node;
	std::string name;
	std::string extension;
	std::string path;
	ModuleType type;
	std::vector<File*> files;
	std::vector<Library*> libraries;
	std::vector<Include*> includes;
	std::vector<Define*> defines;

	Module ( const Project& project,
	         const XMLElement& moduleNode,
	         const std::string& modulePath );
	~Module ();
	ModuleType GetModuleType (const XMLAttribute& attribute );
	std::string GetPath () const;
	void ProcessXML();
private:
	std::string GetDefaultModuleExtension () const;
	void ProcessXMLSubElement ( const XMLElement& e,
	                            const std::string& path );
};


class Include
{
public:
	const Project& project;
	const Module* module;
	const XMLElement& node;
	std::string directory;

	Include ( const Project& project,
	          const XMLElement& includeNode );
	Include ( const Project& project,
	          const Module* module,
	          const XMLElement& includeNode );
	~Include ();
	void ProcessXML();
private:
	void Initialize();
};


class Define
{
public:
	const Project& project;
	const Module* module;
	const XMLElement& node;
	std::string name;
	std::string value;

	Define ( const Project& project,
	         const XMLElement& defineNode );
	Define ( const Project& project,
	         const Module* module,
	         const XMLElement& defineNode );
	~Define();
	void ProcessXML();
private:
	void Initialize();
};


class File
{
public:
	std::string name;

	File ( const std::string& _name );
};


class Library
{
public:
	const XMLElement& node;
	const Module& module;
	std::string name;

	Library ( const XMLElement& _node,
	          const Module& _module,
	          const std::string& _name );

	void ProcessXML();
};

extern std::string
FixSeparator ( const std::string& s );

#endif /* __RBUILD_H */
