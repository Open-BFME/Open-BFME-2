// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
//
// ??0FontLibrary@@QAE@XZ, retail 0x00218942, 103 bytes.
// FontLibrary subsystem ctor: base SubsystemInterface (0x001B4E63), vtable
// 0x007E5AD0, two map<int void*> at +0x14/+0x20 via rowed 0x0033C432,
// scalars +0x0C/+0x10 zeroed, setName("TheFontLibrary") via 0x37BA0+0x6F3CC.
// BFME1 donor GameFont.cpp has trivial ctor (m_fontList/m_count only);
// BFME2 adds Subsystem base plus two maps and the subsystem name.
// Caller at 0x0004C51D constructs the global. Prev/next are stlport hint rows.

#include "../../../Include/Common/BfmeStringData.h"

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

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class GameFont;

class FontLibrary : public SubsystemInterface
{
public:
	FontLibrary();
	virtual ~FontLibrary();
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void reset();
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void releaseFontData(GameFont *font) = 0;

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
