// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2renderobj /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/shims/bfme2_ascii
// ??1BaseHeightMapRenderObjClass@@UAE@XZ @0x0006D0D7 735B
// Terrain render-object destructor (the class whose name getter 0x6D054
// returns "BaseHeightMapRenderObjClass"; vtables BC5DB0/BC5DA8/BC5DA0/BC5D90).
// Body: freeMapResources 0x6933D, null-guarded deletes of the buffers at
// +3850..+387C, then member destruction in reverse order and the
// RenderObjClass base destructor 0x13BE20. Layout from the retail dtor.
#include "ascii_string.h"

class TextureBaseClass
{
public:
	void Release_Ref();
};
void Rva00030830GameFree(void *);

struct RefTex {
	TextureBaseClass *p;
	~RefTex() { if (p) p->Release_Ref(); }
};
struct FreeBuf {
	void *p;
	~FreeBuf() { if (p) Rva00030830GameFree(p); }
};
// Its destructor is the 7-byte vftable store retail folds at 0x0049B47C.
class Rva001F3574Vec {
public:
	virtual ~Rva001F3574Vec() {}
private:
	char m_pad[0x18];
};

class Rva0006933D { public: int rva0006933D(); };
class VBuf { public: virtual ~VBuf(); };
class Rva000D3A17
{
public:
	Rva000D3A17();
	~Rva000D3A17();
	void rva000D3A17();
	char data[272]; // +0x00
};
enum DrawableID
{
	INVALID_DRAWABLE_ID = 0,
	FORCE_DRAWABLEID_TO_LONG_SIZE = 0x7ffffff
};
enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7ffffff
};
class Vector3;
class BaseHeightMapRenderObjClass;
class W3DBibBuffer
{
private:
	friend class BaseHeightMapRenderObjClass;
public:
	void addBibDrawable(Vector3 corners[4], DrawableID id, bool highlight);
	void removeHighlighting();
	void clearAllBibs();
	void removeBib(ObjectID id);
	void removeBibDrawable(DrawableID id);
	void addBib(Vector3 corners[4], ObjectID id, bool highlight);
protected:
	void freeBibBuffers();
	void allocateBibBuffers();
public:
	W3DBibBuffer();
	~W3DBibBuffer();
	char data[68048]; // +0x00
};
class WorldHeightMap;
class W3DRoadBuffer
{
private:
	friend class BaseHeightMapRenderObjClass;
public:
	void loadRoads();
protected:
	void freeRoadBuffers();
	void allocateRoadBuffers();
public:
	W3DRoadBuffer();
	~W3DRoadBuffer();
	void clearAllRoads();
	void setMap(WorldHeightMap*);
	char data[80]; // +0x00
};
class W3DBridgeBuffer { public: ~W3DBridgeBuffer(); };
class W3DWaypointBuffer
{
public:
	W3DWaypointBuffer();
	~W3DWaypointBuffer();
	char data[12]; // +0x00
};
class Rva000E0AE2
{
public:
	Rva000E0AE2();
	~Rva000E0AE2();
	char data[620]; // +0x00
};
class Rva0007311B { public: ~Rva0007311B(); };
class W3DTaint
{
public:
	bool ReAcquireResources();
	~W3DTaint();
	W3DTaint();
	void init(WorldHeightMap*,float,float);
	char data[80]; // +0x00
};

#define BFME_RO_DTOR_DECL_ONLY
#include "../../../../Libraries/Source/WWVegas/WW3D2/rendobj.h"
// Native +0xC4 cleanup table: two resource callbacks and no destructor slot.
class DX8_CleanupHook {
public:
	virtual void ReleaseResources() = 0;
	virtual void ReAcquireResources() = 0;
};
class SnapC8 { public: virtual ~SnapC8() {} };

template <class T> static __forceinline void destroyMember(T *&p)
{
	T *t = p;
	if (t) {
		t->T::~T();
		operator delete(t);
		p = 0;
	}
}

class BaseHeightMapRenderObjClass : public RenderObjClass, public DX8_CleanupHook, public SnapC8 {
public:
	virtual ~BaseHeightMapRenderObjClass();
	virtual void ReleaseResources();
	virtual void ReAcquireResources();
private:
	char m_pad0[0xD4 - 0xCC];
	RefTex m_d4;
	char m_pad1[0xE0 - 0xD8];
	Rva001F3574Vec m_array[500];
	char m_pad2[0x37EC - 0xE0 - 500 * 0x1C];
	FreeBuf m_37ec;
	char m_pad3[0x3800 - 0x37F0];
	FreeBuf m_3800;
	char m_pad4[0x381C - 0x3804];
	RefTex m_381c;
	AsciiString m_3820;
	AsciiString m_3824;
	RefTex m_3828;
	AsciiString m_382c;
	AsciiString m_3830;
	char m_pad5[4];
	RefTex m_3838;
	AsciiString m_383c;
	AsciiString m_3840;
	RefTex m_3844;
	AsciiString m_3848;
	AsciiString m_384c;
	VBuf *m_3850;
	VBuf *m_3854;
	VBuf *m_3858;
	W3DBibBuffer *m_385c;
	VBuf *m_3860;
	W3DWaypointBuffer *m_3864;
	Rva000E0AE2 *m_3868;
	W3DRoadBuffer *m_386c;
	W3DBridgeBuffer *m_3870;
	Rva000D3A17 *m_3874;
	Rva0007311B *m_3878;
	W3DTaint *m_387c;
};

BaseHeightMapRenderObjClass::~BaseHeightMapRenderObjClass()
{
	((Rva0006933D *)this)->rva0006933D();
	if (m_3850) {
		::delete m_3850;
		m_3850 = 0;
	}
	destroyMember(m_3874);
	if (m_3854) {
		::delete m_3854;
		m_3854 = 0;
	}
	if (m_3858) {
		::delete m_3858;
		m_3858 = 0;
	}
	destroyMember(m_385c);
	destroyMember(m_386c);
	W3DBridgeBuffer *bridge = m_3870;
	if (bridge) {
		bridge->W3DBridgeBuffer::~W3DBridgeBuffer();
		operator delete(bridge);
	}
	if (m_3860)
		::delete m_3860;
	destroyMember(m_3864);
	destroyMember(m_3868);
	destroyMember(m_3878);
	destroyMember(m_387c);
}
