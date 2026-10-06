// cl: /MD
// ?rva004DFA0E@Rva004DFA0E@@QAEXPAX0@Z @0x004DFA0E 53B
// __thiscall guarded triple dispatch: if second arg ptr byte+1 >=2, builds
// TwoBytes{1,1} by reusing dead arg slot at [ebp+0xC] (no new stack), calls
// holder vtable+0x28 with it, then this+0xC Rva00596389::rva0059640C(holder).
// EBP frame, ret8, slot reuse gives lea/mov at +0xC not +0xE.
// Evidence: mov eax[ebp+C] cmp [eax+1]2 jb; push esi edi; mov esi[ebp+8];
// lea [ebp+C] push mov ecx esi mov [ebp+C]1 [ebp+D]1 call [eax+28];
// mov ecx[edi+C] push esi call 0x59640C; ret8. Caller at 0x002A8CB2.
class Holder
{
public:
	virtual void v00(void *);
	virtual void v01(void *);
	virtual void v02(void *);
	virtual void v03(void *);
	virtual void v04(void *);
	virtual void v05(void *);
	virtual void v06(void *);
	virtual void v07(void *);
	virtual void v08(void *);
	virtual void v09(void *);
	virtual void v10(void *);
};
struct TwoBytes
{
	unsigned char a;
	unsigned char b;
};
class Rva00596389
{
public:
	void rva0059640C(void *holder);
};
class Rva004DFA0E
{
public:
	void rva004DFA0E(void *holder, void *ptr);
private:
	char m_pad[12];
	Rva00596389 *m_0C;
};
void Rva004DFA0E::rva004DFA0E(void *holder, void *ptr)
{
	if (((unsigned char *)ptr)[1] >= 2)
	{
		TwoBytes *t = (TwoBytes *)&ptr;
		t->a = 1;
		t->b = 1;
		((Holder *)holder)->v10(t);
		m_0C->rva0059640C(holder);
	}
}
