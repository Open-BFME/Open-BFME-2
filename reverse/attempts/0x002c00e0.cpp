// ?rva002C00E0@@YGXPAXPBURva002C00E0Pair@@@Z
// partial score=0.9 date=2026-10-08
// cl: /MD /EHsc
// ?rva002C00E0@@YGXPAXPBURva002C00E0Pair@@@Z @0x002C00E0 64B.
// Stdcall wrapper: copies the two-dword pair at arg 2 into a local object
// (vtable 0x00BFE4F4 in front of the copied words), then calls the unrowed
// stdcall 0x002BFDE6 (pinned by its REL32 at 0x002C0105) with the target and
// the local. The virtual dtor is what gives the frame its unwind state.
// Evidence: target only; the names are address-derived.
struct Rva002C00E0Pair
{
	unsigned int m_00;
	unsigned int m_04;
};

class Rva002C00E0Obj
{
public:
	Rva002C00E0Obj(const Rva002C00E0Pair &p) : m_pair(p) {}
	virtual ~Rva002C00E0Obj() {}

private:
	Rva002C00E0Pair m_pair;
};

void __stdcall rva002BFDE6(void *target, Rva002C00E0Obj *obj);

void __stdcall rva002C00E0(void *target, const Rva002C00E0Pair *pair)
{
	Rva002C00E0Obj obj(*pair);
	rva002BFDE6(target, &obj);
}
