// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002D36C3@Rva002D36C3@@QAEXPAX@Z, retail 0x002D36C3 21B chain via rowed 0x0052518E.
// Null-guarded forwarder: inner = m_mid->m_c4; if inner call rowed setter with same arg; tail jmp.
// Evidence: callee ?rva0052518E@Rva0052518E@@QAEXPAX@Z rowed; caller 0x003BD29E; prev 0x002D3627 next 0x002D36D8 same /O1.
class Rva0052518E
{
public:
	void rva0052518E(void *p);
};

struct Rva002D36C3Mid
{
	char m_pad[0xC4];
	Rva0052518E *m_c4;
};

class Rva002D36C3
{
public:
	void rva002D36C3(void *p);
private:
	char m_pad[0x10];
	Rva002D36C3Mid *m_mid;
};

void Rva002D36C3::rva002D36C3(void *p)
{
	Rva0052518E *inner = m_mid->m_c4;
	if (inner != 0)
		inner->rva0052518E(p);
}
