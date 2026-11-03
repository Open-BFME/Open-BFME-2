// cl: /MD /EHsc
// platformsdk
//
// Zero Hour profile.cpp as built into BFME2 (retail 0x006C5300-0x006C5C5F).
// BFME2 changes read from the retail bytes (layouts in profile.h):
// - StartRange honours a pattern's frame budget and starts the high-level
//   recorder before the function-level one; StopRange closes a frame only
//   when the high-level index is valid. DFAIL_IF compiles to a plain return.
// - ProfileShutdown (the atexit hook) shuts down only the high-level
//   recorder and drops Zero Hour's CPU-speed log line.
// - GetClockCyclesFast registers a third result writer, file_gtt_dot.
// - StartRange matches patterns with Debug::SimpleMatch (0x00039480).
//   Zero Hour's identical Profile::SimpleMatch cannot be in this unit:
//   defining it here changes StartRange's register allocation.
// Not recovered yet: the dynamic initializer that creates `cmd` and
// registers the "profile" command group (Zero Hour builds it from a static
// reference; BFME2 keeps the pointer at 0x00E0C1F8).

#include <windows.h>
#include <string.h>
#include <mmsystem.h>
#include "internal.h"

ProfileCmdInterface *cmd;   // .bss 0x00E0C1F8

// ?ProfileFreeMemory@@YAXPAX@Z
void ProfileFreeMemory(void *ptr)
{
	if (ptr)
		GlobalFree(ptr);
}

// ?RemovePatternEntry@Profile@@CAXPAUPatternListEntry@1@@Z (BFME2-new)
void Profile::RemovePatternEntry(PatternListEntry *entry)
{
	PatternListEntry **link = &firstPatternEntry;
	if (*link)
	{
		do
		{
			if (*link == entry)
				break;
			link = (PatternListEntry **)*link;
		} while (*link);
	}
	PatternListEntry *victim = *link;
	*link = victim->next;
	if (victim->pattern)
		GlobalFree(victim->pattern);
	GlobalFree(victim);
	if (firstPatternEntry)
	{
		PatternListEntry *last = firstPatternEntry;
		while (last->next)
			last = last->next;
		lastPatternEntry = last;
	}
	else
		lastPatternEntry = 0;
}

// ?IsEnabled@Profile@@SA_NXZ (Zero Hour body, retail 0x006C5380)
bool Profile::IsEnabled(void)
{
	for (unsigned k = 0; k < m_names; ++k)
		if (m_frameNames[k].isRecording)
			return true;
	return false;
}

