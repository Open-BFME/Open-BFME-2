// cl: /O1 /MD
class Rva005D3F93
{
public:
	void rva005D3F93(bool v);
private:
	char m_pad[0x3C];
	unsigned char m_flags;
};
void Rva005D3F93::rva005D3F93(bool v)
{
	unsigned char cur = (unsigned char)(m_flags & 1);
	if (v != cur) {
		unsigned char nv = (unsigned char)(v & 1);
		m_flags = (unsigned char)((m_flags & 0xFC) | nv);
	}
}
