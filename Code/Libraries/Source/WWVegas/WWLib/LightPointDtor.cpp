// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS -ICode/Libraries/Source/WWVegas/WW3D2 -ICode/Libraries/Source/WWVegas/WWLib -ICode/Libraries/Source/WWVegas/WWMath -ICode/Libraries/Source/WWVegas/WWSaveLoad -ICode/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/shims/sweep
// stlport
#include <vector>

// Retain the bfmealloc primary bodies inline without competing external copies.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* p, size_t n) const {
 _STLP_ASSERT( (p == 0) == (n == 0) )
 if(p != 0) ::free((void*)p);
}
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int* p, size_t n) {
 __stl_alloc_rebind(static_cast<allocator<int>&>(*this),(int*)0).deallocate(p,n);
}
}


#include "../WW3D2/LightSubPoint.h"


LightSubPoint::~LightSubPoint()
{
}

class LightPoint
{
public:
	_STL::vector<LightSubPoint> m_points;
	~LightPoint();
};

LightPoint::~LightPoint()
{
}

// ?anchorDeleteLightPoint@@YAXPAVLightPoint@@@Z present-unmatched
void anchorDeleteLightPoint(LightPoint *lightPoint)
{
	delete lightPoint;
}
