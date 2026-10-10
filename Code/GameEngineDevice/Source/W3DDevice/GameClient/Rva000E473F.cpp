// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /D_CRTIMP= /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
// stlport
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include "W3DFloorElement.h"
// Use the same direct node comparison as the canonical list<int> provider;
// keep its unused iterator-base wrapper out of this object's definitions.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
// Cursor-slot render helper: release (0x000E473F, 93B) plus reinit
// (0x000E479C, 234B). Both take the DX8 device mutex around their work.
// The reinit drops any live vertex/index buffers through the release body,
// allocates a 32-byte BfmeDynamicNativeVB (0x152, 0x3A9C, 1, 0) and a 24-byte
// DX8IndexBufferClass (0x7534, USAGE_DYNAMIC), zeroes two words, refills the
// embedded texture slot, and when the slot holds a surface, fetches its
// level-0 reset surface and draws one 0x7F7FFF pixel at (0, 0) before
// raising the +0x22 ready flag.
//
// Target facts (read-only retail decode this seat): both bodies open with
// mov eax,imm32 plus call __EH_prolog (0x00629188), save this in esi behind
// BFME_DX8_Thread_Lock (0x0011F520), and close with BFME_DX8_Thread_Assert
// (0x00120F50). The release repeats the REF_PTR_RELEASE shape (test, dec
// [ecx+4], jne, call [eax] slot 0, and-zero) for +0x04 and +0x08, then
// BfmeResetTextureRef::clear (0x0004D75B) on +0x14. The reinit calls the
// release when +0x04 or +0x08 is live, runs operator new (0x0002FDA0) for
// 0x20/0x18 bytes with the standard new-expression EH states 1/2, calls the
// 6-arg slot refill (0x00131DFC) on +0x14, checks the slot head, fetches
// CursorTextureSlot::Get_Surface_Level (0x00132D70) into an ebp-0x10 holder,
// calls SurfaceClass::DrawPixel (0x00116C30) on it with (0, 0, 0x7F7FFF),
// destroys the holder via W3DRadarResetSurface::~ (0x00176CB0), and sets
// [esi+0x22]. Class and member names are address-derived; the slot view
// (reset-ref base, cursor-slot middle, refill tail) is inferred from the
// three co-located calls sharing one unadjusted this, not from a header.

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
void *__cdecl operator new(unsigned);
void __cdecl operator delete(void *) throw();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

struct BfmeResetResource
{
	void Release_Ref();
};

struct BfmeResetTextureRef
{
	BfmeResetResource *pointer;
	void clear();
};

struct SurfaceClass
{
	void DrawPixel(unsigned int x, unsigned int y, unsigned int color);
};

class W3DRadarResetSurface : public SurfaceClass
{
public:
	void *m_surface;
	~W3DRadarResetSurface();
};

struct CursorTextureSlot : public BfmeResetTextureRef
{
	W3DRadarResetSurface Get_Surface_Level();
};

struct Rva00131DFC : public CursorTextureSlot
{
	void rva00131DFC(void *a, void *b, void *c, void *d, int e, int f);
};

class BfmeDynamicVBRefCount
{
public:
	virtual void DeleteThis();
	virtual ~BfmeDynamicVBRefCount();
	int references;
	void Release_Ref() { if (--references == 0) DeleteThis(); }
};

class BfmeDynamicVBBase : public BfmeDynamicVBRefCount
{
public:
	virtual ~BfmeDynamicVBBase();
	unsigned type;
	unsigned short vertexCount;
	int engineReferences;
	void *format;
	bool usesDeclaration;
};

class BfmeDynamicNativeVB : public BfmeDynamicVBBase
{
public:
	void *buffer;
	BfmeDynamicNativeVB(unsigned a, unsigned short b, unsigned c, unsigned d);
};

class DX8IndexBufferClass
{
public:
	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};
	virtual void DeleteThis();
	virtual ~DX8IndexBufferClass();
	int m_references;
	char m_pad08[0x18 - 8];
	void Release_Ref() { if (--m_references == 0) DeleteThis(); }
	DX8IndexBufferClass(unsigned index_count, UsageType usage);
};

