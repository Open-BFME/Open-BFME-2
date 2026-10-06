// cl: /DNDEBUG /MD
// ?rva0039D889@Team@@QAEX_N@Z 0x0039D889 49 Team flag setter between 0x0039D84A and 0x0039D8BA
// Retail sets [esi+0x112]=1 when byte arg true else cleans list at esi+4 via rowed 0x0055B01F when [esi+0x113] nonzero then stores arg to [esi+0x113]. Callers at 0x004F16A2 0x004F170A 0x004F27A3 0x004F30F0. Neighbour TeamRva0039D8BA.cpp shares flags.
class Rva0055B0CC
{
public:
	void rva0055B01F();
};

class Team
{
public:
	void rva0039D889(bool flag);

private:
	unsigned char m_pad00[0x112];
	bool m_112;
	bool m_113;
};

void Team::rva0039D889(bool flag)
{
	if (flag)
		m_112 = true;
	else if (m_113)
		((Rva0055B0CC *)((char *)this + 4))->rva0055B01F();
	m_113 = flag;
}
