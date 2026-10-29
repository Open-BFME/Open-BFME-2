// cl: /DNDEBUG /MD
// stlport
//
// ?Rva004BFD83Parse@@YAXPAVINI@@PAX1PBX@Z, retail 0x004BFD83 (115B): the
// DamageCreationList FieldParse proc (row 0x00C5B2F8). Reads an
// ObjectCreationList (rowed INI::parseObjectCreationList) and two optional
// index tokens (names at 0x00DCD7EC and 0x00DCD7FC, 0 when absent) into a
// 12-byte entry appended to the vector at instance + 0x58 (12-byte POD
// push_back fold 0x002DF89B). Name address-derived.

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);
	int scanIndexList(const char *token, const char *const *names);
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);
};

class ObjectCreationList;

struct Rva004BFD83Entry
{
	const ObjectCreationList *m_ocl;
	int m_damageType;
	int m_deathType;
};

// The retail table at RVA 0x009CD7EC: 4 string pointers.
extern const char *theRockNames[4] = { "NONE", "CATAPULT_ROCK", "TREBUCHET_ROCK", 0 };
// The retail table at RVA 0x009CD7FC: 6 string pointers.
extern const char *theDamageSideNames[6] = { "NONE", "FRONT_DESTROYED", "RIGHT_DESTROYED", "BACK_DESTROYED", "LEFT_DESTROYED", 0 };

struct PrereqUnitRec;

#include <vector>

namespace _STL
{
template <class T, class A> class vector;
template <> class vector<Rva004BFD83Entry, allocator<Rva004BFD83Entry> >
{
public:
	void push_back(const Rva004BFD83Entry &x);
private:
	Rva004BFD83Entry *m_start;
	Rva004BFD83Entry *m_finish;
	Rva004BFD83Entry *m_endOfStorage;
};
// LINK: the push_back fold 0x002DF89B is rowed for vector<PrereqUnitRec>, the same element size.
template <> class vector<PrereqUnitRec, allocator<PrereqUnitRec> >
{
public:
	void push_back(const PrereqUnitRec &x);
};
}

struct Rva004BFD83Owner
{
	unsigned char m_unreconstructed_00[0x58];
	_STL::vector<Rva004BFD83Entry, _STL::allocator<Rva004BFD83Entry> > m_entries;	// +0x58
};

// ?Rva004BFD83Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva004BFD83Parse(INI *ini, void *instance, void *, const void *)
{
	Rva004BFD83Entry entry;
	INI::parseObjectCreationList(ini, instance, &entry.m_ocl, 0);

	const char *token = ini->getNextTokenOrNull();
	if (token)
		entry.m_damageType = ini->scanIndexList(token, theRockNames);
	else
		entry.m_damageType = 0;

	token = ini->getNextTokenOrNull();
	if (token)
		entry.m_deathType = ini->scanIndexList(token, theDamageSideNames);
	else
		entry.m_deathType = 0;

	((_STL::vector<PrereqUnitRec, _STL::allocator<PrereqUnitRec> > *)&((Rva004BFD83Owner *)instance)->m_entries)->push_back(*(const PrereqUnitRec *)&entry);
}
