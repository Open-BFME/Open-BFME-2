// cl: /MD /Oi
//
// Profile::StartRange, retail 0x006C5940 (515 bytes), from Zero Hour's
// profile.cpp built with _PROFILE. ProfileAllocMemory is defined in this
// unit as it is in profile.cpp (its retail body is 0x006C5460, landed from
// profile_alloc_memory.cpp); retail inlines it into this function only.
//
// BFME2 changes read from the retail bytes:
// - FrameName is 0x1C bytes: an extra index at +0x0C (only reset here), the
//   high-level index at +0x10, the function-level index at +0x14,
//   lastGlobalIndex at +0x18.
// - Pattern entries carry a frame budget (+0x0C): when the last matching
//   pattern enables recording and its budget runs out, the entry is removed
//   (0x006C5310).
// - The high-level recorder starts before the function-level one.

extern "C" unsigned int __cdecl strlen(const char *string);
extern "C" int __cdecl strcmp(const char *a, const char *b);
extern "C" char *__cdecl strcpy(char *dest, const char *src);
extern "C" __declspec(dllimport) void *__stdcall GlobalAlloc(unsigned int flags, unsigned int bytes);

void *ProfileReAllocMemory(void *oldPtr, unsigned int newSize);

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *text);   // slot 0x38
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual void CrashDone(bool fatal);            // slot 0x4C
	virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
	virtual void SkipNext();                       // slot 0x60
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, const char *group); // slot 0x6C

	static bool SkipNext(bool set);
};

extern Debug *theDebug;

// ?ProfileAllocMemory@@YAPAXI@Z (byte-exact reconstruction: profile_alloc_memory.cpp)
void *ProfileAllocMemory(unsigned int numBytes)
{
	void *h = GlobalAlloc(0, numBytes);
	if (!h)
	{
		Debug::SkipNext(true);
		theDebug->SkipNext();
		(theDebug->CrashBegin(0, 0, 0) << "Debug mem alloc failed").CrashDone(true);
	}
	return h;
}

class ProfileId
{
public:
	static int FrameStart(void);
};

class ProfileFuncLevelTracer
{
public:
	static int FrameStart(void);
};

class Profile
{
public:
	static void StartRange(const char *range = 0);
	static void StopRange(const char *range = 0);
	static bool SimpleMatch(const char *str, const char *pattern);

private:
	struct FrameName
	{
		char *name;
		unsigned frames;
		bool isRecording;
		bool doAppend;
		int extraIndex;           // +0x0C
		int highIndex;            // +0x10
		int funcIndex;            // +0x14
		int lastGlobalIndex;      // +0x18
	};

	struct PatternListEntry
	{
		PatternListEntry *next;
		bool isActive;
		char *pattern;
		int framesLeft;           // +0x0C, <= 0: unlimited
	};

	static void RemovePatternEntry(PatternListEntry *entry);

	static PatternListEntry *firstPatternEntry;
	static unsigned m_names;
	static FrameName *m_frameNames;
};

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
		if (SimpleMatch(range, cur->pattern))
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
