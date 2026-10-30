// cl: /O1 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// platformsdk
// stlport
// ?addObjectLost@ScoreKeeper@@QAEXPBVObject@@@Z 0x0039CF73 392 scoring-gated lost count with killer player index
// ?addObjectsLost@ScoreKeeper@@QAEXIH@Z 0x0039D0FB 117 dual map add via rowed _M_find 0x00357180 and ImageSubscriptMap operator[] 0x002077D6
// 117B __thiscall with ints at +0x74 +0x1c4 and maps at +0x1d4 +0x2ec; callers 0x00480554 pass Player+0x3bc with Image key and count.
// Same find+subscript shape as Rva00222F0A (find) and Rva00358333 (subscript cast).
//
// addObjectLost is Zero Hour's ScoreKeeper::addObjectLost (ScoreKeeper.cpp)
// with BFME 2's changes read off retail and the WorldBuilder body
// (ScoreKeeper.cpp asserts 747-771): the under-construction test comes
// first and returns; a structure lost decrements the structure count at
// +0x10C (clamped at zero) and bumps +0xCC and +0x16C; anything else counts
// as a unit only when the GlobalData filter at +0x1168 accepts it, which
// decrements the unit count at +0x108 and bumps +0x74 and +0x1C4. Both
// template count maps then grow by one, and the last damage source's player
// index is stored at +0x104 unless it is our own (+0x100).
// The ThingTemplate-keyed count maps fold into the unsigned-key pointer-map
// workers (rowed _M_find 0x00357180, operator[] 0x002077D6), so the maps are
// viewed with that key and value as in addObjectsLost.
// The kind-of tests share one template load in retail (edi holds the
// kind-of mask across both calls), hence the hoisted template local.
#include <map>
// The verified callers inline unsigned comparison; keep the incidental
// /O1 less copy out of this unit so the retail provider owns its external name.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const
{ return a < b; }
}
#include "GameLogicObjectLookupView.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef bool Bool;
typedef int Int;
#include <windows.h>

class Image;

class ImageSubscriptMap
{
public:
	Image *&operator[](const unsigned int &key);
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 0x4C
};

template <int N>
class BitFlags
{
public:
	bool testSetAndClear(const BitFlags &mustBeSet, const BitFlags &mustBeClear) const;

private:
	unsigned m_words[7];
};
typedef BitFlags<116> KindOfMaskType;
extern KindOfMaskType KINDOFMASK_NONE;

class ThingTemplate
{
	char m_pad000[0x108];
	KindOfMaskType m_kindof;

public:
	Bool isKindOfMulti(const KindOfMaskType &mustBeSet, const KindOfMaskType &mustBeClear) const
	{
		return m_kindof.testSetAndClear(mustBeSet, mustBeClear);
	}
};

struct DamageInfo
{
	char m_pad00[8];
	ObjectID m_sourceID;
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual const DamageInfo *getLastDamageInfo() const; // +0x3C
};

class Player
{
	char m_pad00[0x54];
	Int m_playerIndex;

public:
	Int getPlayerIndex() const { return m_playerIndex; }
	bool rva002AA245() const; // 0x002AA245
};

class Object
{
	char m_pad000[4];
	const ThingTemplate *m_template;
	char m_pad008[0x254 - 8];
	// This owner accesses the proven Object+0x254 field directly; the public
	// getBodyModule copies use other Object views.
public:
	BodyModuleInterface *m_body;

public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Bool testStatus(ObjectStatusTypes bit) const;
	Player *getControllingPlayer() const;
};

class Rva2225E0Filter
{
public:
	bool accepts(Object *obj, Player *player);
};

class GlobalData
{
public:
	char m_pad0000[0x1168];
	Rva2225E0Filter m_scoreUnitFilter;
};
extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;

typedef _STL::map<unsigned int, void *> ObjectCountMap;
typedef ObjectCountMap::iterator ObjectCountMapIt;

