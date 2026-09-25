// cl: /O2 /Os /DNDEBUG /MD /EHs-c-
// Default module base copy constructors (retail 0x003AEEB3 cluster).
// The shared three-vtable base: smart-pointer head (vptr 0x00C1B590,
// 12-byte member copied through the rowed 0x0004CC19 body, int at +0x10)
// plus two vtable-only bases sharing 0x00C1C780. The 71-byte body is the
// 59-byte info-base shape (see ParticleModuleInfoCopyCtors.cpp) with one
// more vtable-only base: compare 0x003AF50D.
// Identity: eight per-module template copies (0x003AEA4C, 0x003AEB14,
// 0x003AEBD3, 0x003AEC95, 0x003AED75, 0x003AEE2D, 0x003AEFA5, 0x003AF08D)
// call this address at the same +0x10 displacement; all vftable dwords
// are DIR32 sites the gate takes from the target.

class RvaSmartPtr12
{
public:
	RvaSmartPtr12(const RvaSmartPtr12 &that);
	~RvaSmartPtr12();

private:
	void *m_ptr; // +0x0
	int m_pad04; // +0x4
	int m_pad08; // +0x8
};

// Shared second base at +0x14: vptr 0x00C1C780.
class DefaultModuleSecondBase
{
public:
	virtual ~DefaultModuleSecondBase();
};

// Extra third base at +0x18: vptr 0x00C1C780 (ICF-folded with the second).
class DefaultModuleThirdBase
{
public:
	virtual ~DefaultModuleThirdBase();
};

// Head base: vptr 0x00C1B590, smart member at +0x04, int at +0x10.
// Explicit forceinline copy so the size optimizer still absorbs it.
class DefaultModuleHeadBase
{
public:
	__forceinline DefaultModuleHeadBase(const DefaultModuleHeadBase &other)
		: m_smart(other.m_smart)
		, m_int10(other.m_int10)
	{
	}
	virtual ~DefaultModuleHeadBase();

	RvaSmartPtr12 m_smart; // +0x04
	int m_int10; // +0x10
};

// Retail 0x003AEEB3, 71 bytes: the shared base copy constructor.
// noinline: the template copies below call it; inlining would absorb the
// straight-line body into each caller.
class Rva003AEEB3 : public DefaultModuleHeadBase, public DefaultModuleSecondBase,
	public DefaultModuleThirdBase
{
public:
	__declspec(noinline) Rva003AEEB3(const Rva003AEEB3 &other);
	virtual ~Rva003AEEB3();
};

Rva003AEEB3::Rva003AEEB3(const Rva003AEEB3 &other)
	: DefaultModuleHeadBase(other)
{
}
