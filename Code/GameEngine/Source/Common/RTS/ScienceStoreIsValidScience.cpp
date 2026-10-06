// cl: /DNDEBUG /MD /EHsc
// ?isValidScience@ScienceStore@@QBE_NW4ScienceType@@@Z @0x1FF50D
// (15B): ScienceStore::isValidScience, ZH Science.cpp verbatim (public const):
// findScienceInfo (pinned at 0x1FF3AD) plus null-check normalized to Bool.
// The neg/sbb/neg normalization falls out of the != NULL shape.

enum ScienceType
{
	SCIENCE_INVALID = -1
};

#define NULL 0

class ScienceInfo
{
};

class ScienceStore
{
	const ScienceInfo *findScienceInfo(ScienceType st) const;
public:
	bool isValidScience(ScienceType st) const;
};

// ?isValidScience@ScienceStore@@QBE_NW4ScienceType@@@Z
bool ScienceStore::isValidScience(ScienceType st) const
{
	const ScienceInfo *si = findScienceInfo(st);
	return si != NULL;
}
