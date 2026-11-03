// cl: -DNDEBUG -MD -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Retail 0x003ABC21 destroys the secondary base at +0x20, then the primary.
// Both cleanup calls use their existing rowed owners.

class Rva003AEEB3
{
public:
    virtual ~Rva003AEEB3() throw();
private:
    unsigned char m_storage[0x1C];
};

#include "../../Include/GameClient/LifeEventModuleInfo.h"
namespace FXParticleSystem
{
}

class __declspec(novtable) Rva005E2D20 : public Rva003AEEB3,
    public FXParticleSystem::LifeEventModuleInfo
{
public:
    virtual ~Rva005E2D20();
};

Rva005E2D20::~Rva005E2D20()
{
}
