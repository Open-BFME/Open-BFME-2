// cl: /O1 /Oy- /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva006D0D7@@UAE@XZ @0x0006D0D7 735B
// Terrain render-object destructor (the class whose name getter 0x6D054
// returns "BaseHeightMapRenderObjClass"; vtables BC5DB0/BC5DA8/BC5DA0/BC5D90).
// Body: freeMapResources 0x6933D, null-guarded deletes of the buffers at
// +3850..+387C, then member destruction in reverse order and the
// RenderObjClass base destructor 0x13BE20. Layout from the retail dtor.
#include "ascii_string.h"

class TextureBaseClass { public: void Release_Ref(); };
void Rva00030830GameFree(void *);

struct RefTex {
	TextureBaseClass *p;
	~RefTex() { if (p) p->Release_Ref(); }
};
struct FreeBuf {
	void *p;
	~FreeBuf() { if (p) Rva00030830GameFree(p); }
};
class Rva001F3574Vec {
public:
	virtual ~Rva001F3574Vec();
private:
	char m_pad[0x18];
};

class Rva0006933D { public: int rva0006933D(); };
class VBuf { public: virtual ~VBuf(); };
class Rva000D3A17 { public: ~Rva000D3A17(); };
class W3DBibBuffer { public: ~W3DBibBuffer(); };
class W3DRoadBuffer { public: ~W3DRoadBuffer(); };
class W3DBridgeBuffer { public: ~W3DBridgeBuffer(); };
class W3DWaypointBuffer { public: ~W3DWaypointBuffer(); };
class Rva000E03E2 { public: virtual ~Rva000E03E2(); };
class Rva0007311B { public: virtual ~Rva0007311B(); };
class Rva00073BFE { public: virtual ~Rva00073BFE(); };

class RO0 { public: virtual ~RO0(); private: char m_pad[4]; };
class RO8 { public: virtual ~RO8(); private: char m_pad[0xB8]; };
class ROC4 { public: virtual ~ROC4(); };
class RenderObjClass : public RO0, public RO8, public ROC4 {
public:
	virtual ~RenderObjClass();
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

class Rva006D0D7 : public RenderObjClass, public SnapC8 {
public:
	virtual ~Rva006D0D7();
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
	Rva000E03E2 *m_3868;
	W3DRoadBuffer *m_386c;
	W3DBridgeBuffer *m_3870;
	Rva000D3A17 *m_3874;
	Rva0007311B *m_3878;
	Rva00073BFE *m_387c;
};

Rva006D0D7::~Rva006D0D7()
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
