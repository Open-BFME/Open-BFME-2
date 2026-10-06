// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?rva00074A52@Rva0007517F@@UAEXHHPBD@Z, retail 0x00074A52, 173 bytes.
// Virtual slot 24 offset 0x60 of vtable 0x007C6620 in class Rva0007517F.
// Evidence: vslot lane, donor TU Rva0007517FCtor.cpp, null checks on +0x1C/+0x28,
// AsciiString from char arg plus UnicodeString translate plus three iface calls
// on +0x28 with color and scaled pos args.
#include "ascii_string.h"
#include "unicode_string.h"

class DrawIface
{
public:
	virtual void d0();
	virtual void d1(UnicodeString s);
	virtual void d2();
	virtual void d3();
	virtual void d4();
	virtual void d5();
	virtual void d6();
	virtual void d7();
	virtual void d8();
	virtual void d9();
	virtual void d10(int a, int b);
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14(int a, int b, int c, int d);
};

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
	virtual void _D20();
	virtual void _D21(char *a, char *b, int n, int x1, int x2, int x3, int x4, int x5);
	virtual void _D22();
	virtual void _D23();
	virtual void rva00074A52(int x, int y, const char *text);

private:
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	DrawIface *m_28;
};

void Rva0007517F::rva00074A52(int x, int y, const char *text)
{
	if (m_1c == 0)
		return;
	if (m_28 == 0)
		return;
	UnicodeString w;
	{
		AsciiString a(text);
		w.translate(a);
	}
	m_28->d1(w);
	m_28->d10(-1, (int)0xff000000);
	m_28->d14(m_20 * x, m_24 * y + 13, 1, 1);
}
