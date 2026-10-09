// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE
// ExperienceLevelSystem.cpp -- ExperienceLevelStore accessors recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv). WB's debug build names each
// function and shows the shape: assert IsValid(levelHandle), then read a
// field of levelHandle.m_iter->friend_getFinalOverride(). Retail drops the
// asserts, inlines the first level of the override walk and calls the
// out-of-line Overridable::friend_getFinalOverride (0x001E35DF) for the rest.
//
// Layout (target evidence): a level handle is two dwords passed by value, the
// list and an STLport list iterator whose node keeps the ExperienceLevel at
// +8; the level is an Overridable (next override at +4). Field names follow
// the WB accessor names.
#include <malloc.h>
#include <string.h>
#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;

// STLport vector<AsciiString> view; push_back is the rowed out-of-line copy
// (0x0002DBE6).
namespace _STL
{
	template <class T> class allocator {};

	template <class T, class A = allocator<T> > class vector
	{
	public:
		void push_back(const T &value);
		Int size() const { return m_finish - m_start; }
        T *begin() { return m_start; }
        T *end() { return m_finish; }
        T *erase(T *, T *);

	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

class ExperienceScalarTable
{
public:
	unsigned char m_pad00[0xc];
	AsciiString m_name;			// +0x0C
};

// STLport vector<ExperienceScalarTable *> view.
class ExperienceScalarTableVector
{
public:
	Int size() const { return m_finish - m_start; }
	ExperienceScalarTable *operator[](UnsignedInt i) const { return m_start[i]; }

private:
	ExperienceScalarTable **m_start;
	ExperienceScalarTable **m_finish;
	ExperienceScalarTable **m_endOfStorage;
};

class Overridable
{
public:
	virtual ~Overridable();
	Overridable *friend_getFinalOverride();	// 0x001E35DF
	const Overridable *friend_getFinalOverride() const;	// 0x00288609

	// Zero Hour's inline walk; retail inlines this first level.
	Overridable *getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

protected:
	Overridable *m_nextOverride;		// +0x04
};

class ExperienceLevel : public Overridable
{
public:
	bool rva00288621(const ExperienceLevel &that) const;

	unsigned char m_pad08[0x14 - 8];
	Int m_level;				// +0x14
	Int m_requiredExperience;		// +0x18
	Int m_experienceAward;			// +0x1C
	unsigned char m_pad20[0xfc - 0x20];
	Int m_rank;				// +0xFC
};

struct ExperienceLevelNode
{
	ExperienceLevelNode *m_next;
	ExperienceLevelNode *m_prev;
	ExperienceLevel m_data;			// +0x08
};

class ExperienceLevelIterator
{
public:
	ExperienceLevelIterator() {}
	ExperienceLevelIterator(const ExperienceLevelIterator &that) : m_node(that.m_node) {}
	ExperienceLevel *operator->() const { return &m_node->m_data; }
	ExperienceLevelIterator &operator++() { m_node = m_node->m_next; return *this; }
	bool operator==(const ExperienceLevelIterator &that) const { return m_node == that.m_node; }

	ExperienceLevelNode *m_node;
};

// STLport list: the sentinel node pointer is the only member.
class ExperienceLevelList
{
public:
	ExperienceLevelIterator begin() const { ExperienceLevelIterator it; it.m_node = m_node->m_next; return it; }
	ExperienceLevelIterator end() const { ExperienceLevelIterator it; it.m_node = m_node; return it; }

private:
	ExperienceLevelNode *m_node;
};

struct ExperienceLevelHandle
{
	ExperienceLevelHandle() {}
	ExperienceLevelHandle(ExperienceLevelList *list) : m_list(list) {}
	ExperienceLevelHandle(ExperienceLevelList *list, const ExperienceLevelIterator &iter) : m_list(list), m_iter(iter) {}
	ExperienceLevelHandle(const ExperienceLevelHandle &that) : m_list(that.m_list), m_iter(that.m_iter) {}

	ExperienceLevelList *m_list;
	ExperienceLevelIterator m_iter;
};

// The object FindCurrentLevel and FindExperienceLevelList read: current level
// at +0x0C, level-list key at +0x30.
class ExperienceTracker
{
public:
	unsigned char m_pad00[0xc];
	Int m_currentLevel;			// +0x0C
	unsigned char m_pad10[0x30 - 0x10];
	Int m_levelListKey;			// +0x30
};

// The NameKeyType -> level-list hash_map at the store's +0x0C. Its STLport
// find instantiation is identical to every other NameKeyType hash_map find
// and folded into the one body 0x00148B27, pinned under the
// KeyToBucketMap view (ObjectLookupMapFindSlot.cpp): it fills an out-pair
// {node, map}; a hit's value sits at node +0x08.
enum NameKeyType { NAMEKEY_UNKNOWN = 0 };
class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const AsciiString &);
	class KeyToBucketMap
	{
	public:
		struct Slot
		{
			void *node;
			KeyToBucketMap *map;
		};

