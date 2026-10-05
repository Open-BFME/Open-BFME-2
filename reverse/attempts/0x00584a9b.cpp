// ?rva00584A9B@Rva005843DA@@QAEXPAVXfer@@@Z
// partial score=0.98 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva00584A9B@Rva005843DA@@QAEXPAVXfer@@@Z @0x00584A9B 423B
// Slot 15 (0x3C) of vtable 0x0086FC80 (class of ??0Rva005843DA). Xfer with
// Version(1,1), HordeMeleeSwarm ascii check with throw via _bfmeFormatText,
// bool at +0x14, int count, vector<28B> loop with Coord3D+bool per entry.
// Evidence: disassembly packet, BuildListInfoXfer slot map (Ascii 0x6c bool
// 0x90 int 0x7c Coord3D 0x60 Version 0x28 IsLoading 0x04), grow pin
// 0x00584A3D, releaseBuffer 0x00036410, EmptyString g_Rva0107301CEmptyString.
#include "ascii_string.h"

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

class Xfer
{
public:
	class Version;
	Xfer();
	virtual ~Xfer();
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

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}
	unsigned char m_current;
	unsigned char m_minimum;
};

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

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

class Rva005D6FCC
{
public:
	virtual ~Rva005D6FCC();
	void *m_held;
};

class Rva005843DA : public Rva005D6FCC
{
public:
	void rva00584A9B(Xfer *xfer);
private:
	Rva00584A7DVector<Rva00584A7DEntry> m_vec;
	bool m_flag;
};

struct BfmeFormattedText
{
	char *text;
	int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *result, int tag, const char *format, ...);
void __stdcall _CxxThrowException(void *a, void *b);
extern const char g_Rva0107301CEmptyString[];
extern int g_guardTargetTypeThrowInfo;

// ?rva00584A9B@Rva005843DA@@QAEXPAVXfer@@@Z present-unmatched
void Rva005843DA::rva00584A9B(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;
	AsciiString expected("HordeMeleeSwarm");
	AsciiString actual(expected);
	*xfer == actual;
	if (((const StringBase<char> &)actual).compare((const StringBase<char> &)expected) != 0)
	{
		char *t1 = *(char **)(void *)&expected;
		const char *s1 = t1 ? t1 + 8 : g_Rva0107301CEmptyString;
		char *t2 = *(char **)(void *)&actual;
		const char *s2 = t2 ? t2 + 8 : g_Rva0107301CEmptyString;
		BfmeFormattedText tmp;
		bfmeFormatText(&tmp, 4, "Xfer data saved by %s is now being loaded by %s", s2, s1);
		_CxxThrowException(&tmp, &g_guardTargetTypeThrowInfo);
	}
	*xfer == m_flag;
	Int count = (Int)m_vec.size();
	*xfer == count;
	if (xfer->IsLoading())
		m_vec.grow((UnsignedInt)count);
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
			tmp = m_vec._M_start[i];
		*xfer == tmp.m_pos;
		*xfer == tmp.m_10;
		if (xfer->IsLoading())
			m_vec._M_start[i] = tmp;
	}
}
