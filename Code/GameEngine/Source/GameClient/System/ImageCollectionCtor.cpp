// cl: /O1 /EHsc /DNDEBUG /MD
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
class AsciiStringMember
{
public:
	~AsciiStringMember();
};

class SubsystemInterface
{
public:
	SubsystemInterface() throw();
	virtual ~SubsystemInterface();

private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

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

private:
	_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > m_imageMap;
};

// ??0ImageCollection@@QAE@XZ
ImageCollection::ImageCollection()
	: SubsystemInterface()
{
}
