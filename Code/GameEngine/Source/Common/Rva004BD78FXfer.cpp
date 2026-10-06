// cl: /MD
// ?xfer@Rva004BD78F@@MAEXPAVXfer@@@Z @0x004BD9A1 42B: slot 3 of 0x0085AE34 (class of ??1Rva004BD78F); evidence: Version1 0x000053EE then base ?xfer@BodyModule@@MAEXPAVXfer@@@Z 0x0058B043 then Xfer bool slot 0x90 member at +0x18; donor Code/GameEngine/Source/GameLogic/Object/Body/BodyModuleXfer.cpp Xfer decl verbatim
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
class DamageInfo;
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
class ObjectModule
{
public:
	virtual void objectAnchor();
	const ModuleData *m_moduleData;
	void *m_object;
};
class BehaviorIface
{
public:
	virtual void behaviorIfaceAnchor();
};
class BehaviorModule : public ObjectModule, public BehaviorIface
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	void xfer(Xfer *xfer);
};
class BodyModuleInterface
{
public:
	virtual void bodyAnchor() = 0;
};
class BodyModule : public BehaviorModule, public BodyModuleInterface
{
public:
	BodyModule(Thing *thing, const ModuleData *moduleData);
protected:
	virtual void xfer(Xfer *xfer);
private:
	float m_damageScalar;
};
class Rva004BD78F : public BodyModule
{
public:
	Rva004BD78F(Thing *thing, const ModuleData *moduleData);
protected:
	virtual void xfer(Xfer *xfer);
private:
	bool m_unk18;
};
void Rva004BD78F::xfer(Xfer *xfer)
{
	xfer->Version1();
	BodyModule::xfer(xfer);
	*xfer == m_unk18;
}
