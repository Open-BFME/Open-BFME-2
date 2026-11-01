// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// _STL::sort family over the 4-byte refcounted Rva004F6093Holder with an
// out-of-line comparator, retail 0x002B445C..0x002BBC5F (sort 0x002BBC1C).
//
// Evidence: every placed body is reached from sort 0x002BBC1C through REL32
// calls that agree with this TU's call graph (tools: masked compare plus
// REL32 walk). Element copies call the rowed Holder copy ctor 0x004F6093,
// assignments the rowed holder operator= 0x002B2F97 (same refcounted holder
// under its second placeholder name), and the inlined value destructor
// releases the TargetRef at +0xAC of the pointee through the rowed fastcall
// 0x0007DEEF. Every comparison is a call to 0x002B367C with ecx = &comp and
// both elements by reference, ret 8: the functor's out-of-line operator(),
// rowed as Rva002B367CLess (stdcall view; ecx unused) and pinned here.
//
// The holder copy ctor, operator= and the comparator are defined here (the
// retail TU saw them as header inlines, as in stlport_sort_rva0040cb11entry):
// with their bodies visible cl knows neither call touches the by-value
// element, so __linear_insert 0x002B73AD keeps val.m_ptr in esi across the
// comparator, copy_backward and operator= calls and inlines the element copy
// (inc [m_ptr+0xB0]) as retail does; declared only, it reloaded [ebp+0x10]
// per use. The emitted operator= / comparator copies equal the rows at
// 0x002B2F97 / 0x002B367C. Stock STLport (no bfmealloc shim, whose
// __forceinline __copy_backward_ptrs would fold into the wrapper) emits
// retail's 27-byte copy_backward -> 29-byte __copy_backward_ptrs -> 47-byte
// __copy_backward chain, ICF-folded onto the Rva002B2F97 rows at
// 0x002B5944 / 0x002B4623 / 0x002B3049 (fold-proof pins).
#include <algorithm>

#include "../../Apt/AptRefTarget.h"

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva0037DCA5
{
public:
	int GetCommandPointSize();
	char m_pad00[8];
	float m08; // +0x08
	char m_pad0C[0xAC - 0xC];
	TargetRef00217D4C m_ac; // +0xAC
};

class Rva004F6093Holder
{
	friend struct Rva002BBC1CCmp;

public:
	Rva004F6093Holder(const Rva004F6093Holder &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_ac.references;
	}
	~Rva004F6093Holder()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
	}
	Rva004F6093Holder &operator=(const Rva004F6093Holder &other)
	{
		if (this != &other)
		{
			if (other.m_ptr)
				++other.m_ptr->m_ac.references;
			if (m_ptr)
				ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
			m_ptr = other.m_ptr;
		}
		return *this;
	}

private:
	Rva0037DCA5 *m_ptr;
};

struct Rva002BBC1CCmp
{
	bool operator()(const Rva004F6093Holder &a, const Rva004F6093Holder &b) const
	{
		Rva0037DCA5 *pa = a.m_ptr;
		Rva0037DCA5 *pb = b.m_ptr;
		int diff = (int)(pa->m08 - pb->m08);
		if (diff == 0) {
			int va = pb->GetCommandPointSize();
			int vb = pa->GetCommandPointSize();
			return vb < va;
		}
		return diff < 0;
	}
};

template void _STL::sort<Rva004F6093Holder *, Rva002BBC1CCmp>(Rva004F6093Holder *, Rva004F6093Holder *, Rva002BBC1CCmp);
