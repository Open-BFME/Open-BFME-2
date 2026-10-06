// cl: /MD
//
// ?xfer@GhostObject@@MAEXPAVXfer@@@Z, retail 0x003059F5, 154 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0080793C (class of ??1GhostObject@@UAE@XZ).
// Donor: ZH GeneralsMD GhostObject::xfer (parent ObjectID via getID at Object
// +0x74 plus XferObjectID plus IsLoading-gated findObjectByID via TheGameLogic
// plus FormatText/Throw on missing plus angle then position). BFME2 repairs:
// IsLightCRC early-out via Xfer slot 0x10, Version1 via rowed 0x000053EE,
// ObjectID at +0x0C via rowed XferObjectID 0x003060B2, IsLoading via Xfer slot
// 0x04, float at +0x1C via Xfer slot 0x70, Coord3DBase at +0x10 via Xfer slot
// 0x60. Layout is Snapshot base (vptr) plus +0x04/+0x08 pad giving +0x0C parent
// (cf. retail mov [esi+0x0C] and [eax+0x74] getID), Coord (12B) at +0x10 then
// float at +0x1C (0x10+0x0C=0x1C contiguous). Recipe is PoisonedBehaviorXfer
// slot-3 pattern with Xfer decl verbatim.

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

class Coord3DBase
{
public:
	float x;
	float y;
	float z;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern int g_guardTargetTypeThrowInfo;

class Object
{
public:
	ObjectID getID() const { return m_id; }
	unsigned char m_pad[0x74];
	ObjectID m_id;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class Snapshot
{
public:
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

class GhostObject : public Snapshot
{
protected:
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);

private:
	unsigned int m_04;
	unsigned int m_08;
	Object *m_parentObject; // +0x0C
	Coord3DBase m_10; // +0x10
	float m_1C; // +0x1C
};

void GhostObject::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	ObjectID parentObjectID = INVALID_ID;
	if (m_parentObject)
		parentObjectID = m_parentObject->getID();
	XferObjectID(xfer, &parentObjectID);
	if (xfer->IsLoading()) {
		m_parentObject = TheGameLogic->findObjectByID(parentObjectID);
		if (parentObjectID != INVALID_ID && m_parentObject == 0) {
			XferException error;
			bfmeFormatText(&error, 5, 0);
			_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo); __assume(0);
		}
	}
	*xfer == m_1C;
	*xfer == m_10;
}
