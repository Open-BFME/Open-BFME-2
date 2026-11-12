// ?rva00584A9B@HordeMeleeSwarm@@UAEXPAVXfer@@@Z
// stlport
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00584A9B@HordeMeleeSwarm@@UAEXPAVXfer@@@Z @0x00584A9B 423B
// Slot 15 (0x3C) of vtable 0x0086FC80. The WorldBuilder and rowed ctor
// establish HordeMeleeSwarm (formerly the Rva005843DA view). Xfer with
// Version(1,1), HordeMeleeSwarm ascii check with throw via _bfmeFormatText,
// bool at +0x14, int count, vector<28B> loop with Coord3D+bool per entry.
// Evidence: disassembly packet, BuildListInfoXfer slot map (Ascii 0x6c bool
// 0x90 int 0x7c Coord3D 0x60 Version 0x28 IsLoading 0x04), grow pin
// 0x00584A3D, releaseBuffer 0x00036410, EmptyString g_Rva0107301CEmptyString.
// Target 00584A9B..00584C42 is complete through RET4. The 28-byte entry
// layout agrees with Rva005843DACtor.cpp; actual STLport vector indexing
// reproduces retail's separate offset load and ADD/LEA copy setup. Growth
// retains the established neutral callee at00584A3D; no second name is pinned.
#include "ascii_string.h"
#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;

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

#include "../../../../GameEngine/Include/Common/BfmeXfer.h"

#include "../../../../GameEngine/Include/Common/XferVersion.h"

#include "../../../Include/Lib/Coord3DBase.h"

template <class T>
struct Rva00584A7DVector
{
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
	UnsignedInt size() const { return _M_finish - _M_start; }
	void grow(UnsignedInt count);
};

struct Rva00584A7DEntry
{
	Int m_00;
	Coord3DBase m_pos;
	bool m_10;
	char m_pad11[3];
	UnsignedInt m_14;
	UnsignedInt m_18;
};

#include "Rva005D6FCC.h"

class HordeMeleeSwarm : public Rva005D6FCC
{
public:
	// Slot 15 of the vftable 0x00C6FC80 that the ctor installs: virtual.
	virtual void rva00584A9B(Xfer *xfer);
private:
	_STL::vector<Rva00584A7DEntry> m_vec;
	bool m_flag;
};

#include "../../../../GameEngine/Include/Common/BfmeFormattedText.h"

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *result, int tag, const char *format, ...);
void __stdcall _CxxThrowException(void *a, void *b);
extern const char g_Rva0107301CEmptyString[];
extern int g_guardTargetTypeThrowInfo;

void HordeMeleeSwarm::rva00584A9B(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	AsciiString expected("HordeMeleeSwarm");
	AsciiString actual(expected);
	*xfer == actual;
	if (((const StringBase<char> &)actual).compare((const StringBase<char> &)expected) != 0)
	{
		char *expectedBuffer = *(char **)(void *)&expected;
		const char *s1 = expectedBuffer ? expectedBuffer + 8 : g_Rva0107301CEmptyString;
		char *actualBuffer = *(char **)(void *)&actual;
		const char *s2 = actualBuffer ? actualBuffer + 8 : g_Rva0107301CEmptyString;
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 4, "Xfer data saved by %s is now being loaded by %s", s2, s1);
		_CxxThrowException(&tmp, &g_guardTargetTypeThrowInfo);
	}
	*xfer == m_flag;
	Int count = (Int)m_vec.size();
	*xfer == count;
	if (xfer->IsLoading())
		((Rva00584A7DVector<Rva00584A7DEntry> *)&m_vec)->grow((UnsignedInt)count);
	for (Int i = 0; i < count; ++i)
	{
		Rva00584A7DEntry tmp;
		tmp.m_00 = 0;
		tmp.m_10 = true;
		tmp.m_14 = 0;
		tmp.m_18 = 0;
		tmp.m_pos.x = 0.0f;
		tmp.m_pos.y = 0.0f;
		tmp.m_pos.z = 0.0f;
		if (!xfer->IsLoading())
			tmp = m_vec[i];
		*xfer == tmp.m_pos;
		*xfer == tmp.m_10;
		if (xfer->IsLoading())
			m_vec[i] = tmp;
	}
}

// The rowed by-value vector resize owns the neutral BfmePod28 element spelling.
// Its POD payload is the 28-byte entry used here. This adapter initializes
// exactly the fields the retail 00584A3D wrapper writes before that call.
struct BfmePod28
{
    Int state;
    Coord3DBase position;
    bool needsPosition;
    unsigned char pad11[3];
    unsigned int word14, word18;
    ~BfmePod28() {}
    BfmePod28(const BfmePod28 &v) : state(v.state), position(v.position), needsPosition(v.needsPosition), word14(v.word14), word18(v.word18) {}
    BfmePod28() : state(0), needsPosition(true), word14(0), word18(0)
    { position.x = 0.0f; position.y = 0.0f; position.z = 0.0f; }
};
namespace _STL {
template<> class vector<BfmePod28, allocator<BfmePod28> >
{
public:
    typedef unsigned int size_type;
    void resize(size_type count, BfmePod28 value);
private:
    BfmePod28 *first, *last, *capacity;
};
}
template<>
void Rva00584A7DVector<Rva00584A7DEntry>::grow(UnsignedInt count)
{
    reinterpret_cast<_STL::vector<BfmePod28> *>(this)->resize(count, BfmePod28());
}
