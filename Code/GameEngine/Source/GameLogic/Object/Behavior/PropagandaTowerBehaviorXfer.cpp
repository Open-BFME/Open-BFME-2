// cl: /DNDEBUG /MD
//
// ?xfer@PropagandaTowerBehavior@@MAEXPAVXfer@@@Z retail 0x00481842 216 bytes.
// Slot 3 (offset 0x0C) of vtable 0x00849248 (PropagandaTowerBehavior via pool
// string and name getter 0x0048182C; slot 13 is removeAllInfluence 0x00481D4C).
// Base UpdateModule xfer via rowed 0x0044DF9F first, then Version1 via rowed
// 0x000053EE, then uint at +0x24 via Xfer slot 0x78, then ushort count via Xfer
// slot 0x80, then IsStoring via Xfer slot 0x08, then ObjectIDs via rowed
// XferObjectID 0x003060B2, then FormatText 0x0060C36E plus Throw 0x00629094,
// then new ObjectTracker via rowed operator-new 0x0002FDA0. Layout is the rowed
// ctor shape (UpdateModule base 0x20 plus iface at +0x20 plus lastScan at +0x24
// plus insideList at +0x28). Donor is BFME1 PropagandaTowerBehavior_xfer.cpp
// (same two-phase list count plus save-loop plus load-throw plus new-loop);
// BFME2 uses Version1 plus operator== plus XferObjectID plus IsStoring.

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
class UpgradeTemplate;
class PropagandaTowerBehaviorModuleData;

enum NameKeyType { NK_UNKNOWN = 0 };

#include "../../../../Include/Common/BfmeXfer.h"

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

// Retail ThrowInfo identifies the 8-byte XferException class and its
// established constructor, copy constructor and destructor providers.
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

// Only the direct base call is needed here. The serialization row and seed
// both use the primary receiver; its base subobject starts at offset zero.
class UpdateModule
{
public:
	void xfer(Xfer *xfer);
};

class ObjectTracker
{
public:
	ObjectTracker() : objectID(INVALID_OBJECT_ID), next(0) {}
	virtual ~ObjectTracker() {}
	ObjectID objectID; // +0x04
	ObjectTracker *next; // +0x08
};

class PropagandaTowerBehavior
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
protected:
	virtual void xfer(Xfer *xfer);
public:
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
protected:
	virtual void removeAllInfluence();
	virtual void doScan();
	virtual void effectLogic(Object *obj, bool giving, const PropagandaTowerBehaviorModuleData *modData);
private:
	const PropagandaTowerBehaviorModuleData *getPropagandaTowerBehaviorModuleData() const
	{
		return m_moduleData;
	}
	const PropagandaTowerBehaviorModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
	unsigned char m_pad0C[0x24 - 0x0C];
	unsigned int m_lastScanFrame; // +0x24
	ObjectTracker *m_insideList;	// +0x28
	const UpgradeTemplate *m_upgradeRequired;	// +0x2C
public:
	virtual NameKeyType getModuleNameKey() const;
};

// ?xfer@PropagandaTowerBehavior@@MAEXPAVXfer@@@Z @0x00481842
void PropagandaTowerBehavior::xfer(Xfer *xfer)
{
	xfer->Version1();
	reinterpret_cast<UpdateModule *>(this)->UpdateModule::xfer(xfer);
	*xfer == m_lastScanFrame;

	UnsignedShort insideCount = 0;
	for (ObjectTracker *tracker = m_insideList;
		tracker != 0; tracker = tracker->next)
		++insideCount;
	*xfer == insideCount;

	if (xfer->IsStoring())
	{
		ObjectTracker *tracker = m_insideList;
		while (tracker != 0)
		{
			XferObjectID(xfer, &tracker->objectID);
			tracker = tracker->next;
		}
	}
	else
	{
		if (m_insideList != 0)
		{
			throw XferException(5, 0);
		}

		for (UnsignedShort i = 0; i < insideCount; ++i)
		{
			ObjectTracker *tracker = new ObjectTracker;
			tracker->next = m_insideList;
			m_insideList = tracker;
			XferObjectID(xfer, &tracker->objectID);
		}
	}
}
