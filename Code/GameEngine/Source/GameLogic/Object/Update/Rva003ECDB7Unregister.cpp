// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// FUN_007ecdb7 @0x003ECDB7 (82B): heap-object dtor helper that unregisters
// the +0x550 name when it differs from the global empty at 0xDE0878 then
// destroys that name. Calls the rowed StringBase compare 0x000069D6 plus
// the rowed manager remove 0x003ED2A3 plus the pinned StringBase dtor
// 0x00036410. Called from ThreatFinderUpdate dtor 0x003ECF64 plus two
// 0x002C5xxx sites. No donor name claimed.
#include "ascii_string.h"


class Rva003ED2A3Manager
{
public:
	void remove(const AsciiString &name, void *obj);
	void add(const AsciiString &name, void *obj);
};

class Rva003ECDB7Object
{
public:
	~Rva003ECDB7Object();
	void registerName();

private:
	char m_pad[0x550];
	AsciiString m_name;
};

extern Rva003ED2A3Manager *g_manager;
// g_manager: matched references place it at VA 0xe02e48 (zero-filled .bss).
Rva003ED2A3Manager * g_manager;

Rva003ECDB7Object::~Rva003ECDB7Object()
{
	if (m_name.compare(AsciiString::TheEmptyString) != 0)
		g_manager->remove(m_name, this);
}

void Rva003ECDB7Object::registerName()
{
	if (m_name.compare(AsciiString::TheEmptyString) != 0)
		g_manager->add(m_name, this);
}
