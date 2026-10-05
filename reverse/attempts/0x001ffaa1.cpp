// ?rva000E7C20SciencePrereqMemo@ScienceStore@@ABE_NPBVPlayer@@W4ScienceType@@PAX@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?rva000E7C20SciencePrereqMemo@ScienceStore@@ABE_NPBVPlayer@@W4ScienceType@@PAX@Z @0x001FFAA1 195B
// Memoized science-prerequisite check: a per-call map<ScienceType,Bool> (built
// by playerHasRootPrereqsForScience 0x001FFC55 and passed as void*) caches the
// verdict per ScienceType; otherwise true when the player already has the
// science, true when the science carries no prerequisite groups, or true when
// any one group has every member recursively satisfied.
// Evidence: pin name; retail calls rowed _M_find 0x00388F63 (ICF twin of the
// ScienceType instantiation), virtual hasScience slot 0, rowed findScienceInfo
// 0x001FF3AD, self-recursion, and rowed ScienceType-bool insert_unique
// 0x001FF875; ScienceInfo group range at +0x1c/+0x20; callers 0x001FFB1F (self),
// 0x001FFBFD and playerHasRootPrereqsForScience.

#include <map>

typedef bool Bool;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class Player
{
public:
	virtual Bool hasScience(ScienceType st) const;
};

struct SciencePrereqGroup
{
	ScienceType *m_begin;
	ScienceType *m_end;
	ScienceType *m_capacity;
};

class ScienceInfo
{
public:
	char m_head[0x1c];
	SciencePrereqGroup *m_prereqGroups;
	SciencePrereqGroup *m_prereqGroupsEnd;
};

class ScienceStore
{
private:
	const ScienceInfo *findScienceInfo(ScienceType st) const;

	Bool rva000E7C20SciencePrereqMemo(const Player *player, ScienceType st,
		void *memo) const;
};

// ?rva000E7C20SciencePrereqMemo@ScienceStore@@ABE_NPBVPlayer@@W4ScienceType@@PAX@Z present-unmatched
Bool ScienceStore::rva000E7C20SciencePrereqMemo(const Player *player, ScienceType st,
	void *memo) const
{
	std::map<ScienceType, Bool> *values = (std::map<ScienceType, Bool> *)memo;
	std::map<ScienceType, Bool>::iterator found = values->find(st);
	if (found != values->end())
		return found->second;

	Bool result;
	if (player->hasScience(st))
	{
		result = true;
	}
		else
		{
			result = false;
			const ScienceInfo *science = findScienceInfo(st);
			if (science)
			{
			int byteDiff = (char *)science->m_prereqGroupsEnd - (char *)science->m_prereqGroups;
			int numGroups = byteDiff / (int)sizeof(SciencePrereqGroup);
			result = (numGroups == 0);
				for (SciencePrereqGroup *group = science->m_prereqGroups;
					group != science->m_prereqGroupsEnd; ++group)
				{
					ScienceType *item = group->m_begin;
					if (item == group->m_end)
						goto group_satisfied;
					do
					{
						if (!rva000E7C20SciencePrereqMemo(player, *item, memo))
							goto next_group;
						++item;
					} while (item != group->m_end);
group_satisfied:
					result = true;
next_group:
					if (result)
						break;
				}
			}
		}

	values->insert(std::make_pair(st, result));
	return result;
}
