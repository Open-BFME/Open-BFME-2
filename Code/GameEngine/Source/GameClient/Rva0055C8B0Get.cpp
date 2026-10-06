// cl: /O1 /EHsc /arch:SSE2
// ?rva0055C8B0@Rva0055C8B0@@QAEPAXXZ at 0x0055C8B0 size 12
// Evidence: neighbours ParticleModule005F2CA0Ctor and Rva0055C8BCCtor share flags; calls rowed ConcreteModuleClass DefaultModuleTag 6 getInstance then returns this.

namespace FXParticleSystem
{
template <int N>
class DefaultModuleTag
{
};

template <class TAG>
class ConcreteModuleClass
{
public:
    static const ConcreteModuleClass<TAG> &getInstance();
};
}

class Rva0055C8B0
{
public:
    void *rva0055C8B0();
};

void *Rva0055C8B0::rva0055C8B0()
{
    FXParticleSystem::ConcreteModuleClass<FXParticleSystem::DefaultModuleTag<6> >::getInstance();
    return this;
}
