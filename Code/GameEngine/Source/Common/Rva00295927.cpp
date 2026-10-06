// cl: /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva00295927@Rva00295927@@QAEXIPAVImage@@@Z @0x00295927 66B unlock
// Map insert-if-absent at this+0x268 via rowed _M_find 0x357180 (void* view)
// and rowed insert_unique 0x4D795B (Image* view); same address union since
// void* and Image* layouts match. Frees 0x00452E27. Neighbours share /O1.
#include <map>

class Image;

typedef _STL::map<unsigned, void *, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, void *> > > MapVoid;
typedef _STL::map<unsigned, Image *, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, Image *> > > MapImage;

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
