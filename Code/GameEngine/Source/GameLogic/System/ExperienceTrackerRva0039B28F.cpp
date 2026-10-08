// cl: /O1 /DNDEBUG /MD
//
// ?rva0039B28F@Rva003BD306Target@@QAEXH@Z, retail 0x0039B28F, 56B: an
// ExperienceTracker member (this goes to FindExperienceLevelList as the
// tracker), rowed under the host name and int spelling 3 of its 4 matched
// callers use; retail passes the argument as the int of 0x0039B24F.
// Target evidence: looks the tracker's level list up in
// TheExperienceLevelSystem, takes the entry for the level at +0x0C
// (0x002897A8) and, when both exist, applies it via 0x0039B24F(entry, v,
// false). Names past the rowed callees are placeholders.
class Overridable;
class ExperienceLevelList;
class Rva003BD306Target;
class ExperienceTracker;
struct Rva0039B24FInput;

class ExperienceLevelStore
{
public:
	ExperienceLevelList *FindExperienceLevelList(const ExperienceTracker *tracker) const;	// 0x00288C34
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class Rva0028951F
{
public:
	const Overridable *rva002897A8(void *list, int level);	// 0x002897A8
};

class Rva0039B24F
{
public:
	void rva0039B24F(Rva0039B24FInput *input, int v, bool flag);	// 0x0039B24F
};

class Rva003BD306Target
{
public:
	void rva0039B28F(int v);
private:
	unsigned char m_pad0[0xC];
	int m_level;				// +0x0C
};

void Rva003BD306Target::rva0039B28F(int v)
{
	ExperienceLevelList *list = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->FindExperienceLevelList((const ExperienceTracker *)this);
	if (list)
	{
		const Overridable *entry = ((Rva0028951F *)TheExperienceLevelSystem)->rva002897A8(list, m_level);
		if (entry)
			((Rva0039B24F *)this)->rva0039B24F((Rva0039B24FInput *)entry, v, false);
	}
}
