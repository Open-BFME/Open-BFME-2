// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
//
// ??0FontLibrary@@QAE@XZ, retail 0x00218942, 103 bytes.
// FontLibrary subsystem ctor: base SubsystemInterface (0x001B4E63), vtable
// 0x007E5AD0, two map<int void*> at +0x14/+0x20 via rowed 0x0033C432,
// scalars +0x0C/+0x10 zeroed, setName("TheFontLibrary") via 0x37BA0+0x6F3CC.
// BFME1 donor GameFont.cpp has trivial ctor (m_fontList/m_count only);
// BFME2 adds Subsystem base plus two maps and the subsystem name.
// Caller at 0x0004C51D constructs the global. Prev/next are stlport hint rows.

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


namespace _STL
{

template <class First, class Second> struct pair
{
	First first;
	Second second;
};

template <class Type> struct less
{
};

template <class Type> class allocator
{
};

template <class Key, class Value, class Compare, class Alloc> class map
{
public:
	map();
	~map();
	unsigned char m_pad[0x0C];
};

}

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init();
	void setName(AsciiString name);

private:
	unsigned char m_bfmeBasePad[8];
};

class FontLibrary : public SubsystemInterface
{
public:
	FontLibrary();
	virtual ~FontLibrary();

private:
	void *m_fontList;
	int m_count;
	_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > m_table1;
	_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > m_table2;
};

FontLibrary::FontLibrary()
{
	m_fontList = 0;
	m_count = 0;
	setName("TheFontLibrary");
}
