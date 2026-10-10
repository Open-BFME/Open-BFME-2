// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /O1 /EHsc /DNDEBUG /MD
//
// ImageCollection::ImageCollection, retail 0x002D932B, 55 bytes.
//
// Calls the SubsystemInterface base constructor (0x001B4E63, rowed as
// ??0SubsystemInterface@@QAE@XZ), installs vtable 0x00C03878 and
// builds the image map at +0x0C through the folded map constructor
// (0x0033C432).
//
// Modeling notes, all read off retail or the sibling findImageByName TU:
// - The base is 12 bytes (vptr + byte@4 + dword@8, zeroed by 0x001B4E63),
//   the same footprint as the sibling's SubsystemInterface, whose rowed
//   ctor spelling the base call uses.
// - The map member uses the rowed <int, void*> spelling as the
//   ICF-stand-in for the true <unsigned, Image*> (same size, same bytes;
//   opaque-8B-pod precedent). Only the constructor call is modeled; the
//   real <map> header would drag in the whole tree machinery as extra
//   COMDATs.

// ??_GImageCollection@@UAEPAXI@Z present-unmatched
// BFME2 SubsystemInterface (14-slot vtable 0x00BD77A0) from the subsystem shim,
// so this unit emits the retail 14-slot ImageCollection vtable.
typedef bool Bool;
#include "subsystem_interface.h"

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
	unsigned char m_pad[0x18];
};

}

class ImageCollection : public SubsystemInterface
{
public:
	ImageCollection();

public:
	virtual ~ImageCollection();
	// Retail vtable 0x00C03878 slots 1/9/10 (init/reset/update) are the folded
	// empty body at 0x000B3FD0, as in Zero Hour's ImageCollection.
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

private:
	_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > m_imageMap;
};

// ??0ImageCollection@@QAE@XZ
ImageCollection::ImageCollection()
	: SubsystemInterface()
{
}
