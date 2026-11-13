// cl: /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -ICode/Libraries/Source/WWVegas/WW3D2
// stlport
// RenderableStandingWaterArea::createTexture: native 0x0007EDBC..0x0007EEB0,
// 244 bytes, RET4. WB 0x0073EFF0 identifies the method and W3DWater.cpp.
// Native calls and member accesses prove area+40, texture slots+50, and
// the 60/62/61 fallback order for slot zero. The matched river-water
// createTexture at 7EEBE supplies the loader's counted return lifetime.
// StringBase<char>'s canonical header owns isEmpty; the native string
// prefix read proves its shared-buffer data starts eight bytes later.
// The canonical RenderObjClass and CameraClass, included first: rendobj.h reaches Zero Hour's refcount.h,
// multilist.h and vector3.h, so the canonical RefCountData.h, MultiListObjectClass.h and Vector3Data.h this
// unit includes later add nothing (one definition each). BFME_RO_DTOR_DECL_ONLY keeps the destructor a call to
// retail's 0x0013BE20.
#define BFME_RO_DTOR_DECL_ONLY
#include "../../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"
#define __PLACEMENT_VEC_NEW_INLINE  // always.h defines array placement-new itself
#include <vector>
class ModuleData;
#include "string_base.h"
#include "../../../../../GameEngine/Include/Common/Rva0030812E.h"
enum WW3DFormat { WW3D_FORMAT_UNKNOWN = 0 };
class W3DRadarFormatCaps { public: bool supportTextureFormat(WW3DFormat format); };
class DX8Caps;
class TextureClass;
class ZTextureClass;
struct IDirect3DSurface8;
class DX8Wrapper {
 friend class RenderableStandingWaterArea;
public:
 static void Set_Render_Target_With_Z(TextureClass *texture, ZTextureClass *ztexture);
 static void Set_Render_Target(IDirect3DSurface8 *renderTarget, bool useDefaultDepthBuffer);
protected:
 static DX8Caps *CurrentCaps;
};
class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
	int m_pad[2];
};

template <class T>
class RefCountPtr
{
public:
	const RefCountPtr &operator=(const RefCountPtr &other);
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
	T *m_ptr;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

#include "../../../../Include/W3DDevice/GameClient/TextureAsset.h"


#include "../../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"
class RenderableStandingWaterArea {
public:
 void createTexture(int index);
 void AllocateAndFillBuffers();
 const Vector3 *getBoundaryPoint(int i) {return boundary.begin()+i;}
private:
 char m_pad00[0x14];
 _STL::vector<Vector3> boundary;
 char m_pad20[0x20];
 Rva0030812E *m_area;
 char m_unknown44[0x0c];
 BFME2ParticleTextureHandle m_textures[4];
 char m_pad60[0x10];
 // Existing pointer-sized vector instantiation; concrete element names
 // remain unproven. Native offsets and resource ownership are verified.
 _STL::vector<const ModuleData*> vertexBuffers,vertexCounts,indexBuffers,indexCounts;
};
void RenderableStandingWaterArea::createTexture(int index) {
 StringBase<char> *s=(StringBase<char>*)m_area->getTextureName(index);
 if (!s->isEmpty()) {
  if (index == 0) {
   int format=0;
   if (reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)0x3c)) format=0x3c;
   else if (reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)0x3e)) format=0x3e;
   else if (reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)0x3d)) format=0x3d;
   const char *data=*(const char *const *)s;
   m_textures[0] = TextureAsset::Get(data ? data+8 : "",1,format);
  } else {
   const char *data=*(const char *const *)s;
   m_textures[index] = TextureAsset::Get(data ? data+8 : "",0,0);
  }
 }
}

