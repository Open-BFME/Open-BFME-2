// cl: /MD
// ?Rva002B2FF4Swap@@YAXAAVRva002B2F97@@0@Z, retail 0x002B2FF4, 85 bytes.
// std::swap-style three-move exchange of the ref-counted holder Rva002B2F97:
// copy-construct a temp from a (which incs the refcount and captures a.m_ptr
// in a callee-saved register so it survives both assignments), then assign
// b into a and a into b, and let the temp destructor release the original
// a.m_ptr. The copy ctor / assign / dtor bodies are the same semantics as the
// already-matched Rva002B2F97Assign.cpp; defining them inline here lets /O1 see
// that tmp.m_ptr is captured at entry and released at exit, which is what
// recovers retail's push-esi / mov-esi,[ecx] / pop-esi callee-saved shape.
// Release is rowed fastcall 0x0007DEEF. Copy ctor and dtor are inline only.

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

private:
	Rva002B2F97Target *m_ptr;
};

// ?Rva002B2FF4Swap@@YAXAAVRva002B2F97@@0@Z
void __cdecl Rva002B2FF4Swap(Rva002B2F97 &a, Rva002B2F97 &b)
{
	Rva002B2F97 tmp = a;
	a = b;
	b = tmp;
}