struct ScoreKeeper
{
	char m_pad00[0x20];
	int m_unitsDestroyed[20]; // +0x20
	char m_pad70[0x74 - 0x70];
	int m_74;
	char m_pad01[0xcc - 0x74 - 4];
	int m_totalBuildingsLost; // +0xCC
	char m_pad02[0x100 - 0xcc - 4];
	int m_100;
	int m_104;
	int m_totalUnits; // +0x108
	int m_totalStructures; // +0x10C
	bool m_scoring; // +0x110
	char m_pad03[0x16c - 0x111];
	int m_16c;
	int m_count170[20]; // +0x170
	char m_pad04[0x1c4 - 0x1c0];
	int m_1c4;
	char m_pad05[0x1d4 - 0x1c4 - 4];
	_STL::map<unsigned int, void *> m_map1d4;
	char m_pad06[0x1fc - 0x1d4 - 12];
	ObjectCountMap m_objectsDestroyed[20]; // +0x1FC
	_STL::map<unsigned int, void *> m_map2ec;
	void addObjectLost(const Object *o);
	void addObjectsLost(unsigned int key, int delta);
	void addObjectsDestroyed(unsigned int key, Player *player, unsigned int count);
};

static KindOfMaskType scoringBuildingMask;
static KindOfMaskType scoringBuildingDestroyMask;

void ScoreKeeper::addObjectLost( const Object *object )
{
	if (TheGameLogic->isScoringEnabled() == FALSE)
		return;

	if (object->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
		return;

	Bool addToCount = FALSE;
	const ThingTemplate *thingTemplate = object->getTemplate();
	if (thingTemplate->isKindOfMulti(scoringBuildingMask, KINDOFMASK_NONE))
	{
		if (--m_totalStructures < 0)
			m_totalStructures = 0;
		++m_totalBuildingsLost;
		++m_16c;
		addToCount = TRUE;
	}
	else if (thingTemplate->isKindOfMulti(scoringBuildingDestroyMask, KINDOFMASK_NONE))
	{
		if (--m_totalStructures < 0)
			m_totalStructures = 0;
		++m_totalBuildingsLost;
		++m_16c;
		addToCount = TRUE;
	}
	else if (TheWritableGlobalData->m_scoreUnitFilter.accepts((Object *)object, NULL))
	{
		if (--m_totalUnits < 0)
			m_totalUnits = 0;
		++m_74;
		++m_1c4;
		addToCount = TRUE;
	}

	if (addToCount)
	{
		Int existingCount = 0;
		ObjectCountMapIt it = m_map2ec.find((unsigned int)object->getTemplate());
		if (it != m_map2ec.end())
			existingCount = (Int)it->second;
		((ImageSubscriptMap *)&m_map2ec)->operator[]((unsigned int)object->getTemplate()) = (Image *)(existingCount + 1);

		existingCount = 0;
		it = m_map1d4.find((unsigned int)object->getTemplate());
		if (it != m_map1d4.end())
			existingCount = (Int)it->second;
		((ImageSubscriptMap *)&m_map1d4)->operator[]((unsigned int)object->getTemplate()) = (Image *)(existingCount + 1);

		BodyModuleInterface *body = object->m_body;
		if (body)
		{
			const DamageInfo *info = body->getLastDamageInfo();
			if (info)
			{
				Object *killer = TheGameLogic->findObjectByID(info->m_sourceID);
				if (killer)
				{
					Player *player = killer->getControllingPlayer();
					if (player->rva002AA245())
					{
						Int playerIndex = player ? player->getPlayerIndex() : -1;
						if (playerIndex >= 0 && playerIndex != m_100)
							m_104 = playerIndex;
					}
				}
			}
		}
	}
}

void ScoreKeeper::addObjectsLost(unsigned int key, int delta)
{
	m_74 += delta;
	m_1c4 += delta;
	void *old1 = 0;
	_STL::map<unsigned int, void *>::iterator it1 = m_map2ec.find(key);
	if (it1 != m_map2ec.end())
		old1 = it1->second;
	((ImageSubscriptMap *)&m_map2ec)->operator[](key) = (Image *)((char *)old1 + delta);
	void *old2 = 0;
	_STL::map<unsigned int, void *>::iterator it2 = m_map1d4.find(key);
	if (it2 != m_map1d4.end())
		old2 = it2->second;
	((ImageSubscriptMap *)&m_map1d4)->operator[](key) = (Image *)((char *)old2 + delta);
}

void ScoreKeeper::addObjectsDestroyed(unsigned int key, Player *player, unsigned int count)
{
	if (m_scoring)
	{
		int idx = player->getPlayerIndex();
		m_unitsDestroyed[idx] += count;
		m_count170[idx] += count;
		ObjectCountMap &destroyed = m_objectsDestroyed[idx];
		void *oldValue = 0;
		ObjectCountMapIt it = destroyed.find(key);
		if (it != destroyed.end())
			oldValue = it->second;
		((ImageSubscriptMap *)&destroyed)->operator[](key) = (Image *)((char *)oldValue + count);
	}
}
