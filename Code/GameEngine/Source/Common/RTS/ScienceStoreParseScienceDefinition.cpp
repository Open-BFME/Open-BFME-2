// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
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
#include <vector>
#include "unicode_string.h"

enum ScienceType
{
	SCIENCE_INVALID = -1
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum
{
	INI_LOAD_CREATE_OVERRIDES = 2,
	INI_LOAD_RELOAD = 5
};

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
	int getLoadType() const { return m_loadType; }
private:
	char m_unmodelled00[8];
	int m_loadType;
};

class INIException
{
public:
	INIException(int code, const char *format, ...);
	INIException(const INIException &other);
private:
	int m_code;
	const char *m_msg;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;


// Zero Hour's Overridable, with BFME 2's third word at +0x0C (-1 when new,
// 0 for a reloaded info, 1 once retired by 0x001FFA5A).
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

typedef Rva001FFE93 ScienceInfo;

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
};

class CreateAHeroData;
class Rva001FFA5A
{
public:
	void rva001FFA5A(CreateAHeroData *val);
};

class ModuleData;

class ScienceStore
{
public:
	static void friend_parseScienceDefinition(INI *ini);
private:
	char m_unmodelled00[0x0C];
	_STL::vector<const ModuleData *> m_sciences;
};

extern ScienceStore *TheScienceStore;
extern const FieldParse TheScienceInfoFieldParse[];

// ?friend_parseScienceDefinition@ScienceStore@@SAXPAVINI@@@Z, retail
// 0x001FFF3A..0x00200084 (330B).
void ScienceStore::friend_parseScienceDefinition(INI *ini)
{
	const char *c = ini->getNextToken();
	ScienceType st = (ScienceType)TheNameKeyGenerator->nameToKey(c);

	if (TheScienceStore)
	{
		ScienceInfo *info = 0;
		for (const ModuleData **it = TheScienceStore->m_sciences.begin(); it != TheScienceStore->m_sciences.end(); ++it)
		{
			if (((ScienceInfo *)*it)->m_science == st)
			{
				info = (ScienceInfo *)*it;
				break;
			}
		}

		if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
		{
			ScienceInfo *newInfo = new ScienceInfo;
			if (info == 0)
			{
				info = newInfo;
				info->markAsOverride();
				TheScienceStore->m_sciences.push_back(*(const ModuleData **)&info);
			}
			else
			{
				info = (ScienceInfo *)info->friend_getFinalOverride();
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
				info = new ScienceInfo;
				TheScienceStore->m_sciences.push_back(*(const ModuleData **)&info);
				info->setReloadState(0);
			}
			else
			{
				throw INIException(3, "duplicate science %s!\n", c);
			}
		}
		else
		{
			info = new ScienceInfo;
			TheScienceStore->m_sciences.push_back(*(const ModuleData **)&info);
		}

		ini->initFromINI(info, TheScienceInfoFieldParse);
		info->m_science = st;
	}
}
