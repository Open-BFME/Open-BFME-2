// cl: /MD /EHsc /DNDEBUG
//
// ??0Rva0009AA0F@@QAE@H@Z @0x0009AA0F 30B: derived constructor taking one
// int/pointer stored at +0x108, then installing vtable 0x00BC8900. Calls
// the pinned 563B base constructor 0x00142960 first. Honest
// address-derived names on both sides; boundary verified (push esi at
// 0x9AA0F, pop esi + ret 4 at end).

class Rva00142960Base
{
public:
	Rva00142960Base();
	virtual ~Rva00142960Base();

private:
	char m_pad04[0x108 - 4];
};

class Rva0009AA0F : public Rva00142960Base
{
public:
	Rva0009AA0F(int v);
	virtual ~Rva0009AA0F();

private:
	int m_108;
};

// ??0Rva0009AA0F@@QAE@H@Z
Rva0009AA0F::Rva0009AA0F(int v)
{
	m_108 = v;
}
