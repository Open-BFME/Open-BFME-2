// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Include /ICode/Libraries/Include /Ireference/shims/moduledata
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

class Radar : public Snapshot, public SubsystemInterface {
public:
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
    virtual ~Rva004FA1F();
private:
    char unknown1430[0x1470 - 0x1430];
    RadarTextureRef4 texture0, texture1;
    char unknown1478[8];
    RadarTextureRef4 texture2;
    char unknown1484[8];
    RadarTextureRef4 texture3;
    char unknown1490[8];
    RadarTextureRef4 texture4;
    char unknown149C[0x14E0 - 0x149C];
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
