// ?Rva004B2B64_ParseReplaceObject@INI@@SAXPAV1@PAX1PBX@Z
// partial score=0.9 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /GX /DNDEBUG /MD
//
// Object-record FieldParse procs (names address-derived):
//   0x003F341E 113B ConnectsTo (0x00C36640): for every token (separators
//       from the INI's +0x420 field) a LivingWorldRegionConnection (rowed
//       ctor 0x003F24F3 / virtual dtor 0x003F2517) takes the token as its
//       region name (+0x04) and is appended to the vector at the store
//       (rowed push_back 0x003F309A); it is destroyed after the next token
//       is read.
//   0x004B2B64 128B ReplaceObject (0x00BEF960): news a 0x10-byte
//       Rva004B2B2F entry (rowed ctor 0x004B2B14, unwound on a throwing
//       ctor), fills it from a local MultiIniFieldParse holding table
//       0x00C56D20 through the pinned initFromINIMulti, and appends the
//       pointer to the vector at instance + 0xC8 (pointer push_back fold
//       0x004DFCB0).

#include "ascii_string.h"

#define NULL 0

struct FieldParse;

class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
	void add(const FieldParse *parseTable, unsigned int extraOffset);
private:
	unsigned char m_unreconstructed_00[0x84];
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps = 0);
	void initFromINIMulti(void *what, const MultiIniFieldParse &parseTableList);
	static void Rva003F341E_ParseConnections(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004B2B64_ParseReplaceObject(INI *ini, void *instance, void *store, const void *userData);
	const char *separators() const { return m_separators; }
private:
	unsigned char m_unreconstructed_000[0x420];
	const char *m_separators;		// +0x420
};

class LivingWorldRegionConnection
{
public:
	LivingWorldRegionConnection();
	virtual ~LivingWorldRegionConnection();
	AsciiString m_regionName;		// +0x04
private:
	unsigned char m_unreconstructed_08[0x18 - 0x08];
};

class Rva004B2B2F
{
public:
	Rva004B2B2F();
	~Rva004B2B2F();
private:
	unsigned char m_unreconstructed_00[0x10];
};

extern const FieldParse g_00C56D20[];

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<LivingWorldRegionConnection, allocator<LivingWorldRegionConnection> >
{
public:
	void push_back(const LivingWorldRegionConnection &x);
private:
	LivingWorldRegionConnection *m_start;
	LivingWorldRegionConnection *m_finish;
	LivingWorldRegionConnection *m_endOfStorage;
};
template <> class vector<const Rva004B2B2F *, allocator<const Rva004B2B2F *> >
{
public:
	void push_back(const Rva004B2B2F *const &x);
private:
	const Rva004B2B2F **m_start;
	const Rva004B2B2F **m_finish;
	const Rva004B2B2F **m_endOfStorage;
};
}

struct Rva004B2B64Owner
{
	unsigned char m_unreconstructed_00[0xC8];
	_STL::vector<const Rva004B2B2F *, _STL::allocator<const Rva004B2B2F *> > m_entries;	// +0xC8
};

// ?Rva003F341E_ParseConnections@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva003F341E_ParseConnections(INI *ini, void *, void *store, const void *)
{
	const char *token = ini->getNextTokenOrNull(ini->separators());
	while (token)
	{
		LivingWorldRegionConnection connection;
		connection.m_regionName.set(token);
		((_STL::vector<LivingWorldRegionConnection, _STL::allocator<LivingWorldRegionConnection> > *)store)->push_back(connection);
		token = ini->getNextTokenOrNull(ini->separators());
	}
}

// ?Rva004B2B64_ParseReplaceObject@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva004B2B64_ParseReplaceObject(INI *ini, void *instance, void *, const void *)
{
	MultiIniFieldParse p;
	p.add(g_00C56D20, 0);
	Rva004B2B2F *entry = new Rva004B2B2F;
	ini->initFromINIMulti(entry, p);
	((Rva004B2B64Owner *)instance)->m_entries.push_back(entry);
}
