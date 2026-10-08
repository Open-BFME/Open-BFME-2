// cl: /DNDEBUG /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv506Twin0064C6C0.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoBPB0064C6C0@@YAXPAX00HHPAVBfmeSubBPB0064C6C0@@@Z 0x0038D4AA (26B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Open-BFME7: retail 0x0064C6C0 (29 bytes) is the twin of BfmeConv506.cpp bfmeGoBPB with the
// guarded object as the SIXTH argument (the two arguments before it are not read): the
// three leading arguments are forwarded to its thiscall member.

// The callee is the rowed PeerThreadClass::nickErrorCallback.
class PeerThreadClass
{
public:
	void nickErrorCallback(void *peer, int type, const char *nick);
};

class BfmeSubBPB0064C6C0
{
public:
	void bfmeDoBPB(void *one, void *two, void *three);
};

void bfmeGoBPB0064C6C0(void *one, void *two, void *three, int unusedFour, int unusedFive, BfmeSubBPB0064C6C0 *sub)
{
	if (sub != 0)
		((PeerThreadClass *)sub)->nickErrorCallback(one, (int)two, (const char *)three);
}
