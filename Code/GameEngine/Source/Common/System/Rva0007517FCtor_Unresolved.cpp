// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Split from Rva0007517FCtor.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// ??0Rva0007517F@@QAE@XZ, retail 0x0007517F, 112 bytes.
// Ctor calls rowed base 0x0030B0E3, installs its own vtable, inits +0x1C/+0x20/+0x24/+0x28,
// builds 20x RubbleFXVec at +0x2C through ehvec iterator 0x00629512, registers
// singleton g_00DE1ED0, zeroes 5 dwords at +0x11C. Evidence: chain packet (calls
// 0x0030B0E3 just landed); array 0x2C..0x11C is 0xF0 = 20*0xC matching RubbleFXVec
// size 0xC from RubbleRiseUpdateModuleDataCtor; ctor 0x656646 is ??0RubbleFXVec
// per LINK BONUS on 0x00256646; dtor slot 0x47FAB3 is the folded free-if-non-null
// shared with BasicStringCharDtor_dup; caller 0x00046A50.

// Native one-state cleanup75EF14 keeps the receiver at0 and calls the
// complete7B Rva0030B0E3 destructor7461F. Its54B constructor30B0E3 and
// deleting wrapper30B119 independently establish this20B polymorphic base;
// wrapper30B119 is slot0 of the full100B C08830 interface table. Its own
// base is the existing Rva00074626 view. Other unused interface slots stay
// unspecified; the full native table was inspected before choosing slot0.
// Derived BC6620 slot0 is deleting75279, which calls complete138B751EF.
// The old separate empty base displaced this cleanup. Existing RubbleFXVec
// spelling/layout is retained as a representation lead; this repair makes
// no further claim about the element's original identity. All112 owner bytes
// and its complete native EH graph remain exact.
#include "../../../Include/Common/Rva00074626.h"
class Rva0030B0E3 : public Rva00074626
{
public:
	virtual ~Rva0030B0E3();
	virtual void s1() = 0;
	virtual void s2() = 0;
	virtual void v3(int a, int b) = 0;
	virtual void s4() = 0;
	virtual void s5() = 0;
	virtual int v6() = 0;
	virtual void s7() = 0;
	virtual void v8(int a) = 0;
	virtual void v9(int a) = 0;
	Rva0030B0E3();

private:
	int m_pad04;
	int m_pad08;
	int m_c;
	int m_d;
};

#include <vector>

// The ehvec iterator receives the STLport pointer vector's folded default
// constructor closure 0x00256646 and destructor 0x0007FAB3, as in
// RubbleRiseUpdateModuleDataCtor.cpp.
class FXList;
typedef _STL::vector<const FXList *> RubbleFXVec;

extern void *g_00DE1ED0;

class Rva0007517F : public Rva0030B0E3
{
public:
	virtual ~Rva0007517F();
	Rva0007517F();
	virtual void _D10() = 0;
	virtual void _D11(char *p1, char *p2, int a, int b, int c) = 0;
	virtual void _D12(float const *m, int f, int a, int b, int c) = 0;
	virtual void rva00074BC8(float const *p, int f, int a, int b, int c);
	virtual void _D14(float const *m, float f, int a, int b, int c) = 0;
	virtual void rva00074D39(float const *p, float f, int a, int b, int c);
	virtual void _D16(float const *m, float f1, float f2, int a, int b, int c) = 0;
	virtual void rva00074EA2(float const *p, float f1, float f2, int a, int b, int c);
	virtual void _S18(float const *m, float f, int a, int b, int c) = 0;
	virtual void rva00075016(float const *p, float f, int a, int b, int c);
	virtual void _D20() = 0;
	virtual void rva000749C1(char *a, char *b, int n, int x1, int x2, int x3, int x4, int x5);

private:
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	RubbleFXVec m_arr[20];
	int m_tail[5];
};

Rva0007517F::Rva0007517F()
	: m_1c(0)
	, m_20(9)
	, m_24(13)
	, m_28(0)
{
	g_00DE1ED0 = this;
	for (int i = 0; i < 5; ++i)
		m_tail[i] = 0;
}