// Native 00082140..000822F7,439B; WB742CF0 WaterRenderObjClass destructor.
// Reference BFME1 575ba2b04 WaterRenderObjVirtualDestructor.cpp provides
// resource teardown semantics; target owns three area-list observers and
// different member offsets. Retain the existing opaque owner spelling.
#include "Common/Snapshot.h"
#include <string.h>
#include <vector>
#include <new>
#include "ascii_string.h"
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
#include "../../../../../Libraries/Source/WWVegas/WW3D2/IndexBufferClass.h"
#include "../../../../../Libraries/Source/WWVegas/WWLib/MultiListObjectClass.h"
template<int N> class WaterAreaObserver {public: virtual ~WaterAreaObserver(){} };
class CreateAHeroData;
#include "../../../../../GameEngine/Include/Common/Rva002B7250.h"
struct WaterTextureHandle { TextureBaseClass *ptr; WaterTextureHandle():ptr(0){} ~WaterTextureHandle(){if(ptr)ptr->Release_Ref();} };
struct WaterCountedRef {
 RefCountClass *ptr;
 WaterCountedRef():ptr(0){}
 WaterCountedRef(RefCountClass *refCount):ptr(refCount){}
 __forceinline ~WaterCountedRef(){ RefCountClass *refCount=ptr; if(refCount) refCount->Release_Ref(); }
};
#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"
// The unit's vectors use STLport's own empty construction; their destructor
// is the existing out-of-line instantiation.
namespace _STL {
template<> vector<TreeHintRef00217D4C>::~vector();
// Use the rowed retail folds for out-of-line vector storage cleanup.
template<> _Vector_base<TreeHintRef00217D4C, allocator<TreeHintRef00217D4C> >::~_Vector_base();
template<> void allocator<TreeHintRef00217D4C>::deallocate(TreeHintRef00217D4C *, size_t) const;
}
#include "../../../../Include/W3DDevice/GameClient/WaterTracksRenderSystem.h"
#include "../../../../../GameEngine/Include/Common/Rva0007E12F.h"
void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
// Native destructor EH cleanup 75F6F6 uses the existing device-lock
// destructor 42F8C, paired with lock 11F520 and release 120F50.
#include "../../../../Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"
class WaterSetting;
extern WaterSetting WaterSettings[];
struct WaterSettingClearView {
 void *vtable;
 AsciiString sky,water;
 char rest[0x7C-0xC];
};
class WaterTransparencySetting;
// The native slot is the scalar-deleting destructor ABI, flags=0 and
// returned allocation pointer, followed by the separate game deallocator.
class WaterTransparencyDeleteView {public: virtual void *destroy(unsigned flags);};
template<class T> class OVERRIDE {public: T *ptr;};
extern OVERRIDE<WaterTransparencySetting> TheWaterTransparency;
class WaterRenderObjClass : public Snapshot,public RenderObjClass,
 public WaterAreaObserver<0>,public WaterAreaObserver<1>,public WaterAreaObserver<2> {
public: WaterRenderObjClass(); virtual ~WaterRenderObjClass();
 // Retail's table (VA 0x00BC7108) overrides six of RenderObjClass's 129 slots: the deleting destructor, these
 // two, Render and the two bounding volumes. Clone and Class_ID are one-instruction bodies retail folded with
 // others (0x000D43D0 xor eax,eax; 0x0036CC7A or eax,-1).
 virtual RenderObjClass *Clone(void) const { return 0; }
 virtual int Class_ID(void) const { return CLASSID_UNKNOWN; }
 virtual void Render(RenderInfoClass &rinfo);
 virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &sphere) const;
 virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const;
 struct Setting {Setting():skyTexture(0),waterTexture(0){} ~Setting(); TextureBaseClass *skyTexture,*waterTexture; char data[0x28];};
 void rva0007F87C(void *scene, CameraClass *camera);
