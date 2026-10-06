// cl: /DNDEBUG /MD
//
// ?xfer@PillageModule@@MAEXPAVXfer@@@Z retail 0x00484FBB 39B vslot 3 of
// vtable 0x0084A51C (class of ??0PillageModule@@QAE@PAVThing@@PBVModuleData@@@Z).
// Evidence: Version1 via rowed 0x000053EE then base
// ?xfer@Rva00589051@@MAEXPAVXfer@@@Z via rowed 0x00589051 then uint at +0x18
// via Xfer slot 0x78 matching ctor m_bfme18 zeroed in PillageModuleCtor.cpp.
// Donor TU Code/GameEngine/Source/GameLogic/Object/Behavior/PillageModuleCtor.cpp.

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

class BehaviorModule
{
public:
	virtual void anchor();
	void xfer(Xfer *xfer);
	unsigned int m_04;
	void *m_object;
};

enum ObjectID
{
	INVALID_ID = 0
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva00589051 : public BehaviorModule
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad[0x08];
	ObjectID m_14;
};

class PillageModule : public Rva00589051
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	unsigned int m_18;
};

void PillageModule::xfer(Xfer *xfer)
{
	xfer->Version1();
	Rva00589051::xfer(xfer);
	*xfer == m_18;
}