		Slot *find( Slot &out, const int *key );
	};
};

// Declaration-only experience-level view. The 0x108-byte construction and
// teardown belong to Rva002894A2 at 0x00289CEB / 0x002894A2; this caller
// touches only the fields proved by its native loads and stores.
// The upgrade vector retains the existing void-pointer provider spelling.
// The existing 0x00288E8D sort provider is rowed under this provisional
// STL spelling. This caller passes only its one-pointer list header; it
// neither constructs nor accesses an element through that opaque name.
struct crateCreationEntry;
namespace _STL {
template <class T, class A = allocator<T> > class list;
template <class T> struct less { less() {} };
template <class T, class A, class C> void _S_sort(list<T, A> &, C);
}
struct BfmePod264;
class Rva002894A2
{
public:
    virtual ~Rva002894A2();
    Rva002894A2();
    Rva002894A2(const Rva002894A2 &);
    Rva002894A2 *next04;
    bool override08;
    char pad09[3];
    int overrideIndex0C;
    AsciiString name10;
    int key14, required18, award1C, index20;
    _STL::vector<AsciiString> targets24, attributes30;
    char pad3C[16];
    _STL::vector<void *> upgrades4C;
    char pad58[0xb0];
};
class Rva0028951F { public: const Overridable *rva0028951F(int); };
class Rva0028881C { public: void rva002889BB(); };
extern NameKeyGenerator *TheNameKeyGenerator;
Int SplitUpgrades(void *, const AsciiString &);
Int SplitString(_STL::vector<AsciiString> &, const AsciiString &);

class INI;
class ExperienceLevelStore
{
public:
    bool CreateNewExpLevel(const AsciiString &, const AsciiString &, const AsciiString &, const AsciiString &, const AsciiString &);
    void rva0028A1AA(void *, const BfmePod264 *);
    void rva002891DB(const Rva002894A2 *);
    static void friend_parseExperienceLevelDefinition(INI *);
	Int GetLevelRank(ExperienceLevelHandle levelHandle) const;
	Int GetRequiredExperience(ExperienceLevelHandle levelHandle) const;
	Int GetExperienceAwardForLevel(ExperienceLevelHandle levelHandle) const;
	ExperienceLevelHandle GetNextLevel(ExperienceLevelHandle levelHandle) const;
	bool IsValid(ExperienceLevelHandle levelHandle) const;	// 0x0028891F
	ExperienceScalarTable *FindExperienceScalarTableByName(const AsciiString &name) const;
	ExperienceLevelList *FindExperienceLevelList(const ExperienceTracker *tracker) const;	// 0x00288C34
	ExperienceLevelHandle FindCurrentLevel(const ExperienceTracker *tracker) const;
	Int rva00288CA6(const ExperienceTracker *tracker, Int rank, Int *pastEnd) const;

private:
	unsigned char m_pad00[0xc];
	NameKeyGenerator::KeyToBucketMap *m_levelLists;	// +0x0C
	NameKeyGenerator::KeyToBucketMap *m_reloadLevelLists;
	ExperienceScalarTableVector m_scalarTables;	// +0x14
	ExperienceScalarTable *m_defaultScalarTable;	// +0x20
};

// The address-derived singleton view at 0x288CFA is called by the matched
// ExperienceTracker forwarder at 0x39ABFF. Its direct call to
// FindExperienceLevelList at 0x288C34 supports the shared store layout.
class Rva00288CFA
{
public:
	bool rva00288CFA(Int value);
};

