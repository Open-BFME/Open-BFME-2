// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ?rva0030B055@Rva0030B055@@QAEXXZ, retail 0x0030B055, 37 bytes.
// Four virtual calls slots 3 8 6 9 with 0 0 then 0 then get then forward.
// Evidence: caller 0x0030B0E3 ctor stores vtable then calls; unblocks 0x0030B0E3.
class Rva0030B055
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
	void rva0030B055();
};
void Rva0030B055::rva0030B055()
{
	v3(0, 0);
	v8(0);
	v9(v6());
}
