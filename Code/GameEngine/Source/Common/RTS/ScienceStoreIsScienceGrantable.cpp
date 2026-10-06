// cl: /DNDEBUG /MD /EHsc

// ?isScienceGrantable@ScienceStore@@QBE_NW4ScienceType@@@Z @0x1FF432
// (23B): ScienceStore::isScienceGrantable, BFME1 Science.cpp verbatim shape:
// findScienceInfo (matched row) plus a null-guarded grantable byte read at
// +0x30. Leaf, no pins.

#define NULL 0

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class ScienceInfo
{
	char m_pad[0x30];
public:
	bool m_grantable;
};

class ScienceStore
{
	const ScienceInfo *findScienceInfo(ScienceType st) const;
public:
	bool isScienceGrantable(ScienceType st) const;
};

// ?isScienceGrantable@ScienceStore@@QBE_NW4ScienceType@@@Z
bool ScienceStore::isScienceGrantable(ScienceType st) const
{
	const ScienceInfo *si = findScienceInfo(st);
	if (si)
		return si->m_grantable;
	return false;
}
