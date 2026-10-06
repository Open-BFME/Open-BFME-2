// cl: /MD
// ??0Rva005CED37@@QAE@PBH@Z, retail 0x005CED37, 53 bytes.
// Outer holds new 0xC-byte vtable object g_00C751F8 with +4 refcount and
// +8 payload from *arg, stored to +0 with AddRef inc, returns this.
// Evidence: packet disassembly, push 0xC call ??2@YAPAXI@Z row,
// pop ecx clean, and [eax+4] 0, vtable store, jmp/xor null path,
// test mov je inc mov eax esi ret 4, prev/next Disp0DwordImmSetters,
// callers 0x005CEDFC/0x005CF523.
class Rva005CED37Held
{
public:
	virtual ~Rva005CED37Held();
	Rva005CED37Held(int const *v) : m_04(0) { m_08 = *v; }
	int m_04;
	int m_08;
};

class Rva005CED37
{
public:
	Rva005CED37(int const *arg);

private:
	Rva005CED37Held *m_00;
};

Rva005CED37::Rva005CED37(int const *arg)
{
	Rva005CED37Held *p = new Rva005CED37Held(arg);
	m_00 = p;
	if (p != 0)
		p->m_04++;
}
