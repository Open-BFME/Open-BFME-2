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

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

struct XferVersion
{
	UnsignedByte current;
	UnsignedByte minimum;
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern int g_rva005c5100ThrowInfo;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();

protected:
	void *m_f04;
	Object *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };

class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	void xfer(Xfer *xfer);

private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

class PropagandaTowerBehaviorIface
{
public:
	virtual void slot();
};

class ObjectTracker
{
public:
	ObjectTracker() : objectID(INVALID_OBJECT_ID), next(0) {}
	virtual ~ObjectTracker() {}

	ObjectID objectID;
	ObjectTracker *next;
};

class PropagandaTowerBehavior : public UpdateModule,
	public PropagandaTowerBehaviorIface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	UnsignedInt m_lastScanFrame; // +0x24
	ObjectTracker *m_insideList; // +0x28
};

union XferLocal
{
	XferVersion version;
	XferException error;
};

// ?xfer@PropagandaTowerBehavior@@MAEXPAVXfer@@@Z @0x00481842
void PropagandaTowerBehavior::xfer(Xfer *xfer)
{
	XferLocal local;
	xfer->Version1();
	UpdateModule::xfer(xfer);
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
			bfmeFormatText(&local.error, 5, 0);
			_CxxThrowException(&local.error, (const _s__ThrowInfo *)&g_rva005c5100ThrowInfo); __assume(0);
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
// ?g_rva005c5100ThrowInfo@@3HA: the global at VA 0xcffd18 is ?g_guardTargetTypeThrowInfo@@3HA.
#pragma comment(linker, "/alternatename:?g_rva005c5100ThrowInfo@@3HA=?g_guardTargetTypeThrowInfo@@3HA")
