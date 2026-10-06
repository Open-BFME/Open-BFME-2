// cl: /EHsc /MD
// ??0Rva003F7EC7@@QAE@H@Z @0x003F7E9D 42B
// Ctor storing vtable 0x008372D4 then arg at +4 zeroing +8/+10/+14/+18/+19
// and 1 at +0xC. Evidence: caller 0x003F90A1 pushes [esi+4] then calls;
// alloc 0x1C matches layout to +0x19; neighbour dtor Rva003F7EC7Dtor same flags.
class Rva003F7EC7
{
public:
	virtual ~Rva003F7EC7();
	Rva003F7EC7(int v);
	int m_04;
	void *m_08;
	int m_0C;
	void *m_10;
	void *m_14;
	unsigned char m_18;
	unsigned char m_19;
};

Rva003F7EC7::Rva003F7EC7(int v)
	: m_04(v)
	, m_08(0)
	, m_0C(1)
	, m_10(0)
	, m_14(0)
	, m_18(0)
	, m_19(0)
{
}
