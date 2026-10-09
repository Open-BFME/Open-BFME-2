// cl: /O1 /arch:SSE2 /D_STLP_USE_MALLOC /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference shape: ZH PlayerTemplate's automatic member copy, reconciled
// against target1FE352/957 and PlayerTemplate store/vector476-byte callers.
// Base copy3664DD resets the override links. The native EH map at9114D0
// independently proves37 owned-subobject states, including+1C8 destructor
// 360D26 and+2C root cleanup49B47C; these are target facts, not donor names.
// Field meanings remain neutral. Existing container/handle instantiations
// supply byte-proven constructor ABIs. Coord adapter inherits canonical data.

#include <map>
#include <hash_map>
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"
class Rva001E3624 {public: virtual ~Rva001E3624(); Rva001E3624(const Rva001E3624 &); Rva001E3624():next(0),flag(false),extra(-1){} void *next;bool flag;int extra; };
class Rva003B0E83 {public:Rva003B0E83*rva003B0E83();};
struct S3Handicap {__forceinline S3Handicap(){((Rva003B0E83*)this)->rva003B0E83();} int words[4];};
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class DamageInfo;
class Xfer
{
public:
	class Version;
	Xfer();
	virtual ~Xfer();
	void Version1();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;
	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);
	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class S3Money : public Snapshot { public: int words[2];
 __forceinline S3Money(){words[0]=0;words[1]=0;}
 // ?S3Money::S3Money present-unmatched
 __forceinline S3Money(const S3Money&r){words[0]=r.words[0];words[1]=r.words[1];}
 virtual ~S3Money() {}
 virtual void loadPostProcess();
 virtual const char* GetSnapshotName()const;
 virtual void xfer(Xfer*);
};
struct S3Coord { float x,y,z; };
struct Rva004216D3Coord : Coord3D {
 Rva004216D3Coord();
 Rva004216D3Coord(const Rva004216D3Coord &r) {x=r.x;y=r.y;z=r.z;}
 __declspec(noinline) ~Rva004216D3Coord() {}
};
struct Rva001FDCE1Record {Rva001FDCE1Record();Rva001FDCE1Record(const Rva001FDCE1Record&);~Rva001FDCE1Record();Rva001FDCE1Record&operator=(const Rva001FDCE1Record&);char bytes[1];bool operator<(const Rva001FDCE1Record&)const;bool operator==(const Rva001FDCE1Record&)const;};
struct Rva001FDAB0Less {bool operator()(int,int)const;};
enum ScienceType { S3ScienceForce=0x7fffffff };
struct Rva0021C21BElement { char bytes[4]; };
struct Rva0026F4F4Element { unsigned words[1]; bool operator<(const Rva0026F4F4Element &)const;bool operator==(const Rva0026F4F4Element &)const; };
namespace _STL {template<>struct __type_traits<Rva0026F4F4Element> : __type_traits_aux<1> {};}

