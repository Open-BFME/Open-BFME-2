// ?rva0039B4EC@ExperienceTracker@@QAE_NH_N0@Z
// partial score=0.97 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0039B4EC@ExperienceTracker@@QAE_NH_N0@Z @0x0039B4EC 92B
// Evidence: pin ExperienceTracker member ret 0xC returns bool false for non-positive count; callees rva00289BE0 0x00289BE0 and rva0039B315 0x0039B315; global g_00DFECC4; callers 15 including LevelUpUpgrade and ExperienceLevelCreate.
#include "ascii_string.h"

class ExperienceTracker;

class ExperienceLevelStore
{
public:
	int rva00289BE0(const ExperienceTracker *tracker, int *outRank);
};

extern ExperienceLevelStore *g_00DFECC4;

class ExperienceTracker
{
public:
	void rva0039B315(float amount, bool b1, bool b2, bool b3, int v);
	bool rva0039B4EC(int count, bool b1, bool b2);
};

bool ExperienceTracker::rva0039B4EC(int count, bool b1, bool b2)
{
	if (count <= 0)
		return false;
	bool ret = false;
	for (int i = 0; i < count; ++i)
	{
		int level = g_00DFECC4->rva00289BE0(this, 0);
		if (level <= 0)
			break;
		rva0039B315((float)level, false, false, b1, b2);
		ret = true;
	}
	return ret;
}
