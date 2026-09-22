// cl: /MD /Oi
//
// Profile::StopRange, retail 0x006C57B0 (379 bytes), from Zero Hour's
// profile.cpp built with _PROFILE. BFME2's FrameName is 0x1C bytes: the
// high-level index sits at +0x10 and the function-level one at +0x14 (what
// StartRange stores from ProfileId::FrameStart and
// ProfileFuncLevelTracer::FrameStart), lastGlobalIndex at +0x18. A frame is
// only closed when the high-level index is valid, and ProfileId::FrameEnd
// runs before ProfileFuncLevelTracer::FrameEnd. DFAIL_IF compiles to a
// plain return in this build.

extern "C" unsigned int __cdecl strlen(const char *string);
extern "C" int __cdecl strcmp(const char *a, const char *b);
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *out, const char *fmt, ...);

void *ProfileAllocMemory(unsigned int size);
void *ProfileReAllocMemory(void *oldPtr, unsigned int newSize);

class ProfileId
{
public:
	static void FrameEnd(int which, int mixIndex);
};

class ProfileFuncLevelTracer
{
public:
	static void FrameEnd(int which, int mixIndex);
};

class Profile
{
public:
	static void StopRange(const char *range = 0);

private:
	struct FrameName
	{
		char *name;
		unsigned frames;
		bool isRecording;
		bool doAppend;
		int reserved;             // +0x0C
		int highIndex;            // +0x10
		int funcIndex;            // +0x14
		int lastGlobalIndex;      // +0x18
	};

	static unsigned m_rec;
	static char **m_recNames;
	static unsigned m_names;
	static FrameName *m_frameNames;
};

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
			wsprintfA(m_recNames[m_rec++], "%s:%i", range, ++m_frameNames[k].frames);
		}
		else
			atIndex = m_frameNames[k].lastGlobalIndex;
		if (m_frameNames[k].highIndex >= 0)
			ProfileId::FrameEnd(m_frameNames[k].highIndex, atIndex);
		if (m_frameNames[k].funcIndex >= 0)
			ProfileFuncLevelTracer::FrameEnd(m_frameNames[k].funcIndex, atIndex);
	}
}
