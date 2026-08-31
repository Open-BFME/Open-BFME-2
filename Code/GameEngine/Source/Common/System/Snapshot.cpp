// cl: /O1

class Xfer;

// Snapshot carries no state of its own - both constructors do nothing but
// install the vtable at 0x00BBB554, and the copy constructor ignores its
// argument entirely.
class Snapshot
{
public:
    Snapshot();
    Snapshot(const Snapshot &that);

    virtual ~Snapshot();
    virtual void crc(Xfer *xfer) = 0;
    virtual void xfer(Xfer *xfer) = 0;
    virtual void loadPostProcess() = 0;
};

Snapshot::Snapshot()
{
}

Snapshot::Snapshot(const Snapshot &that)
{
}
