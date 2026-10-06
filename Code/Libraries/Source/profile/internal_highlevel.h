// Zero Hour internal_highlevel.h: ProfileId, one high-level profile value.
// The 0x58-byte layout is the one AddProfile allocates (0x006C6500) and the
// frame recorder (0x006C61B0, 0x006C6220) walks.

#ifndef INTERNAL_HIGHLEVEL_H
#define INTERNAL_HIGHLEVEL_H

class ProfileId
{
	ProfileId(const ProfileId &);
	ProfileId &operator=(const ProfileId &);

public:
	ProfileId(const char *name, const char *descr, const char *unit, int precision, int exp10);

	static ProfileId *GetFirst(void) { return first; }
	ProfileId *GetNext(void) const { return m_next; }
	const char *GetName(void) const { return m_name; }
	const char *GetUnit(void) const { return m_unit ? m_unit : ""; }
	const char *GetDescr(void) const { return m_descr ? m_descr : ""; }
	void Increment(double add);
	void Maximum(double max);
	double GetCurrentValue(void)
	{
		double help = m_curVal;
		m_curVal = 0.;
		return help;
	}
	double GetTotalValue(void) const
	{
		return m_totalVal;
	}
	bool GetFrameValue(unsigned frame, double &value) const
	{
		if (frame < (unsigned)m_firstFrame || frame >= (unsigned)curFrame)
			return false;
		value = m_recFrameVal[frame - m_firstFrame];
		return true;
	}
	const char *AsString(double v) const;
	static void Shutdown(void);
	static int FrameStart(void);
	static void FrameEnd(int which, int mixIndex);
	static void ClearTotals(void)
	{
		for (ProfileId *cur = first; cur; cur = cur->m_next)
			cur->m_totalVal = 0.;
	}

private:
	~ProfileId() {}

	enum
	{
		MAX_FRAME_RECORDS = 4,
		STRING_BUFFER_SIZE = 1024
	};

	enum ValueMode
	{
		Unknown,
		ModeIncrement,
		ModeMaximum
	};

	static ProfileId *first;

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

	static int curFrame;
	static unsigned frameRecordMask;
	static char stringBuf[STRING_BUFFER_SIZE];
	static unsigned stringBufUnused;
};

#endif // INTERNAL_HIGHLEVEL_H
