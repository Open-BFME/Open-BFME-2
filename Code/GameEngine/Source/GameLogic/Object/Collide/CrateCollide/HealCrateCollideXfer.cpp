// cl: /DNDEBUG /MD
//
// ?xfer@HealCrateCollide@@MAEXPAVXfer@@@Z @0x004BD2F9 27B: slot 3 (offset 0x0C)
// of vtable 0x0085A868 (class of ??0HealCrateCollide at 0x004BC80F) and five
// ICF-twin vtables 0x0085A8A0/0x0085A8D8/0x0085A914/0x0085A954/0x0085A9C0
// (Money/Shroud/Unit/Veterancy/Salvage CrateCollide). Version1 via rowed
// 0x000053EE then base CrateCollide xfer via rowed 0x004BC617; no extra
// members. Donor is ZH CrateCollide::xfer pattern; BFME2 derived empties
// fold to this Version1-plus-base shape.
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
    BehaviorModule(Thing *thing, const ModuleData *moduleData);
    virtual void behaviorModuleAnchor();
private:
    unsigned char m_data[8];
};
class InlineCollideModuleInterface
{
public:
    virtual void collideModuleInterfaceAnchor();
};
class ModuleInterface
{
public:
    virtual void moduleInterfaceAnchor();
};
class CollideModule : public BehaviorModule,
    public InlineCollideModuleInterface,
    public ModuleInterface
{
public:
    CollideModule(Thing *thing, const ModuleData *moduleData);
    void xfer(Xfer *xfer);
};
class CrateCollide : public CollideModule
{
public:
    CrateCollide(Thing *thing, const ModuleData *moduleData);
protected:
    virtual void xfer(Xfer *xfer);
private:
    bool m_everExecuted;
};
class HealCrateCollide : public CrateCollide
{
public:
    HealCrateCollide(Thing *thing, const ModuleData *moduleData);
protected:
    virtual void xfer(Xfer *xfer);
};
void HealCrateCollide::xfer(Xfer *xfer)
{
    xfer->Version1();
    CrateCollide::xfer(xfer);
}
