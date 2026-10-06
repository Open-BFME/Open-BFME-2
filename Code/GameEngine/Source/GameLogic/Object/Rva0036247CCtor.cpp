// cl: /MD /EHsc /DNDEBUG
//
// ??0Rva0036247C@@QAE@XZ, retail 0x0036247C, 23 bytes. Leaf ctor storing
// vtable 0x00816FE8 at [this] and zeroing +0x04..+0x10. Prev is
// Rva003623E5MemberCtor.cpp with the same flags; next is
// SubsystemNameGetters4.cpp (TU default flags). Caller is unclaimed
// FUN_00762CF2 (51B) at 0x00362D4F.

class Rva0036247C
{
public:
	Rva0036247C();
private:
	const char *m_name;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0C;
	unsigned int m_10;
};

Rva0036247C::Rva0036247C()
	: m_name("s.v"),
	  m_04(0),
	  m_08(0),
	  m_0C(0),
	  m_10(0)
{
}
