// ?Rva00526309@@YGXPAUObj00526309@@@Z
// partial score=0.95 date=2026-10-06
// cl: /O1 /MD
// ?Rva00526309@@YGXPAUObj00526309@@@Z @0x00526309 42B
// Flag dispatcher: if the +0x113 bit 2 is set run pinned 0x525CC5,
// else if the +0x119 bit 0x80 is set run pinned 0x525D9A.
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

void __stdcall Rva00525CC5(Obj00526309 *obj);
void __stdcall Rva00525D9A(Obj00526309 *obj);

void __stdcall Rva00526309(Obj00526309 *obj)
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