private:
 int fieldD4;
 unsigned fieldD8;
 float fieldDC,fieldE0,fieldE4,fieldE8;
 int fieldEC;
 bool fieldF0;
 int fieldF4;
 WaterTextureHandle textureF8;
 WaterCountedRef refFC;
 WaterTracksRenderSystem *tracks100;
 Rva002B7250 *standing104;
 _STL::vector<TreeHintRef00217D4C> standing108;
 Rva002B7250 *rivers114;
 _STL::vector<TreeHintRef00217D4C> rivers118;
 Rva002B7250 *waves124;
 WaterCountedRef ref128;
 float field12C,field130;
 bool field134,field135;
 Setting settings138[6];
 int field258;
 bool field25C;
 int field260;
};
// Native 00082329..000824C3,410B, the WaterRenderObjClass constructor: it
// stores the vtables this unit's destructor restores and builds the members
// the destructor's unwind map tears down, in the same order (EH states 5..A).
WaterRenderObjClass::WaterRenderObjClass()
 : fieldD4(0),fieldD8(0x10441B),fieldDC(0),fieldE0(0),fieldE4(0),fieldE8(0),
   fieldEC(0),fieldF0(false),fieldF4(0),
   refFC(new CameraClass),tracks100(0),standing104(0),rivers114(0),waves124(0),
   field12C(0),field130(0),field134(false),field135(false),
   field258(2),field25C(false),field260(0)
{
 memset(settings138,0,sizeof(settings138));
}
WaterRenderObjClass::~WaterRenderObjClass() {
 if(standing104) {
  standing104->rva002B7250(reinterpret_cast<CreateAHeroData*>(static_cast<WaterAreaObserver<0>*>(this)));standing104=0;
  rivers114->rva002B7250(reinterpret_cast<CreateAHeroData*>(static_cast<WaterAreaObserver<1>*>(this)));rivers114=0;
  waves124->rva002B7250(reinterpret_cast<CreateAHeroData*>(static_cast<WaterAreaObserver<2>*>(this)));waves124=0;
 }
 BFMEDX8DeviceLock guard;
 for(int i=0;i<6;++i) {
  reinterpret_cast<WaterSettingClearView*>(WaterSettings)[i].sky.clear();
  reinterpret_cast<WaterSettingClearView*>(WaterSettings)[i].water.clear();
 }
 WaterTransparencyDeleteView *transparency=reinterpret_cast<WaterTransparencyDeleteView*>(TheWaterTransparency.ptr);
 ::operator delete(transparency ? transparency->destroy(0) : 0);
 TheWaterTransparency.ptr=0;
 reinterpret_cast<Rva0007E12F*>(this)->rva0007E12F();
 if(tracks100)delete tracks100;
}

// Native 0x0007F87C..0x0007F92A, 174B, RET8: the reflection pass. After the
// mirror camera setup 0x0007F0FB, a live mirror camera (+0xFC) renders the
// scene into the reflection texture (+0xF8): the render target is set with
// an empty z texture holder, the frame begins cleared to black (WW3D::Begin_Render
// 0x00118170) and, when it begins, the scene is drawn through 0x00118660
// and the frame ended; the camera projection override byte is cleared and
// the default render target restored. WB 0x007492F0 (unnamed) has the same
// call chain. The method name stays address-derived.

#include "../../../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"
bool Rva00118660Call(void *scene, void *camera);
extern bool bfmeCameraProjectionOverride;
class Rva0007F0FBOwner {public: void rva0007F0FB(CameraClass *camera, bool flag);};
void WaterRenderObjClass::rva0007F87C(void *scene, CameraClass *camera) {
 reinterpret_cast<Rva0007F0FBOwner*>(this)->rva0007F0FB(camera,false);
 if(refFC.ptr) {
  {
   WaterTextureHandle zbuffer;
   DX8Wrapper::Set_Render_Target_With_Z((TextureClass*)&textureF8,(ZTextureClass*)&zbuffer);
  }
  if(WW3D::Begin_Render(true,true,Vector3(0.0f,0.0f,0.0f),0.0f)) {
   Rva00118660Call(scene,refFC.ptr);
   WW3D::End_Render(false);
  }
  bfmeCameraProjectionOverride=false;
  DX8Wrapper::Set_Render_Target(0,false);
 }
}

