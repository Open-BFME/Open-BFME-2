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
class NameKeyGenerator
{
public:
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

class ExperienceLevelStore
{
public:
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
	unsigned char m_pad10[0x14 - 0x10];
	ExperienceScalarTableVector m_scalarTables;	// +0x14
	ExperienceScalarTable *m_defaultScalarTable;	// +0x20
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
