// cl: /DNDEBUG /MD
// ?rva0029B132@Rva0029B132@@QAEXXZ @0x0029B132 56B.
// Init: zeroes +0 +4 +8 +0xC +0x10 +0x14 +0x18, 1.0f from 0xBBB8D8 to +0x1C, 0x20 to +0x20. Caller 0x002A0FA4.
class Rva0029B132 {
public:
	Rva0029B132 *rva0029B132();
private:
	int m_0;
	float m_4;
	float m_8;
	int m_C;
	int m_10;
	float m_14;
	float m_18;
	float m_1C;
	int m_20;
};
Rva0029B132 *Rva0029B132::rva0029B132()
{
	m_4 = 0.0f;
	m_8 = 0.0f;
	m_14 = 0.0f;
	m_18 = 0.0f;
	float one = 1.0f;
	m_0 = 0;
	m_C = 0;
	m_1C = one;
	m_10 = 0;
	m_20 = 0x20;
	return this;
}
