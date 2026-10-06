// cl: /DNDEBUG /MD
// ?rva005E1C6F@Rva005E1C6F@@QAEXPAX@Z @ 0x005E1C6F (46B). Scan TreeHintRef vector at this+0x14
// for entries whose m_target matches arg, erase via rowed 0x004F70D1 and set byte at +0x20.
// Evidence: ret 4 one ptr arg, begin [this+0x14] end [this+0x18], callers 0x005E1CFF, chain from 0x004F70D1.
struct TreeHintRef00217D4C
{
	void *m_target;
};

class Rva004F70D1
{
public:
	TreeHintRef00217D4C *rva004F70D1(TreeHintRef00217D4C *pos);
};

class Rva005E1C6F
{
public:
	void rva005E1C6F(void *target);
private:
	char m_pad[20];
	TreeHintRef00217D4C *m_begin;
	TreeHintRef00217D4C *m_end;
	TreeHintRef00217D4C *m_eos;
	unsigned char m_20;
};

void Rva005E1C6F::rva005E1C6F(void *target)
{
	for (TreeHintRef00217D4C *it = m_begin; it != m_end; ++it) {
		if (it->m_target == target) {
			((Rva004F70D1 *)&m_begin)->rva004F70D1(it);
			m_20 = 1;
		}
	}
}
