// cl: /Ireference/shims/bfme2_ascii /O1 /GX /DNDEBUG /MD
//
// Zero Hour module-data FieldParse procs on their BFME 2 layouts:
//   GarrisonContainModuleData::parseInitialRoster 0x0025363A (72B): InitialRoster
//       (table 0x00BF3360, read by buildFieldParse 0x00254F75); name/count at
//       +0xA4/+0xA8 (Zero Hour's header-inline static).
//   SiegeEngineContainModuleData InitialCrew 0x0047B9AD (72B): the same body on
//       +0x194/+0x198; tables 0x00C46EC8 (SiegeEngineContain, buildFieldParse
//       0x0047B9F5) and 0x00C47208 (HordeSiegeEngineContain). BFME 2 field;
//       name address-derived.
//   CreateCrateDieModuleData::parseCrateData 0x004858F4 (73B): CrateData
//       (0x00BF0740); the token is appended as an AsciiString to the list at
//       +0x38 (rowed list<AsciiString>::push_back 0x001FD868).

#include "ascii_string.h"

typedef int Int;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	Int scanInt(const char *token);
};

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class list;
template <> class list<AsciiString, allocator<AsciiString> >
{
public:
	void push_back(const AsciiString &x);
private:
	void *m_node;
};
}

struct InitialRoster
{
	AsciiString templateName;
	Int count;
};

class GarrisonContainModuleData
{
public:
	static void parseInitialRoster(INI *ini, void *instance, void *store, const void *);

	unsigned char m_unreconstructed_00[0xA4];
	InitialRoster m_initialRoster;		// +0xA4
};

class SiegeEngineContainModuleData
{
public:
	static void rva0047B9AD(INI *ini, void *instance, void *store, const void *);

	unsigned char m_unreconstructed_00[0x194];
	InitialRoster m_initialCrew;		// +0x194
};

class CreateCrateDieModuleData
{
public:
	static void parseCrateData(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_unreconstructed_00[0x38];
	_STL::list<AsciiString, _STL::allocator<AsciiString> > m_crateNameList;	// +0x38
};

// ?parseInitialRoster@GarrisonContainModuleData@@SAXPAVINI@@PAX1PBX@Z
void GarrisonContainModuleData::parseInitialRoster(INI *ini, void *instance, void * /*store*/, const void *)
{
	GarrisonContainModuleData *self = (GarrisonContainModuleData *)instance;
	const char *name = ini->getNextToken();
	const char *countStr = ini->getNextTokenOrNull();
	Int count = countStr ? ini->scanInt(countStr) : 1;

	self->m_initialRoster.templateName.set(name);
	self->m_initialRoster.count = count;
}

// ?rva0047B9AD@SiegeEngineContainModuleData@@SAXPAVINI@@PAX1PBX@Z
void SiegeEngineContainModuleData::rva0047B9AD(INI *ini, void *instance, void * /*store*/, const void *)
{
	SiegeEngineContainModuleData *self = (SiegeEngineContainModuleData *)instance;
	const char *name = ini->getNextToken();
	const char *countStr = ini->getNextTokenOrNull();
	Int count = countStr ? ini->scanInt(countStr) : 1;

	self->m_initialCrew.templateName.set(name);
	self->m_initialCrew.count = count;
}

// ?parseCrateData@CreateCrateDieModuleData@@SAXPAVINI@@PAX1PBX@Z
void CreateCrateDieModuleData::parseCrateData(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	CreateCrateDieModuleData *self = (CreateCrateDieModuleData *)instance;

	AsciiString crateName = ini->getNextToken();

	self->m_crateNameList.push_back(crateName);
}
