// Target facts (code addresses are RVAs; table addresses are VAs): Rva005248D0's constructor 0x002D2C34 stores its table 0x00C02A80 (0x002D2C8C) and
// calls six non-polymorphic holders at +0x04/+0x10/+0x1C/+0x34/+0x40/+0x4C (0x002D2C42..0x002D2C84); its destructor 0x005248D0 restores 0x00C02A80 (0x005248E1)
// and destroys them in reverse order (0x005248E7..0x0052492D), establishing its 0x58-byte span. AptMpGameSetup derives from it.
#ifndef BFME2_RVA005248D0_H
#define BFME2_RVA005248D0_H

#include "../../../Libraries/Source/Apt/AptCommandMapAdder.h"

class AptExternHandler;
class AptCustomRender;

// AddExternHandler 0x005245F3 registers through AptPlayer::AddExternHandler and appends the name to the string vector
// at +0; ~Rva005241B0 0x005241B0 removes those names through 0x00523F57 (AptPlayer::RemoveExternHandler 0x002244CA).
class AptExternHandlerAdder
{
public:
    void AddExternHandler(const AsciiString &name, int arg, AptRef<AptExternHandler> handler);
private:
    unsigned int field00[3];
};

// AddCustomRender 0x005246C0 registers through AptPlayer::AddCustomRender and appends the name to the string vector
// at +0; ~Rva00524265 0x00524265 removes those names through 0x00523FEC (AptPlayer::RemoveCustomRender 0x002246B1).
class AptCustomRenderAdder
{
public:
    void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);
private:
    unsigned int field00[3];
};

class Rva005241B0
{
public:
    ~Rva005241B0();
    AptExternHandlerAdder holder10;
};

class Rva00524415
{
public:
    ~Rva00524415();
private:
    unsigned int holder1c[6];
};

class Rva00524265
{
public:
    ~Rva00524265();
    AptCustomRenderAdder holder34;
};

class Rva005242D7
{
public:
    ~Rva005242D7();
private:
    unsigned int holder40[3];
};

class AptTimerAdder
{
public:
    ~AptTimerAdder();
private:
    unsigned int holder4c[3];
};

class Rva005248D0 : public AptCommandMapAdder, public Rva005241B0,
    public Rva00524415, public Rva00524265, public Rva005242D7, public AptTimerAdder
{
public:
    Rva005248D0();
    virtual ~Rva005248D0();
};

#endif
