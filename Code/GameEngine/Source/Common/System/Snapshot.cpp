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
    virtual void loadPostProcess() = 0;
    // Slot 3: Xfer's transfer operator for a Snapshot calls [vtable+0x0C] with
    // the Xfer as its only argument, which is what puts this one last.
    virtual void xfer(Xfer *xfer) = 0;
};

Snapshot::Snapshot()
{
}

Snapshot::Snapshot(const Snapshot &that)
{
}
