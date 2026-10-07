// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Retail 0x000A7E9E, 92B. Target evidence: copies the input AsciiString at
// +0, constructs the 8B TreeKey with the input word at +0x38, erases that key
// from the tree at this+0x20 through rowed 0x000A7E31, then subtracts input
// +0x30 from this+0x3C. The const-reference spelling models the observed
// single stack pointer ABI; target bytes do not resolve pointer versus
// reference or the owning class and input identities.

#include <set>
#include "ascii_string.h"

struct TreeKey00242F5E
{
	unsigned int m_id;
	AsciiString m_name;
	TreeKey00242F5E(unsigned int id, AsciiString name);
};

// This is the address-derived template spelling already used by the row at
// 0x000A7E31. The call site passes the TreeKey object as an opaque key pointer.
struct Rva000A7E31Key
{
	int word;
	bool operator<(const Rva000A7E31Key &other) const { return word < other.word; }
	bool operator==(const Rva000A7E31Key &other) const { return word == other.word; }
};

typedef _STL::_Rb_tree<Rva000A7E31Key, Rva000A7E31Key,
	_STL::_Identity<Rva000A7E31Key>, _STL::less<Rva000A7E31Key>,
	_STL::allocator<Rva000A7E31Key> > Rva000A7E9ETree;

struct Rva000A7E9EInput
{
	AsciiString m_at00;
	unsigned char m_pad04[0x2C];
	unsigned int m_at30;
	unsigned char m_pad34[4];
	unsigned int m_at38;
};

class Rva000A7E9E
{
public:
	void rva000A7E9E(const Rva000A7E9EInput &input);

private:
	unsigned char m_pad00[0x20];
	Rva000A7E9ETree m_tree;
	unsigned char m_pad2C[0x10];
	unsigned int m_count;
};

void Rva000A7E9E::rva000A7E9E(const Rva000A7E9EInput &input)
{
	TreeKey00242F5E key(input.m_at38, input.m_at00);
	m_tree.erase((const Rva000A7E31Key &)key);
	register unsigned int amount = input.m_at30;
	m_count -= amount;
}
