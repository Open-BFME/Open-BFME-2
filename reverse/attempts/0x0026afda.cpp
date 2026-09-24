// ?initMember@Rva0026AFDAMember@@QAEPAV1@XZ
// partial score=0.9 date=2026-09-24
// cl: /O1 /DNDEBUG /MD /arch:SSE /D_STLP_USE_STATIC_LIB
// stlport
//
// ?initMember@Rva0026AFDAMember@@QAEPAV1@XZ, retail 0x0026AFDA (99 bytes).
// BANKED PARTIAL 0.9 (see re_attempts.log): everything matches except the
// vector-setup scheduling - retail splits lea-eax plus S1C plus push plus
// lea-ecx while this TU groups the three setup ops after S1C. Two
// _ReadWriteBarrier intrinsics pin the group below S18 and S1C but the
// scheduler will not split the group (barriers are statement-granular).
// Proven levers inside: MSVC explicit-ctor-call for the guard-free direct
// 0x211E58 call (placement new guards on the address and a typed vector
// member would hoist the call above the OR); `|= -1` idiom for the leading
// OR (/O2 canonicalizes it to mov - do not use); raw vector storage keeps
// the class trivial so callers construct it with zero bytes; pointer return
// (mov eax esi epilogue); 0x263895 subobject via pin. Do NOT retry without
// a setup-splitting lever (scheduler version or unseen shape).

#include <new>
#include <vector>

extern "C" void _ReadWriteBarrier(void);

#pragma intrinsic(_ReadWriteBarrier)

struct BfmeE16 { float x, y, z, w; };

typedef _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > BfmeE16VecBase;

class Rva00263895Member
{
public:
	void init();

private:
	unsigned char m_pad[0x7C];		// +0x00..0x7C (interior owned by 0x263895)
};

class Rva0026AFDAMember
{
public:
	// No default ctor on purpose: callers hold this member as raw-trivial
	// storage and run only initMember on it (a typed vector member would
	// summon member construction plus EH funclets into DeployStyle's
	// frameless ctor).
	Rva0026AFDAMember *initMember();

private:
	int m_00;				// +0x00 (`|= -1` idiom)
	int m_04;				// +0x04
	float m_08;				// +0x08
	float m_0C;				// +0x0C
	float m_10;				// +0x10
	int m_14;				// +0x14
	int m_18;				// +0x18
	int m_1C;				// +0x1C
	int m_20;				// +0x20
	unsigned char m_vec24[0xC];		// +0x24 (vector<BfmeE16> storage)
	int m_30;				// +0x30
	int m_34;				// +0x34
	int m_38;				// +0x38
	float m_3C;				// +0x3C
	Rva00263895Member m_mem40;		// +0x40 (init through 0x263895 pin)
	int m_BC;				// +0xBC
	int m_C0;				// +0xC0
};

// ?initMember@Rva0026AFDAMember@@QAEPAV1@XZ @0x26AFDA
Rva0026AFDAMember *Rva0026AFDAMember::initMember()
{
	m_00 |= -1;
	m_04 = 0;
	m_08 = 0.0f;
	m_0C = 0.0f;
	m_10 = 0.0f;
	m_14 = 0;
	m_18 = 0;
	_ReadWriteBarrier();
	m_1C = 0;
	_ReadWriteBarrier();
	m_20 = 0;
	// Explicit in-place base construction (MSVC explicit-ctor-call): emits
	// the guard-free direct 0x211E58 call an init-list would but staged
	// mid-body after the OR above.
	((BfmeE16VecBase &)m_vec24)._STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >::_Vector_base(_STL::allocator<BfmeE16>());
	m_30 = 0;
	m_34 = 0;
	m_38 = 0;
	m_3C = 0.0f;
	m_mem40.init();
	m_BC = 0;
	m_C0 = 0;
	return this;
}
