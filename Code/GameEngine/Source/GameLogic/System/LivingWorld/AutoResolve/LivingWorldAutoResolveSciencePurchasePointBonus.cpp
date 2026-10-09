// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// LivingWorldAutoResolveSciencePurchasePointBonus.cpp -- the science-point
// bonus INI block parser at its WorldBuilder home (WB 0x012E6F40 names it
// LivingWorldAutoResolveSciencePurchasePointBonusScheduleStore::
// parseLivingWorldAutoResolveSciencePurchasePointBonusBlock, assert line 184;
// the retail diagnostic names LivingWorldAutoResolveSciencePurchasePointBonus).
//
// Target facts (retail 0x00413B4D, 120 bytes): the twin of the resource-bonus
// parser 0x0041428F (LivingWorldAutoResolveResourceBonus.cpp). Outside the
// startup INI load (INI +0x08 not 1) it throws INIException(8, ...); otherwise
// it builds a 24-byte bonus record on the stack, lets it parse its block,
// appends it to the schedule store's vector (+0x0C of the store global) and
// destroys the local. The record is rowed under three address names: its
// constructor 0x0041386B with its block parse 0x0041393F, the vector element
// of push_back 0x00413B16, and the destructor 0x0022CCEF the ledger names
// BfmeNarrowRecord00427F75 (an ICF-folded record teardown). The view below
// chains those names on one 24-byte object so the local reaches each row as
// retail's does; the record's real class name is not recovered.

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

struct Rva00413B16Element
{
	char m_data[0x18];
};

struct BfmeNarrowRecord00427F75 : public Rva00413B16Element
{
	~BfmeNarrowRecord00427F75();		// 0x0022CCEF
};

struct Rva0041386B : public BfmeNarrowRecord00427F75
{
	Rva0041386B();						// 0x0041386B
	void rva0041393F(INI *ini);			// 0x0041393F, the record's block parse
};

class Rva0022C38BSubsystem
{
public:
	char m_pad00[0x0c];
	_STL::vector<Rva00413B16Element> m_bonuses;	// +0x0C
};
extern Rva0022C38BSubsystem *TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore;

class LivingWorldAutoResolveSciencePurchasePointBonusScheduleStore
{
public:
	static void parseLivingWorldAutoResolveSciencePurchasePointBonusBlock(INI *ini);
};

// LivingWorldAutoResolveSciencePurchasePointBonusScheduleStore::
// parseLivingWorldAutoResolveSciencePurchasePointBonusBlock, retail 0x00413B4D.
void LivingWorldAutoResolveSciencePurchasePointBonusScheduleStore::parseLivingWorldAutoResolveSciencePurchasePointBonusBlock(INI *ini)
{
	if (ini->m_loadType != 1)
		throw INIException(8, "Cannot define LivingWorldAutoResolveSciencePurchasePointBonus except in main INI files at startup");
	Rva0041386B bonus;
	bonus.rva0041393F(ini);
	TheLivingWorldAutoResolveSciencePurchasePointBonusScheduleStore->m_bonuses.push_back(bonus);
}
