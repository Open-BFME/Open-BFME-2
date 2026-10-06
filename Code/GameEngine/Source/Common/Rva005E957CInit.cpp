// cl: /MD
// ?rva005E957C@Rva005E957C@@QAEXHHHHHH@Z, retail 0x005E957C, 44 bytes.
// 6-dword init: copies 6 stack args to +0..+20; ret 0x18.
// Callers 0x003F5242 and 0x005E9AED pass 6 dwords to a 24-byte local.
class Rva005E957C
{
public:
	Rva005E957C *rva005E957C(int a1, int a2, int a3, int a4, int a5, int a6);
	void rva005E95E9();
private:
	int m_0; // +0
	int m_1; // +4
	int m_2; // +8
	int m_3; // +12
	int m_4; // +16
	int m_5; // +20
};

struct Rva005FD8C1
{
	void rva005FD8C1();
};

struct Rva005E95E9Iface
{
	virtual void f0();
	virtual void f1();
};

struct Rva005E95E9Wrap
{
	Rva005E95E9Iface *m_iface; // +0
};

Rva005E957C *Rva005E957C::rva005E957C(int a1, int a2, int a3, int a4, int a5, int a6)
{
	m_0 = a1;
	m_1 = a2;
	m_2 = a3;
	m_3 = a4;
	m_4 = a5;
	m_5 = a6;
	return this;
}

// ?rva005E95E9@Rva005E957C@@QAEXXZ @0x005E95E9 24B
// Chain from just-landed 0x005FD8C1 forwarder: call it on this, then virtual slot1
// through +8 wrapper's iface, then clear byte +0x10. Retail: push esi mov esi,ecx
// call 0x5fd8c1, mov eax,[esi+8] mov ecx,[eax] mov eax,[ecx] call [eax+4],
// mov byte [esi+10h],0.
void Rva005E957C::rva005E95E9()
{
	((Rva005FD8C1 *)this)->rva005FD8C1();
	Rva005E95E9Wrap *w = *(Rva005E95E9Wrap **)((char *)this + 8);
	w->m_iface->f1();
	*(unsigned char *)((char *)this + 0x10) = 0;
}
