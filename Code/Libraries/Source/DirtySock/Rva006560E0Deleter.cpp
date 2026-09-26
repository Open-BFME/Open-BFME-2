// cl: /DNDEBUG /MD /EHs-c-

// ??_GRva006560E0@@UAEPAXI@Z, retail 0x006562B0 (36B). Scalar-deleting
// destructor of the opaque BfmeDirtyBase-derived class Rva006560E0 (vtable
// 0x00CE0FC8, whose slot 0 lands here). Shape two of Y2ScalarDeleters.cpp:
// the derived destructor is INLINE and empty, so what survives inlining is
// the derived vptr reinstall (DIR32 auto-patch) followed by the call to the
// matched shared base destructor at 0x00658650 (declared here, never
// defined). The flag test then frees through the global one-arg operator
// delete (matched ??3 row, no member delete declared). Per the
// Rva0065F140Deleter recipe, the defined constructor below forces the vtable
// emission, and ??_G rides along with it; the constructor itself is only
// marked present-unmatched, never claimed. Owner identity is the rowed
// ??1Rva006560E0 at 0x006560E0 in BfmeDirtyBaseDerived.cpp.

struct BfmeDirtyBase
{
	BfmeDirtyBase();
	virtual ~BfmeDirtyBase();
};

class Rva006560E0 : public BfmeDirtyBase
{
public:
	Rva006560E0();
	virtual ~Rva006560E0()
	{
	}
};

// ??0Rva006560E0@@QAE@XZ present-unmatched (emission only, unclaimed)
Rva006560E0::Rva006560E0()
{
}
