// cl: /MD
//
// ?Rva005D2F96Build@@YA?AURva005D2F96S24@@ABURva005D2F96S16@@PBD@Z retail 0x005D2F96 58 bytes.
// ?Rva005E35F4Build@@YA?AURva005E35F4S32@@ABURva005D2F96S24@@PBD@Z retail 0x005E35F4 59 bytes.
// Free functions building concat nodes from a struct plus a text literal:
// copy the left struct to a local then store the Pair at local+leftsize then
// copy the whole local to the hidden return buffer. Same struct-concat family
// as rowed operator+ at 0x000B49C5 (12-byte AsciiStringPlusText from 4+8) and
// 0x00109CFD (16-byte AsciiStringCharPlusText from 8+8) and Rva005F17C6Build
// at 0x005F17C6 (16-byte S16 from 12+4). Callee Pair::init at 0x000B3F84 is
// rowed. Callers of 0x005D2F96 include 0x00238CFF 0x002D6320 0x005D3417
// 0x005D3496; callers of 0x005E35F4 include 0x005D3424 0x005D34A3. Honest
// address names.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair *init(const char *src);
	const char *m_ptr;
	int m_len;
};

struct Rva005D2F96S16
{
	int m0, m1, m2, m3;
};

struct Rva005D2F96S24
{
	int m0, m1, m2, m3, m4, m5;
};

struct Rva005E35F4S32
{
	int m0, m1, m2, m3, m4, m5, m6, m7;
};

struct Rva005D2F96S24 __cdecl Rva005D2F96Build(const struct Rva005D2F96S16 &src, const char *text)
{
	Rva000B3F84Pair p;
	p.init(text);
	struct Rva005D2F96S24 r;
	*(struct Rva005D2F96S16 *)&r = src;
	r.m4 = (int)p.m_ptr;
	r.m5 = p.m_len;
	return r;
}

struct Rva005E35F4S32 __cdecl Rva005E35F4Build(const struct Rva005D2F96S24 &src, const char *text)
{
	Rva000B3F84Pair p;
	p.init(text);
	struct Rva005E35F4S32 r;
	*(struct Rva005D2F96S24 *)&r = src;
	r.m6 = (int)p.m_ptr;
	r.m7 = p.m_len;
	return r;
}
