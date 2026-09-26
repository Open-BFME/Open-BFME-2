// cl: /MD /EHsc
//
// ProfileId frame recording from Zero Hour's profile_highlevel.cpp (retail
// 0x006C5DA0 Increment, 0x006C5E00 Maximum, 0x006C61B0 FrameStart,
// 0x006C6220 FrameEnd, 0x006C6360 Shutdown). The unit's critical section is
// WWLib's FastCriticalSectionClass (spin at 0x006C5EF0; the lock releases by
// clearing the flag), where Zero Hour had its own ProfileFastCS.

class FastCriticalSectionClass
{
public:
	unsigned Flag;

	class LockClass
	{
		FastCriticalSectionClass &cs;
		static void __fastcall spin(void *lock);

	public:
		LockClass(FastCriticalSectionClass &critical_section) : cs(critical_section)
		{
			spin(&cs.Flag);
		}
		~LockClass()
		{
			cs.Flag = 0;
		}
	};
};

void *ProfileReAllocMemory(void *oldPtr, unsigned int newSize);
void *ProfileAllocMemory(unsigned int size);

extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *out, const char *fmt, ...);
extern "C" __declspec(dllimport) int __cdecl _snprintf(char *buffer, unsigned int count, const char *fmt, ...);
extern "C" void *__cdecl memcpy(void *dest, const void *src, unsigned int count);
extern "C" int __cdecl strcmp(const char *a, const char *b);

#include <new>

// our own fast critical section
static FastCriticalSectionClass cs;

class ProfileId
{
	friend class ProfileHighLevel;

public:
	ProfileId(const char *name, const char *descr, const char *unit, int precision, int exp10);
	const char *AsString(double v) const;
	const char *GetName(void) const { return m_name; }
	ProfileId *GetNext(void) const { return m_next; }
	static ProfileId *GetFirst(void) { return first; }
	bool GetFrameValue(unsigned frame, double &value) const
	{
		if (frame < (unsigned)m_firstFrame || frame >= (unsigned)curFrame)
			return false;
		value = m_recFrameVal[frame - m_firstFrame];
		return true;
	}
	void Increment(double add);
	void Maximum(double max);
	static int FrameStart(void);
	static void FrameEnd(int which, int mixIndex);
	static void Shutdown(void);

private:
	enum ValueMode { Unknown, ModeIncrement, ModeMaximum };
	enum { MAX_FRAME_RECORDS = 4, STRING_BUFFER_SIZE = 1024 };

	ProfileId *m_next;
	char *m_name;
	char *m_descr;
	char *m_unit;
	int m_precision;
	int m_exp10;
	double m_curVal;
public:
	double m_totalVal;
private:
	double m_frameVal[MAX_FRAME_RECORDS];
	double *m_recFrameVal;
	int m_firstFrame;
	ValueMode m_valueMode;

	static ProfileId *first;
	static int curFrame;
	static unsigned frameRecordMask;
	static char stringBuf[STRING_BUFFER_SIZE];
	static unsigned stringBufUnused;
};

class ProfileHighLevel
{
public:
	class Id
	{
		friend class ProfileHighLevel;
		ProfileId *m_idPtr;

	public:
		Id(void) : m_idPtr(0) {}
		const char *GetValue(unsigned frame) const;
		const char *Rva006C64E0Get(void) const;
	};

	static Id AddProfile(const char *name, const char *descr, const char *unit, int precision, int exp10);
	static bool EnumProfile(unsigned index, Id &id);
	static bool FindProfile(const char *name, Id &id);
};

// ?Increment@ProfileId@@QAEXN@Z
void ProfileId::Increment(double add)
{
	if (m_valueMode != Unknown && m_valueMode != ModeIncrement)
		return;

	m_valueMode = ModeIncrement;
	m_curVal += add;
	m_totalVal += add;
	if (frameRecordMask)
	{
		unsigned mask = frameRecordMask;
		for (unsigned i = 0; i < MAX_FRAME_RECORDS; i++)
		{
			if (mask & 1)
				m_frameVal[i] += add;
			if (!(mask >>= 1))
				break;
		}
	}
}

// ?Maximum@ProfileId@@QAEXN@Z
void ProfileId::Maximum(double max)
{
	if (m_valueMode != Unknown && m_valueMode != ModeMaximum)
		return;

	m_valueMode = ModeMaximum;
	if (max > m_curVal)
		m_curVal = max;
	if (max > m_totalVal)
		m_totalVal = max;
	if (frameRecordMask)
	{
		unsigned mask = frameRecordMask;
		for (unsigned i = 0; i < MAX_FRAME_RECORDS; i++)
		{
			if (mask & 1)
			{
				if (max > m_frameVal[i])
					m_frameVal[i] = max;
			}
			if (!(mask >>= 1))
				break;
		}
	}
}

