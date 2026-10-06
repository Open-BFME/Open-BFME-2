// cl: /MD
//
// ??1Rva0039205C@@QAE@XZ 26B @0x0039205C: dtor for outer holder of
// Rva004D9A3C array at +8 with dword at +0: vector-deletes the array via
// rowed ??_E at 0x00392011 (flag 3) then zeroes +8 and +0. Chain lane:
// calls 0x00392011 just landed so every callee resolves. Evidence: mov
// ecx [esi+8] plus test plus je plus push 3 plus call 0x392011 plus and
// [esi+8] 0 plus and [esi] 0 plus ret, callers at 0x002A2625 0x002A2B4C
// 0x003920A2 0x00392282 0x0039228D 0x00393200 0x00596EA4 0x00596ED8.

void operator delete[](void *p);

class Rva004D9A3C
{
public:
	~Rva004D9A3C();
private:
	char m_pad[0x1C];
};

class Rva0039205C
{
public:
	~Rva0039205C();
private:
	int m_unk00; // +0
	unsigned char m_pad04[4]; // +4
	Rva004D9A3C *m_array08; // +8
};

// ??1Rva0039205C@@QAE@XZ
Rva0039205C::~Rva0039205C()
{
	if (m_array08)
	{
		delete[] m_array08;
		m_array08 = 0;
		m_unk00 = 0;
	}
}
