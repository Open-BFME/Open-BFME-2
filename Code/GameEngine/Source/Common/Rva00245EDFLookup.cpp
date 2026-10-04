// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva00245EDF@GameLogic@@QAE_NPAXPAH@Z, retail 0x00245EDF, 53 bytes.
// GameLogic lookup via Rva00056F61 at +0x10 over AsciiString at arg +0x64:
// rowed iter-find 0x0041534B plus hidden-pointer Iter plus node+8 to out.
// Evidence: rowed 0x0041534B plus caller 0x0033A648 via TheGameLogic plus
// ret 8 plus bool mov-al shape plus prev next same flags.
#include "ascii_string.h"

struct Rva0041534BIter
{
	void *m_node;
	void *m_table;
	Rva0041534BIter(void *n, void *t);
};

class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};

class GameLogic
{
public:
	bool rva00245EDF(void *arg1, int *out);
};

bool GameLogic::rva00245EDF(void *arg1, int *out)
{
	if (!arg1)
		return false;
	AsciiString *key = (AsciiString *)((char *)arg1 + 0x64);
	Rva00056F61 *table = (Rva00056F61 *)((char *)this + 0x10);
	Rva0041534BIter it = table->rva0041534B(key);
	if (it.m_node) {
		*out = *(int *)((char *)it.m_node + 8);
		return true;
	}
	return false;
}
