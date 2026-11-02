// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ImageCollection::~ImageCollection, BFME2 retail 0x002D9283 (115B), slot 0
// of vtable 0x00C03878 through ??_G at 0x002D9362. Zero Hour's destructor
// (GameClient/System/Image.cpp) walks the image map and frees every image;
// BFME 2 frees them with a global delete (virtual destructor with flag 0,
// then operator delete) where Zero Hour returned them to their pool. The
// map's destructor (0x002D922A) and SubsystemInterface's (0x001B4E74) follow.
// Class view as in ImageCollectionFindImage.cpp.

#include <map>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

#include "ascii_string.h"

class NameKeyGenerator
{
public:
	NameKeyType Rva002D91AF(const AsciiString &nameString);
};

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../Include/GameClient/ImageClass.h"

typedef _STL::map<unsigned int, Image *> ImageNameMap;
// BFME2 SubsystemInterface (12-byte base, 14-slot vtable 0x00BD77A0) from the
// subsystem shim, so this unit emits the retail 14-slot ImageCollection vtable.
typedef bool Bool;
#include "subsystem_interface.h"
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<unsigned int,_STL::pair<unsigned int const,Image *>,_STL::_Select1st<_STL::pair<unsigned int const,Image *> >,_STL::less<unsigned int>,_STL::allocator<_STL::pair<unsigned int const,Image *> > >::~_Rb_tree(); }
namespace _STL { template <> _Rb_tree_base<_STL::pair<unsigned int const,Image *>,_STL::allocator<_STL::pair<unsigned int const,Image *> > >::~_Rb_tree_base(); }
namespace _STL { template <> void _Rb_tree<unsigned int,_STL::pair<unsigned int const,Image *>,_STL::_Select1st<_STL::pair<unsigned int const,Image *> >,_STL::less<unsigned int>,_STL::allocator<_STL::pair<unsigned int const,Image *> > >::_M_erase(_STL::_Rb_tree_node<_STL::pair<unsigned int const,Image *> > *); }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<unsigned int const,Image *> > *,_STL::_Rb_tree_node<_STL::pair<unsigned int const,Image *> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<unsigned int const,Image *> > > >::deallocate(_STL::_Rb_tree_node<_STL::pair<unsigned int const,Image *> > *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_Rb_tree_node<_STL::pair<unsigned int const,Image *> > >::deallocate(_STL::_Rb_tree_node<_STL::pair<unsigned int const,Image *> > *,unsigned int) const; }
// bfme link decl-only end

class ImageCollection : public SubsystemInterface
{
public:
	const Image *findImageByName(const AsciiString &name);
	void addImage(Image *image);
	virtual ~ImageCollection();
	// Retail vtable 0x00C03878 slots 1/9/10 (init/reset/update) are the folded
	// empty body at 0x000B3FD0, as in Zero Hour's ImageCollection.
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

protected:
	ImageNameMap m_imageMap;
};


ImageCollection::~ImageCollection()
{
	for (ImageNameMap::iterator it = m_imageMap.begin(); it != m_imageMap.end(); ++it)
		::delete it->second;
}
