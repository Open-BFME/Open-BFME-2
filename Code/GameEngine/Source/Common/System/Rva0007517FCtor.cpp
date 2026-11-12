// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
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
	virtual void s1();
	virtual void s2();
	virtual void v3(int a, int b);
	virtual void s4();
	virtual void s5();
	virtual int v6();
	virtual void s7();
	virtual void v8(int a);
	virtual void v9(int a);
	Rva0030B0E3();

private:
	int m_pad04;
	int m_pad08;
	int m_c;
	int m_d;
};

class RubbleFXVec
{
public:
	RubbleFXVec();
	~RubbleFXVec();

private:
	unsigned char m_data[0x0C];
};

extern void *g_00DE1ED0;
extern float g_Va00BBB8D8;

class Rva0007517F : public Rva0030B0E3
{
public:
	virtual ~Rva0007517F();
	Rva0007517F();
	virtual void _D10();
	virtual void _D11(char *p1, char *p2, int a, int b, int c);
	virtual void _D12(float const *m, int f, int a, int b, int c);
	virtual void rva00074BC8(float const *position, int f, int a, int b, int c);
	virtual void _D14(float const *m, float f, int a, int b, int c);
	virtual void rva00074D39(float const *position, float f, int a, int b, int c);
	virtual void _D16(float const *m, float f1, float f2, int a, int b, int c);
	virtual void rva00074EA2(float const *position, float f1, float f2, int a, int b, int c);
	virtual void _S18(float const *m, float f, int a, int b, int c);
	virtual void rva00075016(float const *position, float f, int a, int b, int c);
	virtual void _D20();
	virtual void rva000749C1(char *firstCorners, char *secondCorners, int count, int verticalEdgeColor, int firstRingEdgeColor, int secondRingEdgeColor, int x4, int x5);

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


void Rva0007517F::rva00075016(float const *position, float f, int a, int b, int c)
{
	float transform[12];
	transform[0] = g_Va00BBB8D8;
	transform[1] = 0.0f;
	transform[2] = 0.0f;
	transform[3] = position[0];
	transform[4] = 0.0f;
	transform[5] = g_Va00BBB8D8;
	transform[6] = 0.0f;
	transform[7] = position[1];
	transform[8] = 0.0f;
	transform[9] = 0.0f;
	transform[10] = g_Va00BBB8D8;
	transform[11] = position[2];
	_S18(transform, f, a, b, c);
}

void Rva0007517F::rva00074BC8(float const *position, int f, int a, int b, int c)
{
	float transform[12];
	transform[0] = g_Va00BBB8D8;
	transform[1] = 0.0f;
	transform[2] = 0.0f;
	transform[3] = position[0];
	transform[4] = 0.0f;
	transform[5] = g_Va00BBB8D8;
	transform[6] = 0.0f;
	transform[7] = position[1];
	transform[8] = 0.0f;
	transform[9] = 0.0f;
	transform[10] = g_Va00BBB8D8;
	transform[11] = position[2];
	_D12(transform, f, a, b, c);
}

void Rva0007517F::rva00074D39(float const *position, float f, int a, int b, int c)
{
	float transform[12];
	transform[0] = g_Va00BBB8D8;
	transform[1] = 0.0f;
	transform[2] = 0.0f;
	transform[3] = position[0];
	transform[4] = 0.0f;
	transform[5] = g_Va00BBB8D8;
	transform[6] = 0.0f;
	transform[7] = position[1];
	transform[8] = 0.0f;
	transform[9] = 0.0f;
	transform[10] = g_Va00BBB8D8;
	transform[11] = position[2];
	_D14(transform, f, a, b, c);
}

void Rva0007517F::rva00074EA2(float const *position, float f1, float f2, int a, int b, int c)
{
	float transform[12];
	transform[0] = g_Va00BBB8D8;
	transform[1] = 0.0f;
	transform[2] = 0.0f;
	transform[3] = position[0];
	transform[4] = 0.0f;
	transform[5] = g_Va00BBB8D8;
	transform[6] = 0.0f;
	transform[7] = position[1];
	transform[8] = 0.0f;
	transform[9] = 0.0f;
	transform[10] = g_Va00BBB8D8;
	transform[11] = position[2];
	_D16(transform, f1, f2, a, b, c);
}

void Rva0007517F::rva000749C1(char *firstCorners, char *secondCorners, int count, int verticalEdgeColor, int firstRingEdgeColor, int secondRingEdgeColor, int x4, int x5)
{
	if (count <= 0)
		return;
	int nextCorner = 1;
	int cornerArrayOffset = (int)(firstCorners - secondCorners);
	int remainingEdges = count;
	char *secondCorner = secondCorners;
	do {
		_D11(secondCorner + cornerArrayOffset, secondCorner, verticalEdgeColor, x4, x5);
		int nextCornerIndex = nextCorner % count;
		_D11(secondCorner + cornerArrayOffset, (char *)&((RubbleFXVec *)firstCorners)[nextCornerIndex], firstRingEdgeColor, x4, x5);
		_D11(secondCorner, (char *)&((RubbleFXVec *)secondCorners)[nextCornerIndex], secondRingEdgeColor, x4, x5);
		++nextCorner;
		secondCorner += 12;
		--remainingEdges;
	} while (remainingEdges != 0);
}