// ?FrameStart@ProfileId@@SAHXZ
int ProfileId::FrameStart(void)
{
	FastCriticalSectionClass::LockClass lock(cs);

	unsigned i;
	for (i = 0; i < MAX_FRAME_RECORDS; i++)
		if (!(frameRecordMask & (1 << i)))
			break;
	if (i == MAX_FRAME_RECORDS)
		return -1;

	for (ProfileId *p = first; p; p = p->m_next)
		p->m_frameVal[i] = 0.;

	frameRecordMask |= 1 << i;
	return i;
}

// ?FrameEnd@ProfileId@@SAXHH@Z
void ProfileId::FrameEnd(int which, int mixIndex)
{
	if (which < 0 || which >= MAX_FRAME_RECORDS)
		return;
	if (!(frameRecordMask & (1 << which)))
		return;
	if (mixIndex >= curFrame)
		return;

	FastCriticalSectionClass::LockClass lock(cs);

	frameRecordMask ^= 1 << which;
	if (mixIndex < 0)
	{
		// new frame
		curFrame++;
		for (ProfileId *p = first; p; p = p->m_next)
		{
			p->m_recFrameVal = (double *)ProfileReAllocMemory(p->m_recFrameVal,
				sizeof(double) * (curFrame - p->m_firstFrame));
			p->m_recFrameVal[curFrame - p->m_firstFrame - 1] = p->m_frameVal[which];
		}
	}
	else
	{
		// append data
		for (ProfileId *p = first; p; p = p->m_next)
		{
			if (p->m_firstFrame > mixIndex)
				continue;

			double &val = p->m_recFrameVal[mixIndex - p->m_firstFrame];
			switch (p->m_valueMode)
			{
			case ModeIncrement:
				val += p->m_frameVal[which];
				break;
			case ModeMaximum:
				if (p->m_frameVal[which] > val)
					val = p->m_frameVal[which];
				break;
			}
		}
	}
}

// ?Shutdown@ProfileId@@SAXXZ
void ProfileId::Shutdown(void)
{
	if (frameRecordMask)
	{
		for (unsigned i = 0; i < MAX_FRAME_RECORDS; i++)
			if (frameRecordMask & (1 << i))
				FrameEnd(i, -1);
	}
}

// ?AsString@ProfileId@@QBEPBDN@Z
const char *ProfileId::AsString(double v) const
{
	char help1[10], help[40];
	wsprintfA(help1, "%%%i.lf", m_precision);

	double mul = 1.0;
	int k;
	for (k = m_exp10; k < 0; k++) mul *= 10.0;
	for (; k > 0; k--) mul /= 10.0;

	unsigned len = _snprintf(help, sizeof(help), help1, v * mul) + 1;

	FastCriticalSectionClass::LockClass lock(cs);
	if (stringBufUnused + len > STRING_BUFFER_SIZE)
		stringBufUnused = 0;
	char *ret = stringBuf + stringBufUnused;
	memcpy(ret, help, len);
	stringBufUnused += len;
	return ret;
}

// ?GetValue@Id@ProfileHighLevel@@QBEPBDI@Z
const char *ProfileHighLevel::Id::GetValue(unsigned frame) const
{
	double v;
	if (!m_idPtr || !m_idPtr->GetFrameValue(frame, v))
		return 0;
	return m_idPtr->AsString(v);
}

// ?Rva006C64E0Get@Id@ProfileHighLevel@@QBEPBDXZ @0x006C64E0 (24B): total-value string via m_totalVal (+0x20).
const char *ProfileHighLevel::Id::Rva006C64E0Get(void) const
{
	if (m_idPtr)
		return m_idPtr->AsString(m_idPtr->m_totalVal);
	return 0;
}

// ?AddProfile@ProfileHighLevel@@SA?AVId@1@PBD00HH@Z
ProfileHighLevel::Id ProfileHighLevel::AddProfile(const char *name, const char *descr,
	const char *unit, int precision, int exp10)
{
	// check if there is already an ID with the given name...
	Id id;
	if (FindProfile(name, id))
		return id;

	// checks...
	if (!name)
		return id;

	// no, allocate one
	FastCriticalSectionClass::LockClass lock(cs);
	id.m_idPtr = new (ProfileAllocMemory(sizeof(ProfileId))) ProfileId(name, descr, unit, precision, exp10);
	return id;
}

// ?EnumProfile@ProfileHighLevel@@SA_NIAAVId@1@@Z
bool ProfileHighLevel::EnumProfile(unsigned index, Id &id)
{
	FastCriticalSectionClass::LockClass lock(cs);
	ProfileId *cur;
	for (cur = ProfileId::GetFirst(); cur && index--; cur = cur->GetNext())
		;
	id.m_idPtr = cur;
	return cur != 0;
}

// ?FindProfile@ProfileHighLevel@@SA_NPBDAAVId@1@@Z
bool ProfileHighLevel::FindProfile(const char *name, Id &id)
{
	if (!name)
		return false;

	FastCriticalSectionClass::LockClass lock(cs);
	for (ProfileId *cur = ProfileId::GetFirst(); cur; cur = cur->GetNext())
		if (!strcmp(name, cur->GetName()))
		{
			id.m_idPtr = cur;
			return true;
		}

	id.m_idPtr = 0;
	return false;
}
