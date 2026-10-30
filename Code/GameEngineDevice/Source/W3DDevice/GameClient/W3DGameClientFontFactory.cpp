// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG
// ?createFontLibrary@W3DGameClient@@MAEPAVFontLibrary@@XZ, retail 0x0004C4F9, 62 bytes.
// W3DGameClient factory slot 40 (offset 0xA0) of vtable 0x007C4738: return new W3DFontLibrary.
// Donor ZH W3DGameClient.h: virtual FontLibrary *createFontLibrary(void) { return NEW W3DFontLibrary; }
// with inline empty W3DFontLibrary(void) {} (no members, sizeof == sizeof(FontLibrary) == 0x2C).
// Retail allocates 0x2C, calls rowed FontLibrary ctor 0x00218942, then stores W3DFontLibrary vtable 0x007C4818.
// Sibling factory createSnowManager 0x0004C5F8 (slot 46) shares EH_prolog plus operator new pattern and flags.
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
class FontLibrary : public SubsystemInterface
{
public:
	FontLibrary();
	~FontLibrary();
private:
	void *m_fontList;
	int m_count;
	_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > m_table1;
	_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > m_table2;
};
typedef char FontLibrarySizeCheck[sizeof(FontLibrary) == 0x2C ? 1 : -1];
class W3DFontLibrary : public FontLibrary
{
public:
	W3DFontLibrary() {}
	virtual ~W3DFontLibrary();
};
typedef char W3DFontLibrarySizeCheck[sizeof(W3DFontLibrary) == 0x2C ? 1 : -1];
class W3DGameClient
{
protected:
	virtual FontLibrary *createFontLibrary();
};
inline FontLibrary *W3DGameClient::createFontLibrary()
{
	return new W3DFontLibrary;
}

// createFontLibrary is a header inline in retail: other units emit select-any
// copies of it, so a strong definition here was a duplicate symbol in the
// linked build. This anchor only makes this unit emit its copy for the ledger
// row; it is not retail code.
struct bfmeW3DGameClientEmitter : W3DGameClient
{
	static void emit(bfmeW3DGameClientEmitter *p);
};
#pragma inline_depth(0)
// ?emit@bfmeW3DGameClientEmitter@@SAXPAU1@@Z present-unmatched
void bfmeW3DGameClientEmitter::emit(bfmeW3DGameClientEmitter *p)
{
	(void)p->W3DGameClient::createFontLibrary();
}
#pragma inline_depth()
