// cl: /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1SpecialAbilityUpdate@@UAE@XZ, retail 0x00451F45, 93 bytes.
// Target evidence: the audited scalar deleting dtor 0x004522F0 (class-name
// string "SpecialAbilityUpdate" via slot 4) calls this body; derived module
// dtors (MissileLauncherBuildingUpdate 0x004CD9C0 and others) call it at the
// base position. Body: compiler vptr restores (+0 +0x0C +0x10 +0x20), a
// thiscall (1, 1) to 0x004502CE, destruction of the list<int> at +0x64
// (0x004EC395), then the base dtor 0x0024A797 (Rva0024A797).
// Donor-carried: the BFME1 SpecialAbilityUpdateDestructor.cpp body
// `onExit(true, true)` supplies the callee name; the BFME1 layout (inline
// UpdateModule, AudioEventRTS member) does not apply here.
#include <list>

// Base view matching Common/Rva0024A797DeletingDtor.cpp: vptrs at +0, +0xC,
// +0x10; 0x20 bytes.
class Rva0049B47C
{
public:
	virtual ~Rva0049B47C() throw();

private:
	char m_pad04[8];
};

class MiBase1
{
public:
	virtual void f1();
};

class PrimaryP451F45 : public Rva0049B47C, public MiBase1
{
public:
	~PrimaryP451F45() {}
};

class Rva0024A797_B2
{
public:
	virtual void f2();

private:
	char m_pad08[12];
};

class Rva0024A797 : public PrimaryP451F45, public Rva0024A797_B2
{
public:
	virtual ~Rva0024A797();
};

class SpecialAbilityUpdateInterface
{
public:
	virtual void slot();
};

class SpecialAbilityUpdate : public Rva0024A797, public SpecialAbilityUpdateInterface
{
public:
	virtual ~SpecialAbilityUpdate();

private:
	void onExit(bool, bool);
	unsigned char m_pad24[0x64 - 0x24];
	_STL::list<int> m_specialObjectIDList;	// +0x64
	unsigned char m_pad6C[0x88 - 0x6C];
};

SpecialAbilityUpdate::~SpecialAbilityUpdate()
{
	onExit(true, true);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva00451F45@@UAE@XZ=??1SpecialAbilityUpdate@@UAE@XZ")

// The rowed constructor and its derived callers use this opaque base spelling.
// Native calls and the shared vtable identify the same complete destructor.
#pragma comment(linker, "/alternatename:??1Rva0044EF5E@@UAE@XZ=??1SpecialAbilityUpdate@@UAE@XZ")
