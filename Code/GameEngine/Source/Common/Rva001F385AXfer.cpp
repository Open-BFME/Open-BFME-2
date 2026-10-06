// cl: /MD

// ?rva001F385A@Rva001F385A@@QAEXPAX@Z, RVA 0x001F385A, 63B.
// Unlock lane: no callees (frameless SSE copy, memcpy inlined as movsd).
// Callers at 0x003A5ABF/0x0055F041/0x005640AA/0x0056461C.
// Copies three floats from this+0xF8/+0x108/+0x118 (via sub at +0xEC
// with +0xC/+0x1C/+0x2C) to out (12B) when out is non-null.

extern "C" void *memcpy(void *dst, const void *src, unsigned int n);
#pragma intrinsic(memcpy)

struct Rva001F385ASub
{
	char m_pad0[0x0C];
	float m_0c;
	char m_pad1[0x1C - 0x0C - 4];
	float m_1c;
	char m_pad2[0x2C - 0x1C - 4];
	float m_2c;
};

class Rva001F385A
{
public:
	void rva001F385A(void *out);

private:
	char m_pad[0xEC];
	Rva001F385ASub m_sub;
};

void Rva001F385A::rva001F385A(void *out)
{
	Rva001F385ASub *sub = (Rva001F385ASub *)((char *)this + 0xEC);
	float buf[3];
	buf[0] = sub->m_0c;
	buf[1] = sub->m_1c;
	buf[2] = sub->m_2c;
	if (out)
		memcpy(out, buf, 12);
}
