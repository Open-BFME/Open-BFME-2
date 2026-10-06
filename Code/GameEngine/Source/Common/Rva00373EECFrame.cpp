// cl: /DNDEBUG /MD
//
// ?rva00373EEC@Rva00373EEC@@QAEXI@Z @0x00373EEC 48B:
// Frame-horizon max store: holder at +0x04 (value at +0x08), stored frame at
// +0x24, base frame from TheGameLogic+0x40 (rowed extern
// ?TheGameLogic@@3PAVGameLogic@@A). Zero arg overwrites, nonzero keeps the
// max (unsigned cmp jae). Callers at 0x003747FF plus 0x00375730.
class GameLogic
{
public:
	char m_pad40[0x40];
	unsigned int m_40;
};

extern GameLogic *TheGameLogic;

struct Rva00373EECSub
{
	char m_pad[8];
	unsigned int m_8;
};

class Rva00373EEC
{
public:
	void rva00373EEC(unsigned int v);
private:
	char m_pad0[4];
	Rva00373EECSub *m_ptr; // +0x04
	char m_pad1[0x24 - 0x08];
	unsigned int m_24; // +0x24
};

void Rva00373EEC::rva00373EEC(unsigned int v)
{
	if (m_ptr == 0)
		return;
	unsigned int base = TheGameLogic->m_40;
	if (v == 0)
		m_24 = m_ptr->m_8 + base;
	else {
		unsigned int nv = base + v;
		if (m_24 < nv)
			m_24 = nv;
	}
}