extern const void *__stdcall Rva00288940Find(const void *arg);
// The retail callsite supplies an otherwise-dead ECX=this as well as the list
// argument. This member-function view preserves that register while resolving
// to the already-rowed stdcall symbol; the callee consumes only its stack arg.
union Rva00288940Call
{
	const void *(__stdcall *freeCall)(const void *);
	const void *(Rva00288CFA::*memberCall)(const void *);
};

static inline ExperienceLevel *finalLevel(const ExperienceLevelHandle &levelHandle)
{
	return (ExperienceLevel *)levelHandle.m_iter->getFinalOverride();
}

// ExperienceLevelStore::GetLevelRank, retail 0x0028879C.
Int ExperienceLevelStore::GetLevelRank(ExperienceLevelHandle levelHandle) const
{
	return finalLevel(levelHandle)->m_rank;
}

// ExperienceLevelStore::GetRequiredExperience, retail 0x002887B8.
Int ExperienceLevelStore::GetRequiredExperience(ExperienceLevelHandle levelHandle) const
{
	return finalLevel(levelHandle)->m_requiredExperience;
}

// ExperienceLevelStore::GetExperienceAwardForLevel, retail 0x002887D1.
Int ExperienceLevelStore::GetExperienceAwardForLevel(ExperienceLevelHandle levelHandle) const
{
	return finalLevel(levelHandle)->m_experienceAward;
}

// ExperienceLevelStore::GetNextLevel, retail 0x00288ABC: the next valid level
// after the handle's, or the list end.
ExperienceLevelHandle ExperienceLevelStore::GetNextLevel(ExperienceLevelHandle levelHandle) const
{
	do
	{
		++levelHandle.m_iter;
		if (levelHandle.m_iter == levelHandle.m_list->end())
			break;
	} while (!IsValid(levelHandle));
	return levelHandle;
}

// Retail 0x00288621 (WorldBuilder pairs it unnamed, ExperienceLevelSystem.cpp
// line 174): orders two levels by the required experience of their final
// overrides.
bool ExperienceLevel::rva00288621(const ExperienceLevel &that) const
{
	const ExperienceLevel *a = (const ExperienceLevel *)friend_getFinalOverride();
	const ExperienceLevel *b = (const ExperienceLevel *)that.friend_getFinalOverride();
	if (a && b)
		return a->m_requiredExperience < b->m_requiredExperience;
	return false;
}

// ExperienceLevelStore::FindExperienceScalarTableByName, retail 0x00288AF2:
// the named table, else the default one.
ExperienceScalarTable *ExperienceLevelStore::FindExperienceScalarTableByName(const AsciiString &name) const
{
	for (UnsignedInt i = 0; i < (UnsignedInt)m_scalarTables.size(); ++i)
	{
		ExperienceScalarTable *table = m_scalarTables[i];
		if (table->m_name.compare(name) == 0)
			return table;
	}
	return m_defaultScalarTable;
}

// ExperienceLevelStore::FindCurrentLevel, retail 0x00288D2F: the handle of
// the level whose final override matches the tracker's current level; a null
// list on failure.
ExperienceLevelHandle ExperienceLevelStore::FindCurrentLevel(const ExperienceTracker *tracker) const
{
	if (tracker)
	{
		ExperienceLevelList *list = FindExperienceLevelList(tracker);
		if (list)
		{
			Int level = tracker->m_currentLevel;
			ExperienceLevelIterator end = list->end();
			for (ExperienceLevelIterator it = list->begin(); !(it == end); ++it)
			{
				if (((ExperienceLevel *)it->getFinalOverride())->m_level == level)
				{
					return ExperienceLevelHandle(list, it);
				}
			}
		}
	}
	return ExperienceLevelHandle(0);
}

