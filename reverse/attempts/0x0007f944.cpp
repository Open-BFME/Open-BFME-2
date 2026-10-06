// ?rva0007F944@Rva0007F944Host@@QAEMMM@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE
struct Rva0007F944Vec
{
	float x;
	float y;
	float z;
};

struct Rva0007F944Inner
{
	unsigned char m_pad[8];
	float h;
};

class Rva0007F944Item
{
public:
	unsigned char m_pad[0x14];
	Rva0007F944Inner *m_p;
	bool rva0007ECA3(const Rva0007F944Vec *v);
};

class Rva0007F944Host
{
public:
	unsigned char m_pad[0x108];
	Rva0007F944Item **m_begin;
	Rva0007F944Item **m_end;
	float rva0007F944(float a, float b);
};

float Rva0007F944Host::rva0007F944(float a, float b)
{
	Rva0007F944Vec v = { a, b, 0.0f };
	float best = 0.0f;
	Rva0007F944Item **begin = m_begin;
	Rva0007F944Item **end = m_end;
	for (Rva0007F944Item **p = begin; p != end; ++p) {
		Rva0007F944Item *o = *p;
		float h = o->m_p->h;
		if (h > best && o->rva0007ECA3(&v))
			best = h;
	}
	return best;
}
