// cl: /EHsc /Oy- /O1 /Ob2
// ?rva005CEDAF@Rva005CEDAF@@QBE?AURva005CEDAFHandle@@XZ, retail 0x005CEDAF, 69 bytes.
// Clone returning handle: allocates 0x20-byte refcounted object copying 24-byte payload from this via rep movsd, wraps in handle with AddRef.
// Evidence: packet disassembly push 0x20 call ??2 row pop ecx je and [eax+4] 0 push edi push 6 rep movsd jmp/xor null path test mov je inc mov eax ret 4, VTABLE slot 1 of table at 0x008751E8.
struct Rva005CEDAFHandle
{
	void *m_p;
	__forceinline Rva005CEDAFHandle(void *p) : m_p(p)
	{
		if (p != 0)
			((int *)p)[1]++;
	}
	~Rva005CEDAFHandle();
};

struct Rva005CEDAFPay
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
};

struct Rva005CEDAF
{
	virtual ~Rva005CEDAF();
	int m_ref;
	Rva005CEDAFPay m_pay;
	__forceinline Rva005CEDAF(const Rva005CEDAF &src) : m_ref(0), m_pay(src.m_pay) {}
	Rva005CEDAFHandle rva005CEDAF() const;
};

Rva005CEDAFHandle Rva005CEDAF::rva005CEDAF() const
{
	return Rva005CEDAFHandle(new Rva005CEDAF(*this));
}
