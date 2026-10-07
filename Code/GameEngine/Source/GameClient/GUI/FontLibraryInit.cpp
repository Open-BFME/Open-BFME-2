// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
// stlport
//
// ?init@FontLibrary@@UAEXXZ, retail 0x00217561, 89 bytes.
// FontLibrary subsystem init: virtual slot 1 (offset 0x4) of vtable 0x007E5AD0.
// Stack INI (0x87C) plus one loadFile("data\\ini\\fontsubstitution.ini",
// INI_LOAD_OVERWRITE, 0) via rowed StringBase<char> ctor 0x00037BA0 and pinned
// INI ctor 0x0002CDB0 / loadFile 0x0002DC75 / dtor 0x0002CE5B. ZH donor
// GameFont.h declares virtual void init; ZH/BFME1 bodies are empty, BFME2 adds
// the font-substitution load. Retail ignores this.

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


class Xfer;

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

class INI
{
public:
	INI();
	~INI();
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *xfer);	// 0x0002DC75 returns 1
	const char *getNextToken(const char *seps);
	int scanIndexList(const char *token, const char * const *names);
	AsciiString getFilename() const;
	int getLineNum() const;
	void initFromINI(void *what, const struct FieldParse *parseTable);
	static void parseAttributeModifier(INI *ini, void *instance, void *store, const void *userData);
	static void parseMeleeBehavior(INI *ini, void *instance, void *store, const void *userData);
private:
	char m_storage[0x87C];
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init();
	void setName(AsciiString name);

private:
	unsigned char m_bfmeBasePad[8];
};

class FontLibrary : public SubsystemInterface
{
public:
	FontLibrary();
	~FontLibrary();
	virtual void init();

private:
	void *m_fontList;
	int m_count;
	unsigned char m_tables[0x18];
};

void FontLibrary::init()
{
	INI ini;
	ini.loadFile("data\\ini\\fontsubstitution.ini", INI_LOAD_OVERWRITE, 0);
}

// ?init@ControlBarResizer@@QAEXXZ, retail 0x001DB71C, 89 bytes.
// Zero Hour's ControlBarResizer::init (ControlBarResizer.cpp): the same stack INI
// and one load of "Data\\INI\\ControlBarResizer.ini", a path nothing else loads.
// Retail places it directly after the rowed ResizerWindow constructor (0x001DB6FD,
// 31 bytes), and nothing calls or references it. Its home unit,
// ControlBarResizer.cpp, links, and the INI ctor, loadFile and dtor are not
// defined yet; this unit already carries those three names, so it lands here.
class ControlBarResizer
{
public:
	void init();
};

void ControlBarResizer::init()
{
	INI ini;
	ini.loadFile("Data\\INI\\ControlBarResizer.ini", INI_LOAD_OVERWRITE, 0);
}

// ?parseIni@Mouse@@QAEXXZ, retail 0x001EE483, 89 bytes.
// Zero Hour's Mouse::parseIni (Mouse.cpp, right after ~Mouse): the same stack
// INI and one load of "Data\\INI\\Mouse.ini". Retail places it directly after
// the 165-byte destructor at 0x001EE3DE (ZH's ~Mouse precedes parseIni), and
// nothing calls or references it; it lands beside ControlBarResizer::init for
// the same INI ctor, loadFile and dtor names.
class Mouse
{
public:
	void parseIni();
};

void Mouse::parseIni()
{
	INI ini;
	ini.loadFile("Data\\INI\\Mouse.ini", INI_LOAD_OVERWRITE, 0);
}

// ?rva00425F10@Rva00425F10@@UAEXXZ, retail 0x00425F10, 89 bytes.
// The same body loading "Data\\INI\\Stances.ini", in slot 1 of vtable 0xC3C2AC
// (the slot FontLibrary::init fills in its vtable).
#include <map>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

struct StanceData
{
	StanceData();
	int m_attributeModifier;
	int m_meleeBehavior;
};

struct BfmePod52
{
	BfmePod52(NameKeyType key);
	NameKeyType m_nameKey;
	StanceData m_stances[6];
};

BfmePod52::BfmePod52(NameKeyType key) : m_nameKey(key)
{
}

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
	const AsciiString &keyToName(NameKeyType key);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
	INIException &operator=(const INIException &that);
};

typedef void (*INIFieldParseProc)(INI *, void *, void *, const void *);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parseFunc;
	const void *userData;
	int offset;
};

extern const char *TheStanceNames[];

void __cdecl parseStance(INI *ini, void *data)
{
	int index = ini->scanIndexList(ini->getNextToken(0), TheStanceNames);
	FieldParse parseTable[] = {
		{ "AttributeModifier", INI::parseAttributeModifier, 0, 0 },
		{ "MeleeBehavior", INI::parseMeleeBehavior, 0, 4 },
		{ 0, 0, 0, 0 }
	};
	ini->initFromINI(&((BfmePod52 *)data)->m_stances[index], parseTable);
}

class Rva00425F10 : public SubsystemInterface
{
public:
	Rva00425F10();
	virtual ~Rva00425F10();
	virtual void rva00425F10();
	static void parseStanceTemplateDefinition(INI *ini);
private:
	_STL::map<int, BfmePod52> m_map;
};

extern Rva00425F10 *TheStancesStore;

Rva00425F10::Rva00425F10()
{
}

Rva00425F10::~Rva00425F10()
{
}

void Rva00425F10::rva00425F10()
{
	INI ini;
	ini.loadFile("Data\\INI\\Stances.ini", INI_LOAD_OVERWRITE, 0);
}


void Rva00425F10::parseStanceTemplateDefinition(INI *ini)
{
	const char *token = ini->getNextToken(0);
	NameKeyType key = TheNameKeyGenerator->nameToKey(token);
	_STL::map<int, BfmePod52>::iterator it = TheStancesStore->m_map.find(key);
	if (it != TheStancesStore->m_map.end())
	{
		throw INIException(3, "%s(%d) : Stance %s already defined",
			ini->getFilename(), ini->getLineNum(), TheNameKeyGenerator->keyToName(key));
	}
	_STL::map<int, BfmePod52>::iterator it2 =
		TheStancesStore->m_map.insert(_STL::pair<const int, BfmePod52>(key, BfmePod52(key))).first;
	FieldParse parseTable[] = {
		{ "Stance", (INIFieldParseProc)parseStance, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	ini->initFromINI(&it2->second, parseTable);
}
