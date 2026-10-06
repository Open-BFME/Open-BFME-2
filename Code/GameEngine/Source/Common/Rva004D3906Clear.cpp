// cl: /MD
//
// ?rva004D3906@Rva004D3906@@QAEXH@Z, retail 0x004D3906, 52 bytes.
// Flag-guarded clear: if +0xc already 1 return; else call rowed global
// shutdown 0x00512C88, set +0xc to 1, clear column i of the +0x30 byte
// matrix across 8 rows of stride 0x40, and zero +0x25c.
// Evidence: calls rowed 0x00512C88 at 0x004D390F; caller 0x004D48DB.
void Rva00512C88Shutdown();
class Rva004D3906
{
public:
	void rva004D3906(int i);
private:
	char m_pad00[0x0c];
	int m_0c;
	char m_pad10[0x30 - 0x10];
	unsigned char m_30[0x25c - 0x30];
	int m_25c;
};
void Rva004D3906::rva004D3906(int i)
{
	if (m_0c == 1)
		return;
	Rva00512C88Shutdown();
	m_0c = 1;
	unsigned char *p = &m_30[i * 8];
	for (int k = 8; k > 0; --k) {
		*p = 0;
		p += 0x40;
	}
	m_25c = 0;
}