#include <vector>
#include <string.h>
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
#define fill bfmeLoaderHeaderFill
#include <stl/_algobase.h>
#undef fill
namespace _STL { void fill(char *, char *, const char &); }
namespace _STL { static inline const unsigned int &max(const unsigned int &a, const unsigned int &b) { return a < b ? b : a; } }
#include <vector>
#include "ascii_string.h"
namespace _STL { extern template char *__uninitialized_copy(char *, char *, char *, const __true_type &); }
namespace _STL { extern template char *uninitialized_fill_n<char *,unsigned int,char>(char *,unsigned int,const char &); }
namespace _STL { extern template char *fill_n<unsigned int>(char *, unsigned int, const char &); }
void Rva00030830FreeAllocation(void *);
namespace _STL { template <> inline void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *p, size_t n) { if(p) Rva00030830FreeAllocation(p); } }


namespace _STL {
template <> inline
allocator<char> &__stl_alloc_rebind(allocator<char> &a, const char *) { return a; }
}
// Preserve visible inline operations without emitting competing /O1 copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
char *_STLP_alloc_proxy<char *,char,allocator<char> >::allocate(size_t n) {
    return __stl_alloc_rebind(static_cast<allocator<char> &>(*this), (char *)0).allocate(n,0);
}
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Vector_base<char, allocator<char> >::~_Vector_base() {
    if (_M_start != 0)
        _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
}
}

// game.dat's STLport passes vector<char>::resize's fill by value (the rowed
// 0x000826E3 body; the call site pushes the byte itself), so this unit
// specializes vector<char> to that interface. The count constructor and
// resize are the rowed out-of-line bodies; swap is STLport's inline one.
// The members resize reaches keep STLport 4.5.3's bodies, so the compiler
// sees that the vector's address is not retained across the file calls.
namespace _STL
{
template <>
class vector<char, allocator<char> > : public _Vector_base<char, allocator<char> >
{
public:
	typedef allocator<char> allocator_type;
	typedef unsigned int size_type;

	explicit vector(const allocator_type &a = allocator_type()) : _Vector_base<char, allocator<char> >(a) {}
	explicit vector(size_type n);

	char *begin() { return this->_M_start; }
	char *end() { return this->_M_finish; }
	size_type size() const { return size_type(this->_M_finish - this->_M_start); }
	char *erase(char *first, char *last)
	{
		char *i = __copy_ptrs(last, this->_M_finish, first, __true_type());
		_Destroy(i, this->_M_finish);
		this->_M_finish = i;
		return first;
	}
protected:
	void _M_clear()
	{
		_Destroy(this->_M_start, this->_M_finish);
		this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
	}
	void _M_set(char *s, char *f, char *e)
	{
		this->_M_start = s;
		this->_M_finish = f;
		this->_M_end_of_storage._M_data = e;
	}
	void _M_insert_overflow(char *position, const char &value, const __true_type &, unsigned int fill_len, bool at_end = false)
	{
    const unsigned int old_size = this->_M_finish - this->_M_start;
    char *new_start;
    const unsigned int new_len = old_size + (max)(old_size, fill_len);
    if (new_len != 0)
        new_start = this->_M_end_of_storage.allocate(new_len);
    else
        new_start = 0;
    char *new_finish = (char *)_STL::__copy_trivial(this->_M_start, position, new_start);
    new_finish = _STL::fill_n(new_finish, fill_len, value);
    if (!at_end)
        new_finish = (char *)_STL::__copy_trivial(position, this->_M_finish, new_finish);
    this->_M_clear();
    this->_M_set(new_start, new_finish, new_start + new_len);
}
public:
	void _M_fill_insert(char *position, size_type n, const char &x);

