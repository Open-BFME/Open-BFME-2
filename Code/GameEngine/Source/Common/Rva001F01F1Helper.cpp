// cl: /DNDEBUG /MD
//
// ?create@ApplyRandomForceNugget@@... @0x001F01F1 86B.
// Tiny x87 float helper (ObjectCreationNugget neighbourhood, per the range
// notes): null-checks the param at [ebp+8] and its +0x25C object pointer,
// spills this+4..this+16 as four floats through the unrowed cdecl helper at
// 0x001F0247 into a stack float, then issues the unrowed thiscall at
// 0x003909FA on the +0x25C object with (&buf, 0, 0). Evidence (target facts
// read from game.dat): ret 0xC with only [ebp+8] read (trailing 8 bytes are
// dead params, kept as ints); fld/fstp order is this+16 first; caller
// cleanup add esp,0x14 proves the 0x001F0247 call takes 5 stack args with
// ecx untouched (cdecl spelling, pinned); the 0x003909FA call is a direct
// E8 with ecx=esi (thiscall spelling on an opaque struct, pinned). The +0x0
// word of this and the strict types of the dead params are unproven.
struct Rva003909FAObj
{
	void consume(void *buf, int a, int b);
};

void __cdecl rva001F0247(float a, float b, float c, float d, void *out);

struct Rva001F01F1Param
{
	char m_pad[0x25C];
	Rva003909FAObj *m_obj;
};

class ApplyRandomForceNugget
{
public:
	int m_00;
	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	void create(Rva001F01F1Param *p, int, int);
};

void ApplyRandomForceNugget::create(Rva001F01F1Param *p, int, int)
{
	if (p == 0)
		return;
	Rva003909FAObj *obj = p->m_obj;
	if (obj == 0)
		return;
	float buf[3];
	rva001F0247(m_04, m_08, m_0C, m_10, buf);
	obj->consume(buf, 0, 0);
}
