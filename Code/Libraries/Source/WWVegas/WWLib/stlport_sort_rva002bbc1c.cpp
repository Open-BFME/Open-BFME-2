// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
#include <algorithm>

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva002BBC1CTarget
{
	char m_pad00[0xAC];
	TargetRef00217D4C m_ac; // +0xAC
};

class Rva004F6093Holder
{
public:
	Rva004F6093Holder(const Rva004F6093Holder &other);
	~Rva004F6093Holder()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
	}
	Rva004F6093Holder &operator=(const Rva004F6093Holder &other);

private:
	Rva002BBC1CTarget *m_ptr;
};

struct Rva002BBC1CCmp
{
	bool operator()(const Rva004F6093Holder &a, const Rva004F6093Holder &b) const;
};

template void _STL::sort<Rva004F6093Holder *, Rva002BBC1CCmp>(Rva004F6093Holder *, Rva004F6093Holder *, Rva002BBC1CCmp);
