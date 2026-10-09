// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva002E048CParse@@YAXPAVINI@@@Z retail 0x002E048C 318 bytes.
// LivingWorldBuilding INI block parse: the parse function of the block-parse
// entry at 0x009BD07C (name VA 0x00C046E8 "LivingWorldBuilding") and its only
// reference. Reads the quoted name (rowed INI::getNextQuotedAsciiString
// 0x0002E93F); without TheLivingWorldBuildingTemplateStore (0x009FF09C) it
// throws INIException(9 "Cannot parse LivingWorldBuilding entries before
// LivingWorldBuildingTemplateStore"). Otherwise it bumps the store's id
// counter (+0x0C) and inserts (id building) into the id map at +0x10: the
// building is built by the rowed ctor 0x002DFA7A from the id and the name,
// paired by the rowed pair ctor 0x002E00AF and inserted by the rowed
// insert_unique 0x002E0403; both temporaries die through the pinned
// 0x002DFAD1 record dtor. It then inserts (name id) into the name map at
// +0x24 (rowed 0x002E035B); a name already present throws INIException(8
// "LivingWorldBuilding '%s' has already been defined. Cannot redefine")
// through ThrowInfo 0x00CFE2FC, else the new building (node+8) is filled by
// INI::initFromINI with the FieldParse table at 0x00804310. Same block-parse
// family as Rva00418AC6BodyBlockParse.cpp; WorldBuilder twin unnamed.
#include "ascii_string.h"
#include <hash_map>

struct FieldParse;

class INI
{
public:
	AsciiString getNextQuotedAsciiString();
	void initFromINI(void *what, const FieldParse *parseTable);
};

// The 72-byte building record (LivingWorldBuilding template); its out-of-line
// destructor is the pinned 0x002DFAD1.
struct Rva002DFAD1Dtor
{
	~Rva002DFAD1Dtor();
	int a[18];
};

struct BfmePod72 : Rva002DFAD1Dtor
{
	BfmePod72(const BfmePod72 &);
};

class Rva002DFA7A : public BfmePod72
{
public:
	Rva002DFA7A(int id, const AsciiString &name);
};

typedef _STL::hash_map<int, BfmePod72, _STL::hash<int>, _STL::equal_to<int>,
	_STL::allocator<_STL::pair<const int, BfmePod72> > > BuildingMap;

namespace _STL {
// Retail calls both out of line (0x002E00AF and 0x002E0403).
template <> pair<const int, BfmePod72>::pair(const int &, const BfmePod72 &);
typedef hashtable<pair<const int, BfmePod72>, int, hash<int>, _Select1st<pair<const int, BfmePod72> >,
	equal_to<int>, allocator<pair<const int, BfmePod72> > > BuildingTable;
template <> pair<BuildingTable::iterator, bool> BuildingTable::insert_unique(const BuildingTable::value_type &);
}

#pragma pack(push, 1)
struct InsertRet002E01F7
{
	void *m_node;
	void *m_owner;
	unsigned char m_found;
};
#pragma pack(pop)

// The name map's insert (rowed 0x002E035B: resize then insert_unique).
class Rva000427195
{
public:
	InsertRet002E01F7 rva002E035B(const void *key);
	InsertRet002E01F7 insert(const _STL::pair<const AsciiString, int> &value) { return rva002E035B(&value); }
private:
	char m_body[0x14];
};

class Rva0022C0CDSubsystem
{
public:
	char m_base[0x0C];
	unsigned int m_lastID; // +0x0C
	BuildingMap m_buildings; // +0x10
	Rva000427195 m_names; // +0x24
};

extern Rva0022C0CDSubsystem *TheLivingWorldBuildingTemplateStore;
extern const FieldParse Rva002E048CFieldParseTable[];

struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

void __cdecl Rva002E048CParse(INI *ini)
{
	AsciiString name = ini->getNextQuotedAsciiString();
	if (TheLivingWorldBuildingTemplateStore == 0)
	{
		INIException e(9, "Cannot parse LivingWorldBuilding entries before LivingWorldBuildingTemplateStore is created.");
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
	++TheLivingWorldBuildingTemplateStore->m_lastID;
	unsigned int id = TheLivingWorldBuildingTemplateStore->m_lastID;
	_STL::pair<BuildingMap::iterator, bool> result = TheLivingWorldBuildingTemplateStore->m_buildings.insert(
		_STL::pair<const int, BfmePod72>(id, Rva002DFA7A(id, name)));
	InsertRet002E01F7 named = TheLivingWorldBuildingTemplateStore->m_names.insert(
		_STL::pair<const AsciiString, int>(name, id));
	if (!named.m_found)
	{
		INIException e(8, "LivingWorldBuilding '%s' has already been defined. Cannot redefine", name.str());
		_CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
		__assume(0);
	}
	BfmePod72 *building = &result.first->second;
	ini->initFromINI(building, Rva002E048CFieldParseTable);
}
