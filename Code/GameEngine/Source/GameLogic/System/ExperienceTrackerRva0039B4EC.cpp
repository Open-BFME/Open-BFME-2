// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva0039B4EC@ExperienceTracker@@QAE_NH_N0@Z, retail 0x0039B4EC, 92B.
// Target evidence: for up to `levels` passes, asks TheExperienceLevelSystem
// (0x00289BE0, with this and no out pointer) for the experience to the next level, stops
// at a non-positive answer, and grants it through the pinned 0x0039B315
// (float amount, false, false, flag1, flag2); returns whether any pass
// granted. Retail pushes flag2 as a dword, so 0x0039B315's fifth parameter
// is bool, matching that body's byte store to it. Names are placeholders.
class ExperienceTracker;
class ExperienceLevelStore
{
public:
	int rva00289BE0(const ExperienceTracker *tracker, int *out);	// 0x00289BE0
};
class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class ExperienceTracker
{
public:
	bool rva0039B4EC(int levels, bool flag1, bool flag2);
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
