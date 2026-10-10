// ?rva00136B5E@@YAXPBD0@Z
// partial score=0.850662 date=2026-10-10
// cl: /O1 /Ob1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngineDevice/Source/W3DDevice/GameClient
#include "ascii_string.h"
#include "BFME2ParticleTextureHandles.h"
template<class T> inline RefCountPtr<T>::~RefCountPtr(){if(Ptr)Ptr->Release_Ref();}
struct BfmeResetTagged;
struct BfmeResetAnyRef{BfmeResetTagged*pointer;};
struct BfmeResetTextureRef{void*pointer;BfmeResetTextureRef&operator=(const BfmeResetAnyRef&);};
class Rva00131DCBTextureRef:public RefCountPtr<TextureClass>{public:Rva00131DCBTextureRef(const BfmeResetAnyRef&);__forceinline ~Rva00131DCBTextureRef() {}};
inline __declspec(noinline) Rva00131DCBTextureRef::Rva00131DCBTextureRef(const BfmeResetAnyRef&rhs){*reinterpret_cast<BfmeResetTextureRef*>(this)=rhs;}
class Rva009EBCE0AssetReference {public:TextureClass*ptr;~Rva009EBCE0AssetReference(){if(ptr)ptr->Release_Ref();}};
Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char*);
class Rva00136A21 {public:AsciiString&rva00136A21(const unsigned&);};
extern Rva00136A21 g_00DF29B4;
void rva00136B5E(const char*name,const char*value){
 if(name&&value){
  Rva00131DCBTextureRef tex((const BfmeResetAnyRef&)Rva009EBCE0_GetPrototype(name));
  unsigned id=tex.Ptr?*(unsigned*)((char*)tex.Ptr+8):~0u;
  AsciiString&dst=g_00DF29B4.rva00136A21(id);((StringBase<char>*)&dst)->set(value);
 }
}
