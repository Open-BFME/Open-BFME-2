// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva007B8190InitCtor.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ??0Rva007B8190Init@@QAE@XZ 0x000EFD4B (44B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

class Rva007B8190Init
{
public:
	Rva007B8190Init();

	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2c;
	unsigned char m_30;
};

Rva007B8190Init::Rva007B8190Init()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0c = 0xffffffff;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
	m_24 = 0;
	m_28 = 0;
	m_2c = 0;
	m_30 = 0;
}
