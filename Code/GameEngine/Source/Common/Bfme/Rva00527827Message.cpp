// ?rva00527827@Rva00527827@@QAEXHPBMHH@Z, retail 0x00527827, 87 bytes (RET 0x10).
// Address-derived name and layout view of the witnessed offsets only: the mode
// word at +0xC selects the handling. Mode 1 rounds the float behind the second
// argument half-up and stores at least 1 at +0x18; modes 3 and 4 forward the
// first two arguments to the object at +0x1C when set (slot-2 forwarder
// 0x005CC208, pinned by the ledger under its Obj00527827 spelling).
class Obj00527827
{
public:
	void Rva005CC208(int a, int b);
};

class Rva00527827
{
public:
	void rva00527827(int a, const float *b, int c, int d);
private:
	char m_pad0[0xC];
	int m_mode;
	char m_pad10[0x18 - 0x10];
	int m_18;
	Obj00527827 *m_1C;
};

void Rva00527827::rva00527827(int a, const float *b, int c, int d)
{
	if (m_mode == 1)
	{
		int one = 1;
		int v = (int)(*b + 0.5f);
		const int *m = v < one ? &one : &v;
		m_18 = *m;
	}
	else if (m_mode == 3 || m_mode == 4)
	{
		if (m_1C != 0)
			m_1C->Rva005CC208(a, (int)b);
	}
}
