// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva007E3160Ready.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?ready@Rva007E3160@@QAEHXZ 0x0010688F (24B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

class Rva007E3160
{
public:
	virtual void v0();
	int ready();

private:
	void *m_04;
	int m_08;
};

// ?ready@Rva007E3160@@QAEHXZ
int Rva007E3160::ready()
{
	return m_04 && (m_08 == 6 || m_08 == 7);
}
