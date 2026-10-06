// cl: /MD
// ??0Rva004D964E@@QAE@ABV0@@Z @0x004D964E (63B):
// Copy ctor: two Rva002390CB members via rowed copy ctor 0x2390CB plus four
// dwords plus byte. Evidence: push esi-edi plus two ??0 calls plus
// 0x10-0x1c dword copies plus 0x20 byte copy plus return-this ret-4;
// unblocks 0x004D9A44 0x004D971D; callers 0x004D9732 0x004D9A57.
class Rva002390CB
{
private:
	char m_pad[8];
public:
	__declspec(nothrow) Rva002390CB(const Rva002390CB &other);
};

class Rva004D964E
{
public:
	Rva004D964E(const Rva004D964E &other);
private:
	Rva002390CB m_00;
	Rva002390CB m_08;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	unsigned char m_20;
};

Rva004D964E::Rva004D964E(const Rva004D964E &other) : m_00(other.m_00), m_08(other.m_08)
{
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1c = other.m_1c;
	m_20 = other.m_20;
}
