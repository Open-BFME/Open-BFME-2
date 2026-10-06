// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// The node path of hash_map<int, Rva0029E067>: its pair copy (0x0029E13C)
// copies one key word, then calls the rowed Rva0029E067 copy constructor
// (0x0029E067, Rva0029E067Ctor.cpp), and its node constructor (0x002A14D5)
// allocates 0x3C bytes, zeroes the next link and places the pair at +4: a
// 0x34-byte value, Rva0029E067's layout there. Only the value's copy
// constructor is used. Only the table's find_or_insert and _M_insert are
// instantiated: the whole class would need operator== on the value
// (_M_equal) and hash_map's operator[] a default-constructed one.

#include <hash_map>

struct Rva0029E067
{
	Rva0029E067(const Rva0029E067 &src);
	char m_bytes[0x34];
};

typedef _STL::pair<const int, Rva0029E067> IntRva0029E067Value;

typedef _STL::hashtable<IntRva0029E067Value, int, _STL::hash<int>, _STL::_Select1st<IntRva0029E067Value>, _STL::equal_to<int>, _STL::allocator<IntRva0029E067Value> > IntRva0029E067Table;

template IntRva0029E067Table::reference IntRva0029E067Table::find_or_insert(const IntRva0029E067Value &);
template IntRva0029E067Table::reference IntRva0029E067Table::_M_insert(const IntRva0029E067Value &);
