// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT
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
private:
	char m_storage[0x87C];
};

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

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

// ?init@Rva00425F10@@UAEXXZ, retail 0x00425F10, 89 bytes.
// The same body loading "Data\\INI\\Stances.ini", in slot 1 of vtable 0xC3C2AC
// (the slot FontLibrary::init fills in its vtable).
#include <map>
// Suppress this TU's non-retail copy of ?_M_insert@?$_Rb_tree@HU?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBfmePod:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod52;
namespace _STL { template <> _Rb_tree_iterator<pair<int const ,BfmePod52>,_Nonconst_traits<pair<int const ,BfmePod52> > > _Rb_tree<int,pair<int const ,BfmePod52>,_Select1st<pair<int const ,BfmePod52> >,less<int>,allocator<pair<int const ,BfmePod52> > >::_M_insert(_Rb_tree_node_base *,_Rb_tree_node_base *,pair<int const ,BfmePod52> const &,_Rb_tree_node_base *); }
// Suppress this TU's non-retail copy of ?_M_create_node@?$_Rb_tree@HU?$pair@$$CBHUBfmePod52@@@_STL@@U?$_Select1st@U?$pair@$$CBHUBf:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod52;
namespace _STL { template <> _Rb_tree_node<pair<int const ,BfmePod52> > * _Rb_tree<int,pair<int const ,BfmePod52>,_Select1st<pair<int const ,BfmePod52> >,less<int>,allocator<pair<int const ,BfmePod52> > >::_M_create_node(pair<int const ,BfmePod52> const &); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@U?$pair@$$CBHUBfmePod52@@@_STL@@V?$allocator@U?$pair@$$CBHUBfmePod52@@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod52;
namespace _STL { template <> _Rb_tree_base<pair<int const ,BfmePod52>,allocator<pair<int const ,BfmePod52> > >::~_Rb_tree_base(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBHUBfmePod52@@@_STL@@@_STL@@@_STL@@QBE:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod52;
namespace _STL { template <> void allocator<_Rb_tree_node<pair<int const ,BfmePod52> > >::deallocate(_Rb_tree_node<pair<int const ,BfmePod52> > *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBHUBfmePod52@@@_STL@@@_STL@@@_STL@@QBEPA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod52;
namespace _STL { template <> _Rb_tree_node<pair<int const ,BfmePod52> > * allocator<_Rb_tree_node<pair<int const ,BfmePod52> > >::allocate(unsigned int,void const *) const; }

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

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
	// Retail array initializer at 0x00425E8A passes the folded two-word ctor.
	StanceData() : m_attributeModifier(0), m_meleeBehavior(0) {}
	int m_attributeModifier;
	int m_meleeBehavior;
};

struct BfmePod52
{
	BfmePod52(NameKeyType key);
	NameKeyType m_nameKey;
	StanceData m_stances[6];
};
// The rowed ~_Rb_tree (stlport_map_int_pod52_tree_dtor.cpp, 0x00425FB4) resets the
// EH state before freeing the header; this unit's copy did not. Bind to it.
namespace _STL { template <> _Rb_tree<int, pair<const int, BfmePod52>, _Select1st<pair<const int, BfmePod52> >, less<int>, allocator<pair<const int, BfmePod52> > >::~_Rb_tree(); }

BfmePod52::BfmePod52(NameKeyType key) : m_nameKey(key)
{
}

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
	const AsciiString &keyToName(NameKeyType key);
	static void parseStringAsNameKeyType(INI *, void *, void *, const void *);
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

extern const char *const TheStanceNames[];

class HordeContainModuleData
{
public:
	static void parseMeleeBehavior(INI *, void *, void *, const void *);
};

void __cdecl parseStance(INI *ini, void *data)
{
	int index = ini->scanIndexList(ini->getNextToken(0), TheStanceNames);
	FieldParse parseTable[] = {
		{ "AttributeModifier", NameKeyGenerator::parseStringAsNameKeyType, 0, 0 },
		{ "MeleeBehavior", HordeContainModuleData::parseMeleeBehavior, 0, 4 },
		{ 0, 0, 0, 0 }
	};
	ini->initFromINI(&((BfmePod52 *)data)->m_stances[index], parseTable);
}

class Rva00425F10 : public SubsystemInterface
{
public:
	Rva00425F10();
	virtual ~Rva00425F10();
	virtual void init();
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

void Rva00425F10::init()
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

// Names this unit references that no unit defines under that spelling. Each is
// bound to the row that owns the pinned retail address (same address, same
// body); the pin keeps the name, the row supplies the definition.
