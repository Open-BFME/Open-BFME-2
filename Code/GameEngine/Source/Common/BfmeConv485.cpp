// cl: /O1
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv485.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoBLD@@YGXPAX@Z 0x0029ACE3 (24B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
class BfmeSinkBLD
{
public:
	void bfmeDoBLD(void *what, int flag);
};

extern BfmeSinkBLD *g_bfmeSinkBLD;

void __stdcall bfmeGoBLD(void *what)
{
	BfmeSinkBLD *sink = g_bfmeSinkBLD;
	if (sink != 0)
		sink->bfmeDoBLD(what, 0);
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_bfmeSinkBLD@@3PAVBfmeSinkBLD@@A=?TheRva002D3627Host@@3PAVRva002D3627Host@@A")
