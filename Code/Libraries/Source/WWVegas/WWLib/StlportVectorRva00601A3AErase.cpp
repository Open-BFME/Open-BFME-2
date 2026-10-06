// cl: /Oy- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native60186F dispatcher forwards first/last/result plus two unused tags.
// The full rowed counted-copy601797 is50B and reads only the first three
// arguments; its29B assignment6016AC copies12 bytes. This call-only five-arg
// view retains native cdecl ABI without asserting its provider's Coord3D
// payload label. The record name comes from rowed push_back601A3A's stride.
#include <iterator>
struct Rva00601A3AElement {unsigned char unknown[12];};
Rva00601A3AElement *__cdecl Rva00601797Copy5(const Rva00601A3AElement*,const Rva00601A3AElement*,Rva00601A3AElement*,const _STL::random_access_iterator_tag&,int*);
Rva00601A3AElement *__cdecl Rva0060186FCopy4(const Rva00601A3AElement* first,const Rva00601A3AElement* last,Rva00601A3AElement* result,const void*) {
 _STL::random_access_iterator_tag tag;
 return Rva00601797Copy5(first,last,result,tag,(int*)0);
}

#pragma comment(linker, "/alternatename:?Rva00601797Copy5@@YAPAURva00601A3AElement@@PBU1@0PAU1@ABUrandom_access_iterator_tag@_STL@@PAH@Z=?Rva00601797Copy@@YAPAVCoord3D@@PBV1@0PAV1@@Z")

// Native60194C shifts the tail through60186F and stores the new finish.
// Its fourth argument is ignored by the complete29B dispatcher. The pointer
// into the first parameter preserves this unused native argument without
// reading it or asserting an object there. No tail destruction is emitted.
class Rva00601A3AVectorView {
 Rva00601A3AElement *start,*finish,*end;
public:
 Rva00601A3AElement* eraseRange(Rva00601A3AElement* first,Rva00601A3AElement* last);
};
Rva00601A3AElement* Rva00601A3AVectorView::eraseRange(Rva00601A3AElement* first,Rva00601A3AElement* last) {
 finish=Rva0060186FCopy4(last,finish,first,reinterpret_cast<const unsigned char*>(&first)+3);
 return first;
}
