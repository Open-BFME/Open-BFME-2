// ?rva001818C0@BfmeFVFDescriptor@@QAEPAXXZ
// Native 0x001818C0..0x00181F69 (1705 B): builds the D3D vertex declaration (element table) for an FVF descriptor and
// hands it to the device's CreateVertexDeclaration (vtable +0x158). Element records are 8 bytes, stored in the canonical
// ICoord2D-shaped vector so overflow resolves to the rowed vector<ICoord2D>::_M_insert_overflow (0x181770).
// U1 r8 (EXACT): container tests and fvf reads follow retail's register forms: `empty()` for the element check,
// `unsigned fb=fvf; if((fb&0xff)&4)` (mov ecx,[ebp]; test cl,N) at the flag tests retail loads into ECX, the plain `fvf&N`
// memory-form test where retail tests memory, and the texture-count read before the usage/index stores.
// cl: /ICode/Libraries/Include /O2 /G7 /EHs /Ob2 /arch:SSE /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Op /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
#include <vector>
#include "Lib/ICoord2D.h"
// Preserve STLport operations inline without unused external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline const unsigned int &
max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
 return a < b ? b : a;
}
}
struct FxVertexElement {unsigned short stream,offset;unsigned char type,method,usage,index;};

namespace _STL {
// Keep STLport's copy loop inline without a competing external copy. Placement
// new, not _Construct (which the import-inline body calls out of line), so the
// emitted vector<ICoord2D>::_M_insert_overflow is retail's 259-byte body
// (0x00181770, MapUtil.cpp's copy).
template <> __declspec(dllimport) __forceinline ICoord2D *
__uninitialized_copy<ICoord2D *, ICoord2D *>(ICoord2D *first, ICoord2D *last, ICoord2D *result, const __false_type &)
{
 ICoord2D *cur = result;
 for (; first != last; ++first, ++cur)
  new (cur) ICoord2D(*first);
 return cur;
}
typedef vector<ICoord2D> FxVertexElements;
template<> __forceinline void FxVertexElements::push_back(const ICoord2D &value) {
 if(this->_M_finish!=this->_M_end_of_storage._M_data){_Construct(this->_M_finish,value);++this->_M_finish;}
 else _M_insert_overflow(this->_M_finish,value,_IsPODType(),1UL,true);
}
}
struct IDirect3DDevice8;
class BfmeFVFDescriptor;
#include "DX8WrapperClass.h"
struct FxDeclarationDevice {
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
 V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
 V10(1) V10(2) V10(3) V10(4) V10(5) V10(6) V10(7)
 V(80) V(81) V(82) V(83) V(84) V(85)
#undef V10
#undef V
 virtual long __stdcall CreateVertexDeclaration(const FxVertexElement *,void **);
};
class BfmeFVFDescriptor
{
public:
	BfmeFVFDescriptor(unsigned,unsigned,bool,unsigned);
	__declspec(noinline) void Initialize(unsigned,unsigned,bool,unsigned);
	void *rva001818C0();
	unsigned fvf; // +0x00
	bool additionalBasis; // +0x04
	char m_pad05[0x3];
	unsigned extensionCount; // +0x08
	unsigned stride; // +0x0C
	unsigned locationOffset; // +0x10
	unsigned extensionOffset; // +0x14
	unsigned normalOffset; // +0x18
	unsigned extensionEnd; // +0x1C
	unsigned blendOffset; // +0x20
	unsigned textureOffsets[8]; // +0x24
	unsigned diffuseOffset; // +0x44
	unsigned specularOffset; // +0x48
	unsigned basisOffset; // +0x4C
	unsigned basisSecondOffset; // +0x50
	unsigned basisEnd; // +0x54
	unsigned extensionDataOffset; // +0x58
	unsigned formatIndex; // +0x5C
};
void *BfmeFVFDescriptor::rva001818C0()
{
 _STL::vector<ICoord2D> elements;
 FxVertexElement e;
 unsigned format;
 elements.reserve(16);
 e.stream=0;e.offset=0;e.type=0;e.method=0;e.usage=0;e.index=0;
 unsigned f0=fvf; if((f0&0xff)&2) {e.type=2;e.usage=0;elements.push_back(*(const ICoord2D *)&e);e.offset=12;}
 unsigned fb=fvf;if((fb&0xff)&4) {e.type=3;e.usage=9;elements.push_back(*(const ICoord2D *)&e);e.offset+=16;}
 format=fvf;if((format&0x4002)==0x4002) {e.type=3;e.usage=0;elements.push_back(*(const ICoord2D *)&e);e.offset+=16;}
 if(elements.empty())return 0;
 if(fvf&0x10) {e.type=2;e.usage=3;elements.push_back(*(const ICoord2D *)&e);e.offset+=12;}
 if(fvf&0x20) {e.type=0;e.usage=4;elements.push_back(*(const ICoord2D *)&e);e.offset+=4;}
 unsigned fb2=fvf;if((fb2&0xff)&0x40) {e.type=4;e.usage=10;elements.push_back(*(const ICoord2D *)&e);e.offset+=4;}
 if(fvf&0x80) {e.type=4;e.usage=10;e.index=1;elements.push_back(*(const ICoord2D *)&e);e.offset+=4;}
 format=fvf; int textures=(format>>8)&15;
 e.usage=5;e.index=0;
 while(e.index<textures) {
  int dimension=0;
  unsigned code=(fvf>>(16+e.index*2))&3;
  if(code==3)dimension=1;
  else if(0 == code)dimension=2;
  else if(code==1)dimension=3;
  else if(code==2)dimension=4;
  e.type=dimension-1;
  elements.push_back(*(const ICoord2D *)&e);
  ++e.index;e.offset+=dimension*4;
 }
 e.index=0;
 if(additionalBasis) {
  e.type=2;e.usage=6;elements.push_back(*(const ICoord2D *)&e);e.offset+=12;
  e.type=2;e.usage=7;elements.push_back(*(const ICoord2D *)&e);e.offset+=12;
 }
 if(extensionCount>0) {
  e.type=4;e.usage=2;elements.push_back(*(const ICoord2D *)&e);e.offset+=4;
  if(extensionCount>1) {
   e.type=extensionCount-1;e.usage=1;elements.push_back(*(const ICoord2D *)&e);e.offset+=extensionCount*4;
   e.type=2;e.usage=0;e.index=1;elements.push_back(*(const ICoord2D *)&e);e.offset+=12;
   e.type=2;e.usage=3;e.index=1;elements.push_back(*(const ICoord2D *)&e);
  }
 }
 e.stream=0xff;e.offset=0;e.type=17;e.method=0;e.usage=0;e.index=0;
 elements.push_back(*(const ICoord2D *)&e);
 void *result=0;
 if(((FxDeclarationDevice*)DX8Wrapper::D3DDevice)->CreateVertexDeclaration((const FxVertexElement *)&elements[0],&result)<0)return 0;
 return result;
}