	char &operator[](size_type n) {return this->_M_start[n];}
	void resize(size_type newSize, char x)
	{
		if (newSize < size())
			erase(begin() + newSize, end());
		else
			_M_fill_insert(end(), newSize - size(), x);
	}
	void swap(vector<char, allocator<char> > &x)
	{
		_STLP_STD::swap(this->_M_start, x._M_start);
		_STLP_STD::swap(this->_M_finish, x._M_finish);
		_STLP_STD::swap(this->_M_end_of_storage, x._M_end_of_storage);
	}
};

inline void vector<char, allocator<char> >::_M_fill_insert(char *position, size_type n, const char &x)
{
	if (n != 0) {
		if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= n) {
			char xCopy = x;
			const size_type elemsAfter = this->_M_finish - position;
			char *oldFinish = this->_M_finish;
			if (elemsAfter > n) {
				(char *)__copy_trivial(this->_M_finish - n, this->_M_finish, this->_M_finish);
				this->_M_finish += n;
				__copy_backward_ptrs(position, oldFinish - n, oldFinish, __true_type());
				_STLP_STD::fill(position, position + n, xCopy);
			} else {
				uninitialized_fill_n(this->_M_finish, n - elemsAfter, xCopy);
				this->_M_finish += n - elemsAfter;
				(char *)__copy_trivial(position, oldFinish, this->_M_finish);
				this->_M_finish += elemsAfter;
				_STLP_STD::fill(position, oldFinish, xCopy);
			}
		} else
			_M_insert_overflow(position, x, __true_type(), n);
	}
}
}

struct BfmeE12 { float x,y,z; };
namespace _STL { template<> vector<BfmeE12>::~vector(); }
#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
namespace _STL { template<> vector<BfmeE16>::~vector(); }
struct BfmePod44 {int a[11];};
// These out-of-line operations retain the existing retail providers. Keep
// this /O1 unit from selecting non-retail copies of their template bodies.
namespace _STL {
 template<> void vector<BfmePod44>::resize(size_t);
 template<> BfmePod44 *vector<BfmePod44>::erase(BfmePod44 *, BfmePod44 *);
 template<> void vector<BfmePod44>::_M_fill_insert(BfmePod44 *, size_t, const BfmePod44 &);
 template<> void vector<BfmePod44>::_M_insert_overflow(BfmePod44 *, const BfmePod44 &, const __false_type &, size_t, bool);
 template<> void vector<BfmePod44>::reserve(size_t);
}
void Rva00030830FreeAllocation(void *);
namespace _STL {
 template<> inline void allocator<BfmeE12>::deallocate(BfmeE12 *p,size_type) const {if(p) Rva00030830FreeAllocation(p);}
 template<> inline void allocator<BfmeE16>::deallocate(BfmeE16 *p,size_type) const {if(p) Rva00030830FreeAllocation(p);}
}
class Rva00082A53 {
 int self;
 _STL::vector<BfmeE12> cells;
 int dimX,dimY;
 public:
 _STL::vector<BfmeE16> records;
 int origin[3]; float spacing;
 __declspec(noinline) Rva00082A53(int,int,int,float,int*,int);
 ~Rva00082A53();
 unsigned short rva00082E33(int,int);
};
class ModuleData;
#include "../../../../../GameEngine/Include/GameLogic/Module/Rva00081F03.h"
class Rva0030D111Shape {public:virtual int count();};
bool Rva0030D111Contains(Rva0030D111Shape*,const Coord2D*);
#include "../../../../../Libraries/Include/Lib/Region2D.h"
#include "../../../../../GameEngine/Include/GameLogic/PolygonTrigger.h"
class GameLODManager;
extern GameLODManager *TheGameLODManager;
void BFME_DX8_Thread_Lock();

