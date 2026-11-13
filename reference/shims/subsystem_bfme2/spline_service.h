// Retail subsystem contracts from tables 0x00BD77A0 and 0x00BE7150.
// Consumers supply the registry layout separately.
#ifndef BFME2_SPLINE_SERVICE_H
#define BFME2_SPLINE_SERVICE_H

// SubsystemInterface is the canonical class (reverse/canonical_classes.csv). This shim's users need its
// virtual slots, which the canonical header declares under BFME_SUBSYSTEM_SLOTS.
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Code/Libraries/Source/subsystem/SubsystemInterface.h"

class Rva0022B3F6Subsystem : public SubsystemInterface
{
public:
#ifdef BFME2_SPLINE_INLINE_CTOR
    __declspec(dllimport) __forceinline Rva0022B3F6Subsystem() {}
#else
    Rva0022B3F6Subsystem();
#endif
    virtual ~Rva0022B3F6Subsystem();
    virtual void init() {}
    virtual void reset() {}
    virtual void update() {}
};

#endif
