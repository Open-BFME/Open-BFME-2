// cl: /MD /Oy-
//
// ?rva001F510D@Rva001F510D@@QAEMXZ, retail 0x001F510D, 34 bytes.
// Null-checked float getter via holder at +0x1B8 and virtual slot +0x10,
// 0.0f fallback via SSE/x87. Siblings Rva001F4E1BGet. Callers
// 0x1F74F6/0x55F061. Honest Rva names.
// The 0.0f fallback is the false arm of a conditional expression, which
// retail materialises with xorps and a stack round-trip on the null path
// only; the banked attempt used a volatile local.

class Rva001F510DHelper
{
public:
	virtual ~Rva001F510DHelper();
	virtual void u1();
	virtual void u2();
	virtual void u3();
	virtual float get();
};

class Rva001F510D
{
public:
	float rva001F510D();
private:
	char m_pad00[0x1B8];
	Rva001F510DHelper *m_ptr;
};

float Rva001F510D::rva001F510D()
{
	Rva001F510DHelper *p = m_ptr;
	return p != 0 ? p->get() : 0.0f;
}
