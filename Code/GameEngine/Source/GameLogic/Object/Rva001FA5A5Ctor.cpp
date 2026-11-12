// cl: /MD
// ??0Rva001FA5A5@@QAE@XZ @0x001FA5A5 22B and its ctor chain, same shape as
// Rva001FA584Ctor.cpp (zeroed ints then an embedded member ctor). Member ctor
// callees by REL32: 001FA5A5 -> rowed Rva001F9060 at +8; 001FB8A9 ->
// 001FA5A5 at +4; 001FBA45 -> 001FA5A5 at +8; 001FBBE4 -> 001FBA45 at +4;
// 001F9B52 -> rowed ObjectCreationList at +4. Original names unknown so
// address-derived Rva names are used.
#include "../../../Include/GameLogic/ObjectCreationListClass.h"

class Rva001F9060
{
public:
    Rva001F9060();
};

class Rva001FA5A5
{
public:
    int m_00;
    int m_04;
    Rva001F9060 m_08;
    Rva001FA5A5();
};

Rva001FA5A5::Rva001FA5A5() : m_00(0), m_04(0), m_08()
{
}

class Rva001FB8A9
{
public:
    int m_00;
    Rva001FA5A5 m_04;
    Rva001FB8A9();
};

Rva001FB8A9::Rva001FB8A9() : m_00(0), m_04()
{
}

class Rva001FBA45
{
public:
    int m_00;
    int m_04;
    Rva001FA5A5 m_08;
    Rva001FBA45();
};

Rva001FBA45::Rva001FBA45() : m_00(0), m_04(0), m_08()
{
}

class Rva001FBBE4
{
public:
    int m_00;
    Rva001FBA45 m_04;
    Rva001FBBE4();
};

Rva001FBBE4::Rva001FBBE4() : m_00(0), m_04()
{
}

class Rva001F9B52
{
public:
    int m_00;
    ObjectCreationList m_04;
    Rva001F9B52();
};

Rva001F9B52::Rva001F9B52() : m_00(0), m_04()
{
}

// ??0ParticleSystemTemplateTail@FXParticleSystem@@QAE@XZ @0x001FBF37 22B:
// the existing opaque pin (ParticleSystemTemplate ctor 0x001FC1E0 calls it on
// +0xA4); zeroes two words then constructs Rva001FBA45 at +8. Member identity
// stays unasserted as in the pin note.
namespace FXParticleSystem
{
class ParticleSystemTemplateTail
{
public:
    int m_00;
    int m_04;
    Rva001FBA45 m_08;
    ParticleSystemTemplateTail();
};

ParticleSystemTemplateTail::ParticleSystemTemplateTail() : m_00(0), m_04(0), m_08()
{
}
}

// ??0Rva001FBCDC@@QAE@XZ: ctor of ParticleSystem's +0x1AC member (dtor row 0x001FBCDC). Retail's
// ParticleSystem ctor calls it at 0x001FBF37, the identical-code fold of the template tail ctor above.
class Rva001FBCDC
{
public:
    int m_00;
    int m_04;
    Rva001FBA45 m_08;
    Rva001FBCDC();
};

// Select-any; the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva001FBCDC::Rva001FBCDC() : m_00(0), m_04(0), m_08()
{
}

// ?bfmeAnchorRva001FBCDCCtor absent-from-retail
void bfmeAnchorRva001FBCDCCtor(Rva001FBCDC *p)
{
    p->Rva001FBCDC::Rva001FBCDC();
}
