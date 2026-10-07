// cl: /MD /EHsc
// ?rva005D3FBD@Rva005D3FBD@@QAEX_N@Z retail 0x005D3FBD 39B
// Evidence: bit2 of byte +0x3C from bool arg clearing bit3; callers 0x0057A488 0x0057A7B0
class Rva005D3FBD
{
public:
	unsigned char rva005D3FB4() const;
	void rva005D3FBD(bool v);
private:
	char m_pad[0x3C];
	union {
		unsigned char m_flags;
		struct {
			unsigned char m_b0 : 1;
			unsigned char m_b1 : 1;
			unsigned char m_b2 : 1;
			unsigned char m_rest : 5;
		};
	};
};

unsigned char Rva005D3FBD::rva005D3FB4() const
{
	return m_b2;
}

void Rva005D3FBD::rva005D3FBD(bool v)
{
	unsigned char cur = (unsigned char)((m_flags >> 2) & 1);
	if (v != cur) {
		unsigned char nv = (unsigned char)((v & 1) << 2);
		m_flags = (unsigned char)((m_flags & 0xF3) | nv);
	}
}
