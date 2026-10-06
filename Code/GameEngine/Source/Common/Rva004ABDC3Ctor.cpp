// cl: /DNDEBUG /MD
//
// ??0Rva004ABDC3@@QAE@XZ @0x004ABDC3 25B.
// Stores vtable VA 0x00C549F0, default-constructs set<AsciiString> at +4
// (rowed 0x000D3A71), then clears the byte at +0x11. The set object is
// 0x0C bytes, so the cleared byte is the second trailing flag.

class AsciiString;

namespace _STL
{
template<class T>
struct less
{
	char unused;
};

template<class T>
class allocator
{
	char unused;
};

template<class Key, class Comp, class Alloc>
class set
{
public:
	set();
	unsigned char m_raw[0x0C];
};
}

class Rva004ABDC3
{
public:
	Rva004ABDC3();
	virtual ~Rva004ABDC3() {}

private:
	_STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> > m_set;
	char m_skip;
	char m_flag;
};

Rva004ABDC3::Rva004ABDC3()
	: m_flag(0)
{
}
