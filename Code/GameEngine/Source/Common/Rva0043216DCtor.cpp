// cl: /MD
// ??0Rva0043216D@@QAE@XZ, retail 0x0043216D, 29 bytes.
// Ctor stores vtable 0x00C3C9C0 then zeroes +0x04..+0x10 dwords and +0x14..+0x15 bytes. Evidence: single vtable store, caller 0x0023A502, no donor.
class Rva0043216D
{
public:
	Rva0043216D();
	virtual void rva0043216DSlot0();
private:
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	unsigned char m_14;
	unsigned char m_15;
};

Rva0043216D::Rva0043216D()
	: m_04(0), m_08(0), m_0C(0), m_10(0), m_14(0), m_15(0)
{
}