struct TreeHintPayload003012F0 {unsigned a,b,c;TreeHintPayload003012F0(const TreeHintPayload003012F0 &r):a(r.a),b(r.b),c(r.c){}};
class BfmeFixedStorage0004543D {public:BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D&);char data[28];};
extern const BfmeFixedStorage0004543D g_009FEFA4;
struct Rva003623E5Member {void initFromStorages(BfmeFixedStorage0004543D,BfmeFixedStorage0004543D);};
struct Rva00360D26Member {Rva00360D26Member();~Rva00360D26Member();unsigned word;};
void __cdecl Rva00030830GameFree(void *);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);
class OpaqueRefCounted {public:virtual ~OpaqueRefCounted();void Release_Ref();long refs;};
struct Rva0010F149Handle {
 __forceinline Rva0010F149Handle():referent(0){}
 __declspec(noinline) __declspec(nothrow) Rva0010F149Handle(const Rva0010F149Handle &r);
 ~Rva0010F149Handle() {if(referent)referent->Release_Ref();}
 OpaqueRefCounted *referent;
};
Rva0010F149Handle::Rva0010F149Handle(const Rva0010F149Handle &r):referent(r.referent) {if(referent)InterlockedIncrement(&referent->refs);}
// ?Rva001FD42B::Rva001FD42B present-unmatched
struct Rva001FD42B { __forceinline Rva001FD42B(){typedef _STL::map<int,void*> T;((T*)this)->T::map();} __forceinline Rva001FD42B(const Rva001FD42B &r) {typedef _STL::map<int,void*> T;((T*)this)->T::map(*reinterpret_cast<const T*>(&r));} ~Rva001FD42B(); void *data[3];};
// ?Rva001FD458::Rva001FD458 present-unmatched
struct Rva001FD458 { __forceinline Rva001FD458(){typedef _STL::map<int,void*,Rva001FDAB0Less> T;((T*)this)->T::map();} __forceinline Rva001FD458(const Rva001FD458 &r) {typedef _STL::map<int,void*,Rva001FDAB0Less> T;((T*)this)->T::map(*reinterpret_cast<const T*>(&r));} ~Rva001FD458(); void *data[3];};
// ?Rva000427195::Rva000427195 present-unmatched
struct Rva000427195 { __forceinline Rva000427195(){typedef _STL::hash_map<int,Rva001FDCE1Record> T;((T*)this)->T::hash_map();} __forceinline Rva000427195(const Rva000427195 &r) {typedef _STL::hash_map<int,Rva001FDCE1Record> T;((T*)this)->T::hash_map(*reinterpret_cast<const T*>(&r));} ~Rva000427195(); void *data[5];};
extern template const unsigned int &_STL::max<unsigned int>(const unsigned int &,const unsigned int &);
namespace _STL {
template<> inline _Vector_base<ScienceType,allocator<ScienceType> >::~_Vector_base() {if(_M_start)Rva00030830GameFree(_M_start);}
template<> inline _Vector_base<unsigned int,allocator<unsigned int> >::~_Vector_base() {if(_M_start)Rva00030830GameFree(_M_start);}
}
struct Rva003B0E5DRecord {Rva003B0E5DRecord();AsciiString text;int a,b,c;};
struct BfmeObject476 : Rva001E3624 {
 BfmeObject476();
 virtual ~BfmeObject476();
 int unknown10;
 UnicodeString unknown14;
 AsciiString unknown18;
 S3Handicap unknown1c;
 S3Money unknown2c;
 S3Coord unknown38;
 AsciiString unknown44;
 AsciiString unknown48[10];
 Rva004216D3Coord unknown70[10];
 _STL::vector<AsciiString> unknowne8;
 Rva001FD42B unknownf4;
 Rva000427195 unknown100;
 Rva001FD458 unknown114;
 _STL::vector<ScienceType> unknown120,unknown12c;
 AsciiString unknown138,unknown13c,unknown140,unknown144;
 int unknown148;
 AsciiString unknown14c;
 bool unknown150,unknown151;
 Rva003B0E5DRecord unknown154;
 AsciiString unknown164,unknown168,unknown16c,unknown170,unknown174,unknown178,unknown17c;
 _STL::vector<AsciiString> unknown180,unknown18c,unknown198;
 Rva0010F149Handle unknown1a4,unknown1a8,unknown1ac;
 AsciiString unknown1b0,unknown1b4,unknown1b8;
 bool unknown1bc;
 AsciiString unknown1c0,unknown1c4;
 Rva00360D26Member unknown1c8;
 _STL::vector<unsigned int> unknown1cc;
 AsciiString unknown1d8;
};


// Compiler emission witness; no retail body is claimed for this wrapper.
// ?S3CopyConstruct476 absent-from-retail
BfmeObject476 *S3CopyConstruct476(void *where,const BfmeObject476 &src) { return new(where) BfmeObject476(src); }

typedef char BfmeObject476Extent[sizeof(BfmeObject476)==476?1:-1];

BfmeObject476::~BfmeObject476() {}

void S3Money::loadPostProcess() {}
const char *S3Money::GetSnapshotName() const {return "Money";}
void S3Money::xfer(Xfer *xfer) {xfer->Version1();*xfer == *(unsigned int*)&words[0];}

extern "C" void * __cdecl memset(void*,int,unsigned);
BfmeObject476::BfmeObject476():unknown10(0),unknown148(0),unknown150(false),unknown151(false),unknown1bc(false) {
unknown18="";unknown44="";unknown138="";unknown13c="";unknown140="";unknown144="";unknown14c="";
unknown38.x=unknown38.y=unknown38.z=0;
unknown17c="";unknown164="";unknown168="";unknown16c="";unknown170="";unknown174="";unknown178="";unknown17c="";
unknown180.clear();unknown1b0="";unknown1b4="";unknown1b8="";
((Rva003623E5Member*)&unknown1c8)->initFromStorages(g_009FEFA4,g_009FEFA4);
memset(unknown70,0,sizeof(unknown70));}

// Default constructor: target [1FEB8B,1FEEA3) is 792B through RET.
// Same aggregate as the copied476-byte record. The additional16-byte member
// ctor3B0E5D has its own24-byte RET boundary before3B0E75.
