// ?RemovePatternEntry@Profile@@CAXPAUPatternListEntry@1@@Z
// partial score=0.99 date=2026-09-22
// cl: /MD /Oi
//
// Small profile.cpp functions (Zero Hour source, _PROFILE build):
//   0x006C5300 ProfileFreeMemory
//   0x006C5310 Profile::RemovePatternEntry (BFME2, see below)
//   0x006C53C0 Profile::GetFrameName
//   0x006C53E0 Profile::GetClockCyclesPerSecond
//   0x006C5400 ProfileShutdown (the atexit hook: BFME2 shuts down only the
//              high-level recorder and drops the CPU-speed log line)
// RemovePatternEntry is BFME2's: StartRange calls it when a pattern's frame
// budget runs out. It unlinks the entry, frees it (ProfileFreeMemory inlined)
// and recomputes lastPatternEntry the way the debug "clear" command does.

extern "C" __declspec(dllimport) void *__stdcall GlobalFree(void *mem);

class ProfileId
{
public:
	static void Shutdown(void);
};

class ProfileCmdInterface
{
public:
	void RunResultFunctions(void);
};

// ?ProfileFreeMemory@@YAXPAX@Z
void ProfileFreeMemory(void *ptr)
{
	if (ptr)
		GlobalFree(ptr);
}

class Profile
{
public:
	static const char *GetFrameName(unsigned frame);
	static __int64 GetClockCyclesPerSecond(void);

private:
	struct PatternListEntry
	{
		PatternListEntry *next;
		bool isActive;
		char *pattern;
		int framesLeft;
	};

	static void RemovePatternEntry(PatternListEntry *entry);

	static unsigned m_rec;
	static char **m_recNames;
	static __int64 m_clockCycles;
	static PatternListEntry *firstPatternEntry;
	static PatternListEntry *lastPatternEntry;
};

// ?RemovePatternEntry@Profile@@CAXPAUPatternListEntry@1@@Z
void Profile::RemovePatternEntry(PatternListEntry *entry)
{
	PatternListEntry **entryPtr = &firstPatternEntry;
	PatternListEntry *walk = firstPatternEntry;
	while (walk && walk != entry)
	{
		entryPtr = &walk->next;
		walk = *entryPtr;
	}

	PatternListEntry *cur = *entryPtr;
	*entryPtr = cur->next;
	ProfileFreeMemory(cur->pattern);
	ProfileFreeMemory(cur);

	// must fixup lastPatternEntry now
	if (firstPatternEntry)
	{
		for (cur = firstPatternEntry; cur->next; cur = cur->next)
			;
		lastPatternEntry = cur;
	}
	else
		lastPatternEntry = 0;
}

// ?GetFrameName@Profile@@SAPBDI@Z
const char *Profile::GetFrameName(unsigned frame)
{
	return frame >= m_rec ? 0 : m_recNames[frame];
}

// ?GetClockCyclesPerSecond@Profile@@SA_JXZ
__int64 Profile::GetClockCyclesPerSecond(void)
{
	return m_clockCycles;
}

extern ProfileCmdInterface *cmd;

// ?ProfileShutdown@@YAXXZ
void ProfileShutdown(void)
{
	ProfileId::Shutdown();
	cmd->RunResultFunctions();
}
