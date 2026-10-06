// cl: /MD /Oi-
// ?rva005427F1@Rva005427F1@@QAEXXZ @0x005427F1 21B
// Flush pending output byte: if +0x20 non-null store +0x24 byte there then clear both. Evidence: retail bytes unlock lane plus neighbours Rva005426DBDecode and Rva00542806Init same +0x20/+0x24 layout.
class Rva005427F1
{
public:
	void rva005427F1();
private:
	char m_pad[0x20];
	char *m_out;
	unsigned char m_ch;
};

void Rva005427F1::rva005427F1()
{
	if (m_out != 0) {
		*m_out = (char)m_ch;
		m_out = 0;
		m_ch = 0;
	}
}
