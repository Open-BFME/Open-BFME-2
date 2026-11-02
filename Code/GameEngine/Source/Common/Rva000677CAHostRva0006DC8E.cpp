// cl: /O1 /DNDEBUG /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
//
// ?updateView@Rva000677CAHost@@QAEX_NHHHH@Z, retail 0x0006dc8e, 195 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> _Bit_reference _Bit_iter<_Bit_reference, _Bit_reference *>::operator*() const; }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> & _Bit_iter<_Bit_reference, _Bit_reference *>::operator+=(int); }
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
namespace _STL { template <> void vector<bool, allocator<bool> >::_M_fill_insert(_Bit_iter<_Bit_reference, _Bit_reference *>, unsigned int, bool); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> vector<bool, allocator<bool> >::begin(); }
namespace _STL { template <> void vector<bool, allocator<bool> >::insert(_Bit_iter<_Bit_reference, _Bit_reference *>, unsigned int, bool); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??A?$vector@_NV?$allocator@_N@_STL@@@_STL@@QAE?AU_Bit_reference@1@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Bit_reference vector<bool,allocator<bool> >::operator[](unsigned int); }
// Suppress this TU's non-retail copy of ?resize@?$vector@_NV?$allocator@_N@_STL@@@_STL@@QAEXI_N@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<bool,allocator<bool> >::resize(unsigned int,bool); }

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}
// The corner probe at 0x00067494 is the rowed BaseHeightMapRenderObjClass::CheckCorners.
class BaseHeightMapRenderObjClass { public: void CheckCorners(int, int, int, int, int, int, bool *, bool *); };
struct Rva0006DC8EDimensions {char opaque00[8]; int width; int height;};
class Rva000677CAHost
{
public:
    void updateView(bool partial, int minX, int maxX, int minY, int maxY);
	bool rva000677CA(int cellX, int cellY, float f);
private:
    char opaque00[0x37A0];
    float slope;
    char opaque37A4[0x37C0-0x37A4];
    Rva0006DC8EDimensions *map;
    char opaque37C4[0x3800-0x37C4];
    _STL::vector<bool> bits;
};

bool Rva000677CAHost::rva000677CA(int cellX, int cellY, float f)
{
	bool out = false;
	unsigned char *p = &((unsigned char *)&f)[3];
	int fi = (int)f;
	((BaseHeightMapRenderObjClass *)this)->CheckCorners(cellX, cellY, 0x100, 0, fi, 0, (bool *)p, &out);
	return out == false;
}

void Rva000677CAHost::updateView(bool partial, int minX, int maxX, int minY, int maxY)
{
    int xSize=map->width;
    int ySize=map->height;
    if (bits.size()!=xSize*ySize)
        bits.resize(xSize*ySize);
    if (!partial) {
        minX=0; minY=0; maxX=xSize; maxY=ySize;
    }
    for (int j=minY; j<maxY; ++j)
        for (int i=minX; i<maxX; ++i)
            bits[i+j*xSize]=rva000677CA(i,j,slope);
}
