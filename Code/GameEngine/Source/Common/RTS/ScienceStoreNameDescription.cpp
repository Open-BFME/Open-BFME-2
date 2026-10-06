// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc

// ?getNameAndDescription@ScienceStore@@QBE_NW4ScienceType@@AAVUnicodeString@@1@Z @0x1FF449
// (52B): ScienceStore::getNameAndDescription, BFME1 Science.cpp verbatim
// shape: findScienceInfo (matched row 0x1FF3AD) plus null-guarded copies of
// m_name (+0x14) and m_description (+0x18) via StringBase<wchar_t>::set
// (pin 0x37150). Adjacent to grantable (ends 0x1FF446) and prereqs (starts
// 0x1FF47D); ret 0xC proves 3 params. Leaf, no new pins.

#define NULL 0

enum ScienceType
{
	SCIENCE_INVALID = -1
};

#include "unicode_string.h"


class Overridable
{
public:
	void *m_vftable;
	Overridable *m_nextOverride;
	int m_isOverride;
	int m_third;
};

class ScienceInfo : public Overridable
{
public:
	ScienceType m_science;
	UnicodeString m_name;
	UnicodeString m_description;
};

class ScienceStore
{
	const ScienceInfo *findScienceInfo(ScienceType st) const;
public:
	bool getNameAndDescription(ScienceType st, UnicodeString &name, UnicodeString &description) const;
};

// ?getNameAndDescription@ScienceStore@@QBE_NW4ScienceType@@AAVUnicodeString@@1@Z
bool ScienceStore::getNameAndDescription(ScienceType st, UnicodeString &name, UnicodeString &description) const
{
	const ScienceInfo *si = findScienceInfo(st);
	if (si)
	{
		name.set(si->m_name);
		description.set(si->m_description);
		return true;
	}
	return false;
}
