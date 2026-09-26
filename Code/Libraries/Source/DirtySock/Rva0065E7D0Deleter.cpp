// cl: /DNDEBUG /MD /EHs-c-

// ??_GRva0065E7D0@@UAEPAXI@Z, retail 0x0065E8E0 (36B). Scalar-deleting
// destructor of the opaque BfmeDirtyBase-derived class Rva0065E7D0 (vtable
// 0x00CE2368, whose slot 0 lands here). Shape two of Y2ScalarDeleters.cpp:
// the derived destructor is INLINE and empty, so what survives inlining is
// the derived vptr reinstall (DIR32 auto-patch) followed by the call to the
// matched shared base destructor at 0x00658650 (declared here, never
// defined). The flag test then frees through the global one-arg operator
// delete (matched ??3 row, no member delete declared). Per the
// Rva006560E0Deleter recipe, the defined constructor below forces the vtable
// emission, and ??_G rides along with it; the constructor itself is only
// marked present-unmatched, never claimed. Owner identity is the rowed
// ??1Rva0065E7D0 at 0x0065E7D0 in BfmeDirtyBaseDerived.cpp.

struct BfmeDirtyBase
{
	BfmeDirtyBase();
	virtual ~BfmeDirtyBase();
};

class Rva0065E7D0 : public BfmeDirtyBase
{
public:
	Rva0065E7D0();
	virtual ~Rva0065E7D0()
	{
	}
};

// ??0Rva0065E7D0@@QAE@XZ present-unmatched (emission only, unclaimed)
Rva0065E7D0::Rva0065E7D0()
{
}
