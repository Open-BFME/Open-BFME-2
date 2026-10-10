// ?rva001818C0@Rva001818C0@@QAEPAXXZ
// partial score=0.711310650181467 date=2026-10-10
// cl: /O2 /G7 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /DNDEBUG /MD /EHsc /D_CRTIMP= /ICode/Libraries/Include
// stlport
// NEW1818C0..181F69 RET0. Native 8B records are D3D9 vertex elements, consumed
// by device COM slot158 (stdcall this+elements+output). Source object words:
// FVF0, tangent4, blendCount8. Original application owner/method unknown.
// BF1/ZH dx8fvf.cpp supplies FVF definitions and layout semantics; D3D9
// declaration/tangent/skin extensions are independently reconstructed from target.
// Native independent XYZ/XYZRHW/XYZW tests are preserved, including duplication.
// The existing ICoord2D vector8 provider is an ABI/storage view only: no
// coordinate semantics are inferred for these actual declaration records.
extern "C" void free(void*);
struct ICoord2D{int x,y;};
#include <vector>
typedef _STL::vector<ICoord2D,_STL::allocator<ICoord2D> > VertexVec8;
namespace _STL {
template<> void VertexVec8::_M_insert_overflow(ICoord2D*,const ICoord2D&,const __false_type&,unsigned,bool);
template<> __forceinline void VertexVec8::push_back(const ICoord2D&value) {
 if(this->_M_finish!=this->_M_end_of_storage._M_data){_Construct(this->_M_finish,value);++this->_M_finish;}
 else _M_insert_overflow(this->_M_finish,value,_IsPODType(),1UL,true);
}
}
struct VertexDeclElement{unsigned short stream,offset;unsigned char type,method,usage,index;};
union VertexDeclStorage {VertexDeclElement element;ICoord2D words;};
class VertexDeclDeviceView {public:
virtual void __stdcall s00();
virtual void __stdcall s01();
virtual void __stdcall s02();
virtual void __stdcall s03();
virtual void __stdcall s04();
virtual void __stdcall s05();
virtual void __stdcall s06();
virtual void __stdcall s07();
virtual void __stdcall s08();
virtual void __stdcall s09();
virtual void __stdcall s0A();
virtual void __stdcall s0B();
virtual void __stdcall s0C();
virtual void __stdcall s0D();
virtual void __stdcall s0E();
virtual void __stdcall s0F();
virtual void __stdcall s10();
virtual void __stdcall s11();
virtual void __stdcall s12();
virtual void __stdcall s13();
virtual void __stdcall s14();
virtual void __stdcall s15();
virtual void __stdcall s16();
virtual void __stdcall s17();
virtual void __stdcall s18();
virtual void __stdcall s19();
virtual void __stdcall s1A();
virtual void __stdcall s1B();
virtual void __stdcall s1C();
virtual void __stdcall s1D();
virtual void __stdcall s1E();
virtual void __stdcall s1F();
virtual void __stdcall s20();
virtual void __stdcall s21();
virtual void __stdcall s22();
virtual void __stdcall s23();
virtual void __stdcall s24();
virtual void __stdcall s25();
virtual void __stdcall s26();
virtual void __stdcall s27();
virtual void __stdcall s28();
virtual void __stdcall s29();
virtual void __stdcall s2A();
virtual void __stdcall s2B();
virtual void __stdcall s2C();
virtual void __stdcall s2D();
virtual void __stdcall s2E();
virtual void __stdcall s2F();
virtual void __stdcall s30();
virtual void __stdcall s31();
virtual void __stdcall s32();
virtual void __stdcall s33();
virtual void __stdcall s34();
virtual void __stdcall s35();
virtual void __stdcall s36();
virtual void __stdcall s37();
virtual void __stdcall s38();
virtual void __stdcall s39();
virtual void __stdcall s3A();
virtual void __stdcall s3B();
virtual void __stdcall s3C();
virtual void __stdcall s3D();
virtual void __stdcall s3E();
virtual void __stdcall s3F();
virtual void __stdcall s40();
virtual void __stdcall s41();
virtual void __stdcall s42();
virtual void __stdcall s43();
virtual void __stdcall s44();
virtual void __stdcall s45();
virtual void __stdcall s46();
virtual void __stdcall s47();
virtual void __stdcall s48();
virtual void __stdcall s49();
virtual void __stdcall s4A();
virtual void __stdcall s4B();
virtual void __stdcall s4C();
virtual void __stdcall s4D();
virtual void __stdcall s4E();
virtual void __stdcall s4F();
virtual void __stdcall s50();
virtual void __stdcall s51();
virtual void __stdcall s52();
virtual void __stdcall s53();
virtual void __stdcall s54();
virtual void __stdcall s55();
virtual long __stdcall createVertexDeclaration(const VertexDeclElement*,void**);
};
struct IDirect3DDevice8;
class DX8Wrapper{friend class Rva001818C0;protected:static IDirect3DDevice8*D3DDevice;};
class Rva001818C0 {public:void*rva001818C0();unsigned fvf;bool tangent;char pad05[3];unsigned blendCount;};
void*Rva001818C0::rva001818C0()
{
 _STL::vector<ICoord2D,_STL::allocator<ICoord2D> >elements;
 elements.reserve(16);
 VertexDeclStorage record;
 record.element.stream=0;record.element.offset=0;record.element.type=0;record.element.method=0;record.element.usage=0;record.element.index=0;
 if(fvf&2){record.element.type=2;record.element.usage=0;elements.push_back(record.words);record.element.offset=12;}
 if(fvf&4){record.element.type=3;record.element.usage=9;elements.push_back(record.words);record.element.offset+=16;}
 if((fvf&0x4002)==0x4002){record.element.type=3;record.element.usage=0;elements.push_back(record.words);record.element.offset+=16;}
 if(elements.begin()==elements.end())return 0;
 if(fvf&0x10){record.element.type=2;record.element.usage=3;elements.push_back(record.words);record.element.offset+=12;}
 if(fvf&0x20){record.element.type=0;record.element.usage=4;elements.push_back(record.words);record.element.offset+=4;}
 if(fvf&0x40){record.element.type=4;record.element.usage=10;elements.push_back(record.words);record.element.offset+=4;}
 if(fvf&0x80){record.element.type=4;record.element.usage=10;record.element.index=1;elements.push_back(record.words);record.element.offset+=4;}
 int textures=(fvf>>8)&15;record.element.usage=5;record.element.index=0;
 for(;record.element.index<textures;) {
  unsigned mode=(fvf>>(16+2*record.element.index))&3;unsigned size=0;
  if(mode==3)size=1;else if(mode==0)size=2;else if(mode==1)size=3;else if(mode==2)size=4;
  record.element.type=(unsigned char)(size-1);elements.push_back(record.words);
  record.element.index++;record.element.offset+=(unsigned short)(4*size);
 }
 record.element.index=0;
 if(tangent){record.element.type=2;record.element.usage=6;elements.push_back(record.words);record.element.offset+=12;record.element.type=2;record.element.usage=7;elements.push_back(record.words);record.element.offset+=12;}
 if(blendCount>0) {
  record.element.type=4;record.element.usage=2;elements.push_back(record.words);record.element.offset+=4;
  if(blendCount>1) {
   record.element.type=(unsigned char)(blendCount-1);record.element.usage=1;elements.push_back(record.words);record.element.offset+=(unsigned short)(4*blendCount);
   record.element.type=2;record.element.usage=0;record.element.index=1;elements.push_back(record.words);record.element.offset+=12;
   record.element.type=2;record.element.usage=3;record.element.index=1;elements.push_back(record.words);
  }
 }
 record.element.stream=0xFF;record.element.offset=0;record.element.type=17;record.element.method=0;record.element.usage=0;record.element.index=0;
 elements.push_back(record.words);
 void*result=0;
 long hr=((VertexDeclDeviceView*)DX8Wrapper::D3DDevice)->createVertexDeclaration((const VertexDeclElement*)elements.begin(),&result);
 if(hr<0)return 0;
 return result;
}
