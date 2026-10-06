// cl: /MD
// ?rva001E6731@Rva001E6731@@QAEXXZ @0x001E6731 41B chain via rowed rva001E4954
// __thiscall clear: if m_04==0 return else destroy m_00->m_04 via rowed 0x001E4954 then reset m_00 links and m_04.
// Evidence: calls rowed 0x001E4954 with [eax+4]; and [m],0 idiom; callers 0x001E6773 0x001E6F3C 0x001E7305; unblocks 0x001E675A 0x001E72B4.
struct Rva001E4954Node
{
	char _00[8];
	struct Rva001E4954Node *m_08;
	struct Rva001E4954Node *m_0c;
};
class Rva001E4954
{
public:
	void rva001E4954(Rva001E4954Node *p);
};
struct Rva001E6731Head
{
	int _00;
	Rva001E4954Node *m_04;
	struct Rva001E6731Head *m_08;
	struct Rva001E6731Head *m_0c;
};
class Rva001E6731
{
public:
	void rva001E6731();
private:
	Rva001E6731Head *m_00;
	int m_04;
};
void Rva001E6731::rva001E6731()
{
	if (m_04 == 0)
		return;
	((Rva001E4954 *)this)->rva001E4954(m_00->m_04);
	m_00->m_08 = m_00;
	m_00->m_04 = 0;
	m_00->m_0c = m_00;
	m_04 = 0;
}
