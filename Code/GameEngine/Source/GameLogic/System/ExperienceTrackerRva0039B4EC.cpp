// cl: /O1 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
//
// ?rva0039B4EC@ExperienceTracker@@QAE_NH_N0@Z, retail 0x0039B4EC, 92B.
// Target evidence: for up to `levels` passes, asks TheExperienceLevelSystem
// (0x00289BE0, with this and no out pointer) for the experience to the next level, stops
// at a non-positive answer, and grants it through the pinned 0x0039B315
// (float amount, false, false, flag1, flag2); returns whether any pass
// granted. Retail pushes flag2 as a dword, so 0x0039B315's fifth parameter
// is bool, matching that body's byte store to it. Names are placeholders.
class ExperienceTracker;
class ExperienceLevelList;
class ExperienceLevelStore
{
public:
	int rva00289BE0(const ExperienceTracker *tracker, int *out);	// 0x00289BE0
	ExperienceLevelList *FindExperienceLevelList(const ExperienceTracker *tracker) const;
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class ExperienceTracker
{
public:
	bool rva0039B4EC(int levels, bool flag1, bool flag2);
	void rva0039B438(const AsciiString &name, bool feedback);
	void rva0039B315(float amount, bool a, bool b, bool c, bool d);	// 0x0039B315
};

bool ExperienceTracker::rva0039B4EC(int levels, bool flag1, bool flag2)
{
	if (levels <= 0)
		return false;
	bool any = false;
	for (int i = 0; i < levels; ++i)
	{
		int xp = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->rva00289BE0(this, 0);
		if (xp <= 0)
			break;
		rva0039B315((float)xp, false, false, flag1, flag2);
		any = true;
	}
	return any;
}

class Overridable
{
public:
	Overridable *friend_getFinalOverride();
	Overridable *getFinalOverride()
	{
		return next ? next->friend_getFinalOverride() : this;
	}
private:
	void *vptr;
	Overridable *next;
};
class ExperienceLevel : public Overridable
{
public:
	char unknown08[8];
	AsciiString name;
};
struct ExperienceLevelNode
{
	ExperienceLevelNode *next, *prev;
	ExperienceLevel data;
};
class ExperienceLevelList
{
public:
	ExperienceLevelNode *sentinel;
};
class Rva003BD306Target
{
public:
	void rva0039B28F(int value);
};
struct Rva0039B24FInput;
class Rva0039B24F
{
public:
	void rva0039B24F(Rva0039B24FInput *level, int value, bool feedback);
};

// Native0039B438..0039B4B8 RET8. The list lookup identifies this as an
// ExperienceTracker receiver; the repeated AsciiString compare calls prove
// the name argument and the level's +10 string. The override/node layout is
// also used by the verified store lookups. Keep the two comparisons: applying
// the current level may change the compared entry. Callee names are opaque.
void ExperienceTracker::rva0039B438(const AsciiString &name, bool feedback)
{
	ExperienceLevelList *list = reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem)->FindExperienceLevelList(this);
	if (!list) return;
	for (ExperienceLevelNode *node = list->sentinel->next;
		node != list->sentinel; node = node->next)
	{
		ExperienceLevel *level = static_cast<ExperienceLevel *>(node->data.getFinalOverride());
		if (level->name.compare(name) != 0)
			reinterpret_cast<Rva003BD306Target *>(this)->rva0039B28F(0);
		if (level->name.compare(name) == 0)
		{
			reinterpret_cast<Rva0039B24F *>(this)->rva0039B24F(reinterpret_cast<Rva0039B24FInput *>(level), 0, feedback);
			break;
		}
	}
}
