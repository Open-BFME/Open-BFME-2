// cl: /MD
// ?rva005FC19E@Rva005FC19E@@QAEXH@Z retail 0x005FC19E 8B
// Evidence: chain tail forwarder to rowed 0x005FBFE5 via +0x04 with same int arg; caller 0x005EA4E8; prev shares // cl: /O1 /MD
class Rva005FBFE5
{
public:
	void rva005FBFE5(int v);
};

class Rva005FC19E
{
public:
	void rva005FC19E(int v);
private:
	char m_pad00[4];
	Rva005FBFE5 *m_04;
};

void Rva005FC19E::rva005FC19E(int v)
{
	m_04->rva005FBFE5(v);
}
