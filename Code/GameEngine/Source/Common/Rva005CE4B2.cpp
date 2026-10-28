// cl: /MD
// ??0Rva005CE4B2@@QAE@PBH@Z, retail 0x005CE4B2, 53 bytes.
// Outer holds new 0xC-byte vtable object g_00C75140 with +4 refcount and
// +8 payload from *arg, stored to +0 with AddRef inc, returns this.
// Evidence: packet disassembly, push 0xC call ??2@YAPAXI@Z row,
// pop ecx clean, and [eax+4] 0, vtable store, jmp/xor null path,
// test mov je inc mov eax esi ret 4, prev Rva005CDF6CCtor /O1 /MD,
// callers 0x005CE4EF/0x005CE765/0x005CF0FB.
class Rva005CE4B2Held
{
public:
	// Declared inline and empty (as the rowed family template
	// Rva005CE259Ctor.cpp does) so the vtable this unit emits resolves in-TU:
	// 0x005CE4B2 is the rowed outer ctor row, and the held object's real dtor
	// is the empty ICF fold 0x004E84A4 that retail's vtable slot 0 reaches.
	virtual ~Rva005CE4B2Held() {}
	Rva005CE4B2Held(int const *v) : m_refCount(0) { m_08 = *v; }
	int m_refCount;
	int m_08;
};

class Rva005CE4B2
{
public:
	Rva005CE4B2(int const *arg);

private:
	Rva005CE4B2Held *m_00;
};

Rva005CE4B2::Rva005CE4B2(int const *arg)
{
	Rva005CE4B2Held *p = new Rva005CE4B2Held(arg);
	m_00 = p;
	if (p != 0)
		p->m_refCount++;
}
