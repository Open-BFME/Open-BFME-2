// ?rva004F941E@Rva004F941E@@QAEXABURva004F9018Element@@@Z
// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004F941E@Rva004F941E@@QAEXABURva004F9018Element@@@Z @0x004F941E 33B.
// Append-then-triple: push the element through the rowed 0x004F9018 vector
// push_back on the +0x00 vector, then forward its begin/finish/flag byte to
// the pinned 0x004F7767 triple. Shadow vector exposes the bounds with the
// rowed push_back spelling.
struct Rva004F9018Element;

namespace _STL
{
template<class _T> class allocator { };
template<class _Tp, class _Alloc = allocator<_Tp> > class vector
{
public:
	void push_back(const _Tp &v);
	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end_of_storage;
};
}

void rva004F7767(void *a, void *b, bool c);

class Rva004F941E
{
public:
	void rva004F941E(const Rva004F9018Element &e);
private:
	_STL::vector<Rva004F9018Element> m_vec;
	bool m_C;
};

void Rva004F941E::rva004F941E(const Rva004F9018Element &e)
{
	m_vec.push_back(e);
	rva004F7767(m_vec._M_start, m_vec._M_finish, m_C);
}
