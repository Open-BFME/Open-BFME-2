// cl: /MD
// ?rva00406F27@Rva00406F27@@QAE_NH@Z @0x00406F27 21B: conditional setter comparing +0x30 and setting bit 8 at +0x38. Sibling of 0x00406F12. Owner unknown so honest-address name.
class Rva00406F27
{
	int m_00[12];
	int m_30;
	int m_34;
	int m_38;
public:
	bool rva00406F27(int v);
};
bool Rva00406F27::rva00406F27(int v)
{
	if (m_30 != v) {
		m_38 |= 8;
		m_30 = v;
	}
	return true;
}
