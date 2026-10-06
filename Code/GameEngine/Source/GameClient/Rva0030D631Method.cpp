// cl: /Ireference/shims/bfme2_ascii
// ?rva0030D631@Rva0030D631@@QAEPAVBfmeRetBWF@@XZ, retail 0x0030D631, 42B.
// Gap between 0x0030D606 and 0x0030D773: thiscall returning BfmeRetBWF pointer.
// Null holder returns +0x08 source; else BfmeCalcBWF at holder+0xa0 transforms +0x08 into +0x48 via rowed 0x006BD900 and returns +0x48.
// Evidence: packet disasm plus rowed bfmeCalcBWF plus callers 0x000921F7 0x000DD4E5 plus prev/next cl lines.
class BfmeRetBWF
{
public:
	float x;
	float y;
	float z;
};

class BfmeCalcBWF
{
public:
	bool bfmeCalcBWF(BfmeRetBWF *one, float value, BfmeRetBWF *two);
private:
	char pad[8];
	float m_field0x8;
	float m_field0xc;
};

struct Rva0030D631Holder
{
	char m_pad[0xa0];
	BfmeCalcBWF m_calc;
};

class Rva0030D631
{
public:
	BfmeRetBWF *rva0030D631();
private:
	char m_pad0[8];
	BfmeRetBWF m_8;
	char m_pad1[4];
	Rva0030D631Holder *m_holder;
	float m_angle;
	char m_pad2[0x28];
	BfmeRetBWF m_48;
};

BfmeRetBWF *Rva0030D631::rva0030D631()
{
	if (m_holder != 0)
	{
		m_holder->m_calc.bfmeCalcBWF(&m_8, m_angle, &m_48);
		return &m_48;
	}
	return &m_8;
}