// ?GetFrameCount@Profile@@SAIXZ
unsigned Profile::GetFrameCount(void)
{
	return m_rec;
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

// ?AddResultFunction@Profile@@SAXP6APAVProfileResultInterface@@HPBQBD@ZPBD2@Z (0x006C53F0,
// between GetClockCyclesPerSecond and ProfileShutdown): Zero Hour's public forwarder, a
// tail jump to ProfileCmdInterface::AddResultFunction (0x006C67F0).
void Profile::AddResultFunction(ProfileResultInterface *(*func)(int, const char *const *),
	const char *name, const char *arg)
{
	ProfileCmdInterface::AddResultFunction(func, name, arg);
}

// ?ProfileShutdown@@YAXXZ
void ProfileShutdown(void)
{
	ProfileId::Shutdown();
	cmd->RunResultFunctions();
}

// ?ClearTotals@Profile@@SAXXZ (0x006C5410, right after ProfileShutdown):
// Zero Hour's Profile::ClearTotals without the _PROFILE function-level
// tracer, so only the inline ProfileId::ClearTotals walk remains.
void Profile::ClearTotals(void)
{
	ProfileId::ClearTotals();
}

// ?ProfileAllocMemory@@YAPAXI@Z
void *ProfileAllocMemory(unsigned numBytes)
{
	void *h = GlobalAlloc(GMEM_FIXED, numBytes);
	if (!h)
	{
		Debug::SkipNext(true);
		theDebug->SkipNext();
		(theDebug->CrashBegin(0, 0, 0) << "Debug mem alloc failed").CrashDone(true);
	}
	return h;
}

// ?ProfileReAllocMemory@@YAPAXPAXI@Z
void *ProfileReAllocMemory(void *oldPtr, unsigned newSize)
{
	// Windows doesn't like ReAlloc with NULL handle/ptr...
	if (!oldPtr)
		return newSize ? ProfileAllocMemory(newSize) : 0;

	// Shrinking to 0 size is basically freeing memory
	if (!newSize)
	{
		GlobalFree(oldPtr);
		return 0;
	}

	// now try GlobalReAlloc first
	void *h = GlobalReAlloc(oldPtr, newSize, 0);
	if (!h)
	{
		// this failed (Windows doesn't like ReAlloc'ing larger
		// fixed memory blocks) - go with Alloc/Free instead
		h = GlobalAlloc(GMEM_FIXED, newSize);
		if (!h)
		{
			Debug::SkipNext(true);
			theDebug->SkipNext();
			(theDebug->CrashBegin(0, 0, 0) << "Debug mem realloc failed").CrashDone(true);
		}
		unsigned oldSize = GlobalSize(oldPtr);
		memcpy(h, oldPtr, oldSize < newSize ? oldSize : newSize);
		GlobalFree(oldPtr);
	}

	return h;
}

// ?GetClockCyclesFast@@YA_JXZ
__int64 GetClockCyclesFast(void)
{
	// this is where we're adding our internal result functions
	ProfileCmdInterface::AddResultFunction(ProfileResultFileCSV::Create,
		"file_csv",
		"");
	ProfileCmdInterface::AddResultFunction(ProfileResultFileDOT::Create,
		"file_dot",
		"[ file [ frame_name [ fold_threshold ] ] ]");
	ProfileCmdInterface::AddResultFunction(ProfileResultFileGTT::Create,
		"file_gtt_dot",
		"[ file [ frame_name [ percent_threshold, 10000=100%, def=1% ] ] ]");

	// this must not take a very huge CPU hit...

	// measure clock cycles 3 times for 20 msec each
	// then take the 2 counts that are closest, average
	__int64 cycles[3];
	for (int k = 0; k < 3; k++)
	{
		// wait for end of current tick
		unsigned timeEnd = timeGetTime() + 2;
		while (timeGetTime() < timeEnd);

		// get cycles
		__int64 start, startQPC, endQPC;
		QueryPerformanceCounter((LARGE_INTEGER *)&startQPC);
		ProfileGetTime(start);
		timeEnd += 20;
		while (timeGetTime() < timeEnd);
		ProfileGetTime(cycles[k]);
		cycles[k] -= start;

		// convert to 1 second
		if (QueryPerformanceCounter((LARGE_INTEGER *)&endQPC))
		{
			__int64 freq;
			QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
			cycles[k] = (cycles[k] * freq) / (endQPC - startQPC);
		}
		else
		{
			cycles[k] = (cycles[k] * 1000) / 20;
		}
	}

	// find two closest values
	__int64 d01 = cycles[1] - cycles[0], d02 = cycles[2] - cycles[0], d12 = cycles[2] - cycles[1];
	if (d01 < 0) d01 = -d01;
	if (d02 < 0) d02 = -d02;
	if (d12 < 0) d12 = -d12;
	__int64 avg;
	if (d01 < d02)
	{
		avg = d01 < d12 ? cycles[0] + cycles[1] : cycles[1] + cycles[2];
	}
	else
	{
		avg = d02 < d12 ? cycles[0] + cycles[2] : cycles[1] + cycles[2];
	}

	// return result
	// (rounded to the next MHz)
	return ((avg / 2 + 500000) / 1000000) * 1000000;
}

// .bss 0x00E0C1E0..0x00E0C207
Profile::PatternListEntry *Profile::lastPatternEntry;
Profile::PatternListEntry *Profile::firstPatternEntry;
Profile::FrameName *Profile::m_frameNames;
unsigned Profile::m_names;
char **Profile::m_recNames;
unsigned Profile::m_rec;
// Zero Hour initializes this from GetClockCyclesFast(); with that dynamic
// initializer in the unit StopRange's register allocation no longer
// matches retail; BFME2's initializer is rva007B66E0 in
// GameEngine/Source/Common/System/GlobalChainCleanup.cpp (a friend of Profile).
__int64 Profile::m_clockCycles;

// ?StopRange@Profile@@SAXPBD@Z
void Profile::StopRange(const char *range)
{
	// set default
	if (!range)
		range = "frame";

	// known name?
	unsigned k;
	for (k = 0; k < m_names; ++k)
		if (!strcmp(range, m_frameNames[k].name))
			break;
	if (k == m_names)
		return;
	if (!m_frameNames[k].isRecording)
		return;

	// stop recording
	m_frameNames[k].isRecording = false;
	if (m_frameNames[k].highIndex >= 0)
	{
		// add to list of known frames?
		int atIndex;
		if (!m_frameNames[k].doAppend ||
			m_frameNames[k].lastGlobalIndex < 0)
		{
			atIndex = -1;
			m_frameNames[k].lastGlobalIndex = m_rec;
			m_recNames = (char **)ProfileReAllocMemory(m_recNames, (m_rec + 1) * sizeof(char *));
			m_recNames[m_rec] = (char *)ProfileAllocMemory(strlen(range) + 1 + 6);
			wsprintf(m_recNames[m_rec++], "%s:%i", range, ++m_frameNames[k].frames);
		}
		else
			atIndex = m_frameNames[k].lastGlobalIndex;
		if (m_frameNames[k].highIndex >= 0)
			ProfileId::FrameEnd(m_frameNames[k].highIndex, atIndex);
		if (m_frameNames[k].funcIndex >= 0)
			ProfileFuncLevelTracer::FrameEnd(m_frameNames[k].funcIndex, atIndex);
	}
}

// ?StartRange@Profile@@SAXPBD@Z
void Profile::StartRange(const char *range)
{
	// set default
	if (!range)
		range = "frame";

	// known name?
	unsigned k;
	for (k = 0; k < m_names; ++k)
		if (!strcmp(range, m_frameNames[k].name))
			break;
	if (k == m_names)
	{
		// no, must add to list
		m_frameNames = (FrameName *)ProfileReAllocMemory(m_frameNames, (++m_names) * sizeof(FrameName));
		m_frameNames[k].name = (char *)ProfileAllocMemory(strlen(range) + 1);
		strcpy(m_frameNames[k].name, range);
		m_frameNames[k].frames = 0;
		m_frameNames[k].isRecording = false;
		m_frameNames[k].doAppend = false;
		m_frameNames[k].lastGlobalIndex = -1;
	}

	// stop old recording?
	if (m_frameNames[k].isRecording)
		StopRange(range);

	// start new recording
	m_frameNames[k].isRecording = true;
	m_frameNames[k].doAppend = false;

	// but check first: is recording enabled?
	bool active = false;
	PatternListEntry *match = 0;
	for (PatternListEntry *cur = firstPatternEntry; cur; cur = cur->next)
	{
		if (Debug::SimpleMatch(range, cur->pattern))
		{
			active = cur->isActive;
			match = cur;
		}
	}

	if (active)
	{
		if (match->framesLeft > 0 && !--match->framesLeft)
			RemovePatternEntry(match);
		m_frameNames[k].highIndex = ProfileId::FrameStart();
		m_frameNames[k].funcIndex = ProfileFuncLevelTracer::FrameStart();
	}
	else
	{
		m_frameNames[k].extraIndex = -1;
		m_frameNames[k].highIndex = -1;
		m_frameNames[k].funcIndex = -1;
	}
}

// ?AppendRange@Profile@@SAXPBD@Z (retail 0x006C5B50): Zero Hour's body with
// StartRange's BFME2 changes (Debug::SimpleMatch, high-level index first,
// the extra index cleared when inactive); no frame budget here.
void Profile::AppendRange(const char *range)
{
	// set default
	if (!range)
		range = "frame";

	// known name?
	unsigned k;
	for (k = 0; k < m_names; ++k)
		if (!strcmp(range, m_frameNames[k].name))
			break;
	if (k == m_names)
	{
		// no, so StartRange will do the job for us
		StartRange(range);
		return;
	}

	// still recording?
	if (m_frameNames[k].isRecording)
		// don't do anything
		return;

	// start new recording
	m_frameNames[k].isRecording = true;
	m_frameNames[k].doAppend = true;

	// but check first: is recording enabled?
	bool active = false;
	for (PatternListEntry *cur = firstPatternEntry; cur; cur = cur->next)
	{
		if (Debug::SimpleMatch(range, cur->pattern))
			active = cur->isActive;
	}

	if (active)
	{
		m_frameNames[k].highIndex = ProfileId::FrameStart();
		m_frameNames[k].funcIndex = ProfileFuncLevelTracer::FrameStart();
	}
	else
	{
		m_frameNames[k].extraIndex = -1;
		m_frameNames[k].highIndex = -1;
		m_frameNames[k].funcIndex = -1;
	}
}
