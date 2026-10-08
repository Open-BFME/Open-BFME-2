// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva00289BE0@ExperienceLevelStore@@QAEHPBVExperienceTracker@@PAH@Z,
// retail 0x00289BE0, 68B. Target evidence: finds the tracker's level list
// (rowed FindExperienceLevelList), takes the entry for the tracker's level
// (+0x0C, rowed 0x002897A8), and returns that entry's +0x18 requirement minus
// the tracker's +0x10 experience truncated to int (0 when either lookup
// fails), storing the entry's +0xFC through the optional out pointer. The
// level-up loop 0x0039B4EC calls it with a null out pointer. Names past the
// rowed callees are placeholders.
class Overridable;
class ExperienceLevelList;

class ExperienceTracker
{
public:
	unsigned char m_pad0[0xC];
	int m_level;		// +0x0C
	float m_experience;	// +0x10
};

struct Rva00289BE0Level
{
	unsigned char m_pad0[0x18];
	int m_requiredExperience;	// +0x18
	unsigned char m_pad1C[0xFC - 0x1C];
	int m_xFC;			// +0xFC
};

class Rva0028951F
{
public:
	const Overridable *rva002897A8(void *list, int level);	// 0x002897A8
};

class ExperienceLevelStore
{
public:
	ExperienceLevelList *FindExperienceLevelList(const ExperienceTracker *tracker) const;	// 0x00288C34
	int rva00289BE0(const ExperienceTracker *tracker, int *out);
};

int ExperienceLevelStore::rva00289BE0(const ExperienceTracker *tracker, int *out)
{
	ExperienceLevelList *list = FindExperienceLevelList(tracker);
	if (list == 0)
		return 0;
	const Rva00289BE0Level *level = (const Rva00289BE0Level *)((Rva0028951F *)this)->rva002897A8(list, tracker->m_level);
	if (level == 0)
		return 0;
	int current = (int)tracker->m_experience;
	if (out)
		*out = level->m_xFC;
	return level->m_requiredExperience - current;
}
