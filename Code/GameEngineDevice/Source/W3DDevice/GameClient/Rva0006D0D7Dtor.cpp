// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2renderobj /DNDEBUG /DBFME_SNAPSHOT_NAME_SLOT /D_OPERATOR_NEW_DEFINED_ /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/shims/moduledata/Common
// stlport
// BaseHeightMapRenderObjClass::~BaseHeightMapRenderObjClass, retail 0x0006D0D7, 735 bytes.
// Body: freeMapResources 0x6933D, null-guarded deletes of the buffers at +3850..+387C, then
// member destruction in reverse order and the RenderObjClass base destructor 0x13BE20.
#include <vector>
void Rva00030830GameFree(void *);
namespace _STL {
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ Rva00030830GameFree(__p); }
}
#define BFME_RO_DTOR_DECL_ONLY
#include "../../../Include/W3DDevice/GameClient/BaseHeightMap.h"
class TextureBaseClass {public:void Release_Ref();};
class TextureClass:public TextureBaseClass {};

class VBuf { public: virtual ~VBuf(); };
class Rva000D3A17 { public: ~Rva000D3A17(); void rva000D3A17(); char data[272]; };
class W3DBibBuffer { public: ~W3DBibBuffer(); char data[68048]; };
class W3DRoadBuffer { public: ~W3DRoadBuffer(); char data[80]; };
class W3DBridgeBuffer { public: ~W3DBridgeBuffer(); };
class W3DWaypointBuffer { public: ~W3DWaypointBuffer(); char data[12]; };
class Rva000E0AE2 { public: ~Rva000E0AE2(); char data[620]; };
class Rva0007311B { public: ~Rva0007311B(); };
class W3DTaint { public: ~W3DTaint(); char data[80]; };

template <class T> static __forceinline void destroyMember(T *&p)
{
	T *t = p;
	if (t) {
		t->T::~T();
		operator delete(t);
		p = 0;
	}
}

BaseHeightMapRenderObjClass::~BaseHeightMapRenderObjClass()
{
	BaseHeightMapRenderObjClass::rva0006933D();
	VBuf *&tree = reinterpret_cast<VBuf *&>(m_treeBuffer);
	if (tree) {
		::delete tree;
		tree = 0;
	}
	destroyMember(reinterpret_cast<Rva000D3A17 *&>(field3874));
	VBuf *&shrub = reinterpret_cast<VBuf *&>(m_shrubBuffer);
	if (shrub) {
		::delete shrub;
		shrub = 0;
	}
	VBuf *&prop = reinterpret_cast<VBuf *&>(m_propBuffer);
	if (prop) {
		::delete prop;
		prop = 0;
	}
	destroyMember(m_bibBuffer);
	destroyMember(m_roadBuffer);
	W3DBridgeBuffer *bridge = m_bridgeBuffer;
	if (bridge) {
		bridge->W3DBridgeBuffer::~W3DBridgeBuffer();
		operator delete(bridge);
	}
	VBuf *other = reinterpret_cast<VBuf *&>(field3860);
	if (other)
		::delete other;
	destroyMember(m_waypointBuffer);
	destroyMember(reinterpret_cast<Rva000E0AE2 *&>(field3868));
	destroyMember(reinterpret_cast<Rva0007311B *&>(m_shroud));
	destroyMember(field387C);
}
