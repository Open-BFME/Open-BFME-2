// cl: /MD
// ?rva00285672@Rva00285672@@QBE_NABV1@@Z @ 0x00285672 42B
// Lexicographic less on two dwords at +8/+0xC. Callers at 0x00286227 0x0028624A
// 0x002868AC 0x00286E52 0x00286E8E pass node+0x10 as this and key+0x10 as arg
// and test al. RB-tree key compare feeding 0x00286214 0x0028688A 0x00286E33.
class Rva00285672
{
public:
	bool rva00285672(const Rva00285672 &other) const;
	char m_lead[8];
	int m_first;
	int m_second;
};
bool Rva00285672::rva00285672(const Rva00285672 &other) const
{
	if (m_first < other.m_first)
		return true;
	if (m_first > other.m_first)
		return false;
	return m_second < other.m_second;
}
