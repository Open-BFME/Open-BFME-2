// cl: /DNDEBUG /MD
//
// ?rva00262271@Rva00262271@@QAEXHHH@Z, retail 0x00262271, 30 bytes.
// Thiscall leaf with three int-sized args: push arg3 then arg2 then FLT_MAX
// from global 0x00BBB8E0 through a reused push slot then arg1 into virtual
// slot 0x38. Outer ret 0x0C. Sibling of 0x0026228F (slot 0x34). Honest
// address-derived owner and name; slot identity unproven. No named callees.

extern float g_Va00BBB8E0;

#define Gbl00BBB8E0 g_Va00BBB8E0

class Rva00262271
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
	virtual void s38(int a, float f, int b, int c);
	void rva00262271(int a, int b, int c);
};

void Rva00262271::rva00262271(int a, int b, int c)
{
	s38(a, Gbl00BBB8E0, b, c);
}
