// cl: /DNDEBUG /MD /EHsc

// ?findScienceInfo@ScienceStore@@ABEPBVScienceInfo@@W4ScienceType@@@Z @0x1FF3AD
// (47B): ScienceStore::findScienceInfo, BFME1 Science.cpp verbatim shape with a
// BFME2 null-guarded override hop: retail only calls the out-of-line
// Overridable::getFinalOverride worker (pin 0x1E35DF) when m_nextOverride is
// non-null, otherwise it keeps the vector element directly. ScienceInfo carries
// m_science at +0x10 (Overridable base is 0x10 bytes in BFME2, with the third
// word at +0x0C like RankInfo); m_sciences vector starts at +0x0C.

#define NULL 0

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class Overridable
{
public:
	void *m_vftable;
	Overridable *m_nextOverride;
	int m_isOverride;
	int m_third;

	const Overridable *getFinalOverride() const;
};

class ScienceInfo : public Overridable
{
public:
	ScienceType m_science;
};

class ScienceStore
{
	ScienceInfo **m_beginPad[3];
	ScienceInfo **m_begin;
	ScienceInfo **m_end;

	const ScienceInfo *findScienceInfo(ScienceType st) const;
};

// ?findScienceInfo@ScienceStore@@ABEPBVScienceInfo@@W4ScienceType@@@Z
const ScienceInfo *ScienceStore::findScienceInfo(ScienceType st) const
{
	ScienceInfo **begin = m_begin;
	ScienceInfo **end = m_end;
	for (ScienceInfo **it = begin; it != end; ++it)
	{
		const ScienceInfo *si = *it;
		if (si->m_nextOverride)
			si = (const ScienceInfo *)si->m_nextOverride->getFinalOverride();
		if (si->m_science == st)
			return si;
	}
	return NULL;
}
