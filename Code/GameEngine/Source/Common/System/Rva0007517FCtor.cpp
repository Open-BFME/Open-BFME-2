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
class Rva00074626
{
public:
    virtual ~Rva00074626();
};
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
	virtual void rva000749C1(char *a, char *b, int count, int x1, int x2, int x3, int x4, int x5);

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
	float m[12];
	m[0] = g_Va00BBB8D8;
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = position[0];
	m[4] = 0.0f;
	m[5] = g_Va00BBB8D8;
	m[6] = 0.0f;
	m[7] = position[1];
	m[8] = 0.0f;
	m[9] = 0.0f;
	m[10] = g_Va00BBB8D8;
	m[11] = position[2];
	_S18(m, f, a, b, c);
}

void Rva0007517F::rva00074BC8(float const *position, int f, int a, int b, int c)
{
	float m[12];
	m[0] = g_Va00BBB8D8;
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = position[0];
	m[4] = 0.0f;
	m[5] = g_Va00BBB8D8;
	m[6] = 0.0f;
	m[7] = position[1];
	m[8] = 0.0f;
	m[9] = 0.0f;
	m[10] = g_Va00BBB8D8;
	m[11] = position[2];
	_D12(m, f, a, b, c);
}

void Rva0007517F::rva00074D39(float const *position, float f, int a, int b, int c)
{
	float m[12];
	m[0] = g_Va00BBB8D8;
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = position[0];
	m[4] = 0.0f;
	m[5] = g_Va00BBB8D8;
	m[6] = 0.0f;
	m[7] = position[1];
	m[8] = 0.0f;
	m[9] = 0.0f;
	m[10] = g_Va00BBB8D8;
	m[11] = position[2];
	_D14(m, f, a, b, c);
}

void Rva0007517F::rva00074EA2(float const *position, float f1, float f2, int a, int b, int c)
{
	float m[12];
	m[0] = g_Va00BBB8D8;
	m[1] = 0.0f;
	m[2] = 0.0f;
	m[3] = position[0];
	m[4] = 0.0f;
	m[5] = g_Va00BBB8D8;
	m[6] = 0.0f;
	m[7] = position[1];
	m[8] = 0.0f;
	m[9] = 0.0f;
	m[10] = g_Va00BBB8D8;
	m[11] = position[2];
	_D16(m, f1, f2, a, b, c);
}

void Rva0007517F::rva000749C1(char *a, char *b, int count, int x1, int x2, int x3, int x4, int x5)
{
	if (count <= 0)
		return;
	int i = 1;
	int diff = (int)(a - b);
	int left = count;
	char *pb = b;
	do {
		_D11(pb + diff, pb, x1, x4, x5);
		int index = i % count;
		_D11(pb + diff, (char *)&((RubbleFXVec *)a)[index], x2, x4, x5);
		_D11(pb, (char *)&((RubbleFXVec *)b)[index], x3, x4, x5);
		++i;
		pb += 12;
		--left;
	} while (left != 0);
}
