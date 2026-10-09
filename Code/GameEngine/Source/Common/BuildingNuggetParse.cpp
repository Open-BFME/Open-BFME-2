// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva0052B8ED_ParseNugget@@YA?AU?$auto_ptr@VRva0052B685Pointee@@@_STL@@PAVINI@@@Z
// retail 0x0052B8ED..0x0052BA03 (279 bytes) cdecl.
//
// The BuildingNugget factory parse (one caller 0x002E0142; WorldBuilder twin
// 0x0131B5D0 by its "Unknown BuildingNugget type '%s'" literal): reads the
// quoted nugget type, looks it up in the nugget factory table (rowed
// 0x0052B84F, hash lookup 0x00056F61) and throws an INIException for an
// unknown type; otherwise reads the quoted nugget name, has the factory
// (node +0x08, vtable slot 1) create the nugget, lets the nugget build its
// MultiIniFieldParse (vtable slot 3), parses the block through
// INI::initFromINIMulti and hands the nugget out through the rowed holder
// release 0x0052B685 as an auto_ptr (the holder's destructor is the folded
// 0x000AD6F4). The nugget and holder identities stay address-derived.
#include <memory>
#include "ascii_string.h"

class MultiIniFieldParse
{
public:
	MultiIniFieldParse();				// 0x0002BAA0
private:
	unsigned char m_data[0x84];
};

class INI
{
public:
	AsciiString getNextQuotedAsciiString();		// 0x0002E93F
	void initFromINIMulti(void *what, const MultiIniFieldParse &parse);	// 0x0002D7A8
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);	// 0x0002F681
	INIException(const INIException &that);
	~INIException();
private:
	char *m_failureMessage;
	int m_argCount;
};

// The nugget: vtable slot 3 builds its field parse.
class Rva0052B685Pointee
{
public:
	virtual ~Rva0052B685Pointee();
	virtual void v1();
	virtual void v2();
	virtual void buildFieldParse(MultiIniFieldParse &parse);
};

// A nugget type's factory: vtable slot 1 creates one by name.
class BuildingNuggetFactory
{
public:
	virtual void v0();
	virtual Rva0052B685Pointee *create(const AsciiString *name);
};

struct BuildingNuggetFactoryNode
{
	void *m_next;
	AsciiString m_type;				// +0x04
	BuildingNuggetFactory *m_factory;		// +0x08
};

class Rva0052B7F8Owner;
Rva0052B7F8Owner *rva0052B84F();			// 0x0052B84F, the factory table

class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *key);	// 0x00056F61, the node or null
};

// The owning holder: its destructor is the folded 0x000AD6F4.
class Gen_uw_000ad6f4
{
public:
	~Gen_uw_000ad6f4();
	Rva0052B685Pointee *ptr;
};
class Rva0052B685Holder : public Gen_uw_000ad6f4
{
public:
	Rva0052B685Holder(Rva0052B685Pointee *p) { ptr = p; }
	_STL::auto_ptr<Rva0052B685Pointee> release();	// 0x0052B685
};

_STL::auto_ptr<Rva0052B685Pointee> Rva0052B8ED_ParseNugget(INI *ini)
{
	AsciiString typeName = ini->getNextQuotedAsciiString();
	Rva00056F61 *factories = (Rva00056F61 *)rva0052B84F();
	BuildingNuggetFactoryNode *node = (BuildingNuggetFactoryNode *)factories->rva00056F61(&typeName);
	if (!node)
		throw INIException(3, "Unknown BuildingNugget type '%s'", typeName.str());

	AsciiString name = ini->getNextQuotedAsciiString();
	Rva0052B685Pointee *created = node->m_factory->create(&name);
	Rva0052B685Holder nugget(created);
	MultiIniFieldParse fieldParse;
	created->buildFieldParse(fieldParse);
	ini->initFromINIMulti(created, fieldParse);
	return nugget.release();
}
