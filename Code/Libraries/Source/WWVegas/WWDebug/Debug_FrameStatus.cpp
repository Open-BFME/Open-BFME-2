// cl: /DNDEBUG /MD /EHs-c- /Oy-
//
// Debug::frameStatus, retail 0x0003A6A0 (175 bytes).
// Ported from Open-BFME-1 WWDebug/Debug_frameStatus.cpp: fast-path check at
// +0x9DF8, critical section 0x00DE0884, prefix slot 5 records the address,
// hash lookup, reset clears status, 2/3 means already decided, lazy
// UpdateFrameStatus when Unknown, true only for status 1.
// Dedicated TU with frame pointer (retail has ebp frame).

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *critsec);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *critsec);

struct DebugCriticalSection;
extern DebugCriticalSection g_bfmeCsDWC;

// LookupFrame is frameless at retail RVA 0x00038330.
#pragma optimize("y", on)

class Debug
{
private:
	struct FrameHashEntry
	{
		FrameHashEntry *next;
		unsigned int frameAddr;
		unsigned int frameType;
		const char *fileOrGroup;
		int line;
		int hits;
		int status;
	};

	enum { FRAME_HASH_SIZE = 10007 };

	int m_prefix[4];	// after the vptr
	int m_14;	// +0x14, the address last looked up
	FrameHashEntry *frameHash[FRAME_HASH_SIZE];
	unsigned char m_gap[0x9DF8 - 0x9C74];
	int m_fastPath;

	void UpdateFrameStatus(FrameHashEntry &entry);

	__forceinline FrameHashEntry *LookupFrame(unsigned int addr)
	{
		for (FrameHashEntry *entry = frameHash[addr % FRAME_HASH_SIZE]; entry;
			entry = entry->next)
		{
			if (entry->frameAddr == addr)
				return entry;
		}
		return 0;
	}

public:
	virtual bool frameStatus(unsigned int addr, bool reset);	// slot 23 of 0x00BBE810
};

// The matched caller retains its frame pointer.
#pragma optimize("y", off)

// ?frameStatus@Debug@@UAE_NI_N@Z
bool Debug::frameStatus(unsigned int addr, bool reset)
{
	if (m_fastPath != 0)
		return true;

	EnterCriticalSection((void *)&g_bfmeCsDWC);
	m_14 = (int)addr;
	FrameHashEntry *entry = LookupFrame(addr);
	if (reset)
	{
		if (entry != 0)
			entry->status = 0;
		LeaveCriticalSection((void *)&g_bfmeCsDWC);
		return false;
	}
	if (entry == 0)
	{
		LeaveCriticalSection((void *)&g_bfmeCsDWC);
		return false;
	}
	if (entry->status == 2 || entry->status == 3)
	{
		LeaveCriticalSection((void *)&g_bfmeCsDWC);
		return false;
	}
	if (entry->status == 0)
		UpdateFrameStatus(*entry);
	LeaveCriticalSection((void *)&g_bfmeCsDWC);
	return entry->status == 1;
}
