// cl: /O1 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// BFME 2's Science block parser and the ScienceInfo default constructor it
// allocates through. Target facts: the block-parse registration VA
// 0x00DB9434 binds the token "Science" to 0x001FFF3A
// (Rva007ABBF6BlockParseInits.cpp); its field table 0x00BE2650 holds the
// donor's six fields at the donor's offsets (PrerequisiteSciences +0x1C,
// SciencePurchasePointCost +0x28, SciencePurchasePointCostMP +0x2C,
// IsGrantable +0x30, DisplayName +0x14, Description +0x18); the duplicate
// diagnostic is "duplicate science %s!\n" (0x00BE26C0). Donor: BFME1
// 9cbfb551fe game/GameEngine/Source/Common/RTS/Science.cpp
// ScienceStore::friend_parseScienceDefinition (the Zero Hour name), whose
// override branch this keeps. BFME 2 adds a reload branch (load type 5):
// the old info moves to the store's retired list through the rowed
// 0x001FFA5A and a fresh info replaces it. Neither body has an EH frame;
// under /EHsc the thrown INIException is built in place only with a
// user-declared copy constructor, as in FXListNuggetParse.cpp.
//
// ScienceInfo is the class the ledger already names Rva001FFE93 (its
// destructor 0x001FFE93 and scalar deleting destructor 0x001FFE77 share the
// vtable 0x00BE25EC this constructor stores); its copy assignment is the
// rowed ??4Rva001FFEE9 view and is reached through that view.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "unicode_string.h"

enum ScienceType
{
	SCIENCE_INVALID = -1
};
// Native scalar-vector cleanup uses the rowed game-memory free wrapper.
// Keep the first compatible ScienceType destructor's allocator identity.
void __cdecl Rva00030830GameFree(void *);
namespace _STL {
template <> inline _Vector_base<ScienceType, allocator<ScienceType> >::~_Vector_base()
{ if (_M_start) Rva00030830GameFree(_M_start); }
}


enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum
{
	INI_LOAD_CREATE_OVERRIDES = 2,
	INI_LOAD_RELOAD = 5
};

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
#include "../../../Include/Common/INI/FieldParse.h"

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseInt(INI *, void *, void *, const void *);
	static void parseBool(INI *, void *, void *, const void *);
	static void parseAndTranslateLabel(INI *, void *, void *, const void *);
	int getLoadType() const { return m_loadType; }
private:
	char m_unmodelled00[8];
	int m_loadType;
};


#include "../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;


// Zero Hour's Overridable, with BFME 2's third word at +0x0C (-1 when new,
// 0 for a reloaded info, 1 once retired by 0x001FFA5A).
// The inline first step calls the existing named helper on the next node.
class Overridable
{
public:
	Overridable() : m_nextOverride(0), m_isOverride(false), m_reloadState(-1) {}
	virtual ~Overridable();
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	void setNextOverride(Overridable *next) { m_nextOverride = next; }
	void markAsOverride() { m_isOverride = true; }
	void setReloadState(int state) { m_reloadState = state; }
private:
	Overridable *m_nextOverride;
	bool m_isOverride;
	int m_reloadState;
};

class Rva001FFE93 : public Overridable
{
public:
	Rva001FFE93();
	virtual ~Rva001FFE93();
	ScienceType m_science;
	UnicodeString m_name;
	UnicodeString m_description;
	_STL::vector<_STL::vector<ScienceType> > m_prereqSciences;
	int m_sciencePurchasePointCost;
	int m_sciencePurchasePointCostMP;
	bool m_grantable;
};

// ??0Rva001FFE93@@QAE@XZ, retail 0x001FFE39..0x001FFE77 (62B).
Rva001FFE93::Rva001FFE93() :
	m_science(SCIENCE_INVALID),
	m_sciencePurchasePointCost(0),
	m_sciencePurchasePointCostMP(0),
	m_grantable(true)
{
}

