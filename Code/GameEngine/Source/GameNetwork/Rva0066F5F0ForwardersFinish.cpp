// cl: /O2 /Ob1
// FESL browser factory secondary-base forwarders at 0x66F5F0/11, 0x66F600/12,
// 0x66F610/12, 0x66F620/12 (BFME1 donor T2MemberVirtualForwarders.cpp at
// 5cc75ddda6455c338a5068307e587a793f96d6b3, taken without header dependencies).
// Each native entry is INT3-bounded and independent: it reads this+0xC, takes
// the vptr at that raw object+4, adjusts ECX+4, then tail-jumps through its own
// slot 0/4/8/C. The four form secondary table 0x00CE3F08, installed at owner+4
// by the landed ctor 0x66F860 (FeslBrowserFactory_ctor.cpp) and dtor 0x66F8D0
// (Rva00803890FeslDtor.cpp). Those rows fix the +0xC slot and the +4
// adjustment as target facts; the void/no-argument shape of the forwarded slots
// is the donor's, not an independently proven target ABI, so no application
// identity is claimed for the far side. No vtable, ctor or dtor is emitted here.

struct Rva0066F5F0Slots
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
};

class Rva0066F5F0Secondary
{
public:
	void forward0();
	void forward1();
	void forward2();
	void forward3();

	unsigned char m_unobserved00[12];
	void *m_rawObject0C;
};

// ?Rva0066F5F0Secondary::forward0 present-unmatched
void Rva0066F5F0Secondary::forward0()
{
	reinterpret_cast<Rva0066F5F0Slots *>( static_cast<char *>( m_rawObject0C ) + 4 )->slot0();
}

// ?Rva0066F5F0Secondary::forward1 present-unmatched
void Rva0066F5F0Secondary::forward1()
{
	reinterpret_cast<Rva0066F5F0Slots *>( static_cast<char *>( m_rawObject0C ) + 4 )->slot1();
}

// ?Rva0066F5F0Secondary::forward2 present-unmatched
void Rva0066F5F0Secondary::forward2()
{
	reinterpret_cast<Rva0066F5F0Slots *>( static_cast<char *>( m_rawObject0C ) + 4 )->slot2();
}

// ?Rva0066F5F0Secondary::forward3 present-unmatched
void Rva0066F5F0Secondary::forward3()
{
	reinterpret_cast<Rva0066F5F0Slots *>( static_cast<char *>( m_rawObject0C ) + 4 )->slot3();
}