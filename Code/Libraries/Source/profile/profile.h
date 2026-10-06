// Zero Hour profile.h with BFME2's layouts (read from retail's
// Profile::StartRange 0x006C5940 and StopRange 0x006C57B0):
// - FrameName is 0x1C bytes: an extra index at +0x0C that only StartRange
//   resets, the high-level index at +0x10, the function-level index at
//   +0x14, lastGlobalIndex at +0x18 (Zero Hour: funcIndex, highIndex,
//   lastGlobalIndex at +0x0C..+0x14).
// - A pattern entry carries a frame budget at +0x0C; StartRange removes an
//   entry whose budget runs out (RemovePatternEntry, 0x006C5310).
// Statics sit in .bss at 0x00E0C1E0 (lastPatternEntry) .. 0x00E0C200
// (m_clockCycles), as defined in profile.cpp.

#ifndef PROFILE_H
#define PROFILE_H

#include "profile_highlevel.h"
#include "profile_funclevel.h"
#include "profile_result.h"

class Profile
{
	friend class ProfileCmdInterface;
	Profile();

public:
	static void StartRange(const char *range = 0);
	static void AppendRange(const char *range = 0);
	static void StopRange(const char *range = 0);
	static bool IsEnabled(void);
	static unsigned GetFrameCount(void);
	static const char *GetFrameName(unsigned frame);
	static void ClearTotals(void);
	static __int64 GetClockCyclesPerSecond(void);
	static void AddResultFunction(ProfileResultInterface *(*func)(int, const char *const *),
		const char *name, const char *arg);

private:
	// Zero Hour's private SimpleMatch is gone: BFME2's StartRange matches
	// with Debug::SimpleMatch (0x00039480), which has the same body.

	struct FrameName
	{
		char *name;
		unsigned frames;
		bool isRecording;
		bool doAppend;
		int extraIndex;           // +0x0C, BFME2
		int highIndex;            // +0x10
		int funcIndex;            // +0x14
		int lastGlobalIndex;      // +0x18
	};

	struct PatternListEntry
	{
		PatternListEntry *next;
		bool isActive;
		char *pattern;
		int framesLeft;           // +0x0C, BFME2; <= 0: unlimited
	};

	static void RemovePatternEntry(PatternListEntry *entry);

	static PatternListEntry *firstPatternEntry;
	static PatternListEntry *lastPatternEntry;
	static unsigned m_rec;
	static char **m_recNames;
	static unsigned m_names;
	static FrameName *m_frameNames;
	static __int64 m_clockCycles;
};

#endif // PROFILE_H
