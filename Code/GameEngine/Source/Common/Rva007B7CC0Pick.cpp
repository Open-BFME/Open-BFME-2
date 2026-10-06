// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva007B7CC0Pick.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?pick@Rva007B7CC0Pick@@QAEPAURva007B7CC0Target@@E@Z 0x000EFA35 (25B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

struct Rva007B7CC0Target
{
	int m_pad;
	int m_refs;
};

class Rva007B7CC0Pick
{
public:
	Rva007B7CC0Target *pick(unsigned char flag);

	char m_pad[0x30];
	Rva007B7CC0Target *m_30;
	Rva007B7CC0Target *m_34;
};

Rva007B7CC0Target *Rva007B7CC0Pick::pick(unsigned char flag)
{
	Rva007B7CC0Target *target;
	if (flag)
		target = m_34;
	else
		target = m_30;
	if (target)
		++target->m_refs;
	return target;
}
