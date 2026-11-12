// cl: /O1 /Ob1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngineDevice/Source/W3DDevice/GameClient
// Native 136B5E..136BE7 (RET): cdecl (name, value) callee of the HouseColor
// INI block parser tail 0x00417A6B. Target evidence: the prototype lookup
// 0x0061F230 result feeds the counted texture-ref ctor 0x00131DCB, the
// prototype temporary dies right after it (EH state 0 -> 2), the texture's
// +8 id (or ~0 when empty) keys the unsigned->AsciiString map 0x00136A21 on
// 0x00DF29B4, and the mapped string is assigned from value.
// Structural inference from the WorldBuilder twin 0x009B4960: the id comes
// from an id getter on the texture ref (WB 0x009B49D0, 46 B) that calls an
// inline id accessor on the texture (WB 0x009B4A00) when the ref is set;
// that statement shape gives retail's frame homes. Names are address-derived.
#include "ascii_string.h"
#include "BFME2ParticleTextureHandles.h"
template<class T> inline RefCountPtr<T>::~RefCountPtr(){if(Ptr)Ptr->Release_Ref();}
struct BfmeResetTagged;
#include "../../../Libraries/Source/WWVegas/WW3D2/BfmeResetAnyRef.h"
inline unsigned BfmeTexIdOf(TextureClass*texture){return *(unsigned*)((char*)texture+8);}
class Rva00131DCBTextureRef:public RefCountPtr<TextureClass>{public:Rva00131DCBTextureRef(const BfmeResetAnyRef&);__forceinline ~Rva00131DCBTextureRef() {}
 unsigned getID() const {return Ptr?BfmeTexIdOf(Ptr):~0u;}};
class Rva009EBCE0AssetReference {public:TextureClass*ptr;~Rva009EBCE0AssetReference(){if(ptr)ptr->Release_Ref();}};
Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char*);
class Rva00136A21 {public:AsciiString&rva00136A21(const unsigned&);};
// The map at 0x00DF29B4 is defined once, by its global dtor thunk's unit,
// as g_Va00DF29B4; read it through the map view.
extern unsigned int g_Va00DF29B4;
void Rva00136B5E(const char*name,const char*value){
 if(name&&value){
  Rva00131DCBTextureRef tex((const BfmeResetAnyRef&)Rva009EBCE0_GetPrototype(name));
  AsciiString&dst=((Rva00136A21*)&g_Va00DF29B4)->rva00136A21(tex.getID());((StringBase<char>*)&dst)->set(value);
 }
}
