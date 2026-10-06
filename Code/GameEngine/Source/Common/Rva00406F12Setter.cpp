// cl: /MD
// ?rva00406F12@Rva00406F12@@QAE_NH@Z @0x00406F12 21B: conditional setter comparing +0x2C and setting bit 8 at +0x38. Sibling of 0x00406EFD. Owner unknown so honest-address name.
class Rva00406F12
{
	int m_00[11];
	int m_2C;
	int m_30[2];
	int m_38;
public:
	bool rva00406F12(int v);
};
bool Rva00406F12::rva00406F12(int v)
{
	if (m_2C != v) {
		m_38 |= 8;
		m_2C = v;
	}
	return true;
}
