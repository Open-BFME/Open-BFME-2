// cl: /MD /Oi
// Zero Hour profile_highlevel.cpp at donor revision 9cbfb551 supplies the
// constructor's semantic source. Retail 0x006C5C60..0x006C5D9A establishes
// the sorted insertion absent from Zero Hour, with strcmp > 0 as its stop.
// Target layout: AddProfile allocates 0x58 bytes; existing recorder/accessor
// rows prove the shared ProfileId header offsets. The direct link-pointer
// loop gives the conditional EBP save that a separately cached cursor loses.
#include "internal_highlevel.h"
extern "C" unsigned int __cdecl strlen(const char *);
extern "C" int __cdecl strcmp(const char *, const char *);
extern "C" char *__cdecl strcpy(char *, const char *);
void *ProfileAllocMemory(unsigned int);

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

	ProfileId **link = &first;
	for (; *link; link = &(*link)->m_next)
	{
		if (strcmp(m_name, (*link)->m_name) > 0)
			break;
	}
	m_next = *link;
	*link = this;
}
