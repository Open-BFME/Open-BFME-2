// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0020E9A1@Rva0020E9A1Inner@@QAEXXZ @0x0020E9A1 47B.
// Walks the STLport vector of pointers at this+0x2C (start +0x2C, finish
// +0x30) and calls the rowed 0x003EFDF5 on each element with 1. Same idiom
// as Rva0020EE29Clear.cpp. The loop bound is vector::size() re-read every
// iteration (finish loaded before start, sar 2), which only the real STLport
// vector reproduces; raw pointer spellings load start first.
#include <vector>

class Rva003EFDF5Host
{
public:
	void rva003EFDF5(void *v);
};

struct Rva0020E9A1Inner
{
	char m_pad[0x2C];
	_STL::vector<Rva003EFDF5Host *> m_items; // +0x2C
	void rva0020E9A1();
};

void Rva0020E9A1Inner::rva0020E9A1()
{
	for (unsigned i = 0; i < m_items.size(); ++i)
		m_items[i]->rva003EFDF5((void *)1);
}
