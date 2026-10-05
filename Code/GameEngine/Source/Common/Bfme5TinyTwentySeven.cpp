// cl: /O1
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Bfme5TinyTwentySeven.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeReset@@YAXXZ 0x00309E30 (27B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Five more: two flag tests, a three-word block handed out through a pointer,
// a thirty-six byte copy between two globals, and a mask built from two flags.

class Gen_0040B9E0
{
public:
	int bfmeReady(void) const;

private:
	int m_bfmeHead[7];					// +0x00
	bool m_bfmeEnabled;					// +0x1C
	char m_bfmeGap[0x8B];					// +0x1D
	int m_bfmeMode;						// +0xA8
};

// ?bfmeReady@Gen_0040B9E0@@QBEHXZ

class BfmeTripleCU
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	int m_bfmeThird;					// +0x08
};

class Gen_004108D0
{
public:
	BfmeTripleCU bfmeGetTriple(void) const;

private:
	int m_bfmeHead[11];					// +0x00
	BfmeTripleCU m_bfmeTriple;				// +0x2C
};

// The triple comes back by value: the hidden return slot arrives as the
// argument and has to stay in eax, so the copy runs through its own register.
// ?bfmeGetTriple@Gen_004108D0@@QBE?AVBfmeTripleCU@@XZ

class Gen_00410BA0
{
public:
	int bfmeBusy(void) const;

private:
	char m_bfmeHead[0x3AD];					// +0x000
	bool m_bfmeSending;					// +0x3AD
	bool m_bfmeReceiving;					// +0x3AE
};

// ?bfmeBusy@Gen_00410BA0@@QBEHXZ

class BfmeBlockCU
{
public:
	int m_bfmeData[9];					// 36 bytes
};

extern BfmeBlockCU g_bfmeDefaultCU;				// retail 0x012B4FF8
extern BfmeBlockCU g_bfmeCurrentCU;				// retail 0x012B501C
extern bool g_bfmeDirtyCU;					// retail 0x012F13FC

// ?bfmeReset@@YAXXZ
void __cdecl bfmeReset(void)
{
	g_bfmeCurrentCU = g_bfmeDefaultCU;

	g_bfmeDirtyCU = true;
}

// ?bfmeMask@@YAH_N0@Z
