// ??1Rva003F2D03@@QAE@XZ
// cl: /Ireference/shims/bfme2_ascii /O1 /EHs /arch:SSE /ICode/Libraries/Include/Lib /Ireference/shims/bfmealloc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ??1Rva003F2D03@@QAE@XZ @0x003F2D03 545B
// Target bytes show two DeleteRange calls over members at +0xfc/+0x100 and
// +0x08/+0x0c, then reverse member teardown, two Release_Ref calls and a
// Snapshot vtable restore at +0x78. Callees: 0x003F2BEB 0x003F1E87
// 0x00036410 0x00030830 0x003F1797 0x00050ED3 0x0002CC70; EH states 0x1d..0.
// Constructor3F3749..3F3967 and parser210620 independently prove this
// 118B descriptor is embedded at region14; original class spelling remains
// unresolved. BF1 f989 region descriptor destructor is a semantic/layout
// lead only. All offsets and defaults below come from target ctor/dtor.
// Header views use the established29B empty BfmeE16 base constructor solely
// for its three-pointer initialization; no16B application element identity
// is asserted. Its ctor/proxy and29B bonus ctor only store, so nothrow
// declarations preserve the native EH frontier. Full545B dtor remains exact.
// Structural inference: this is an address-named cleanup object in the
// Common/System chain. Adjacent LivingWorldRegionConnection functions do not
// establish this object's real class name. No named donor source was used.
#include <vector>
#include <string>
#include "ascii_string.h"
#include "Coord2D.h"

extern "C" void __cdecl free(void *block);

extern const void *const g_00BBB554[];

class Rva000D1930 {public:__declspec(nothrow) Rva000D1930();int *vtable;int values[6];};
class Snapshot78 {public:__forceinline Snapshot78(){}~Snapshot78(){*(const void **)this=g_00BBB554;}__forceinline void reset(){bonus.values[0]=0;bonus.values[1]=0;bonus.values[2]=0;bonus.values[3]=0;bonus.values[4]=0;bonus.values[5]=0;}Rva000D1930 bonus;};
class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct BfmeE16{float x,y,z,w;};
namespace _STL {
template<>void allocator<BfmeE16>::deallocate(pointer p,size_type)const{free(p);}
template<>__declspec(nothrow) _Vector_base<BfmeE16,allocator<BfmeE16> >::_Vector_base(const allocator<BfmeE16>&);
template<>__declspec(nothrow) _Vector_base<AsciiString,allocator<AsciiString> >::_Vector_base(const allocator<AsciiString>&);
}
struct PtrTriple:public _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >{using _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::_M_start;using _STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::_M_finish;__forceinline PtrTriple():_STL::_Vector_base<BfmeE16,_STL::allocator<BfmeE16> >(_STL::allocator<BfmeE16>()){} };
struct FreeStore:public PtrTriple{__forceinline FreeStore(){}};
struct RefStore{RefStore():p(0){}~RefStore(){if(p)p->Release_Ref();}OpaqueRefCounted*p;};
class Rva003F0C6C;
struct Rva003F1E87Holder
{
	bool flag;
	void doDelete(Rva003F0C6C *p);
};

bool __cdecl Rva003F2BEBDeleteRange(
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > **first,
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > **last,
	bool flag);

bool __cdecl Rva003F1E87DeleteRange(Rva003F0C6C **first, Rva003F0C6C **last, Rva003F1E87Holder h);

class LivingWorldRegionConnection;
struct Rva003F1797:public PtrTriple
{
	~Rva003F1797();
 __forceinline Rva003F1797(){}

};

