// cl: /MD
// Range-27 view-dispatch lookup.
// ?Rva0052BAC1@Holder0052BAC1@@QAEHH@Z @0x0052BAC1 61B
// Thiscall: answers arg unchanged when this+0x1C is null; otherwise runs
// the arg through the rowed view lookup 0x0020EAF6 on the 0x00DFEF10
// logic's +0xB0 view, answers -1 on a null lookup, else the +0x12C int of
// the 0x004FCA0C result built from this+0x1C and the lookup pointer.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva0020E89C;

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int index);
};

struct Logic0052BAC1
{
	char m_pad[0xB0];
	Rva0020EAF6View *m_B0;
};

struct Res004FCA0C
{
	char m_pad[0x12C];
	int m_12C;
};

struct Sub0052BAC1
{
	Res004FCA0C *Rva004FCA0C(Rva0020E89C *found);
};

struct Holder0052BAC1
{
	char m_pad[0x1C];
	Sub0052BAC1 *m_1C;
	int Rva0052BAC1(int arg);
};

int Holder0052BAC1::Rva0052BAC1(int arg)
{
	Sub0052BAC1 *sub = m_1C;
	if (sub != 0)
	{
		Rva0020E89C *found = (*(Logic0052BAC1 **)&TheLivingWorldLogic)->m_B0->rva0020EAF6(arg);
		if (found == 0)
			return -1;
		return sub->Rva004FCA0C(found)->m_12C;
	}
	return arg;
}