// The Xfer virtual declaration follows the already verified E5725 provider.
// Only Version is stored here; the geometry types are reference parameters.
class Xfer;
class AsciiString;
class UnicodeString;
class PooledString;
class Snapshot;
struct XferUnknown11;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
struct Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
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

	void xferAsciiString(AsciiString *value) { *this == *value; }

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


class Rva000E5725 { public: void rva000E5725(Xfer *xfer); };

class Drawable;
class GameClient;
extern GameClient *TheGameClient;
class FloorClientSlots {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual Drawable *findDrawable(int id);
};
class Rva000E5EC1;
class Rva000E5F60 { public: Rva000E5EC1 *rva000E5F60(int, StringBase<char>); };
class Rva000E440D { public: bool rva000E440D(); };
class Rva000E459F { public: void rva000E46DA(Drawable *, const AsciiString &, const AsciiString &, bool, bool); };


class W3DFloorBuffer
{
public:
	void rva000E473F();
	void allocateFloorBuffers();
	void rva000E598B();
	void DoXfer(Xfer *xfer);
	Gen_uw_000e5033 *addFloor(int id, AsciiString *name, AsciiString *second, bool front, bool flag);

private:
	char m_pad00[4];
	BfmeDynamicNativeVB *m_vb;
	DX8IndexBufferClass *m_ib;
	int m_0C;
	int m_10;
	CursorTextureSlot m_slot;
	_STL::list<Gen_uw_000e5033 *> m_floors;
	int m_numFloors;
	bool m_ready20, m_flag21, m_ready22;
};

// ?rva000E473F@W3DFloorBuffer@@QAEXXZ @0x000E473F 93B
void W3DFloorBuffer::rva000E473F()
{
	BFMEDX8DeviceLock guard;
	if (m_vb != 0)
	{
		m_vb->Release_Ref();
		m_vb = 0;
	}
	if (m_ib != 0)
	{
		m_ib->Release_Ref();
		m_ib = 0;
	}
	m_slot.clear();
}

// ?allocateFloorBuffers@W3DFloorBuffer@@QAEXXZ @0x000E479C 234B
void W3DFloorBuffer::allocateFloorBuffers()
{
	BFMEDX8DeviceLock guard;
	if (m_vb != 0 || m_ib != 0)
		rva000E473F();
	m_vb = new BfmeDynamicNativeVB(0x152, 0x3A9C, 1, 0);
	m_ib = new DX8IndexBufferClass(0x7534, DX8IndexBufferClass::USAGE_DYNAMIC);
	m_0C = 0;
	m_10 = 0;
	static_cast<Rva00131DFC *>(&m_slot)->rva00131DFC((void *)1, (void *)1, (void *)0x15, (void *)1, 1, 0);
	if (m_slot.pointer != 0)
	{
		m_slot.Get_Surface_Level().DrawPixel(0, 0, 8355839); // 0x7F7FFF: DrawPixel color, not an image address
	}
	m_ready22 = true;
}

// Native E598B..E59D3 and WB 8841B0 prove the pointer list at +18,
// element cleanup before delete, and the final +10/+1C resets. Adapted from
// Open-BFME-1 6c1e0b51 W3DFloorBuffer_rva006F9050.cpp's reset semantics.
// The emitted pointer-list clear is proved against the complete 39-byte
// retail list<int> owner, including its free call, by the normal byte gate.
void W3DFloorBuffer::rva000E598B()
{
    for (_STL::list<Gen_uw_000e5033 *>::iterator it = m_floors.begin(); it._M_node != m_floors.end()._M_node; ++it) {
        reinterpret_cast<Rva000E4567 *>(*it)->rva000E4567();
        delete *it;
    }
    m_floors.clear();
    m_10 = 0;
    m_numFloors = 0;
}

