// cl: /O1 /MD
// ?rva001EDDC6@Rva001EDDC6@@QAEXE@Z @0x001EDDC6 57B: if m_4FA1 return else shift 0x4F9D..0x4FA0 and store arg plus flag. Evidence: caller 0x0051B48B plus prev 0x001EDDBB plus next 0x001EDDFF.
class Rva001EDDC6
{
public:
	void rva001EDDC6(unsigned char v);
private:
	char m_pad[0x4F9D];
	unsigned char m_4F9D;
	unsigned char m_4F9E;
	unsigned char m_4F9F;
	unsigned char m_4FA0;
	unsigned char m_4FA1;
};

void Rva001EDDC6::rva001EDDC6(unsigned char v)
{
	if (m_4FA1)
		return;
	m_4F9F = m_4F9D;
	m_4FA0 = m_4F9E;
	m_4F9E = v;
	m_4F9D = v;
	m_4FA1 = 1;
}
