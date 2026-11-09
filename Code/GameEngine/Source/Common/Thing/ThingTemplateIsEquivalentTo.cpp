// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Retail RE: ?isEquivalentTo@ThingTemplate@@QBE_NPBV1@@Z @0x0033BB04 (335B).
//
// BFME2 ThingTemplate equivalence. ZH/BFME1 donor
// (Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp isEquivalentTo) kept
// the finalOverride identity plus BuildVariations name checks; BFME2 drops the
// three m_reskinnedFrom pointer checks and adds an explicit EquivalentTo list.
// INI evidence from game.dat .rdata: EquivalentTo token VA 0xC0F540 offset
// +0x33c and BuildVariations token VA 0xC0F550 offset +0x330 share parse fn
// 0x42F196 (parseAsciiStringVector), file offsets 0x9bdc58/0x9bdc48.
// Layout is retail-measured: Rva001E35DFView m_nextOverride +0x4 (via rowed
// getFinalOverride 0x1E35DF), name +0x64 (StringBase<char> compareNoCase rowed
// 0x6A00), prereq vec +0x324 (per parsePrerequisites TU), m_buildVariations
// +0x330, m_equivalentTo +0x33c. EquivalentTo uses iterator (pointer) loops
// with a common-entry intersection; BuildVariations keeps the donor index
// loops. Callers include 0x0032879E and 0x0033C3AF.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef bool Bool;
typedef int Int;

#include "../../../Include/Common/ThingTemplate.h"

// TU-scoped ABI view for the exact14-byte getter at0x001E35DF.
// Separate spelling avoids incompatible shared Overridable getter COMDATs;
// Native335B callers and the14B getter prove the chain pointer at+4.
// Original base-class spelling Overridable comes from donor source;
// target bytes establish this view and chain walk, not that original name.
class Rva001E35DFView
{
public:
	const Rva001E35DFView *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Rva001E35DFView *m_nextOverride;
	Bool m_isOverride;
};

typedef std::vector<StringBase<char> > ThingTemplateStringVector;

// Non-owning views keep the existing StringBase comparison ABI and vector
// element representation; no strings or containers are constructed here.
static __forceinline const StringBase<char> &stringNameView(const AsciiString &name)
{
	return reinterpret_cast<const StringBase<char> &>(name);
}

static __forceinline const ThingTemplateStringVector &stringVectorView(const unsigned char (&storage)[12])
{
	return *reinterpret_cast<const ThingTemplateStringVector *>(storage);
}


Bool ThingTemplate::isEquivalentTo(const ThingTemplate *tt) const
{
	if (!(this && tt))
		return false;
	if (this == tt)
		return true;
	if (reinterpret_cast<const Rva001E35DFView *>(this)->getFinalOverride() ==
	    reinterpret_cast<const Rva001E35DFView *>(tt)->getFinalOverride())
		return true;

	const StringBase<char> &thisName = stringNameView(m_nameString);
	const StringBase<char> *thisEnd = &*stringVectorView(m_equivalentTo).end();
	std::vector<StringBase<char> >::const_iterator it;
	for (it = stringVectorView(m_equivalentTo).begin(); it != thisEnd; ++it)
		if (it->compareNoCase(stringNameView(tt->m_nameString)) == 0)
			return true;

	std::vector<StringBase<char> >::const_iterator jt = stringVectorView(tt->m_equivalentTo).begin();
	const StringBase<char> *otherEnd = &*stringVectorView(tt->m_equivalentTo).end();
	for (; jt != otherEnd; ++jt)
	{
		if (jt->compareNoCase(thisName) == 0)
			return true;
		for (it = stringVectorView(m_equivalentTo).begin(); it != thisEnd; ++it)
			if (it->compareNoCase(*jt) == 0)
				return true;
	}

	Int i;
	Int numVariations = (Int)stringVectorView(m_buildVariations).size();
	for (i = 0; i < numVariations; ++i)
		if (stringVectorView(m_buildVariations)[i].compareNoCase(stringNameView(tt->m_nameString)) == 0)
			return true;

	numVariations = (Int)stringVectorView(tt->m_buildVariations).size();
	for (i = 0; i < numVariations; ++i)
		if (stringVectorView(tt->m_buildVariations)[i].compareNoCase(thisName) == 0)
			return true;

	return false;
}
