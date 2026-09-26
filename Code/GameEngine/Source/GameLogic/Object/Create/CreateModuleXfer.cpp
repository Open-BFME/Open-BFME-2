// cl: /O1 /MD
//
// ?xfer@CreateModule@@MAEXPAVXfer@@@Z, retail 0x004B8D4E, 51 bytes. Virtual
// slot 3 (offset 0x0C) of vtable 0x00859368 (class of rowed ctor
// ??0CreateModule@@QAE@PAVThing@@PBVModuleData@@@Z in CreateModule.cpp):
// base BehaviorModule xfer via rowed 0x4C9C7D then IsLightCRC early-out via
// Xfer slot 0x10 then Version1 via rowed 0x53EE then bool at +0x14 via Xfer
// slot 0x90. Layout is BehaviorModule 0x0C plus CreateModuleInterface plus
// ModuleInterface giving +0x14 start (cf. SupplyCenterCreateConstructor
// precedent); ZH donor CreateModule.cpp proves the base-plus-bool shape.

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
	virtual void behaviorModuleAnchor();
	void xfer(Xfer *xfer);

private:
	unsigned char m_data[8];
};

class CreateModuleInterface
{
public:
	virtual void createModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class CreateModule : public BehaviorModule,
	public CreateModuleInterface,
	public ModuleInterface
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_needToRunOnBuildComplete;
};

void CreateModule::xfer(Xfer *xfer)
{
	BehaviorModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
	*xfer == m_needToRunOnBuildComplete;
}
