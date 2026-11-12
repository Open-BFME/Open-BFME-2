// cl: /DNDEBUG /MD /EHs-c-

// ??_GRva0065F140Derived@@UAEPAXI@Z, retail 0x0065F140 (34B). Scalar-deleting
// destructor of an opaque BfmeDirtyBase-derived class (vtable 0x00CE24A0,
// whose slot 0 lands here; the other eleven slots fold to 0x003B810). Shape
// two of Y2ScalarDeleters.cpp: the derived destructor is INLINE and empty,
// so what survives inlining is the derived vptr reinstall (DIR32
// auto-patch) followed by the call to the matched shared base destructor at
// 0x00658650 (declared here, never defined). The flag test then frees
// through the global one-arg operator delete (matched ??3 row, no member
// delete declared). Per the Y2ScalarDeleters recipe, the defined constructor
// below forces the vtable emission, and ??_G rides along with it; the
// constructor itself is only marked present-unmatched, never claimed. Owner
// identity is unproven (opaque Rva name).

struct BfmeDirtyBase
{
	BfmeDirtyBase();
	virtual ~BfmeDirtyBase();
};

class Rva0065F140Derived : public BfmeDirtyBase
{
public:
	Rva0065F140Derived();
	virtual ~Rva0065F140Derived()
	{
	}
public:
	// Retail table 0x00CE24A0: the deleting destructor, then 12 __purecall entries.
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
};

// ??0Rva0065F140Derived@@QAE@XZ present-unmatched (emission only, unclaimed)
Rva0065F140Derived::Rva0065F140Derived()
{
}
