// cl: /MD
// ?rva0029B732@Rva0029B732@@QAE_NXZ @0x0029B732 24B.
// Null-guarded word check: returns (m_0 ? m_0->m_4 > 0 : false).
// Callers at 0x002A4C3A 0x002A4C49 0x002A4C58 0x002A4DF3.
struct Inner0029B732 {
	char m_pad[4];
	unsigned short m_4;
};
class Rva0029B732 {
public:
	bool rva0029B732();
private:
	Inner0029B732 *m_0;
};
bool Rva0029B732::rva0029B732()
{
	int v = m_0 ? m_0->m_4 : 0;
	return v > 0;
}
