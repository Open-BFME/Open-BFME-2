// cl: /DNDEBUG /MD
// ?xfer@NotifyTargetsOfImminentProbableCrushingUpdate@@MAEXPAVXfer@@@Z retail 0x004CEE39 53B
// Slot 3 of 0x007F186C (NotifyTargets) and 0x007F17F8 (Horde twin shared body).
// Evidence: Version11 via Xfer slot 0x28 then rowed UpdateModule xfer 0x0044DF9F then rowed Rva004CE6E4 member at +0x20.
class Snapshot;
class Thing;
class ModuleData;
class Xfer {
public:
    class Version {
    public:
        unsigned char m_current;
        unsigned char m_minimum;
    };
    virtual ~Xfer();
    virtual bool IsLoading() const;
    virtual bool IsStoring() const;
    virtual bool IsCRC() const;
    virtual bool IsLightCRC() const;
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void SkipBadBlock(Snapshot &s, unsigned int size);
    virtual Xfer &XferRawBytes(void *data, unsigned int size);
    virtual Xfer &operator==(Version &v);
};
class Thing;
class ModuleData;
class UpdateModule {
public:
    virtual ~UpdateModule();
    void xfer(Xfer *xfer);
};
class Rva004CE6E4 {
public:
    void rva004CE6E4(Xfer *xfer);
};
class NotifyTargetsOfImminentProbableCrushingUpdate : public UpdateModule {
public:
protected:
    virtual void xfer(Xfer *xfer);
};
void NotifyTargetsOfImminentProbableCrushingUpdate::xfer(Xfer *xfer)
{
    Xfer::Version version;
    version.m_current = 1;
    version.m_minimum = 1;
    *xfer == version;
    UpdateModule::xfer(xfer);
    ((Rva004CE6E4 *)((char *)this + 0x20))->rva004CE6E4(xfer);
}
