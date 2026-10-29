// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?drawBox@Rva0007517F@@UAEXPADHHHHH@Z, retail 0x0007490F, 178 bytes.
// Virtual slot 20 offset 0x50 of vtable 0x007C6620 in class Rva0007517F.
// Evidence: vslot lane, donor TU Rva0007517FCtor.cpp, triple _D11 slot 0x2C
// calls per iteration with 12-byte stride plus g_00BC6610 index table.
// Retail's own 16-byte index table at RVA 0x007C6610 (.rdata, file offset
// 0x007C5F90): the four corner orders 0, 1, 3, 2 - which is exactly the ledger's
// 16-byte bound, and exactly the four entries the loop below reads (it indexes
// at g_00BC6610[i] and g_00BC6610[i % 4] with a 12-byte element stride). The
// words that follow it in .rdata belong to retail's next object.
// Symbol ?g_00BC6610@@3PAHA, transcribed below.
extern int g_00BC6610[] = { 0, 1, 3, 2 };

class EmptyBase2
{
public:
	~EmptyBase2();
};

class Rva0030B0E3B
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual void v3(int a, int b);
	virtual void s4();
	virtual void s5();
	virtual int v6();
	virtual void s7();
	virtual void v8(int a);
	virtual void v9(int a);
	Rva0030B0E3B();

private:
	int m_pad04;
	int m_pad08;
	int m_c;
	int m_d;
};

class Rva0007517F : public Rva0030B0E3B, public EmptyBase2
{
public:
	Rva0007517F();
	virtual void _D10();
	virtual void _D11(char *p1, char *p2, int a, int b, int c);
	virtual void _D12(float const *m, int f, int a, int b, int c);
	virtual void _D13(float const *p, int f, int a, int b, int c);
	virtual void _D14(float const *m, float f, int a, int b, int c);
	virtual void _D15(float const *p, float f, int a, int b, int c);
	virtual void _D16(float const *m, float f1, float f2, int a, int b, int c);
	virtual void _D17(float const *p, float f1, float f2, int a, int b, int c);
	virtual void _S18(float const *m, float f, int a, int b, int c);
	virtual void _D19(float const *p, float f, int a, int b, int c);
	virtual void drawBox(char *base, int b, int c, int d, int e, int f);

private:
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	void *m_28;
};

void Rva0007517F::drawBox(char *base, int b, int c, int d, int e, int f)
{
	int i = 1;
	int *currentCornerIndexPtr = g_00BC6610;
	char *currentCorner = base;
	int remainingCorners = 4;
	do {
		_D11(currentCorner, currentCorner + 48, b, e, f);
		int nextCornerIndex = i % 4;
		int *nextCornerIndexPtr = g_00BC6610 + nextCornerIndex;
		_D11(base + (*currentCornerIndexPtr) * 12, base + (*nextCornerIndexPtr) * 12, c, e, f);
		_D11(base + (*currentCornerIndexPtr + 4) * 12, base + (*nextCornerIndexPtr + 4) * 12, d, e, f);
		currentCorner += 12;
		++i;
		++currentCornerIndexPtr;
		--remainingCorners;
	} while (remainingCorners != 0);
}
