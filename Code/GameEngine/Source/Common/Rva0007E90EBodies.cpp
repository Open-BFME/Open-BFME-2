// cl: /O1 /DNDEBUG /MD
struct TargetRef00217D4C { virtual void *destroy(unsigned flags); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva0007E90ECallee
{
public:
	void rva000FF5E6(int a);
};

class Rva0007E90EElem
{
public:
	int m_0;
	int m_ref;
	unsigned char m_pad[0xA0 - 8];
	unsigned char m_flag;
};

class Rva0007E90EHost
{
public:
	void rva0007E90E(int a);
	unsigned char m_pad[0x100];
	Rva0007E90ECallee *m_100;
	int m_104;
	Rva0007E90EElem **m_start;
	Rva0007E90EElem **m_end;
};

void Rva0007E90EHost::rva0007E90E(int a)
{
	if (m_100 != 0)
		m_100->rva000FF5E6(a);
	Rva0007E90EElem **pp = m_start;
	while (pp != m_end) {
		Rva0007E90EElem *e = *pp;
		if (e != 0)
			e->m_ref++;
		e->m_flag = 1;
		ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)e);
		++pp;
	}
}
