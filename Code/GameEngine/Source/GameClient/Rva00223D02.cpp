// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva00223D02@Rva00223D02@@QAEXPBVAsciiString@@PAVCreateAHeroData@@@Z @0x00223D02 74B
// Table at +0x48 via rowed Iter find 0x0041534B then vector find-and-erase.
// Evidence: add ecx 0x48 then rowed Rva00056F61::rva0041534B with hidden Iter out; null second arg returns; null node returns; node+8 holds vector<CreateAHeroData*> with end at +4; rowed find 0x0020E873 then rowed voidptr erase 0x001FF51F like Rva004DFB55HeroRemover; caller 0x000A9CFC; neighbours Rva00223CDB AptPlayer.
#include "ascii_string.h"
#include <vector>
#include <algorithm>

struct Rva0041534BIter
{
	void *m_node;
	void *m_table;
};

class Rva00056F61
{
public:
	Rva0041534BIter rva0041534B(const AsciiString *key);
};

class CreateAHeroData;

class Rva00223D02
{
public:
	void rva00223D02(const AsciiString *key, CreateAHeroData *val);
private:
	char m_pad[0x48];
	Rva00056F61 m_table;
};

void Rva00223D02::rva00223D02(const AsciiString *key, CreateAHeroData *val)
{
	if (val == 0)
		return;
	Rva0041534BIter it = m_table.rva0041534B(key);
	if (it.m_node == 0)
		return;
	_STL::vector<CreateAHeroData *> *vec = (_STL::vector<CreateAHeroData *> *)((char *)it.m_node + 8);
	_STL::vector<CreateAHeroData *>::iterator found = _STL::find(vec->begin(), vec->end(), val);
	if (found != vec->end())
		((_STL::vector<void *> *)vec)->erase((void **)found);
}
