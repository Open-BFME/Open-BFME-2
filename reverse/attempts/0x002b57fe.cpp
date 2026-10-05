// ?Rva002B57FEPartition@@YAPAVRva002B2F97@@PAV1@0V1@@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /MD /EHsc
// ?Rva002B57FEPartition@@YAPAVRva002B2F97@@PAU1@0U1@@Z @0x002B57FE 117B.
// Partition of Rva002B2F97 holders around pivot via rowed Less 0x2B367C
// and Swap 0x2B2FF4 with terminal Release 0x7DEEF. Evidence: callers
// at 0x002BB74E, callees Less Swap Release, ret edi partition point.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva002B2F97Target
{
	char m_pad[0xAC];
	TargetRef00217D4C m_ac;
};

class Rva0037DCA5;
bool __stdcall Rva002B367CLess(Rva0037DCA5 **a, Rva0037DCA5 **b);

class Rva002B2F97
{
public:
	Rva002B2F97() : m_ptr(0) {}
	Rva002B2F97(const Rva002B2F97 &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->m_ac.references;
	}
	~Rva002B2F97()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
	}
	Rva002B2F97 &operator=(const Rva002B2F97 &other)
	{
		if (this != &other) {
			if (other.m_ptr)
				++other.m_ptr->m_ac.references;
			if (m_ptr)
				ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
			m_ptr = other.m_ptr;
		}
		return *this;
	}
	Rva002B2F97Target *m_ptr;
};
void __cdecl Rva002B2FF4Swap(Rva002B2F97 &a, Rva002B2F97 &b);

// ?Rva002B57FEPartition@@YAPAVRva002B2F97@@PAV1@0V1@@Z present-unmatched
Rva002B2F97 *Rva002B57FEPartition(Rva002B2F97 *first, Rva002B2F97 *last, Rva002B2F97 pivot)
{
	Rva002B2F97 *hi = last;
	Rva002B2F97 *lo = first;
	while (true) {
		while (Rva002B367CLess((Rva0037DCA5 **)lo, (Rva0037DCA5 **)&pivot))
			++lo;
		--hi;
		while (Rva002B367CLess((Rva0037DCA5 **)&pivot, (Rva0037DCA5 **)hi))
			--hi;
		if (lo >= hi)
			break;
		Rva002B2FF4Swap(*lo, *hi);
		++lo;
	}
	return lo;
}
