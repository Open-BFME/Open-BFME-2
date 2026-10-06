// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?newCrateTemplate@CrateSystem@@QAEPAVCrateTemplate@@VAsciiString@@@Z
// retail 0x0035CF2C (190B), Zero Hour CrateSystem::newCrateTemplate: an
// empty name gives NULL; otherwise a new CrateTemplate copies the
// "DefaultCrate" template when there is one (BFME 2 raises g_00E01EA8 around
// that copy as newCrateTemplateOverride does), takes the name and is appended
// to the template vector at +0x0C (pointer-vector push_back 0x004DFCB0). The
// lookup is the rowed friend_findCrateTemplate 0x0035CA2F (by-value name),
// called through TheCrateSystem's this. And
// ?setName@CrateTemplate@@QAEXVAsciiString@@@Z retail 0x0035C972 (52B):
// Zero Hour's inline CrateTemplate::setName, out of line in BFME 2 (m_name
// at +0x10, the by-value name released after the assignment).
//
// ?newCrateTemplateOverride@CrateSystem@@QAEPAVCrateTemplate@@PAV2@@Z
// retail 0x0035CEA6 (106B).
// Zero Hour CrateSystem::newCrateTemplateOverride: news a 0x44-byte
// CrateTemplate through the rowed ctor 0x0035CC36, copies the template being
// overridden into it with the rowed operator= 0x0035CE52, marks it as an
// override (+0x08 = 1) and links it as the overridden template's next
// override (+0x04). The REL32 at CrateSystem::parseCrateTemplateDefinition
// 0x0035CFEA names this address. BFME 2 deltas (target evidence): the pool
// newInstance became a plain operator new (0x0002FDA0), and the copy runs
// with the byte g_00E01EA8 raised (CrateSystem::newCrateTemplate does the
// same around its default-template copy); `this` is unused (ret 4).
//
// ?friend_findCrateTemplate@CrateSystem@@QAEPAVCrateTemplate@@VAsciiString@@@Z
// retail 0x0035CA2F (133B), Zero Hour's body: the first template whose name
// (+0x10) compares equal (AsciiString::compare 0x000069D6) is returned through
// OVERRIDE<CrateTemplate>, i.e. its final override: the inline
// getFinalOverride follows a non-NULL +0x04 link through
// Overridable::friend_getFinalOverride 0x001E35DF.

#include "ascii_string.h"

class Overridable
{
public:
	Overridable *friend_getFinalOverride();	// 0x001E35DF
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	void markAsOverride() { m_isOverride = 1; }
	void setNextOverride(Overridable *next) { m_nextOverride = next; }

private:
	void *m_vptr;				// +0x00
	Overridable *m_nextOverride;		// +0x04
	unsigned char m_isOverride;		// +0x08
	char m_pad09[0x10 - 0x09];
};

// Zero Hour's Override.h handle: holds the pointer and resolves the final
// override when read.
template <class T> class OVERRIDE
{
public:
	OVERRIDE(const T *overridable = 0) { m_overridable = overridable; }
	operator const T *() const
	{
		if (!m_overridable)
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}

private:
	const T *m_overridable;
};

class CrateTemplate : public Overridable
{
public:
	CrateTemplate();
	CrateTemplate &operator=(const CrateTemplate &that);

	void setName(AsciiString name);
	const AsciiString &getName() const { return m_name; }

private:
	AsciiString m_name;			// +0x10
	char m_pad14[0x44 - 0x14];
};

typedef OVERRIDE<CrateTemplate> CrateTemplateOverride;

namespace _STL
{
template <class T> class allocator {};
template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &value);	// 0x004DFCB0, the folded pointer-vector push_back
	unsigned int size() const { return m_finish - m_start; }
	T *begin() { return m_start; }
	T &operator[](unsigned int n) { return *(begin() + n); }	// STLport's spelling; m_start[n] allocates registers differently
private:
	T *m_start;
	T *m_finish;
	T *m_endOfStorage;
};
}

class CrateSystem
{
public:
	CrateTemplate *newCrateTemplate(AsciiString name);
	CrateTemplate *newCrateTemplateOverride(CrateTemplate *crateToOverride);
	CrateTemplate *friend_findCrateTemplate(AsciiString name);

private:
	char m_pad00[0x0C];
	_STL::vector<CrateTemplate *> m_crateTemplateVector;	// +0x0C
};

#include <new>

void CrateTemplate::setName(AsciiString name)
{
	m_name = name;
}

CrateTemplate *CrateSystem::friend_findCrateTemplate(AsciiString name)
{
	// search weapon list for name
	for (int i = 0; i < m_crateTemplateVector.size(); i++)
		if (m_crateTemplateVector[i]->getName() == name)
		{
			CrateTemplateOverride overridable(m_crateTemplateVector[i]);
			return const_cast<CrateTemplate *>((const CrateTemplate *)overridable);
		}
	return 0;
}

extern void *__cdecl operator new(unsigned int size);
extern unsigned char g_00E01EA8;
// g_00E01EA8: matched references place it at VA 0xe01ea8 (zero-filled .bss).
unsigned char g_00E01EA8;

CrateTemplate *CrateSystem::newCrateTemplateOverride(CrateTemplate *crateToOverride)
{
	if (crateToOverride == 0)
		return 0;

	CrateTemplate *newOverride = new CrateTemplate();
	g_00E01EA8 = 1;
	*newOverride = *crateToOverride;
	g_00E01EA8 = 0;

	newOverride->markAsOverride();

	crateToOverride->setNextOverride(newOverride);
	return newOverride;
}

// Shape: retail keeps the new template in esi and gives push_back a stack
// copy that shares its slot with operator new's EH temporary, so the copy's
// scope starts after the allocation; written as the inner block below. With
// `ct` pushed directly cl keeps the template in memory throughout.
CrateTemplate *CrateSystem::newCrateTemplate(AsciiString name)
{
	// sanity
	if (name.isEmpty())
		return 0;

	// allocate a new weapon
	CrateTemplate *ct = new CrateTemplate();
	{
		CrateTemplate *entry = ct;

		// if the default template is present, get it and copy over any data to the new template
		const CrateTemplate *defaultCT = friend_findCrateTemplate(AsciiString("DefaultCrate"));
		if (defaultCT)
		{
			g_00E01EA8 = 1;
			*ct = *defaultCT;
			g_00E01EA8 = 0;
		}

		ct->setName(name);
		m_crateTemplateVector.push_back(entry);
	}

	return ct;
}
