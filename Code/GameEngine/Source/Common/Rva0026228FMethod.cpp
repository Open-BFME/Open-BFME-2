// cl: /DNDEBUG /MD
//
// ?rva0026228F@Rva0026228F@@QAEXHH@Z, retail 0x0026228F, 26 bytes.
// Thiscall leaf with two int-sized args: push arg2 then FLT_MAX from global
// 0x00BBB8E0 through a reused push slot then arg1 into virtual slot 0x34.
// Outer ret 8. Honest address-derived owner and name; slot identity unproven.
// No direct named callees.

extern float g_Va00BBB8E0;

#define Gbl00BBB8E0 g_Va00BBB8E0

class Rva0026228F
{
public:
	virtual void s00();
	virtual void s04();
	virtual void s08();
	virtual void s0C();
	virtual void s10();
	virtual void s14();
	virtual void s18();
	virtual void s1C();
	virtual void s20();
	virtual void s24();
	virtual void s28();
	virtual void s2C();
	virtual void s30();
	virtual void s34(int a, float f, int b);
	void rva0026228F(int a, int b);
};

void Rva0026228F::rva0026228F(int a, int b)
{
	s34(a, Gbl00BBB8E0, b);
}
