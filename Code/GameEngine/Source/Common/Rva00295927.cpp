// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport46
// ?rva00295927@Rva00295927@@QAEXIPAVImage@@@Z @0x00295927 66B unlock
// Map insert-if-absent at this+0x268 via rowed _M_find 0x357180 (void* view)
// and rowed insert_unique 0x4D795B (Image* view); same address union since
// void* and Image* layouts match. Frees 0x00452E27. Neighbours share /O1.
#include <map>

// map<unsigned> internals otherwise emit an unreferenced
// less<unsigned>::operator() COMDAT in a register shape retail's 0x00758C50
// does not have. Every compare here is inlined, so an inline-only
// specialization keeps them so and emits no copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const { return a < b; }
}

class Image;

typedef _STL::map<unsigned, void *, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, void *> > > MapVoid;
typedef _STL::map<unsigned, Image *, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, Image *> > > MapImage;

// map::insert calls the rowed insert_unique 0x004D795B
// (stlport_map_uint_image_insert.cpp); declaring the specialization keeps
// this unit from emitting its own differing copy.
typedef _STL::_Rb_tree<unsigned, _STL::pair<const unsigned, Image *>, _STL::_Select1st<_STL::pair<const unsigned, Image *> >, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, Image *> > > TreeImage;
namespace _STL {
template <> pair<TreeImage::iterator, bool> TreeImage::insert_unique(const TreeImage::value_type &);
}

class Rva00295927
{
public:
	void rva00295927(unsigned int key, Image *value);
private:
	unsigned char m_pad00[0x268];
	unsigned char m_mapPad[sizeof(MapVoid)];
};

void Rva00295927::rva00295927(unsigned int key, Image *value)
{
	if (value == 0)
		return;
	MapVoid *m_void = (MapVoid *)m_mapPad;
	MapImage *m_image = (MapImage *)m_mapPad;
	if (m_void->find(key) == m_void->end()) {
		m_image->insert(_STL::pair<const unsigned, Image *>(key, value));
	}
}
