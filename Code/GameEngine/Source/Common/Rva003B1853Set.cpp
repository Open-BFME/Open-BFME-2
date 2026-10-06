// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva003B1853@Rva003B1853@@QAEXPBDH@Z @0x003B1853 (38B):
// Entry setter: clears the AsciiString vector at +0x08 via the rowed
// range erase at 0x0002CCFC, sets the StringBase<char> name at +0x00 from
// the char pointer via the rowed set at 0x000055F5, stores the int value
// at +0x04. Layout matches the 0x14 entry probed by 0x003B1820 (string
// +0x00, int +0x04, vector +0x08). Returns void, callee cleans 8B.
// Evidence: unlock lane, both callees rowed, caller 0x003B1879.
class AsciiString;

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
public:
	typedef Type *iterator;
	iterator erase(iterator first, iterator last);
	iterator begin() { return m_start; }
	iterator end() { return m_finish; }
private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};
}

template <typename T>
class StringBase
{
public:
	void set(const char *text);
private:
	T *m_data;
};

class Rva003B1853
{
public:
	void rva003B1853(const char *name, int value);
private:
	StringBase<char> m_00; // +0x00
	int m_04; // +0x04
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_08; // +0x08
};

void Rva003B1853::rva003B1853(const char *name, int value)
{
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > &vec = m_08;
	vec.erase(vec.begin(), vec.end());
	m_00.set(name);
	m_04 = value;
}
