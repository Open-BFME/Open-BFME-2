// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?xfer@ObjectTypes@@MAEXPAVXfer@@@Z, retail 0x00376B70, 224 bytes.
// Slot 3 of vtable 0x00818630 (class of ObjectTypes ctor 0x003769F9).
// ObjectTypes xfer: IsLightCRC early-out via slot 0x10, Version1 via rowed
// 0x000053EE, m_listName via slot 0x6C, vector<AsciiString> m_objectTypes at +8
// with WORD count via slot 0x80, IsStoring via slot 8, saving walks via slot
// 0x6C, loading checks empty via FormatText 0x0060C36E plus Throw 0x00629094
// then push_back via pinned 0x0002DBE6 with temp AsciiString released via rowed
// 0x00036410. Layout from ObjectTypesCtor.cpp; Xfer decl verbatim from
// PoisonedBehaviorXfer.cpp.
#define _STLP_NO_EXCEPTIONS 1
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

template <typename T> struct BfmeStringData;

#include "ascii_string.h"


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

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};


class ObjectTypes
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	AsciiString m_listName;
	_STL::vector<AsciiString> m_objectTypes;
};

void ObjectTypes::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_listName;
	unsigned short count = (unsigned short)m_objectTypes.size();
	*xfer == count;
	if (xfer->IsStoring()) {
		for (AsciiString *p = m_objectTypes.begin(); p != m_objectTypes.end(); ++p)
			*xfer == *p;
	} else {
		if (!m_objectTypes.empty()) {
			throw XferException(5, (const char *)0);
		}
		AsciiString tmp;
		for (unsigned short i = 0; i < count; ++i) {
			*xfer == tmp;
			m_objectTypes.push_back(tmp);
		}
	}
}
