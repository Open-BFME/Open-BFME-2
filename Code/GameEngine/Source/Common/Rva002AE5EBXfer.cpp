// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Oy- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva002A7818@Rva002AE5EB@@UAEXPAVXfer@@@Z, retail 0x002A7818, 393 bytes.
// Slot 3 (offset 0x0C) of vtable 0x007FDDB4 (class of ??0Rva002AE5EB rowed
// at 0x002AE5EB in Rva002AE5EBCtor.cpp). Version(1,7) via Xfer slot 0x28,
// ints via slot 0x7C, bool via slot 0x90, IsLoading via slot 0x04; vector
// at +0x20 holds 12B records (int/ObjectID/filter) erased via rowed
// 0x002A7644 and grown via rowed push_back 0x002A778D; per-record fields
// via rowed XferObjectID 0x003060B2, pin rva00362255 and rowed ctor/dtor
// 0x002A7400/0x00360D26. Layout matches Rva002AE5EBCtor plus +0x0C/+0x10.
#include "../../../Libraries/Include/Lib/Coord2D.h"

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
struct Coord3DBase
{
	float x;
	float y;
	float z;
};
struct ICoord3D
{
	int x;
	int y;
	int z;
};
struct Region3D
{
	Coord3DBase lo;
	Coord3DBase hi;
};
struct IRegion3D
{
	ICoord3D lo;
	ICoord3D hi;
};
struct ICoord2D
{
	int x;
	int y;
};
struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};
struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};
struct RealRange
{
	float lo;
	float hi;
};
struct RGBColor
{
	float red;
	float green;
	float blue;
};
struct RGBAColorReal
{
	float red;
	float green;
	float blue;
	float alpha;
};
struct RGBAColorInt
{
	unsigned int red;
	unsigned int green;
	unsigned int blue;
	unsigned int alpha;
};
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
class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}
	unsigned char m_current;
	unsigned char m_minimum;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *value);

class Rva003189ADSub10
{
public:
	void rva00362255(Xfer *xfer);
	int m_handle;
};

class Rva00360D26Member : public Rva003189ADSub10
{
public:
	~Rva00360D26Member();
};

struct BfmePod12
{
	int m_a;
	int m_b;
	int m_c;
};

struct Rva002A76A0Element
{
	int m_value;
	ObjectID m_id;
	Rva00360D26Member m_filter;
};

class Rva002A7400
{
public:
	Rva002A7400();
	int m_value;
	ObjectID m_id;
	Rva00360D26Member m_filter;
};

namespace _STL
{
template <class _Tp>
class allocator
{
};
template <class _Tp, class _Alloc = allocator<_Tp> >
class vector
{
public:
	void push_back(const _Tp &item);
	_Tp *erase(_Tp *first, _Tp *last);
	_Tp *m_start;
	_Tp *m_finish;
	_Tp *m_endOfStorage;
};
}

class Rva002AE5EB
{
public:
	virtual ~Rva002AE5EB();
	virtual void v01();
	virtual void v02();
	virtual void rva002A7818(Xfer *xfer);
private:
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	union
	{
		_STL::vector<BfmePod12> m_vecPod;
		_STL::vector<Rva002A76A0Element> m_vecElem;
	};
	bool m_2C;
};

void Rva002AE5EB::rva002A7818(Xfer *xfer)
{
	Xfer::Version version(1, 7);
	*xfer == version;
	*xfer == m_04;
	*xfer == m_08;
	*xfer == m_14;
	if (version.m_minimum >= 2)
		*xfer == m_18;
	if (version.m_minimum >= 3)
		*xfer == m_1C;
	if (version.m_minimum >= 4)
		*xfer == m_0C;
	if (version.m_minimum >= 5)
	{
		if (xfer->IsLoading())
		{
			_STL::vector<BfmePod12> *pv = &m_vecPod;
			BfmePod12 *last = pv->m_finish;
			BfmePod12 *first = pv->m_start;
			pv->erase(first, last);
			int count = 0;
			*xfer == count;
			for (int i = 0; i < count; ++i)
			{
				Rva002A7400 tmp;
				*xfer == tmp.m_value;
				XferObjectID(xfer, &tmp.m_id);
				tmp.m_filter.rva00362255(xfer);
				m_vecElem.push_back(*(const Rva002A76A0Element *)&tmp);
			}
		}
		else
		{
			int count = m_vecElem.m_finish - m_vecElem.m_start;
			*xfer == count;
			for (Rva002A76A0Element *p = m_vecElem.m_start; p != m_vecElem.m_finish; ++p)
			{
				*xfer == p->m_value;
				XferObjectID(xfer, &p->m_id);
				p->m_filter.rva00362255(xfer);
			}
		}
	}
	if (version.m_minimum >= 6)
		*xfer == m_10;
	if (version.m_minimum >= 7)
		*xfer == m_2C;
}
