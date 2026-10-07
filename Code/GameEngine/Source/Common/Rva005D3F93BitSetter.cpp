// cl: /MD
class Rva005D3F93
{
public:
	unsigned char rva005D3F8D() const;
	void rva005D3F93(bool v);
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

unsigned char Rva005D3F93::rva005D3F8D() const
{
	return m_b0;
}

void Rva005D3F93::rva005D3F93(bool v)
{
	unsigned char cur = (unsigned char)(m_flags & 1);
	if (v != cur) {
		unsigned char nv = (unsigned char)(v & 1);
		m_flags = (unsigned char)((m_flags & 0xFC) | nv);
	}
}
