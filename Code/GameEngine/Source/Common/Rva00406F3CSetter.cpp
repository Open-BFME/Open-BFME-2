// cl: /MD
// ?rva00406F3C@Rva00406F3C@@QAE_NH@Z @0x00406F3C 21B: conditional setter comparing +0x34 and setting bit 8 at +0x38. Sibling of 0x00406F27. Owner unknown so honest-address name.
class Rva00406F3C
{
	int m_00[13];
	int m_34;
	int m_38;
public:
	bool rva00406F3C(int v);
};
bool Rva00406F3C::rva00406F3C(int v)
{
	if (m_34 != v) {
		m_38 |= 8;
		m_34 = v;
	}
	return true;
}
