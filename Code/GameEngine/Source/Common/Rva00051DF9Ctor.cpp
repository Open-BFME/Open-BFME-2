// cl: /O1 /arch:SSE /G7 /GX /DNDEBUG /MD /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /Ireference/shims/moduledata
// ??0Rva005813E@@QAE@XZ, retail 0x00051DF9, 84 bytes.
// Default ctor of Rva005813E: empty OpaqueRefElement4 temp plus zero builds base
// Rva0051D93 then restores derived tables BC5324 and BC5320. Evidence: leaf lane,
// caller 0x00059933, callee 0x00051D22 rowed in OpaqueScalarDeletingDtorsB09,
// Release_Ref rowed, vtables BC5324 and BC5320 per Rva005813E comment in that TU.
#include "../../../Libraries/Source/WWVegas/WWLib/OpaqueRefCounted.h"

#include "../../Include/Common/OpaqueRefElement4.h"

struct EmitVtableTag;

class MyAudioPrefix88
{
public:
    MyAudioPrefix88(EmitVtableTag *);
    virtual ~MyAudioPrefix88();
private:
    char m_pad[0x88 - 4];
};

class Rva00051E4D
{
public:
    Rva00051E4D() { m_count = 0; }
    Rva00051E4D(EmitVtableTag *);
    virtual ~Rva00051E4D() {}
private:
    volatile int m_count;
};

class Rva0051D93 : public MyAudioPrefix88, public Rva00051E4D
{
public:
    Rva0051D93(EmitVtableTag *);
    Rva0051D93(const OpaqueRefElement4 &reference, int value30);
    virtual ~Rva0051D93();
};

class Rva005813E : public Rva0051D93
{
public:
    Rva005813E();
    Rva005813E(EmitVtableTag *);
    virtual ~Rva005813E();
};

Rva005813E::Rva005813E() : Rva0051D93(OpaqueRefElement4(), 0)
{
}

// ?<Rva00051E4D::Rva00051E4D> absent-from-retail
Rva00051E4D::Rva00051E4D(EmitVtableTag *) : m_count(0)
{
}
