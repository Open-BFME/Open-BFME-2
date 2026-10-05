// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Rva004F81DBQueue::pop @0x004F81DB (33B): pop_heap over a vector of 12-byte
// Rva004F6966 records followed by pop_back. The queue keeps the vector at +0
// and the one-byte empty comparator at +0xC like STLport's priority_queue, but
// retail has no try/catch around the pop (STLport's priority_queue::pop clears
// the container on unwind), so it is spelled as a plain member here. pop_back
// tail-jumps to the out-of-line record destructor, ICF-folded with the rowed
// holder destructor 0x005F8F96 (pinned); the heap chain is in
// stlport_pop_heap_rva004f7e61.cpp. Names are address-derived placeholders.
#include <algorithm>
#include <vector>

struct TreeHintRef00217D4C
{
	void *m_ptr;
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other);
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C();
};

struct Rva004F6966
{
	TreeHintRef00217D4C m_00;
	int m_04;
	int m_08;
	Rva004F6966(const Rva004F6966 &other);
	Rva004F6966 &operator=(const Rva004F6966 &other);
	~Rva004F6966();
};

struct Rva004F81DBGreater
{
	bool operator()(const Rva004F6966 &x, const Rva004F6966 &y) const
	{
		return x.m_08 > y.m_08;
	}
};

struct Rva004F81DBQueue
{
	_STL::vector<Rva004F6966> m_c;
	Rva004F81DBGreater m_comp;

	void pop();
};

void Rva004F81DBQueue::pop()
{
	_STL::pop_heap(m_c.begin(), m_c.end(), m_comp);
	m_c.pop_back();
}
