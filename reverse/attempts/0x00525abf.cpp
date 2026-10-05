// ?rva00525ABF@Rva00525ABF@@QAEXPAVXfer@@@Z
// partial score=0.93 date=2026-10-05
// cl: /Ireference/shims/bfmelist /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00525ABF@Rva00525ABF@@QAEXPAVXfer@@@Z, retail 0x00525ABF, 518 bytes.
// Unlock lane: missing callee of 1 free function; landing makes 0x00525E00 ready.
// Storing (IsStoring via Xfer slot 0x08) counts two lists and xfers counts plus
// ObjectID/int/int per node plus int at +0x18; loading Version(1,3) via slot
// 0x28 rebuilds both lists via temp list<BfmePod12> insert (rowed 0x004E7B49)
// then swaps into +0x10/+0x14, version-gated second list (>=2) and +0x18 (>=3),
// then forEach listener 0x005CC208. Layout: Rva005258E2List base 0x10 plus two
// 4-byte STL lists plus int, same as Rva00526275 ctor precedent.
#include <list>

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

void XferObjectID(Xfer *xfer, ObjectID *objectID);

extern const float g_00BBB9AC;

class Rva005258E2Listener
{
public:
	virtual void notify();
};

struct Rva005253A0Call
{
	void (Rva005258E2Listener::*notify)();
};

class Rva005258E2List
{
public:
	void forEach(void (Rva005258E2Listener::*notify)());
	void apply(const Rva005253A0Call &call);

private:
	Rva005258E2Listener **m_begin;
	Rva005258E2Listener **m_end;
	Rva005258E2Listener **m_capacity;
	unsigned int m_index;
};

class Rva005CC208 : public Rva005258E2Listener
{
public:
	virtual void rva005CC208();
};

struct BfmePod12 { int a[3]; };

class Rva00525ABF : public Rva005258E2List
{
public:
	void rva00525ABF(Xfer *xfer);
private:
	_STL::list<BfmePod12> m_list10;
	_STL::list<BfmePod12> m_list14;
	int m_18;
};

// ?rva00525ABF@Rva00525ABF@@QAEXPAVXfer@@@Z present-unmatched
void Rva00525ABF::rva00525ABF(Xfer *xfer)
{
	Xfer::Version version(1, 3);
	*xfer == version;
	if (xfer->IsStoring()) {
		int n10 = (int)m_list10.size();
		*xfer == n10;
		for (_STL::list<BfmePod12>::iterator it = m_list10.begin(); it != m_list10.end(); ++it) {
			BfmePod12 &e = *it;
			XferObjectID(xfer, (ObjectID *)&e.a[0]);
			*xfer == e.a[1];
			*xfer == e.a[2];
		}
		int n14 = (int)m_list14.size();
		*xfer == n14;
		for (_STL::list<BfmePod12>::iterator it = m_list14.begin(); it != m_list14.end(); ++it) {
			BfmePod12 &e = *it;
			XferObjectID(xfer, (ObjectID *)&e.a[0]);
		}
		*xfer == m_18;
		return;
	}
	int n10;
	*xfer == n10;
	_STL::list<BfmePod12> tmp10;
	for (; n10 > 0; --n10) {
		BfmePod12 v;
		v.a[0] = 0;
		v.a[1] = 0;
		v.a[2] = 0;
		XferObjectID(xfer, (ObjectID *)&v.a[0]);
		*xfer == v.a[1];
		*xfer == v.a[2];
		tmp10.insert(tmp10.end(), v);
	}
	tmp10.swap(m_list10);
	_STL::list<BfmePod12> tmp14;
	if (version.m_minimum >= 2) {
		int n14;
		*xfer == n14;
		for (; n14 > 0; --n14) {
			BfmePod12 v;
			v.a[0] = 0;
			((char *)&v.a[1])[0] = 0;
			*(float *)&v.a[2] = g_00BBB9AC;
			XferObjectID(xfer, (ObjectID *)&v.a[0]);
			tmp14.insert(tmp14.end(), v);
		}
	}
	tmp14.swap(m_list14);
	if (version.m_minimum >= 3) {
		*xfer == m_18;
	} else {
		m_18 = 0;
	}
	forEach(reinterpret_cast<void (Rva005258E2Listener::*)()>(&Rva005CC208::rva005CC208));
}