#include "../../../../../Libraries/Source/WWVegas/WW3D2/DX8IndexBufferClass.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/VertexBufferClass.h"
class BfmeDynamicNativeVB {
 public:char record[32];
 BfmeDynamicNativeVB(unsigned,unsigned short,unsigned,unsigned);
};
class MathCoord2D {
public:
 MathCoord2D(){} MathCoord2D(float a,float b):x(a),y(b){}
 MathCoord2D(const MathCoord2D &p):x(p.x),y(p.y){} ~MathCoord2D(){}
 float x,y;
};
__declspec(noinline) MathCoord2D operator+(MathCoord2D,const MathCoord2D&);
inline int *BfmeOriginInts(const Vector3 &v){return (int*)&v;}

struct BfmeWordVec : _STL::vector<unsigned short> {
 void resize(unsigned int,unsigned short);
};
inline Rva00082A53::Rva00082A53(int a1,int a2,int a3,float a4,int *a5,int a6)
 :self(a1),cells(),dimX(a2+1),dimY(a3+1),records()
{
 origin[0]=a5[0];origin[1]=a5[1];origin[2]=a5[2];spacing=a4;
 int n=dimX*dimY;
 ((BfmeWordVec*)&cells)->resize((unsigned int)n,(unsigned short)0xFFFF);
 ((_STL::vector<BfmePod44>*)&records)->reserve((unsigned int)a6);
}

inline MathCoord2D operator+(MathCoord2D left,const MathCoord2D &right){left.x+=right.x;left.y+=right.y;return left;}

// Target82E33..82EB8 and WB740340 establish cached vertex lookup/append.
// Existing constructor proves cells04/dim10/records18/origin24/spacing30.
// Original nested class name remains a donor lead; neutral owner retained.
struct StandingWaveInfo;
class Rva0008026BStandingWaveQuery
{
public:
    void rva0008026B(StandingWaveInfo *record);
};

typedef _STL::vector<BfmePod44, _STL::allocator<BfmePod44> > BfmePod44Vector;

unsigned short Rva00082A53::rva00082E33(int x, int y)
{
    int index = y * dimX + x;
    unsigned short *cells = *(unsigned short **)((char *)this + 4);
    unsigned short *cell = cells + index;
    register unsigned short old_value = *cell;
    if (old_value != 0xFFFF) return old_value;
    {
        char **vec = (char **)((char *)this + 0x18);
        *cell = (unsigned short)(((int)vec[1] - (int)vec[0]) / 44);
        ((BfmePod44Vector *)((char *)this + 0x18))->resize(((int)vec[1] - (int)vec[0]) / 44 + 1);
        BfmePod44 *record = (BfmePod44 *)((char *)*(char **)((char *)this + 0x1C) - 44);
        *(float *)((char *)record + 0) = (float)x * spacing + *(float *)((char *)this + 0x24);
        *(float *)((char *)record + 4) = (float)y * spacing + *(float *)((char *)this + 0x28);
        record->a[2] = origin[2];
        ((Rva0008026BStandingWaveQuery *)self)->rva0008026B((StandingWaveInfo *)record);
    }
    return *cell;
}

