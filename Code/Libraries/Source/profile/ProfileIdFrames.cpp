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

// our own fast critical section
static FastCriticalSectionClass cs;

class ProfileId
{
public:
	void Increment(double add);
	void Maximum(double max);
	static int FrameStart(void);
	static void FrameEnd(int which, int mixIndex);
	static void Shutdown(void);

private:
	enum ValueMode { Unknown, ModeIncrement, ModeMaximum };
	enum { MAX_FRAME_RECORDS = 4 };

	ProfileId *m_next;
	char *m_name;
	char *m_descr;
	char *m_unit;
	int m_precision;
	int m_exp10;
	double m_curVal;
	double m_totalVal;
	double m_frameVal[MAX_FRAME_RECORDS];
	double *m_recFrameVal;
	int m_firstFrame;
	ValueMode m_valueMode;

	static ProfileId *first;
	static int curFrame;
	static unsigned frameRecordMask;
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
