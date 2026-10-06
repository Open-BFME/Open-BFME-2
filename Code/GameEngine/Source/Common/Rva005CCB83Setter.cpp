// cl: /MD
// ?rva005CCB83@Rva005CCB83@@QAEXPAX@Z @0x005CCB83 13B ptr-chase setter stores arg at inner +0x10. Evidence: ret 4 plus callers 0x005285EF 0x005D1BA1 0x005D1DCB 0x005D2184 plus prev 0x005CCB6B next 0x005CCB90 plus LINK 0x005285EF.
struct Rva005CCB83Inner
{
	char m_pad[0x10];
	void *m_10;
};
class Rva005CCB83
{
public:
	void rva005CCB83(void *p);
	char m_lead[8];
	Rva005CCB83Inner *m_ptr;
};
void Rva005CCB83::rva005CCB83(void *p)
{
	m_ptr->m_10 = p;
}
