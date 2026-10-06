// cl: /MD
// ?rva005C45D2@Rva005C45D2@@QAEXPAVXfer@@@Z retail 0x005C45D2 44B
// Version(1 1) via Xfer slot 0x28 then rowed Rva004CE6E4 0x004CE6E4 with this.
// Evidence: chain from 0x004CE6E4 landing; no callers; class unproven so honest Rva name.
class Snapshot;
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
class Rva004CE6E4 {
public:
    void rva004CE6E4(Xfer *xfer);
};
class Rva005C45D2 {
public:
    void rva005C45D2(Xfer *xfer);
};
void Rva005C45D2::rva005C45D2(Xfer *xfer)
{
    Xfer::Version version;
    version.m_current = 1;
    version.m_minimum = 1;
    *xfer == version;
    ((Rva004CE6E4 *)this)->rva004CE6E4(xfer);
}
