// ??0ProfileId@@QAE@PBD00HH@Z
// partial score=0.7 date=2026-09-23
// cl: /MD /Oi
//
// ProfileId::ProfileId, retail 0x006C5C60 (314 bytes), from Zero Hour's
// profile_highlevel.cpp. Zero Hour pushes each new id at the head of the
// list; BFME2 keeps the list ordered, inserting the new id in front of the
// first entry whose name compares lower (strcmp > 0).

extern "C" unsigned int __cdecl strlen(const char *string);
extern "C" int __cdecl strcmp(const char *a, const char *b);
extern "C" char *__cdecl strcpy(char *dest, const char *src);

void *ProfileAllocMemory(unsigned int size);

class ProfileId
{
public:
	ProfileId(const char *name, const char *descr, const char *unit, int precision, int exp10);

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
};

// ??0ProfileId@@QAE@PBD00HH@Z
ProfileId::ProfileId(const char *name, const char *descr, const char *unit, int precision, int exp10)
{
	m_name = (char *)ProfileAllocMemory(strlen(name) + 1);
	strcpy(m_name, name);
	if (descr)
	{
		m_descr = (char *)ProfileAllocMemory(strlen(descr) + 1);
		strcpy(m_descr, descr);
	}
	else
		m_descr = 0;
	if (unit)
	{
		m_unit = (char *)ProfileAllocMemory(strlen(unit) + 1);
		strcpy(m_unit, unit);
	}
	else
		m_unit = 0;
	m_precision = precision;
	m_exp10 = exp10;
	m_curVal = m_totalVal = 0.;
	m_recFrameVal = 0;
	m_firstFrame = curFrame;
	m_valueMode = Unknown;

	// keep the list ordered by name
	ProfileId **link = &first;
	for (ProfileId *cur = first; cur; cur = *link)
	{
		if (strcmp(m_name, cur->m_name) > 0)
			break;
		link = &cur->m_next;
	}
	m_next = *link;
	*link = this;
}