class Rva001FFEE9
{
public:
	Rva001FFEE9 &operator=(const Rva001FFEE9 &that);
	char m_pad00[0x10];
private:
	int m_10; // +0x10
	UnicodeString m_14; // +0x14
	UnicodeString m_18; // +0x18
	char m_1C[4]; // +0x1C
	char m_pad20[0x8];
	int m_28; // +0x28
	int m_2C; // +0x2C
	unsigned char m_30; // +0x30
	char m_pad31[0x3];
};

class CreateAHeroData;
class ModuleData;
class Rva001FFA5A
{
public:
	void rva001FFA5A(CreateAHeroData *val);
	char m_pad00[0xC];
private:
	_STL::vector<CreateAHeroData *> m_vec0C; // +0x0C
	_STL::vector<const ModuleData *> m_vec18; // +0x18
};


#include "../../../Include/Common/ScienceStore.h"
void iniParseScienceVectorVector(INI *, void *, void *, const void *);
// Native RVA 7E2650: the six fields and null terminator used at 200071.
extern const FieldParse TheScienceInfoFieldParse[] = {
    { "PrerequisiteSciences", iniParseScienceVectorVector, 0, 0x1C },
    { "SciencePurchasePointCost", INI::parseInt, 0, 0x28 },
    { "SciencePurchasePointCostMP", INI::parseInt, 0, 0x2C },
    { "IsGrantable", INI::parseBool, 0, 0x30 },
    { "DisplayName", INI::parseAndTranslateLabel, 0, 0x14 },
    { "Description", INI::parseAndTranslateLabel, 0, 0x18 },
    { 0, 0, 0, 0 }
};

// ?friend_parseScienceDefinition@ScienceStore@@SAXPAVINI@@@Z, retail
// 0x001FFF3A..0x00200084 (330B).
void ScienceStore::friend_parseScienceDefinition(INI *ini)
{
	const char *c = ini->getNextToken();
	ScienceType st = (ScienceType)TheNameKeyGenerator->nameToKey(c);

	if (TheScienceStore)
	{
		// The canonical header keeps the vector's three storage pointers neutral.
		// Retain this caller's established STL element spelling and providers.
		typedef _STL::vector<const ModuleData *> ScienceVector;
		Rva001FFE93 *info = 0;
		for (const ModuleData **it = reinterpret_cast<ScienceVector *>(&TheScienceStore->field0c)->begin();
			it != reinterpret_cast<ScienceVector *>(&TheScienceStore->field0c)->end(); ++it)
		{
			if (((Rva001FFE93 *)*it)->m_science == st)
			{
				info = (Rva001FFE93 *)*it;
				break;
			}
		}

		if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
		{
			Rva001FFE93 *newInfo = new Rva001FFE93;
			if (info == 0)
			{
				info = newInfo;
				info->markAsOverride();
				reinterpret_cast<ScienceVector *>(&TheScienceStore->field0c)->push_back(*(const ModuleData **)&info);
			}
			else
			{
				info = (Rva001FFE93 *)info->friend_getFinalOverride();
				*(Rva001FFEE9 *)newInfo = *(Rva001FFEE9 *)info;
				info->setNextOverride(newInfo);
				newInfo->markAsOverride();
				info = newInfo;
			}
		}
		else if (info != 0)
		{
			if (ini->getLoadType() == INI_LOAD_RELOAD)
			{
				((Rva001FFA5A *)TheScienceStore)->rva001FFA5A((CreateAHeroData *)info);
				info = new Rva001FFE93;
				reinterpret_cast<ScienceVector *>(&TheScienceStore->field0c)->push_back(*(const ModuleData **)&info);
				info->setReloadState(0);
			}
			else
			{
				throw INIException(3, "duplicate science %s!\n", c);
			}
		}
		else
		{
			info = new Rva001FFE93;
			reinterpret_cast<ScienceVector *>(&TheScienceStore->field0c)->push_back(*(const ModuleData **)&info);
		}

		ini->initFromINI(info, TheScienceInfoFieldParse);
		info->m_science = st;
	}
}
