#ifndef BFME2_LOOKUPTABLEPOSTEFFECT_H
#define BFME2_LOOKUPTABLEPOSTEFFECT_H

#include "Rva001164B6.h"

class Rva00111C05Effect;

struct RefCounted
{
	virtual void Release();
	int m_ref;
};

// +0x08: the ref-counted effect handle; the ctor nulls it, the dtor
// releases it inline (its out-of-line copy is the ICF fold 0x0007B724).
struct Field08
{
	RefCounted *m_ptr;
	Field08() : m_ptr(0) {}
	~Field08()
	{
		RefCounted *refCounted = m_ptr;
		if (refCounted && --refCounted->m_ref == 0)
			refCounted->Release();
	}
	Rva00111C05Effect *get() const { return (Rva00111C05Effect *)m_ptr; }
};

// Retail vftable 0x00BCFAC8: slot 0 rva00111BE9, slot 1 the deleting dtor
// 0x00111D9A, slot 2 rva00111DB6, slot 3 rva00111D65, slot 4 doApply.
class LookupTablePostEffect : public Rva001164B6
{
public:
	LookupTablePostEffect();
	virtual AsciiString rva00111BE9() const;
	virtual ~LookupTablePostEffect();
	virtual void rva00111DB6();
	virtual void rva00111D65();
	virtual void doApply();

private:
	Field08 m_08;
};

#endif
