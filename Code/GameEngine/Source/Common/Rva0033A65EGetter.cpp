// cl: /MD
// ?rva0033A65E@Rva0033A65E@@QAEPAXXZ @0x0033A65E 22B
// Evidence: callers at 0x0059ADE3 0x0059AF90 0x004FAA9 use result as Body-like ptr (byte +0x1D);
// falls back to global Rva0041811D table at 0x00E030B0 via rowed DefaultBody 0x00418825.
class Rva0041811D
{
public:
	void *rva00418825();
};

// TheLivingWorldAutoResolveBodyStore: VA 0x00E030B0 (.data/bss); zero-filled pointer to the
// Rva0041811D table used for the default-body fallback.
Rva0041811D *TheLivingWorldAutoResolveBodyStore;

#include "../../Include/Common/Rva0033A65E.h"

void *Rva0033A65E::rva0033A65E()
{
	if (m_body != 0)
		return m_body;
	Rva0041811D *table = TheLivingWorldAutoResolveBodyStore;
	return table->rva00418825();
}

// ?rva004F5FAC@Rva004F5FACOwner@@QAEPAXXZ @0x004F5FAC 8B: loads the Rva0033A65E pointer held at +0x2C and
// tail-jumps Rva0033A65E::rva0033A65E. Owner and name are address-derived; no
// referencing site was found in this pass.
class Rva004F5FACOwner
{
public:
	void * rva004F5FAC();
private:
	char m_pad00[0x2C];
	Rva0033A65E *m_target;
};

void * Rva004F5FACOwner::rva004F5FAC()
{
	return m_target->rva0033A65E();
}
