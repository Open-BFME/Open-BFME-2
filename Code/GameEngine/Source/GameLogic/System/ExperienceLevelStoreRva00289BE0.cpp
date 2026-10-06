// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHsc /MD /arch:SSE
// ?rva00289BE0@ExperienceLevelStore@@QAEHPBVExperienceTracker@@PAH@Z @0x00289BE0 68B. Calls FindExperienceLevelList 0x288C34 then Rva0028951F::rva002897A8 0x2897A8 with list and current level. Returns required experience minus float experience and stores rank.
typedef int Int;

class ExperienceLevelList
{
public:
	void *m_node;
};

class ExperienceTracker
{
public:
	unsigned char m_pad00[0xc];
	Int m_currentLevel;
	float m_experience;
	unsigned char m_pad14[0x30 - 0x14];
	Int m_levelListKey;
};

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	void *m_v0;
	Overridable *m_next;
	unsigned char m_pad08[0x10];
	Int m_val18;
	unsigned char m_pad1C[0xfc - 0x1c];
	Int m_rank;
};

class Rva0028951F
{
public:
	const Overridable *rva0028951F(Int key);
	const Overridable *rva002897A8(void *outer, Int key);
};

class ExperienceLevelStore : public Rva0028951F
{
public:
	ExperienceLevelList *FindExperienceLevelList(const ExperienceTracker *tracker) const;
	Int rva00289BE0(const ExperienceTracker *tracker, Int *outRank);
};

Int ExperienceLevelStore::rva00289BE0(const ExperienceTracker *tracker, Int *outRank)
{
	ExperienceLevelList *list = FindExperienceLevelList(tracker);
	if (list == 0)
		return 0;
	const Overridable *best = rva002897A8(list, tracker->m_currentLevel);
	if (best == 0)
		return 0;
	Int have = (Int)tracker->m_experience;
	if (outRank != 0)
		*outRank = best->m_rank;
	return best->m_val18 - have;
}
