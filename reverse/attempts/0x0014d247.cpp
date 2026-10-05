// ?rva0014D247@Rva0014D247Holder@@QAEXPAVRva0014D247Other@@@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
//
// ?rva0014D247@Rva0014D247Holder@@QAEXPV2@0@Z placeholder (renamed below).
// @0x0014D247 71B void, straight-line, 1 pin, no EH/floats/branches.
// Retail (this=esi Holder, 1 arg Other* ret 4): char tmp10[0x10] at ebp-0x10;
// callee = this->rva000717B40(arg, &tmp) via pin 0x000717B40 (returns 16B*);
// this->[0..0xC] = ret->[0..0xC] (4 DWORDs); this->[0x10]=arg->[0xC];
// this->[0x14]=arg->[0x1C]; this->[0x18]=arg->[0x2C].
// Names opaque; pin proves nothing.
class Rva0014D247Other
{
public:
	char m_pad00[0x0C];
	int m_0C; // +0x0C
	char m_pad10[0x1C - 0x10];
	int m_1C; // +0x1C
	char m_pad20[0x2C - 0x20];
	int m_2C; // +0x2C
};

class Rva0014D247Holder
{
public:
	void *rva000717B40(void *a, void *b);
	void rva0014D247(Rva0014D247Other *o);
	int m_00; // +0x00
	int m_04; // +0x04
	int m_08; // +0x08
	int m_0C; // +0x0C
	int m_10; // +0x10
	int m_14; // +0x14
	int m_18; // +0x18
};

void Rva0014D247Holder::rva0014D247(Rva0014D247Other *o)
{
	char tmp[0x10];
	int *r = (int *)rva000717B40(tmp, o);
	m_00 = r[0];
	m_04 = r[1];
	m_08 = r[2];
	m_0C = r[3];
	m_10 = o->m_0C;
	m_14 = o->m_1C;
	m_18 = o->m_2C;
}