// ?rva00288CFA@Rva00288CFA@@QAE_NH@Z
// Target evidence: calls the rowed list lookup at 0x288C34, searches that list
// through 0x288940, then compares the returned level's +0x18 integer against
// the input tracker's +0x10 float. No named target identity is established.
bool Rva00288CFA::rva00288CFA(Int value)
{
	ExperienceLevelStore *store = (ExperienceLevelStore *)this;
	const ExperienceTracker *tracker = (const ExperienceTracker *)value;
	ExperienceLevelList *list = store->FindExperienceLevelList(tracker);
	if (list == 0)
		return false;
	Rva00288940Call find;
	find.freeCall = Rva00288940Find;
	const ExperienceLevel *level = (const ExperienceLevel *)((this->*find.memberCall)(list));
	if (level == 0)
		return false;
	return level->m_requiredExperience > *(const float *)((const char *)tracker + 0x10);
}

// SplitString, retail 0x0028970B (WorldBuilder name): split on whitespace into
// the vector and return its size.
Int SplitString(_STL::vector<AsciiString> &out, const AsciiString &str)
{
	char *buffer = (char *)_alloca(str.getLength() + 1);
	strcpy(buffer, str.str());
	const char *separators = " \n\r\t";
	for (char *token = strtok(buffer, separators); token; token = strtok(0, separators))
		out.push_back(AsciiString(token));
	return out.size();
}

// ?rva00288CA6@ExperienceLevelStore@@QBEHPBVExperienceTracker@@HPAH@Z, retail
// 0x00288CA6: the required experience of the tracker's level whose final
// override has the given rank (+0xFC); past the end of the list it answers
// the last level's and sets *pastEnd; 0 without a list. Each level goes
// through the out-of-line const friend_getFinalOverride 0x00288609. Callers
// 0x00248B0D and 0x0039ADC8 (the ExperienceTracker clamp 0x0039ADB9). WorldBuilder's unnamed
// counterpart 0xBEA9E0 (call graph, calls FindExperienceLevelList) has the
// same walk.
Int ExperienceLevelStore::rva00288CA6(const ExperienceTracker *tracker, Int rank, Int *pastEnd) const
{
	ExperienceLevelList *list = FindExperienceLevelList(tracker);
	if (pastEnd)
		*pastEnd = 0;
	if (list == 0)
		return 0;
	const ExperienceLevel *level = 0;
	ExperienceLevelIterator end = list->end();
	for (ExperienceLevelIterator it = list->begin(); !(it == end); ++it)
	{
		level = (const ExperienceLevel *)((const Overridable *)&it.m_node->m_data)->friend_getFinalOverride();
		if (level->m_rank == rank)
			return level->m_requiredExperience;
	}
	if (level)
	{
		if (pastEnd)
			*pastEnd = 1;
		return level->m_requiredExperience;
	}
	return 0;
}

// ExperienceLevelStore::FindExperienceLevelList, retail 0x00288C34 (named by
// WorldBuilder's call-graph lead, ExperienceLevelSystem.cpp line 423): the
// level list keyed by the tracker's +0x30, or null.
ExperienceLevelList *ExperienceLevelStore::FindExperienceLevelList(const ExperienceTracker *tracker) const
{
	if (tracker)
	{
		NameKeyGenerator::KeyToBucketMap::Slot it;
		m_levelLists->find(it, &tracker->m_levelListKey);
		NameKeyGenerator::KeyToBucketMap::Slot found = it;
		if (found.node)
			return (ExperienceLevelList *)((char *)found.node + 8);
	}
	return 0;
}

// WB 0x00BE9C10 names CreateNewExpLevel and ExperienceLevelSystem.cpp.
// Retail 0x0028A473..0x0028A5D5 copies a named source when the new name
// is absent, installs its target/attribute/upgrade lists, then invalidates
// the cache at store+0x28. An existing destination only updates those lists.
// Full 354-byte body, established callees and one-state EH graph verified.
bool ExperienceLevelStore::CreateNewExpLevel(const AsciiString &sourceName, const AsciiString &newName, const AsciiString &target, const AsciiString &upgrades, const AsciiString &attributes)
{
    Rva002894A2 *existing = (Rva002894A2 *)((Rva0028951F *)this)->rva0028951F(TheNameKeyGenerator->nameToKey(newName));
    if (!existing) {
        const Rva002894A2 *source = (const Rva002894A2 *)((Rva0028951F *)this)->rva0028951F(TheNameKeyGenerator->nameToKey(sourceName));
        if (!source) return false;
        Rva002894A2 level(*source);
        level.name10 = newName;
        level.key14 = TheNameKeyGenerator->nameToKey(newName);
        level.targets24.erase(level.targets24.begin(), level.targets24.end());
        level.targets24.push_back(target);
        SplitString(level.attributes30, attributes);
        level.upgrades4C.erase(level.upgrades4C.begin(), level.upgrades4C.end());
        SplitUpgrades(&level.upgrades4C, upgrades);
        rva0028A1AA(m_levelLists, (const BfmePod264 *)&level);
        ((Rva0028881C *)((char *)this + 0x28))->rva002889BB();
    } else {
        _STL::vector<AsciiString> &targets = existing->targets24;
        targets.erase(targets.begin(), targets.end());
        targets.push_back(target);
        SplitString(existing->attributes30, attributes);
        _STL::vector<void *> &upgradeList = existing->upgrades4C;
        upgradeList.erase(upgradeList.begin(), upgradeList.end());
        SplitUpgrades(&upgradeList, upgrades);
    }
    return true;
}

