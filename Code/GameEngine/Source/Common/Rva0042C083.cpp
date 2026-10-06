// cl: /EHsc /MD
// ?rva0042C083@Rva0042C083@@QAEXPBURva0042C083Param@@@Z @0x0042C083 31B via two-dword copy plus flag set
// Evidence: stores [ecx+0x8c] [ecx+0x90] from [eax] [eax+4] plus byte [ecx+0x94]=1; callers 0x0042C134 0x0042C7D5; unblocks 0x0042C7B1 0x0042C0DB
struct Rva0042C083Param
{
	int m_00;
	int m_04;
};

class Rva0042C083
{
public:
	void rva0042C083(const Rva0042C083Param *p);
private:
	char m_pad00[0x8C];
	int m_8C;
	int m_90;
	unsigned char m_94;
};

void Rva0042C083::rva0042C083(const Rva0042C083Param *p)
{
	m_8C = p->m_00;
	m_90 = p->m_04;
	m_94 = 1;
}
