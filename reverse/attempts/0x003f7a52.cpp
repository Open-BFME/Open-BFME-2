// ?GetFinalBonuses@LivingWorldAutoResolveBattleBonus@@QAEXPAM00@Z
// partial score=0.9787234043 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// LivingWorldAutoResolveBattleBonus.cpp -- the auto-resolve battle bonus
// table's INI parser at its WorldBuilder home (WB 0x01047450,
// LivingWorldAutoResolveBattleBonusTable::iniAppendBonusToTable).
//
// Target facts (retail 0x003F777F, 298 bytes, a cdecl field-parse proc): the
// entry's MinCount comes first; Weapon, Armor and Experience bonuses (1.0
// unless given) are read as percentages through the rowed 0x0002EE10 (scanReal
// scaled by 0.01, rowed under an opaque INI name); an unknown keyword throws
// INIException(5) and a MinCount already in the table throws INIException(3)
// after the rowed insert 0x003F775C reports no insertion. The table is the
// rowed set wrapper Rva003F775C over 16-byte entries ordered by MinCount
// (stlport_rb_tree_insert_003f75ec.cpp); the entry is built in place. The
// keyword compares import msvcr71 _strcmpi.

#include <string.h>
#include <set>

class INI
{
public:
	const char *getNextToken(const char *seps = 0);			// 0x0002DF97
	const char *getNextTokenOrNull(const char *seps = 0);	// 0x0002DEED
	int scanInt(const char *token);							// 0x0002ECCF
	float dup_002EE10(const char *token);					// 0x0002EE10, percent to real

	unsigned char m_pad000[0x420];
	const char *m_sepsColon;								// +0x420
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);	// 0x0002F681
	INIException(const INIException &that);
	char *mFailureMessage;
	int mErrorCode;
};

// One bonus entry: the rowed tree's 16-byte value, keyed by MinCount.
struct Rva003F75ECValue
{
	int minCount;
	float weaponBonus;
	float armorBonus;
	float experienceBonus;
};

class Rva003F775C
{
public:
	typedef _STL::_Rb_tree_iterator<Rva003F75ECValue, _STL::_Const_traits<Rva003F75ECValue> > iterator;
	_STL::pair<iterator, bool> insert(const Rva003F75ECValue &entry);	// 0x003F775C
};

class LivingWorldAutoResolveBattleBonusTable
{
public:
	static void iniAppendBonusToTable(INI *ini, void *instance, void *store, const void *userData);
};

// LivingWorldAutoResolveBattleBonusTable::iniAppendBonusToTable, retail
// 0x003F777F.
void LivingWorldAutoResolveBattleBonusTable::iniAppendBonusToTable(INI *ini, void *instance, void *store, const void *userData)
{
	Rva003F75ECValue entry;
	entry.minCount = ini->scanInt(ini->getNextToken());
	entry.weaponBonus = 1.0f;
	entry.armorBonus = 1.0f;
	entry.experienceBonus = 1.0f;

	for (const char *token = ini->getNextTokenOrNull(ini->m_sepsColon); token; token = ini->getNextTokenOrNull(ini->m_sepsColon))
	{
		if (_strcmpi("Weapon", token) == 0)
			entry.weaponBonus = ini->dup_002EE10(ini->getNextToken(ini->m_sepsColon));
		else if (_strcmpi("Armor", token) == 0)
			entry.armorBonus = ini->dup_002EE10(ini->getNextToken(ini->m_sepsColon));
		else if (_strcmpi("Experience", token) == 0)
			entry.experienceBonus = ini->dup_002EE10(ini->getNextToken(ini->m_sepsColon));
		else
			throw INIException(5, "Unknown Living World Autio Resolve Battle Bonus type %s", token);
	}

	bool inserted;
	{
		_STL::pair<Rva003F775C::iterator, bool> result = ((Rva003F775C *)store)->insert(entry);
		inserted = result.second;
	}
	if (!inserted)
		throw INIException(3, "Duplicate MinCount entries of %d in Living World auto resolve battle bonus table", entry.minCount);
}

#include <hash_map>
class GameWindow;
class WindowVideo;
// Declaration view of the existing native provider's empty hash functor.
// No WindowVideoManager object is sized or accessed in this unit.
class WindowVideoManager {
public: struct hashConstGameWindowPtr {
 unsigned int operator()(const GameWindow *) const;
};
};
typedef _STL::pair<const GameWindow *const,WindowVideo *> NativeBeginPair;
typedef _STL::hashtable<NativeBeginPair,const GameWindow *,
 WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<NativeBeginPair>,
 _STL::equal_to<const GameWindow *>,_STL::allocator<NativeBeginPair> > NativeBeginTable;
namespace _STL { template<> NativeBeginTable::iterator NativeBeginTable::begin(); }


class Rva000411084
{
public:
    void *next();
};
struct Rva003F751ANode
{
    int opaque00;
    void *opaque04, *opaque08, *opaque0C;
    int minCount;
    float weapon, armor, experience;
};
class Rva003F751A
{
public:
    Rva003F751ANode *rva003F751A(const int *key);
    Rva003F751ANode *header;
};
struct BonusHashNodeView
{
    void *next;
    void *name;
    Rva003F751A *table;
    int minCount;
};
class LivingWorldAutoResolveBattleBonus
{
public:
    void GetFinalBonuses(float *weapon, float *armor, float *experience);
private:
    unsigned char opaque00[0x20];
    float m_weapon, m_armor, m_experience;
};
void LivingWorldAutoResolveBattleBonus::GetFinalBonuses(float *weapon, float *armor, float *experience)
{
    float one = 1.0f;
    *weapon = one;
    *armor = one;
    *experience = one;
    NativeBeginTable *table = reinterpret_cast<NativeBeginTable *>((char *)this + 8);
    for (NativeBeginTable::iterator iter = table->begin(); iter != table->end();
        ((Rva000411084 *)&iter)->next())
    {
        BonusHashNodeView *node = (BonusHashNodeView *)iter._M_cur;
        Rva003F75ECValue key;
        key.minCount = node->minCount;
        Rva003F751A *bonuses = node->table;
        Rva003F751ANode *found = bonuses->rva003F751A(&key.minCount);
        if (found != bonuses->header)
        {
            *weapon *= found->weapon;
            *armor *= found->armor;
            *experience *= found->experience;
        }
    }
    *weapon *= m_weapon;
    *armor *= m_armor;
    *experience *= m_experience;
}
