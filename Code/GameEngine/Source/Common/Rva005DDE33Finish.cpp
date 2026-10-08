// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc

// ?rva005DDE33@Rva005DDE33@@QAEMIII@Z, RVA 0x005DDE33, 54B. Chain lane:
// bounds-checked delegate; count is the byte range at +4/+8 divided by 0x18
// via push/pop idiv, out of range returns pooled 0.0f BfmeZeroRange, else calls
// the rowed float range-sum 0x005DDC6B on the indexed 0x18 element head with
// (lo,hi). 12 callers in 0x005DE100. Owner unknown so honest address-derived
// method name; element head overlaps the callee layout at +4 by construction.
// Flags copy the prev neighbour allocate_copy TU (frameless-friendly, no EH).
// The body mirrors landed sibling Rva005DDE69 (0x005DDE69): count hoisted
// before the barrier, pointer-cast element access. That form is what schedules
// the hi push ahead of the imul, which retail 0x005DDE33 also does; the
// start/finish-local form emits the imul first and is one byte short of exact.
extern const float BfmeZeroRange;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva005DDC6B
{
public:
	float rva005DDC6B(unsigned lo, unsigned hi);
private:
	int m_00;
	char *m_04;
};

class Rva005DDE33
{
public:
	float rva005DDE33(unsigned idx, unsigned lo, unsigned hi);
private:
	int m_00;
	char *m_04;
	char *m_08;
};

float Rva005DDE33::rva005DDE33(unsigned idx, unsigned lo, unsigned hi)
{
	int count = (m_08 - m_04) / 0x18;
	_ReadWriteBarrier();
	if (idx >= (unsigned)count)
		return BfmeZeroRange;
	return ((Rva005DDC6B *)(m_04 + idx * 0x18))->rva005DDC6B(lo, hi);
}