// Unnamed WB 0x00BEB9E0 and the parser call establish this store helper.
// Native 0x002891DB..0x00289218 looks up the level key at +0x14, sorts
// the hit list at hash-node+8 through the existing whole-byte provider,
// and clears store+0x28. Full61 bytes and all three call targets exact.
void ExperienceLevelStore::rva002891DB(const Rva002894A2 *level)
{
    NameKeyGenerator::KeyToBucketMap::Slot found;
    m_levelLists->find(found, &level->key14);
    if (found.node) {
        _STL::_S_sort(*reinterpret_cast<_STL::list<crateCreationEntry> *>((char *)found.node + 8), _STL::less<crateCreationEntry>());
        ((Rva0028881C *)((char *)this + 0x28))->rva002889BB();
    }
}

//
// INI reload slots of the ExperienceLevels store (vftable 0x00BFB8F4, class
// Rva00289ABD; its constructor is 0x00289ABD):
//
//   slot 4, 0x00289812  clear the table at +0x10 (0x00289371) and the
//                       "needs restart" byte, then, when the shared slot 2
//                       (0x001B5384) reports a reload, put "RIF:
//                       ExperienceLevels reloaded..." on screen through
//                       TheInGameUI (slot 16, cdecl), latch the "reloaded"
//                       byte and +0x24, and pass a pending restart out
//                       through the argument; answer the latch.
//   slot 5, 0x00289874  once after a reload latched its byte: swap the
//                       tables at +0x0C and +0x10, clear the tree at +0x28
//                       (0x002889BB), clear the table now at +0x10, and
//                       answer true.
//
// Both bytes (VA 0x00DFECC8 "reloaded", 0x00DFECC9 "needs restart") are
// file-static: slot 4 loads +0x10 before it stores the restart byte and tests
// that byte before its two stores, which MSVC 7.1 schedules that way only for
// a static it can prove `this` does not alias. All their other readers and
// writers (0x00289874 and the parse body around 0x0028A429) sit beside these
// slots. Names are address-derived; the byte meanings are inferred from
// their uses.

#include "unicode_string.h"

class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void message(UnicodeString format, ...);
};
extern InGameUI *TheInGameUI;	// VA 0x00DFEDF0

// g_Va00DFECC8: VA 0x00DFECC8 (.bss); retail initial byte 00.
static bool g_Va00DFECC8;
// g_Va00DFECC9: VA 0x00DFECC9 (.bss); retail initial byte 00.
static bool g_Va00DFECC9;

class Rva00289371HashTable
{
public:
	void clear();	// 0x00289371
};


class Rva00289ABDBase
{
public:
	virtual void v00();
	virtual void v01();
	virtual bool rva001B5384Slot2();
};

class Rva00289ABD : public Rva00289ABDBase
{
public:
	bool rva00289812(bool *needsRestart);
	bool rva00289874();
private:
	char m_unmodelled04[0x0C - 0x04];
	Rva00289371HashTable *m_table0C;
	Rva00289371HashTable *m_table10;
	char m_unmodelled14[0x24 - 0x14];
	bool m_reloaded24;
	char m_unmodelled25[0x28 - 0x25];
	Rva0028881C m_tree28;
};

