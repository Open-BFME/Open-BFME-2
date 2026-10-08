// cl: /Ireference/shims/moduledata /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?xferTheSellList@BuildAssistant@@QAEXPAVXfer@@@Z, retail 0x003924FE
// (204 bytes).
// Identity (target): WorldBuilder's debug BuildAssistant.cpp:497
// BuildAssistant::xferTheSellList (align lead) and Zero Hour's body agree
// with retail: count the sell list, move the count as an Int, then on load
// clear the list and append a new ObjectSellInfo per entry (id through
// XferObjectID, sell frame as an unsigned int), on save move each entry.
// Layout (target): the sell list at BuildAssistant+0x0C; a 0x0C-byte
// ObjectSellInfo (vtable, id +0x04, frame +0x08) from plain operator new.
// The list's clear and push_back are the folded four-byte STLport bodies
// (0x0023DAA5, 0x0005548F).
#include "Common/Snapshot.h"
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

class ObjectSellInfo
{
public:
	ObjectSellInfo() : m_id(INVALID_ID), m_sellFrame(0) {}
	virtual ~ObjectSellInfo();

	ObjectID m_id; // +0x04
	unsigned int m_sellFrame; // +0x08
};

typedef _STL::list<ObjectSellInfo *, _STL::allocator<ObjectSellInfo *> > ObjectSellList;
typedef ObjectSellList::iterator ObjectSellListIterator;

class BuildAssistant
{
public:
	void xferTheSellList(Xfer *xfer);

private:
	unsigned char m_pad00[0x0C];
	ObjectSellList m_sellList; // +0x0C
};

void BuildAssistant::xferTheSellList(Xfer *xfer)
{
	ObjectSellInfo *sellInfo;

	int count = 0;
	ObjectSellListIterator it;
	for (it = m_sellList.begin(); it != m_sellList.end(); ++it)
		count++;
	*xfer == count;

	if (xfer->IsLoading())
	{
		m_sellList.clear();
		int i;
		for (i = 0; i < count; i++)
		{
			sellInfo = new ObjectSellInfo;
			XferObjectID(xfer, &sellInfo->m_id);
			*xfer == sellInfo->m_sellFrame;
			m_sellList.push_back(sellInfo);
		}
	}
	else
	{
		for (it = m_sellList.begin(); it != m_sellList.end(); ++it)
		{
			sellInfo = (*it);
			XferObjectID(xfer, &sellInfo->m_id);
			*xfer == sellInfo->m_sellFrame;
			count--;
		}
	}
}
