// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?rva0007490F@Rva0007517F@@UAEXPADHHHHH@Z, retail 0x0007490F, 178 bytes.
// Virtual slot 20 offset 0x50 of vtable 0x007C6620 in class Rva0007517F.
// Evidence: vslot lane, donor TU Rva0007517FCtor.cpp, triple _D11 slot 0x2C
// calls per iteration with 12-byte stride plus g_00BC6610 index table.
extern int g_00BC6610[];

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
	virtual void rva0007490F(char *base, int b, int c, int d, int e, int f);

private:
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	void *m_28;
};

void Rva0007517F::rva0007490F(char *base, int b, int c, int d, int e, int f)
{
	int i = 1;
	int *q = g_00BC6610;
	char *p = base;
	int n = 4;
	do {
		_D11(p, p + 48, b, e, f);
		int r = i % 4;
		int *a = g_00BC6610 + r;
		_D11(base + (*q) * 12, base + (*a) * 12, c, e, f);
		_D11(base + (*q + 4) * 12, base + (*a + 4) * 12, d, e, f);
		p += 12;
		++i;
		++q;
		--n;
	} while (n != 0);
}
