// XML.h

#ifndef XML_H
#define XML_H

#include "pch.h"

void
InitWorkingDirectory();

class Path
{
	std::vector<std::string> path;
public:
	Path(); // initializes path to getcwd();
	Path ( const Path& cwd, const std::string& filename );
	std::string Fixup ( const std::string& filename, bool include_filename ) const;

	static std::string RelativeFromWorkingDirectory ( const std::string& path );

	static void Split ( std::vector<std::string>& out,
	                    const std::string& path,
	                    bool include_last );
};

class XMLFile
{
	friend class XMLElement;
public:
	XMLFile();
	void close();
	bool open(const std::string& filename);
	void next_token();
	bool next_is_text();
	bool more_tokens();
	bool get_token(std::string& token);
	const std::string& filename() { return _filename; }
	std::string Location() const;

private:
	std::string _buf, _filename;

	const char *_p, *_end;
};


class XMLAttribute
{
public:
	std::string name;
	std::string value;

	XMLAttribute();
	XMLAttribute ( const std::string& name_, const std::string& value_ );
};


class XMLElement
{
public:
	std::string location;
	std::string name;
	std::vector<XMLAttribute*> attributes;
	XMLElement* parentElement;
	std::vector<XMLElement*> subElements;
	std::string value;

	XMLElement ( const std::string& location_ );
	~XMLElement();
	bool Parse(const std::string& token,
	           bool& end_tag);
	void AddSubElement ( XMLElement* e );
	XMLAttribute* GetAttribute ( const std::string& attribute,
	                             bool required);
	const XMLAttribute* GetAttribute ( const std::string& attribute,
	                                   bool required) const;
};

XMLElement*
XMLParse(XMLFile& f,
         const Path& path,
         bool* pend_tag = NULL);

#endif//XML_H
