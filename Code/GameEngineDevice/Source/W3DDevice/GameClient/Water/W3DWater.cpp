// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// RenderableStandingWaterArea::createTexture: native 0x0007EDBC..0x0007EEB0,
// 244 bytes, RET4. WB 0x0073EFF0 identifies the method and W3DWater.cpp.
// Native calls and member accesses prove area+40, texture slots+50, and
// the 60/62/61 fallback order for slot zero. The matched river-water
// createTexture at 7EEBE supplies the loader's counted return lifetime.
// StringBase<char>'s canonical header owns isEmpty; the native string
// prefix read proves its shared-buffer data starts eight bytes later.
#include "string_base.h"
class Rva0030812E { public: void *rva0030812E(int index); };
enum WW3DFormat { WW3D_FORMAT_UNKNOWN = 0 };
class W3DRadarFormatCaps { public: bool supportTextureFormat(WW3DFormat format); };
class DX8Caps;
class DX8Wrapper {
 friend class RenderableStandingWaterArea;
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

BFME2ParticleTextureHandle __cdecl BFME2LoadParticleTexture(const char *filename, int a, int b);


class RenderableStandingWaterArea {
public:
 void createTexture(int index);
private:
 char m_pad00[0x40];
 Rva0030812E *m_area;
 char m_unknown44[0x0c];
 BFME2ParticleTextureHandle m_textures[4];
};
void RenderableStandingWaterArea::createTexture(int index) {
 StringBase<char> *s=(StringBase<char>*)m_area->rva0030812E(index);
 if (!s->isEmpty()) {
  if (index == 0) {
   int format=0;
   if (reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)0x3c)) format=0x3c;
   else if (reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)0x3e)) format=0x3e;
   else if (reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)0x3d)) format=0x3d;
   const char *data=*(const char *const *)s;
   m_textures[0] = BFME2LoadParticleTexture(data ? data+8 : "",1,format);
  } else {
   const char *data=*(const char *const *)s;
   m_textures[index] = BFME2LoadParticleTexture(data ? data+8 : "",0,0);
  }
 }
}

// Native 00082140..000822F7,439B; WB742CF0 WaterRenderObjClass destructor.
// Reference BFME1 575ba2b04 WaterRenderObjVirtualDestructor.cpp provides
// resource teardown semantics; target owns three area-list observers and
// different member offsets. Retain the existing opaque owner spelling.
#include "Common/Snapshot.h"
#include "ascii_string.h"
void __cdecl operator delete(void*) throw();
class RefCountClass { public: virtual void Delete_This(); virtual ~RefCountClass(); int refs; };
class MultiListObjectClass { public: virtual ~MultiListObjectClass(); void *node; };
class RenderObjClass : public RefCountClass,public MultiListObjectClass {
public: virtual ~RenderObjClass();
private: char unmodelled[0xC4-0x10];
};
template<int N> class WaterAreaObserver {public: virtual ~WaterAreaObserver(){} };
class CreateAHeroData;
class Rva002B7250 {public: void rva002B7250(CreateAHeroData*);};
struct WaterTextureHandle { TextureBaseClass *ptr; ~WaterTextureHandle(){if(ptr)ptr->Release_Ref();} };
struct WaterCountedRef {
 RefCountClass *ptr;
 __forceinline ~WaterCountedRef(){ RefCountClass *p=ptr; if(p && --p->refs==0)p->Delete_This(); }
};
struct TreeHintRef00217D4C { ~TreeHintRef00217D4C(); };
namespace _STL { template<class T> class allocator; template<class T,class A=allocator<T> > class vector {
public: ~vector();
private: void *first,*last,*limit;
}; }
class WaterTracksRenderSystem {public: ~WaterTracksRenderSystem();};
class Rva0007E12F {public: void rva0007E12F();};
void BFME_DX8_Thread_Lock();
void BFME_DX8_Thread_Assert();
struct WaterDestructorGuard {~WaterDestructorGuard(){BFME_DX8_Thread_Assert();}};
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
class WaterRenderObjClass {
public:
 struct Setting {~Setting(); char data[0x30];};
};
class Rva0082140 : public Snapshot,public RenderObjClass,
 public WaterAreaObserver<0>,public WaterAreaObserver<1>,public WaterAreaObserver<2> {
public: virtual ~Rva0082140();
private:
 char unknownD4[0xF8-0xD4];
 WaterTextureHandle textureF8;
 WaterCountedRef refFC;
 WaterTracksRenderSystem *tracks100;
 Rva002B7250 *standing104;
 _STL::vector<TreeHintRef00217D4C> standing108;
 Rva002B7250 *rivers114;
 _STL::vector<TreeHintRef00217D4C> rivers118;
 Rva002B7250 *waves124;
 WaterCountedRef ref128;
 char unknown12C[0x138-0x12C];
 WaterRenderObjClass::Setting settings138[6];
};
Rva0082140::~Rva0082140() {
 if(standing104) {
  standing104->rva002B7250(reinterpret_cast<CreateAHeroData*>(static_cast<WaterAreaObserver<0>*>(this)));standing104=0;
  rivers114->rva002B7250(reinterpret_cast<CreateAHeroData*>(static_cast<WaterAreaObserver<1>*>(this)));rivers114=0;
  waves124->rva002B7250(reinterpret_cast<CreateAHeroData*>(static_cast<WaterAreaObserver<2>*>(this)));waves124=0;
 }
 BFME_DX8_Thread_Lock();
 WaterDestructorGuard guard;
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
