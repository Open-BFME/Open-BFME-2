// cl: /MD
// ?rva0035B164@Rva0035B164@@QAEHH@Z retail 0x0035B164 58B
// Three-slot fallback mapper over +0x84/+0x88/+0x8c with sentinel 5.
// Evidence: unlock lane, callers 0x00296749 0x0035B6FA, ecx-first thiscall.
class Rva0035B164
{
public:
	int rva0035B164(int v);

private:
	char m_pad[0x84];
	int m_84;
	int m_88;
	int m_8c;
};

int Rva0035B164::rva0035B164(int v)
{
	if (v == m_84) {
		if (m_88 == 5)
			return m_84;
		return m_88;
	}
	if (v == m_88) {
		if (m_8c == 5)
			return m_84;
		return m_8c;
	}
	if (v == m_8c)
		return m_84;
	return v;
}
