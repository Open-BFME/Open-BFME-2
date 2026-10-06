// cl: /O1 /MD
// Range-27 flag dispatcher.
// ?Rva00526309@Holder00526309@@QAEXPAUObj00526309@@@Z @0x00526309 42B
// Thiscall: this (ecx) passes straight through to the callee; the stack
// arg rides in edx. If the +0x113 bit 2 is set run 0x525CC5, else if the
// +0x119 bit 0x80 is set run 0x525D9A.
struct Flags00526309
{
	char m_pad[0x113];
	unsigned char m_113;
	char m_pad114[0x119 - 0x114];
	unsigned char m_119;
};

struct Obj00526309
{
	char m_pad[4];
	Flags00526309 *m_4;
};

struct Holder00526309
{
	void Rva00525CC5(Obj00526309 *obj);
	void Rva00525D9A(Obj00526309 *obj);
	void Rva00526309(Obj00526309 *obj);
};

void Holder00526309::Rva00526309(Obj00526309 *obj)
{
	Flags00526309 *flags = obj->m_4;
	if (flags->m_113 & 4)
	{
		Rva00525CC5(obj);
		return;
	}
	if (flags->m_119 & 0x80)
		Rva00525D9A(obj);
}
