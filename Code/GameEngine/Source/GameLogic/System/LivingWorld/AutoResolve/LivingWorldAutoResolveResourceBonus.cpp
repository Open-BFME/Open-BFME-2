// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// LivingWorldAutoResolveResourceBonus.cpp -- the resource-bonus INI block
// parser at its WorldBuilder home (WB 0x012E87C0 names it
// LivingWorldAutoResolveResourceBonusScheduleStore::
// parseLivingWorldAutoResolveResourceBonusBlock, assert line 184; the retail
// diagnostic names LivingWorldAutoResolveResourceBonus).
//
// Target facts (retail 0x0041428F, 120 bytes): outside the startup INI load
// (INI +0x08 not 1) it throws INIException(8, ...); otherwise it builds a
// 24-byte bonus record on the stack, lets the record parse its block, appends
// it to the schedule store's vector (+0x0C of the store global) and destroys
// the local. The record is rowed under four address names, one per row: its
// constructor 0x00413F8B, its block parse 0x00414081, the vector element of
// push_back 0x00414258 and its destructor 0x0022CD2A. The view below chains
// those names on one 24-byte object so the local reaches each row as retail's
// does; the record's real class name is not recovered.

#include <vector>

class INI
{
public:
	char m_pad00[8];
	int m_loadType;						// +0x08, 1 for the startup files
};

class INIException
{
public:
	INIException(int code, const char *format, ...);	// 0x0002F681
	INIException(const INIException &that);
	~INIException();
	char *mFailureMessage;
	int mErrorCode;
};

struct Rva00414258Element
{
	char m_data[0x18];
};

struct Rva0022CD2A : public Rva00414258Element
{
	~Rva0022CD2A();						// 0x0022CD2A
};

struct Rva00413F8B : public Rva0022CD2A
{
	Rva00413F8B();						// 0x00413F8B
};

class Rva00414081
{
public:
	void rva00414081(INI *ini);			// 0x00414081, the record's block parse
};

class Rva0022C316Subsystem
{
public:
	char m_pad00[0x0c];
	_STL::vector<Rva00414258Element> m_bonuses;	// +0x0C
};
extern Rva0022C316Subsystem *TheLivingWorldAutoResolveResourceBonusScheduleStore;

class LivingWorldAutoResolveResourceBonusScheduleStore
{
public:
	static void parseLivingWorldAutoResolveResourceBonusBlock(INI *ini);
};

// LivingWorldAutoResolveResourceBonusScheduleStore::
// parseLivingWorldAutoResolveResourceBonusBlock, retail 0x0041428F.
void LivingWorldAutoResolveResourceBonusScheduleStore::parseLivingWorldAutoResolveResourceBonusBlock(INI *ini)
{
	if (ini->m_loadType != 1)
		throw INIException(8, "Cannot define LivingWorldAutoResolveResourceBonus except in main INI files at startup");
	Rva00413F8B bonus;
	((Rva00414081 *)&bonus)->rva00414081(ini);
	TheLivingWorldAutoResolveResourceBonusScheduleStore->m_bonuses.push_back(bonus);
}