struct RegionZeroCoord:public Coord2D{__forceinline RegionZeroCoord(){x=0;y=0;}};
class Rva003F2D03
{
public:
	~Rva003F2D03();
 Rva003F2D03(const AsciiString &name);
private:
	AsciiString m00; // +0x00
	AsciiString m04; // +0x04
	PtrTriple m08; // +0x08 (first/last/end)
	_STL::vector<AsciiString> m14; // +0x14
	AsciiString m20; // +0x20
	AsciiString m24; // +0x24
	AsciiString m28; // +0x28
	AsciiString m2c; // +0x2c
	AsciiString m30; // +0x30
	AsciiString m34; // +0x34
	RefStore m38; // +0x38
	RefStore m3c; // +0x3c
	AsciiString m40; // +0x40
	int m44,m48; // +0x44
	Rva003F1797 m4c; // +0x4c
	AsciiString m58; // +0x58
	AsciiString m5c; // +0x5c
	FreeStore m60; // +0x60
	RegionZeroCoord m6c;bool m74,m75;char m76_pad[2]; // +0x64
	Snapshot78 m78; // +0x78
	bool m94,m95,m96,m97;int m98;RegionZeroCoord m9c; // +0x7c
	AsciiString ma4; // +0xa4
	FreeStore ma8; // +0xa8
	 // +0xac
	FreeStore mb4; // +0xb4
	 // +0xb8
	FreeStore mc0; // +0xc0
	 // +0xc4
	AsciiString mcc; // +0xcc
	FreeStore md0; // +0xd0
	 // +0xd4
	FreeStore mdc; // +0xdc
	 // +0xe0
	FreeStore me8; // +0xe8
	int mf4,mf8; // +0xec
	PtrTriple mfc; // +0xfc
	bool m108;char m109_pad[3]; // +0x108
	AsciiString m10c; // +0x10c
	AsciiString m110; // +0x110
	AsciiString m114; // +0x114
};

Rva003F2D03::~Rva003F2D03()
{
	{
		void *first = mfc._M_start;
		Rva003F1E87Holder h1 = Rva003F1E87Holder();
		void *last = mfc._M_finish;
		Rva003F2BEBDeleteRange(
			(_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > **)first,
			(_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > **)last,
			h1.flag);
	}
	{
		void *first = m08._M_start;
		Rva003F1E87Holder h2 = Rva003F1E87Holder();
		void *last = m08._M_finish;
		Rva003F1E87DeleteRange((Rva003F0C6C **)first, (Rva003F0C6C **)last, h2);
	}
}

struct BfmePod8{int a,b;};
namespace _STL{template<>BfmePod8 *vector<BfmePod8>::erase(BfmePod8*,BfmePod8*);template<>void**vector<void*>::erase(void**,void**);}
struct ConnectionVec{LivingWorldRegionConnection*rva003F35B0(LivingWorldRegionConnection*,LivingWorldRegionConnection*);LivingWorldRegionConnection*start,*finish;};
Rva003F2D03::Rva003F2D03(const AsciiString &name)
 :m00(name),m04(),m14(_STL::allocator<AsciiString>()),m20("APT:LivingWorldRegionConqueredNotice"),m24(),m28(),m2c(),m30(),m34(),m40(),m44(20),m48(0),m58(),m5c(),m74(true),m75(false),m94(false),m95(false),m96(false),m97(false),m98(0),ma4(),mcc(),mf4(1000),mf8(400),m108(false),m10c(),m110(),m114()
{

 {ConnectionVec *v=(ConnectionVec*)&m4c;v->rva003F35B0(v->start,v->finish);}
 {_STL::vector<BfmePod8> *v=(_STL::vector<BfmePod8>*)&m60;v->erase(v->begin(),v->end());}
 {_STL::vector<void*> *v=(_STL::vector<void*>*)&ma8;v->erase(v->begin(),v->end());}
 {_STL::vector<void*> *v=(_STL::vector<void*>*)&mb4;v->erase(v->begin(),v->end());}
 {_STL::vector<void*> *v=(_STL::vector<void*>*)&mc0;v->erase(v->begin(),v->end());}
 m78.reset();
 {_STL::vector<BfmePod8> *v=(_STL::vector<BfmePod8>*)&md0;v->erase(v->begin(),v->end());}
 {_STL::vector<BfmePod8> *v=(_STL::vector<BfmePod8>*)&mdc;v->erase(v->begin(),v->end());}
 {_STL::vector<BfmePod8> *v=(_STL::vector<BfmePod8>*)&me8;v->erase(v->begin(),v->end());}
}

typedef char RegionDefinitionSizeCheck[sizeof(Rva003F2D03)==0x118?1:-1];
