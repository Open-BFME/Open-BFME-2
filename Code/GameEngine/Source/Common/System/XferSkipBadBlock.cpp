// cl: /O1
// BFME1 Xfer::SkipBadBlock is an intentional no-op; BFME2 retains the same
// virtual hook and emits only the thiscall epilogue.

class Snapshot;

class Xfer
{
public:
    virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
};

void Xfer::SkipBadBlock(Snapshot &, unsigned int)
{
}
