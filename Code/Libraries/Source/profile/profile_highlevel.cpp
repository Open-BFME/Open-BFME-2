// cl: /MD /EHsc
//
// Zero Hour profile_highlevel.cpp as built into BFME2 (retail
// 0x006C5C60-0x006C65EF). The lock is WWLib's FastCriticalSectionClass;
// its spin (0x006C5EF0) and an out-of-line lock constructor (0x006C5F40)
// are WWLib inline COMDATs that retail emitted from this unit (their rows
// are still sourced from WWLib/). ProfileId::GetFrameValue (0x006C5EC0) is
// the header inline that GetValue did not inline.

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <new>
#include "internal.h"

// our own fast critical section
static FastCriticalSectionClass cs;

ProfileId *ProfileId::first;   // .bss 0x00E0C620
int ProfileId::curFrame;
unsigned ProfileId::frameRecordMask;
char ProfileId::stringBuf[ProfileId::STRING_BUFFER_SIZE];
unsigned ProfileId::stringBufUnused;

// ProfileId constructor is recovered in ProfileIdConstructor.cpp (/Oi).

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

// ?AsString@ProfileId@@QBEPBDN@Z
const char *ProfileId::AsString(double v) const
{
	char help1[10], help[40];
	wsprintf(help1, "%%%i.lf", m_precision);

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

//////////////////////////////////////////////////////////////////////////////
// ProfileHighLevel::Id

// Zero Hour's Id::Increment and Id::SetMax are left out: no retail
// evidence that BFME2 keeps them.

// ?GetName@Id@ProfileHighLevel@@QBEPBDXZ
const char *ProfileHighLevel::Id::GetName(void) const
{
	return m_idPtr ? m_idPtr->GetName() : NULL;
}

// ?GetDescr@Id@ProfileHighLevel@@QBEPBDXZ
const char *ProfileHighLevel::Id::GetDescr(void) const
{
	return m_idPtr ? m_idPtr->GetDescr() : NULL;
}

// ?GetUnit@Id@ProfileHighLevel@@QBEPBDXZ
const char *ProfileHighLevel::Id::GetUnit(void) const
{
	return m_idPtr ? m_idPtr->GetUnit() : NULL;
}

// ?GetCurrentValue@Id@ProfileHighLevel@@QBEPBDXZ (0x006C6470)
const char *ProfileHighLevel::Id::GetCurrentValue(void) const
{
	return m_idPtr ? m_idPtr->AsString(m_idPtr->GetCurrentValue()) : NULL;
}

// ?GetValue@Id@ProfileHighLevel@@QBEPBDI@Z
const char *ProfileHighLevel::Id::GetValue(unsigned frame) const
{
	double v;
	if (!m_idPtr || !m_idPtr->GetFrameValue(frame, v))
		return NULL;
	return m_idPtr->AsString(v);
}

// ?GetTotalValue@Id@ProfileHighLevel@@QBEPBDXZ (0x006C64E0)
const char *ProfileHighLevel::Id::GetTotalValue(void) const
{
	return m_idPtr ? m_idPtr->AsString(m_idPtr->GetTotalValue()) : NULL;
}

//////////////////////////////////////////////////////////////////////////////
// ProfileHighLevel

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
	return cur != NULL;
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

	id.m_idPtr = NULL;
	return false;
}
