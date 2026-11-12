#pragma once

// Both wind-info constructors install table RVA 0081B568, whose last slot
// transfers the float at +4. The copy constructor copies its bits unchanged.
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class Rva003AE07D : public Snapshot
{
public:
    Rva003AE07D();
    Rva003AE07D(const Rva003AE07D &other);
    virtual void LoadPostProcess() {}
    virtual const char *GetSnapshotName() const;
    virtual void DoXfer(Xfer &xfer);

private:
    union {
        int m_field04;
        float m_real04;
    };
};
