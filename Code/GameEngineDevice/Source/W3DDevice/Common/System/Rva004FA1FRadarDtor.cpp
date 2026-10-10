// cl: /O1 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Include /ICode/Libraries/Include /Ireference/shims/moduledata
// stlport
// Native [4FA1F,4FAFF), 224B. Constructor4F8EA, the217B resource
// teardown and98B Radar base destructor establish this radar family.
// ZH W3DRadar::~W3DRadar supplies the resource-delete purpose. Native
// bytes prove five counted handles, four8B entries, the pointer list at
//1500 and clearing each observer+C before teardown. The additional field
// names and original entry type are unknown. The existing coordinate
// lifetime provider supplies the observed8B layout and empty destructor.
#include "Common/Snapshot.h"
#include "Lib/Coord2D.h"
typedef bool Bool;
#include "subsystem_interface.h"
#include <list>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

class Radar : public Snapshot, public SubsystemInterface {
public:
    Radar();
    virtual ~Radar();
private:
    char unknown10[0x1430 - 0x10];
};
class TextureClass {
public:
    void Release_Ref();
};
struct RadarTextureRef4 {
    TextureClass *ptr;
    RadarTextureRef4() : ptr(0) {}
    ~RadarTextureRef4() { if (ptr) ptr->Release_Ref(); }
};
struct BfmeRadarMapPoint : Coord2D {
    BfmeRadarMapPoint();
    ~BfmeRadarMapPoint();
};
struct Rva004FA1FObserver {
    char unknown[0xC];
    void *radar;
};
namespace _STL {
// The independently verified provider supplies the unchanged STLport body.
// Its declaration-only consumer view preserves native unwind state6.
template<> _List_base<Rva004FA1FObserver*, allocator<Rva004FA1FObserver*> >::~_List_base();
}
class W3DRadar {
    friend class Rva004FA1F;
protected:
    void deleteResources();
};
class Rva004FA1F : public Radar {
public:
    Rva004FA1F();
    virtual ~Rva004FA1F();
private:
    char unknown1430[0x1464-0x1430];
    bool flag1464;
    char unknown1465[3];
    int format0; void *image0;
    RadarTextureRef4 texture0, texture1;
    int format1; void *image1;
    RadarTextureRef4 texture2;
    int format2; void *image2;
    RadarTextureRef4 texture3;
    int format3; void *image3;
    RadarTextureRef4 texture4;
    int width, height;
    void *unknown14A4;
    void *images[11];
    bool reconstruct, flag14D5, flag14D6;
    float angle, zoom;
    BfmeRadarMapPoint entries[4];
    _STL::list<Rva004FA1FObserver*> observers;
};
Rva004FA1F::~Rva004FA1F()
{
    ((W3DRadar*)this)->deleteResources();
    typedef _STL::list<Rva004FA1FObserver*>::iterator Iterator;
    for (Iterator it = observers.begin(), end = observers.end(); it != end; ++it)
        (*it)->radar = 0;
}

Rva004FA1F::Rva004FA1F() : flag1464(true), unknown14A4(0), flag14D6(false)
{
    width = 128; height = 128;
    format0 = 0; image0 = 0;
    format1 = 0; image1 = 0;
    format2 = 0; image2 = 0;
    format3 = 0; image3 = 0;
    reconstruct = true;
    angle = 0.0f; zoom = 0.0f;
    for(int i=0;i<4;++i) { entries[i].x=0; entries[i].y=0; }
    memset(images,0,sizeof images);
    flag14D5 = false;
}