bool Rva00289ABD::rva00289812(bool *needsRestart)
{
	g_Va00DFECC9 = false;
	m_table10->clear();
	if (rva001B5384Slot2())
	{
		TheInGameUI->message(UnicodeString(L"RIF: ExperienceLevels reloaded. All units will need to be refreshed."));
		g_Va00DFECC8 = true;
		m_reloaded24 = true;
		if (g_Va00DFECC9)
			*needsRestart = true;
	}
	return g_Va00DFECC8;
}

bool Rva00289ABD::rva00289874()
{
	if (g_Va00DFECC8)
	{
		Rva00289371HashTable *old = m_table0C;
		m_table0C = m_table10;
		m_tree28.rva002889BB();
		m_table10 = old;
		old->clear();
		g_Va00DFECC8 = false;
		return true;
	}
	return false;
}

class INI {
public:
    const char *getNextToken(const char * = 0);
    void initFromINI(void *, const struct FieldParse *);
    char pad00[8];
    int loadType08;
    int getLoadType() const { return loadType08; }
};
class INIException {
public:
    INIException(int, const char *, ...);
    INIException(const INIException &);
    ~INIException();
    char *message;
    int argumentCount;
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
void *operator new(unsigned int);
void operator delete(void *);
struct Rva00289FBCRecord { Rva00289FBCRecord &operator=(const Rva00289FBCRecord &); };
// Native and WB both pass this ExperienceLevel FieldParse table. Its
// contents remain retail data; this code establishes only the table address,
// not a recovered data definition.
extern "C" const char g_00BFBAC0[];
static const FieldParse *const experienceLevelFieldParse = reinterpret_cast<const FieldParse *>(g_00BFBAC0);
// WB 0x00BEBDE0 names this callback. BFME1 874e3848 parser at 0x00382460
// supplies the source guide; BFME2 native evidence establishes the 0x108
// layout, +0x0C override index, name key and additional load-type-5 reload
// path. The rehomed reload methods above share the original file-static
// restart flag with this parser. All479 bytes and three EH actions exact.
void ExperienceLevelStore::friend_parseExperienceLevelDefinition(INI *ini)
{
    if (!TheExperienceLevelSystem) return;
    AsciiString name(ini->getNextToken(0));
    if (ini->getLoadType() == 2) {
        Rva002894A2 *existing = (Rva002894A2 *)((Rva0028951F *)TheExperienceLevelSystem)->rva0028951F(TheNameKeyGenerator->nameToKey(name));
        if (!existing) throw INIException(3, "Experience Level %s not found in map.ini", name.str());
        Rva002894A2 *created = new Rva002894A2;
        if (existing->next04)
            existing = (Rva002894A2 *)((Overridable *)existing->next04)->friend_getFinalOverride();
        reinterpret_cast<Rva00289FBCRecord *>(created)->operator=(reinterpret_cast<const Rva00289FBCRecord &>(*existing));
        existing->next04 = created;
        created->override08 = true;
        ini->initFromINI(created, experienceLevelFieldParse);
        ((ExperienceLevelStore *)TheExperienceLevelSystem)->rva002891DB(created);
    } else {
        Rva002894A2 level;
        level.name10 = name;
        level.key14 = TheNameKeyGenerator->nameToKey(name);
        ini->initFromINI(&level, experienceLevelFieldParse);
        if (ini->loadType08 != 5) {
            ((ExperienceLevelStore *)TheExperienceLevelSystem)->rva0028A1AA(((ExperienceLevelStore *)TheExperienceLevelSystem)->m_levelLists, (const BfmePod264 *)&level);
            ((Rva0028881C *)((char *)TheExperienceLevelSystem + 0x28))->rva002889BB();
        } else {
            Rva002894A2 *existing = (Rva002894A2 *)((Rva0028951F *)TheExperienceLevelSystem)->rva0028951F(TheNameKeyGenerator->nameToKey(name));
            if (existing) {
                existing->overrideIndex0C = 1;
                if (existing->override08) g_Va00DFECC9 = true;
            }
            level.overrideIndex0C = 0;
            ((ExperienceLevelStore *)TheExperienceLevelSystem)->rva0028A1AA(((ExperienceLevelStore *)TheExperienceLevelSystem)->m_reloadLevelLists, (const BfmePod264 *)&level);
        }
    }
}