// Native 0x0008304A..0x000834CE, 1156B; named WB 0x0073F580.
// WB establishes the two indexed mask passes, boundary vector at +0x14,
// capacity calculation and six cached indices per selected grid cell.
// Native bytes prove target offsets, 44-byte records, resource ownership and
// the helper calls. The cache class retains its existing neutral owner name.
// Its visible constructor and MathCoord2D addition are whole-body retail
// copies. The cache constructor and lookup rows live here with their caller.
void RenderableStandingWaterArea::AllocateAndFillBuffers() {
 reinterpret_cast<Rva00081F03*>(this)->rva00081F03();
 BFMEDX8DeviceLock guard;
 Region2D bounds=reinterpret_cast<PolygonTrigger*>(reinterpret_cast<char*>(m_area)+0x30)->rva0007E03A();
 int limit=60000;register float spacing=20.0f;
 if(TheGameLODManager && *reinterpret_cast<int*>(reinterpret_cast<char*>(TheGameLODManager)+0x1784)<=2){limit=30000;spacing=40.0f;}
 int nx,ny,total;
 do {
  nx=int(bounds.hi.x/spacing)-int(bounds.lo.x/spacing)+1;
  ny=int(bounds.hi.y/spacing)-int(bounds.lo.y/spacing)+1;
  total=nx*ny;
  if(total>limit)spacing*=2.0f;
 }while(total>limit);
 bounds.lo.x=(float)int(bounds.lo.x/spacing)*spacing;
 bounds.lo.y=(float)int(bounds.lo.y/spacing)*spacing;
 bounds.hi.x=float(int(bounds.hi.x/spacing))*spacing+spacing;
 bounds.hi.y=float(int(bounds.hi.y/spacing))*spacing+spacing;
 _STL::vector<char> flags;
 flags.resize(total,0);
 MathCoord2D half(spacing*.5f,spacing*.5f);
 MathCoord2D center=(*reinterpret_cast<MathCoord2D*>(&bounds))+half;
 int y;
 int count=0;

 for(y=0;y<ny;++y) {
  Coord2D pos;pos.y=y*spacing+center.y;
  for(int x=0;x<nx;++x){
   pos.x=x*spacing+center.x;

   Rva0030D111Shape *shape=m_area ? reinterpret_cast<Rva0030D111Shape*>(reinterpret_cast<char*>(m_area)+0x18+(*reinterpret_cast<int**>(reinterpret_cast<char*>(m_area)+0x18))[1]) : 0;
   bool in=Rva0030D111Contains(shape,&pos);
   int idx=y*nx+x;
   flags[idx]=in;
   count+=in;
  }
 }
 if(!count)return;
 {
  // WB keeps these counts separate; their lifetimes also fix native stack coloring.
  int numCells=count;
  int indexCount=numCells*2*3;
  int capacity=numCells*2+nx+1;
  Rva00082A53 cache(reinterpret_cast<int>(this),nx,ny,spacing,BfmeOriginInts(Vector3(bounds.lo.x,bounds.lo.y,getBoundaryPoint(0)->Z)),capacity);
  const ModuleData *ib=reinterpret_cast<const ModuleData*>(new DX8IndexBufferClass(indexCount,DX8IndexBufferClass::USAGE_DEFAULT));
  indexBuffers.push_back(ib);
  {
   IndexBufferClass::WriteLockClass lock(reinterpret_cast<IndexBufferClass*>(const_cast<ModuleData*>(indexBuffers.back())),0);
   unsigned short *out=lock.indices;
   for(y=0;y<ny;++y){
    for(int x=0;x<nx;++x) {
     int cell=y*nx+x;
     if(flags[cell]) {
      out[0]=cache.rva00082E33(x,y);
      out[1]=cache.rva00082E33(x+1,y+1);
      out[2]=cache.rva00082E33(x,y+1);
      out[3]=cache.rva00082E33(x,y);
      out[4]=cache.rva00082E33(x+1,y);
      out[5]=cache.rva00082E33(x+1,y+1);
      out+=6;
     }
    }
   }
  }
  _STL::vector<BfmePod44> *records = reinterpret_cast<_STL::vector<BfmePod44>*>(&cache.records);
  const ModuleData *vb=reinterpret_cast<const ModuleData*>(new BfmeDynamicNativeVB(0x252,records->size(),0,0));
  vertexBuffers.push_back(vb);
  {
   VertexBufferClass::WriteLockClass lock(reinterpret_cast<VertexBufferClass*>(const_cast<ModuleData*>(vertexBuffers.back())),0);
   memcpy(lock.Get_Vertex_Array(),records->begin(),records->size()*44);
  }
  int vc=records->size();vertexCounts.push_back(*reinterpret_cast<const ModuleData**>(&vc));
  indexCounts.push_back(*reinterpret_cast<const ModuleData**>(&indexCount));
 }
}