// WB8844D0 identifies addFloor; native E6005..E6135 proves the entire
// 304-byte body, the five stack arguments, 0xA0 allocation and list order.
// Element constructor/destructor and both list folds are independently verified.
Gen_uw_000e5033 *W3DFloorBuffer::addFloor(int id, AsciiString *name, AsciiString *second, bool front, bool flag)
{
    Drawable *drawable = TheGameClient ? reinterpret_cast<FloorClientSlots *>(TheGameClient)->findDrawable(id) : 0;
    if (m_numFloors >= 450 || !drawable || !m_ready20) return 0;
    // The existing lookup owns a four-byte by-value StringBase<char>.
    // AsciiString owns the same storage and invokes its verified copy/cleanup;
    // use its accessible value interface for this ABI-equivalent member call.
    typedef Gen_uw_000e5033 *(Rva000E5F60::*AsciiLookup)(int, AsciiString);
    AsciiLookup lookup = reinterpret_cast<AsciiLookup>(&Rva000E5F60::rva000E5F60);
    Gen_uw_000e5033 *floor = (reinterpret_cast<Rva000E5F60 *>(this)->*lookup)(id, *name);
    if (floor) {
        if (!reinterpret_cast<Rva000E440D *>(floor)->rva000E440D()) return 0;
        reinterpret_cast<Rva000E459F *>(floor)->rva000E46DA(drawable,*name,*second,front,flag);
        return floor;
    }
    floor = new Gen_uw_000e5033;
    reinterpret_cast<Rva000E459F *>(floor)->rva000E46DA(drawable,*name,*second,front,flag);
    if (floor->load()) {
        if (front) m_floors.push_front(floor); else m_floors.push_back(floor);
        m_numFloors = m_floors.size();
        m_ready22 = true;
        return floor;
    }
    delete floor;
    return 0;
}

// WB8854D0 names DoXfer; native E6186..E6350 is the complete 458-byte
// RET4 body. Version 3, loading/store branches, element construction and
// cleanup, all transferred scalar/matrix fields and list traversal agree.
// The stack element and its unwind action use the shared verified layout.
void W3DFloorBuffer::DoXfer(Xfer *xfer)
{
    if (xfer->IsLightCRC()) return;
    Xfer::Version version(3,3);
    *xfer == version;
    int count = m_floors.size();
    *xfer == count;
    if (xfer->IsLoading()) {
        rva000E598B();
        for (int index=0; index<count; ++index) {
            Gen_uw_000e5033 current;
            reinterpret_cast<Rva000E5725 *>(&current)->rva000E5725(xfer);
            Gen_uw_000e5033 *floor = addFloor(current.m_id4c, &current.m_name8c, &current.m_name90, current.m_flag82, current.m_flag81);
            if (floor) {
                floor->m_matrix50.rows[0].x = current.m_matrix50.rows[0].x;
                floor->m_matrix50.rows[0].y = current.m_matrix50.rows[0].y;
                floor->m_matrix50.rows[0].z = current.m_matrix50.rows[0].z;
                floor->m_matrix50.rows[0].w = current.m_matrix50.rows[0].w;
                floor->m_matrix50.rows[1].x = current.m_matrix50.rows[1].x;
                floor->m_matrix50.rows[1].y = current.m_matrix50.rows[1].y;
                floor->m_matrix50.rows[1].z = current.m_matrix50.rows[1].z;
                floor->m_matrix50.rows[1].w = current.m_matrix50.rows[1].w;
                floor->m_matrix50.rows[2].x = current.m_matrix50.rows[2].x;
                floor->m_matrix50.rows[2].y = current.m_matrix50.rows[2].y;
                floor->m_matrix50.rows[2].z = current.m_matrix50.rows[2].z;
                floor->m_matrix50.rows[2].w = current.m_matrix50.rows[2].w;
                floor->m_active80 = current.m_active80;
                floor->m_flag81 = current.m_flag81;
                floor->m_flag82 = current.m_flag82;
                floor->m_opacity84 = current.m_opacity84;
                floor->m_speed88 = current.m_speed88;
                floor->m_94 = current.m_94;
                floor->m_state98 = current.m_state98;
                floor->m_flag9c = current.m_flag9c;
                floor->m_flag9d = current.m_flag9d;
            }
        }
    } else {
        for (_STL::list<Gen_uw_000e5033 *>::iterator it=m_floors.begin(); it._M_node != m_floors.end()._M_node; ++it)
            reinterpret_cast<Rva000E5725 *>(*it)->rva000E5725(xfer);
    }
}
