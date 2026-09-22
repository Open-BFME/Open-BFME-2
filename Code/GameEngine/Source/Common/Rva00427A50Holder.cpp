// Single-function extraction from BFME1 RvaTinyBodies_20260920.cpp.
//
// Retail 0x005E744F is BFME1's ??0Rva00427A50Holder@@QAE@PAVRva00427A50Target@@@Z
// verbatim: a holder constructor that parks its pointer argument and, when it
// is not null, raises a plain non-interlocked count at +0x28 of the pointee.
// The store happens before the branch (assignment-then-guard source order).
//
// The donor TU also defines 34 functions the sweep never placed (under 16B or
// ambiguous), so the hook's find_declared_unmatched gate refuses the whole
// file; only this body moves here under its own TU name.

// One dword argument, `ret 4` and `this` returned in eax: a constructor that
// parks its pointer argument and, when it is not null, raises a plain
// non-interlocked count at +0x28 of the pointee.
class Rva00427A50Target
{
public:
	char m_lead[0x28];
	int m_refCount;
};

class Rva00427A50Holder
{
public:
	Rva00427A50Holder(Rva00427A50Target *target);

private:
	Rva00427A50Target *m_target;
};

// ??0Rva00427A50Holder@@QAE@PAVRva00427A50Target@@@Z
Rva00427A50Holder::Rva00427A50Holder(Rva00427A50Target *target)
{
	m_target = target;
	if (target != 0)
		target->m_refCount++;
}
